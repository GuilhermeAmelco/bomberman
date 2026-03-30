#include <iostream>
#include <windows.h>
#include <conio.h>

using namespace std;

/*
MAPA (valores):
0 - parede dura
1 - parede frágil
2 - bomba
3 - explosão
4 - inimigo
5 - personagem
*/

const char BLOCO = 219;
const char BLOCO_CLARO = 177;
const int LARGURA = 3;
const int ALTURA = 3;

/* =========================
   INPUT
========================= */

int escuta_tecla()
{
  if (_kbhit())
    return getch();

  return -1;
}

/* =========================
   REGRAS
========================= */

bool pode_mover(int mapa[LARGURA][ALTURA], int x, int y)
{
  if (x < 0 || x >= LARGURA)
    return false;

  if (y < 0 || y >= ALTURA)
    return false;

  if (mapa[x][y] == 0 || mapa[x][y] == 1 || mapa[x][y] == 2)
    return false;

  return true;
}

/* =========================
   LÓGICA DO JOGADOR
========================= */

void mover_jogador(int player_position[2], int tecla, int mapa[LARGURA][ALTURA])
{
  int x = player_position[0];
  int y = player_position[1];

  switch (tecla)
  {
  case 72:
    y--;
    break; // cima
  case 80:
    y++;
    break; // baixo
  case 75:
    x--;
    break; // esquerda
  case 77:
    x++;
    break; // direita
  }

  if (!pode_mover(mapa, x, y))
    return;

  player_position[0] = x;
  player_position[1] = y;
}

/* =========================
   RENDER
========================= */

void desenhar(int mapa[LARGURA][ALTURA], int player_position[2], HANDLE out)
{
  for (int i = 0; i < ALTURA; i++)
  {
    for (int j = 0; j < LARGURA; j++)
    {
      bool isPlayer = (player_position[0] == j && player_position[1] == i);

      // desenha jogador por cima do mapa
      if (isPlayer)
      {
        SetConsoleTextAttribute(out, 10);
        cout << BLOCO << BLOCO;
        continue;
      }

      int valor = mapa[i][j];

      switch (valor)
      {
      case 0: // bloco
        SetConsoleTextAttribute(out, 3);
        cout << BLOCO << BLOCO;
        break;
      case 1: // bloco-fragil
        SetConsoleTextAttribute(out, 3);
        cout << BLOCO_CLARO << BLOCO_CLARO;
        break;
      case 9: // vazio
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
  // configuração do console
  HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);

  CONSOLE_CURSOR_INFO cursorInfo;
  GetConsoleCursorInfo(out, &cursorInfo);
  cursorInfo.bVisible = false;
  SetConsoleCursorInfo(out, &cursorInfo);

  COORD coord;
  coord.X = 0;
  coord.Y = 0;

  // mapa
  int mapa[LARGURA][ALTURA] = {
      {9, 9, 1},
      {9, 0, 9},
      {9, 9, 9}};

  // jogador
  int player_position[2] = {0, 0};

  int tecla;

  while (true)
  {
    // limpa tela (reposiciona cursor)
    SetConsoleCursorPosition(out, coord);

    desenhar(mapa, player_position, out);

    tecla = escuta_tecla();
    mover_jogador(player_position, tecla, mapa);
  }

  return 0;
}