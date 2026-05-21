#include "../config/config.h"

#ifndef BOMBA_H
#define BOMBA_H

extern const int LARGURA;
extern const int ALTURA;

struct Bomba
{
  int range = 1, tempo = 3000, tempo_explosa = 500;
  ESTADO_BOMBA estado = ESTADO_BOMBA::INATIVA;
};

void explodir_bomba(int mapa[ALTURA][LARGURA], int bomba_posicao[2], ESTADO_BOMBA &bomba_estado, int &bomba_tempo);
void limpar_explosao(int mapa[ALTURA][LARGURA], int bomba_posicao[2], ESTADO_BOMBA &bomba_estado, int &bomba_tempo);
void atualiza_bomba(int bomba_posicao[2], ESTADO_BOMBA &bomba_estado, int &bomba_tempo, int mapa[ALTURA][LARGURA]);

#endif