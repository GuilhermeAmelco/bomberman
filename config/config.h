#ifndef CONFIG_H
#define CONFIG_H

#include <string>

using namespace std;

const int LARGURA = 15;
const int ALTURA = 11;

const string ESTADO_ATIVA = "ATIVA";
const string ESTADO_DESATIVADA = "INATIVA";
const string ESTADO_EXPLODINDO = "EXPLODINDO";

struct Player
{
  int x = 1, y = 1;
  bool vivo = true;
}

#endif