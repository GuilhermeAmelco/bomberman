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

// const string ESTADO_ATIVA = "ATIVA";
// const string ESTADO_DESATIVADA = "INATIVA";
// const string ESTADO_EXPLODINDO = "EXPLODINDO";

enum class ESTADO_BOMBA
{
  ATIVA,
  INATIVA,
  EXPLODINDO
}

struct Jogador
{
  int x = 1, y = 1;
  bool vivo = true;
};

struct Inimigo
{
  int x, int y;
};

struct Bomba
{
  int range = 1, tempo = 3000, tempo_explosa = 500;
  ESTADO_BOMBA estado = ESTADO_BOMBA::INATIVA;
};

#endif