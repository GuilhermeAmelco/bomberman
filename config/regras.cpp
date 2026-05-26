#include "regras.h"
#include "./config.h"

bool pode_mover(
    int mapa[ALTURA][LARGURA],
    Bomba bombas[2],
    int x,
    int y)
{
  if (x < 0 || x >= LARGURA)
    return false;

  if (y < 0 || y >= ALTURA)
    return false;

  if (mapa[y][x] == 0 || mapa[y][x] == 1)
    return false;

  for (int i = 0; i < 2; i++)
  {
    if (bombas[i].posicao[0] == y &&
        bombas[i].posicao[1] == x &&
        bombas[i].estado == ESTADO_BOMBA::ATIVA)
    {
      return false;
    }
  }

  return true;
}

bool bomba_ativa(ESTADO_BOMBA bomba_estado)
{
  return bomba_estado != ESTADO_BOMBA::INATIVA;
}