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
*/

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
    int jogador_posicao[2],
    int inimigo_posicao[2], bool inimigo_vivo,
    int bomba_posicao[2], ESTADO_BOMBA bomba_estado,
    HANDLE out)
{
  for (int i = 0; i < ALTURA; i++)
  {
    for (int j = 0; j < LARGURA; j++)
    {
      bool isBomb = (bomba_posicao[0] == i && bomba_posicao[1] == j && bomba_estado == ESTADO_BOMBA::ATIVA);
      bool isPlayer = (jogador_posicao[0] == i && jogador_posicao[1] == j);
      bool isEnemy = (inimigo_vivo && inimigo_posicao[0] == i && inimigo_posicao[1] == j);

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

      int valor = mapa[i][j];

      switch (valor)
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

  int jogador_posicao[2] = {1, 1};
  bool jogador_vivo = true;

  int inimigo_posicao[2] = {1, 13};
  bool inimigo_vivo = true;
  int tempo_inimigo = GetTickCount();

  int bomba_posicao[2] = {-1, -1};
  ESTADO_BOMBA bomba_estado = ESTADO_BOMBA::INATIVA;
  int bomba_tempo = 0;

  const int FPS = 60;
  int tempo_por_segundo = 1000 / FPS;

  while (jogador_vivo)
  {
    SetConsoleCursorPosition(out, coord);

    desenhar(
        mapa,
        jogador_posicao,
        inimigo_posicao, inimigo_vivo,
        bomba_posicao, bomba_estado,
        out);

    int tecla = escuta_tecla();

    atualiza_jogador(jogador_posicao, bomba_posicao, bomba_estado, bomba_tempo, mapa, tecla);
    atualiza_bomba(bomba_posicao, bomba_estado, bomba_tempo, mapa);
    atualiza_inimigo(inimigo_posicao, inimigo_vivo, mapa, bomba_posicao, bomba_estado, tempo_inimigo);

    // logica da morte da explosao
    if (mapa[jogador_posicao[0]][jogador_posicao[1]] == 3)
      jogador_vivo = false;

    if (inimigo_vivo && mapa[inimigo_posicao[0]][inimigo_posicao[1]] == 3)
      inimigo_vivo = false;

    if (inimigo_vivo && inimigo_posicao[0] == jogador_posicao[0] && inimigo_posicao[1] == jogador_posicao[1])
      jogador_vivo = false;

    if (!inimigo_vivo)
      break;

    // 30 fps / 60 fps
    // TODO ajustar o frame por segundo
    Sleep(tempo_por_segundo);
  }

  SetConsoleCursorPosition(out, coord);
  desenhar(
      mapa,
      jogador_posicao,
      inimigo_posicao, inimigo_vivo,
      bomba_posicao, bomba_estado,
      out);

  SetConsoleTextAttribute(out, 15);
  if (jogador_vivo && !inimigo_vivo)
    cout << "\nVOCE VENCEU!\n";
  else
    cout << "\nVOCE PERDEU!\n";

  while (_kbhit())
    _getch();

  cout << "Pressione qualquer tecla para sair...";
  _getch();

  return 0;
}
