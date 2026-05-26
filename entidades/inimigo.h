#ifndef INIMIGO_H
#define INIMIGO_H

#include "../config/config.h"
#include "./bomba.h"
#include "./player.h"
#include <windows.h>

extern const int LARGURA;
extern const int ALTURA;

struct Inimigo
{
  int posicao[2] = {1, 13};
  bool vivo = false;
  int tempo = GetTickCount();
  int tempo_dano = 0;
  bool is_boss = false;
  int vida = 1;
};

void atualiza_inimigo(Inimigo &inimigo, Bomba bombas[2], int mapa[ALTURA][LARGURA], Jogador jogador);

#endif