#ifndef CONFIG_H
#define CONFIG_H

#include <string>

using namespace std;

const unsigned char BLOCO = 219;
const unsigned char BLOCO_CLARO = 176;
const int LARGURA = 15;
const int ALTURA = 11;
const int TEMPO_BOMBA = 3000;
const int TEMPO_EXPLOSAO = 500;
const int TEMPO_INIMIGO = 500;
const int MAX_INIMIGOS = 7;

enum class ESTADO_BOMBA
{
  ATIVA,
  INATIVA,
  EXPLODINDO
};

extern bool modo_multiplayer;

#endif