#include <iostream>
#include <windows.h>
#include "../config/regras.h"
#include "./inimigo.h"
#include "./bomba.h"

using namespace std;

void atualiza_inimigo(Inimigo &inimigo, Bomba bomba, int mapa[ALTURA][LARGURA])
{
  if (!inimigo.vivo)
    return;

  if (mapa[inimigo.posicao[0]][inimigo.posicao[1]] == 3)
  {
    inimigo.vivo = false;
    return;
  }

  if (GetTickCount() - inimigo.tempo < TEMPO_INIMIGO)
    return;

  inimigo.tempo = GetTickCount();

  int x = inimigo.posicao[1];
  int y = inimigo.posicao[0];
  int dir = rand() % 4;
  int passos = 1 + rand() % 3;

  for (int i = 0; i < passos; i++)
  {
    int novo_x = x;
    int novo_y = y;

    if (dir == 0)
      novo_y--;
    if (dir == 1)
      novo_y++;
    if (dir == 2)
      novo_x--;
    if (dir == 3)
      novo_x++;

    if (!pode_mover(mapa, bomba.posicao, bomba.estado, novo_x, novo_y))
      break;

    x = novo_x;
    y = novo_y;
  }

  inimigo.posicao[1] = x;
  inimigo.posicao[0] = y;
}
