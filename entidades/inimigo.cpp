#include <iostream>
#include <windows.h>
#include <cmath>
#include "../config/regras.h"
#include "./inimigo.h"
#include "./bomba.h"

using namespace std;

void atualiza_inimigo(Inimigo &inimigo, Bomba bombas[2], int mapa[ALTURA][LARGURA], Jogador jogador)
{
  if (!inimigo.vivo)
    return;

  if (mapa[inimigo.posicao[0]][inimigo.posicao[1]] == 3)
  {
    if (GetTickCount() - inimigo.tempo_dano > 1000)
    {
      inimigo.vida--;
      inimigo.tempo_dano = GetTickCount();
      if (inimigo.vida <= 0)
      {
        inimigo.vivo = false;
        return;
      }
    }
  }

  if (GetTickCount() - inimigo.tempo < TEMPO_INIMIGO)
    return;

  inimigo.tempo = GetTickCount();

  int x = inimigo.posicao[1];
  int y = inimigo.posicao[0];

  if (inimigo.is_boss)
  {
    int dist_x = jogador.posicao[1] - x;
    int dist_y = jogador.posicao[0] - y;

    int novo_x = x;
    int novo_y = y;

    if (abs(dist_x) > abs(dist_y))
    {
      novo_x += (dist_x > 0) ? 1 : -1;
      if (!pode_mover(mapa, bombas, novo_x, y))
      {
        novo_x = x;
        novo_y += (dist_y > 0) ? 1 : -1;
      }
    }
    else
    {
      novo_y += (dist_y > 0) ? 1 : -1;
      if (!pode_mover(mapa, bombas, x, novo_y))
      {
        novo_y = y;
        novo_x += (dist_x > 0) ? 1 : -1;
      }
    }

    if (pode_mover(mapa, bombas, novo_x, novo_y))
    {
      inimigo.posicao[1] = novo_x;
      inimigo.posicao[0] = novo_y;
    }
  }
  else
  {
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

      if (!pode_mover(mapa, bombas, novo_x, novo_y))
        break;

      x = novo_x;
      y = novo_y;
    }
    inimigo.posicao[1] = x;
    inimigo.posicao[0] = y;
  }
}