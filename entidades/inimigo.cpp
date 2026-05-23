#include <iostream>
#include <windows.h>
#include "../config/regras.h"

using namespace std;

void atualiza_inimigo(int inimigo_posicao[2], bool &inimigo_vivo, int mapa[ALTURA][LARGURA], int bomba_posicao[2], ESTADO_BOMBA bomba_estado, int &tempo_inimigo)
{
  if (!inimigo_vivo)
    return;

  if (mapa[inimigo_posicao[0]][inimigo_posicao[1]] == 3)
  {
    inimigo_vivo = false;
    return;
  }

  if (GetTickCount() - tempo_inimigo < TEMPO_INIMIGO)
    return;

  tempo_inimigo = GetTickCount();

  int x = inimigo_posicao[1];
  int y = inimigo_posicao[0];
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

    if (!pode_mover(mapa, bomba_posicao, bomba_estado, novo_x, novo_y))
      break;

    x = novo_x;
    y = novo_y;
  }

  inimigo_posicao[1] = x;
  inimigo_posicao[0] = y;
}
