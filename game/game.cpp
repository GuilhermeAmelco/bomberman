#include "game.h"

#include <windows.h>
#include <ctime>

#include "estados/estados.h"

using namespace std;

void iniciar_jogo()
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

  Jogador jogador;
  Inimigo inimigo;
  Bomba bomba;

  ESTADO_JOGO estado = MENU;

  while (estado != SAIR)
  {
    SetConsoleCursorPosition(out, coord);

    switch (estado)
    {
    case MENU:
    {
      estado = estado_menu();
      break;
    }

    case JOGANDO:
    {
      estado = estado_jogando(
          mapa,
          jogador,
          inimigo,
          bomba,
          out);

      break;
    }

    case VITORIA:
    {
      estado = estado_vitoria(
          mapa,
          jogador,
          inimigo,
          bomba,
          out);

      break;
    }

    case DERROTA:
    {
      estado = estado_derrota(
          mapa,
          jogador,
          inimigo,
          bomba,
          out);

      break;
    }
    }
  }
}