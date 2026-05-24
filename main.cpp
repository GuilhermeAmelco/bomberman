#include <iostream>
#include <windows.h>
#include <conio.h>
#include <string.h>
#include <ctime>

#include "entidades/player.h"
#include "entidades/bomba.h"
#include "entidades/inimigo.h"

using namespace std;

/*
MAPA (valores):
0 - parede dura
1 - parede fragil
2 - bomba
3 - explosao
4 - inimigo
5 - personagem
9 - vazio
*/

enum ESTADO_JOGO
{
  MENU,
  JOGANDO,
  VITORIA,
  DERROTA,
  SAIR
};

/* =========================
   INPUT
========================= */

int escuta_tecla()
{
  if (_kbhit())
    return _getch();

  return -1;
}

/* =========================
   RENDER
========================= */

void desenhar(
    int mapa[ALTURA][LARGURA],
    Jogador jogador,
    Inimigo inimigo,
    Bomba bomba,
    HANDLE out)
{
  for (int i = 0; i < ALTURA; i++)
  {
    for (int j = 0; j < LARGURA; j++)
    {
      bool isBomb =
          bomba.estado == ESTADO_BOMBA::ATIVA &&
          bomba.posicao[0] == i &&
          bomba.posicao[1] == j;

      bool isPlayer =
          jogador.posicao[0] == i &&
          jogador.posicao[1] == j;

      bool isEnemy =
          inimigo.vivo &&
          inimigo.posicao[0] == i &&
          inimigo.posicao[1] == j;

      if (isBomb)
      {
        SetConsoleTextAttribute(out, 5);
        cout << BLOCO << BLOCO;
        continue;
      }

      if (isEnemy)
      {
        SetConsoleTextAttribute(out, 12);
        cout << BLOCO << BLOCO;
        continue;
      }

      if (isPlayer)
      {
        SetConsoleTextAttribute(out, 10);
        cout << BLOCO << BLOCO;
        continue;
      }

      switch (mapa[i][j])
      {
      case 0:
        SetConsoleTextAttribute(out, 3);
        cout << BLOCO << BLOCO;
        break;

      case 1:
        SetConsoleTextAttribute(out, 6);
        cout << BLOCO_CLARO << BLOCO_CLARO;
        break;

      case 3:
        SetConsoleTextAttribute(out, 12);
        cout << BLOCO << BLOCO;
        break;

      case 9:
        SetConsoleTextAttribute(out, 0);
        cout << BLOCO << BLOCO;
        break;
      }
    }

    cout << endl;
  }
}

/* =========================
   MAIN
========================= */

int main()
{
  srand(time(NULL));

  HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);

  CONSOLE_CURSOR_INFO cursorInfo;
  GetConsoleCursorInfo(out, &cursorInfo);

  cursorInfo.bVisible = false;
  SetConsoleCursorInfo(out, &cursorInfo);

  COORD coord;
  coord.X = 0;
  coord.Y = 0;

  int mapa[ALTURA][LARGURA] = {
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
      {0, 9, 9, 1, 9, 1, 9, 9, 9, 1, 9, 1, 9, 9, 0},
      {0, 9, 0, 9, 0, 9, 0, 9, 0, 9, 0, 9, 0, 9, 0},
      {0, 1, 9, 9, 9, 1, 9, 9, 9, 9, 9, 1, 9, 9, 0},
      {0, 9, 0, 9, 0, 9, 0, 1, 0, 9, 0, 9, 0, 9, 0},
      {0, 9, 9, 1, 9, 9, 9, 9, 9, 9, 9, 1, 9, 9, 0},
      {0, 9, 0, 9, 0, 9, 0, 9, 0, 1, 0, 9, 0, 9, 0},
      {0, 1, 9, 9, 9, 9, 9, 1, 9, 9, 9, 9, 9, 1, 0},
      {0, 9, 0, 9, 0, 1, 0, 9, 0, 9, 0, 9, 0, 9, 0},
      {0, 9, 9, 1, 9, 9, 9, 9, 9, 1, 9, 9, 9, 9, 0},
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}};

  Jogador Jogador;
  Inimigo Inimigo;
  Bomba Bomba;

  ESTADO_JOGO estado = MENU;

  while (estado != SAIR)
  {
    SetConsoleCursorPosition(out, coord);

    switch (estado)
    {
    case MENU:
    {
      SetConsoleTextAttribute(out, 15);

      cout << "===== BOMBERMAN =====\n";
      cout << "1 - Jogar\n";
      cout << "2 - Sair\n";

      int tecla = _getch();

      if (tecla == '1')
      {
        estado = JOGANDO;
      }
      else if (tecla == '2')
      {
        estado = SAIR;
      }

      break;
    }

    case JOGANDO:
    {
      desenhar(
          mapa,
          Jogador,
          Inimigo,
          Bomba,
          out);

      int tecla = escuta_tecla();

      atualiza_jogador(Jogador, Bomba, mapa, tecla);
      atualiza_bomba(Bomba, mapa);
      atualiza_inimigo(Inimigo, Bomba, mapa);

      // jogador morreu pela explosao
      if (mapa[Jogador.posicao[0]][Jogador.posicao[1]] == 3)
      {
        Jogador.vivo = false;
      }

      // inimigo morreu pela explosao
      if (Inimigo.vivo &&
          mapa[Inimigo.posicao[0]][Inimigo.posicao[1]] == 3)
      {
        Inimigo.vivo = false;
      }

      // inimigo encostou no jogador
      if (Inimigo.vivo &&
          Inimigo.posicao[0] == Jogador.posicao[0] &&
          Inimigo.posicao[1] == Jogador.posicao[1])
      {
        Jogador.vivo = false;
      }

      // troca de estados
      if (!Jogador.vivo)
      {
        estado = DERROTA;
      }

      if (!Inimigo.vivo)
      {
        estado = VITORIA;
      }

      break;
    }

    case VITORIA:
    {
      desenhar(
          mapa,
          Jogador,
          Inimigo,
          Bomba,
          out);

      SetConsoleTextAttribute(out, 10);

      cout << "\nVOCE VENCEU!\n";
      cout << "Pressione qualquer tecla para sair...";

      _getch();

      estado = SAIR;

      break;
    }

    case DERROTA:
    {
      desenhar(
          mapa,
          Jogador,
          Inimigo,
          Bomba,
          out);

      SetConsoleTextAttribute(out, 12);

      cout << "\nVOCE PERDEU!\n";
      cout << "Pressione qualquer tecla para sair...";

      _getch();

      estado = SAIR;

      break;
    }
    }
  }

  return 0;
}