#ifndef REGRAS_H
#define REGRAS_H

#include "./config.h"

using namespace std;

extern const int LARGURA;
extern const int ALTURA;

bool pode_mover(
    int mapa[ALTURA][LARGURA],
    int bomba_posicao[2],
    ESTADO_BOMBA bomba_estado,
    int x,
    int y);

bool bomba_ativa(ESTADO_BOMBA bomba_estado);

#endif