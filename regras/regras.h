#ifndef REGRAS_H
#define REGRAS_H

#include <string>

using namespace std;

extern const int LARGURA;
extern const int ALTURA;

extern const string ESTADO_ATIVA;

bool pode_mover(
    int mapa[ALTURA][LARGURA],
    int bomba_posicao[2],
    string bomba_estado,
    int x,
    int y);

bool bomba_ativa(string bomba_estado);

#endif