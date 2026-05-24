#include "estados.h"

#include "../../render/render.h"

#include <conio.h>

int escuta_tecla()
{
  if (_kbhit())
    return _getch();

  return -1;
}

ESTADO_JOGO estado_jogando(
    int mapa[ALTURA][LARGURA],
    Jogador &jogador,
    Inimigo &inimigo,
    Bomba &bomba,
    HANDLE out)
{
  desenhar(
      mapa,
      jogador,
      inimigo,
      bomba,
      out);

  int tecla = escuta_tecla();

  if (tecla == 27)
  {
    return menu_loop(MENU_PAUSE);
  }

  atualiza_jogador(jogador, bomba, mapa, tecla);

  atualiza_bomba(bomba, mapa);

  atualiza_inimigo(inimigo, bomba, mapa);

  // jogador morreu pela explosao
  if (mapa[jogador.posicao[0]][jogador.posicao[1]] == 3)
  {
    jogador.vivo = false;
  }

  // inimigo morreu pela explosao
  if (inimigo.vivo &&
      mapa[inimigo.posicao[0]][inimigo.posicao[1]] == 3)
  {
    inimigo.vivo = false;
  }

  // inimigo encostou no jogador
  if (inimigo.vivo &&
      inimigo.posicao[0] == jogador.posicao[0] &&
      inimigo.posicao[1] == jogador.posicao[1])
  {
    jogador.vivo = false;
  }

  if (!jogador.vivo)
    return DERROTA;

  if (!inimigo.vivo)
    return VITORIA;

  return JOGANDO;
}