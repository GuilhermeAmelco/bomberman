#include <iostream>
#include <windows.h>
#include "../config/regras.h"

using namespace std;

void explodir_bomba(int mapa[ALTURA][LARGURA], int bomba_posicao[2], ESTADO_BOMBA &bomba_estado, int &bomba_tempo)
{
  int tempo_passado = GetTickCount() - bomba_tempo;

  if (tempo_passado < TEMPO_BOMBA)
    return;

  int dl[5] = {0, 0, 0, 1, -1};
  int dc[5] = {0, 1, -1, 0, 0};

  for (int i = 0; i < 5; i++)
  {
    int l = bomba_posicao[0] + dl[i];
    int c = bomba_posicao[1] + dc[i];

    if (l < 0 || l >= ALTURA || c < 0 || c >= LARGURA)
      continue;

    if (mapa[l][c] == 0)
      continue;

    mapa[l][c] = 3;
  }

  bomba_estado = ESTADO_BOMBA::EXPLODINDO;
  bomba_tempo = GetTickCount();
}

void limpar_explosao(int mapa[ALTURA][LARGURA], int bomba_posicao[2], ESTADO_BOMBA &bomba_estado, int &bomba_tempo)
{
  int tempo_passado = GetTickCount() - bomba_tempo;

  if (tempo_passado < TEMPO_EXPLOSAO)
    return;

  int dl[5] = {0, 0, 0, 1, -1};
  int dc[5] = {0, 1, -1, 0, 0};

  for (int i = 0; i < 5; i++)
  {
    int l = bomba_posicao[0] + dl[i];
    int c = bomba_posicao[1] + dc[i];

    if (l < 0 || l >= ALTURA || c < 0 || c >= LARGURA)
      continue;

    if (mapa[l][c] == 3)
      mapa[l][c] = 9;
  }

  bomba_estado = ESTADO_BOMBA::INATIVA;
  bomba_tempo = 0;
  bomba_posicao[0] = -1;
  bomba_posicao[1] = -1;
}

void atualiza_bomba(int bomba_posicao[2], ESTADO_BOMBA &bomba_estado, int &bomba_tempo, int mapa[ALTURA][LARGURA])
{
  if (bomba_estado == ESTADO_BOMBA::ATIVA)
    explodir_bomba(mapa, bomba_posicao, bomba_estado, bomba_tempo);

  if (bomba_estado == ESTADO_BOMBA::EXPLODINDO)
    limpar_explosao(mapa, bomba_posicao, bomba_estado, bomba_tempo);
}