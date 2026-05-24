#include "estados.h"

#include "../../render/render.h"

#include <iostream>
#include <conio.h>

using namespace std;

ESTADO_JOGO estado_derrota(
    int mapa[ALTURA][LARGURA],
    Jogador jogador,
    Inimigo inimigo,
    Bomba bomba,
    HANDLE out)
{
  desenhar(
      mapa,
      jogador,
      inimigo,
      bomba,
      out);

  SetConsoleTextAttribute(out, 12);

  cout << "\nVOCE PERDEU!\n";
  cout << "Pressione qualquer tecla para sair...";

  _getch();

  return SAIR;
}