#ifndef REGRAS_H
#define REGRAS_H

#include "./config.h"
#include "../entidades/bomba.h"

using namespace std;

extern const int LARGURA;
extern const int ALTURA;

bool pode_mover(
    int mapa[ALTURA][LARGURA],
    Bomba bombas[2],
    int x,
    int y);

bool bomba_ativa(ESTADO_BOMBA bomba_estado);

#endif