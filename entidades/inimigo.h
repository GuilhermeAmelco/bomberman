#include "../config/config.h"

#ifndef INIMIGO_H
#define INIMIGO_H

extern const int LARGURA;
extern const int ALTURA;

struct Inimigo
{
  int x, y;
};

void atualiza_inimigo(int inimigo_posicao[2], bool &inimigo_vivo, int mapa[ALTURA][LARGURA], int bomba_posicao[2], ESTADO_BOMBA bomba_estado, int &tempo_inimigo);

#endif