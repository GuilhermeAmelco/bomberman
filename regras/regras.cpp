#include "regras.h"

bool pode_mover(
    int mapa[ALTURA][LARGURA],
    int bomba_posicao[2],
    string bomba_estado,
    int x,
    int y)
{
  if (x < 0 || x >= LARGURA)
    return false;

  if (y < 0 || y >= ALTURA)
    return false;

  if (mapa[y][x] == 0 || mapa[y][x] == 1)
    return false;

  if (
      bomba_posicao[0] == y &&
      bomba_posicao[1] == x &&
      bomba_estado == ESTADO_ATIVA)
  {
    return false;
  }

  return true;
}

bool bomba_ativa(string bomba_estado)
{
  return bomba_estado == ESTADO_ATIVA;
}