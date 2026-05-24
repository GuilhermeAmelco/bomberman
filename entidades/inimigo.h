#ifndef INIMIGO_H
#define INIMIGO_H

#include "../config/config.h"
#include "./bomba.h"
#include <windows.h>

extern const int LARGURA;
extern const int ALTURA;

struct Inimigo
{
  int posicao[2] = {1, 13};
  bool vivo = true;
  int tempo = GetTickCount();
};

void atualiza_inimigo(Inimigo &inimigo, Bomba bomba, int mapa[ALTURA][LARGURA]);

#endif