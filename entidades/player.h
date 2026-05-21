#include "../config/config.h"

#ifndef PLAYER_H
#define PLAYER_H

extern const int LARGURA;
extern const int ALTURA;

struct Jogador
{
  int x = 1, y = 1;
  bool vivo = true;
};

void mover_jogador(int jogador_posicao[2], int bomba_posicao[2], ESTADO_BOMBA bomba_estado, int mapa[ALTURA][LARGURA], int tecla);

void coloca_bomba(int jogador_posicao[2], int bomba_posicao[2], ESTADO_BOMBA &bomba_estado, int &bomba_tempo, int tecla);

void atualiza_jogador(int jogador_posicao[2], int bomba_posicao[2], ESTADO_BOMBA &bomba_estado, int &bomba_tempo, int mapa[ALTURA][LARGURA], int tecla);

#endif