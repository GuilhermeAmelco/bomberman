#include <iostream>
#include <windows.h>
#include "../config/regras.h"
#include "./player.h"
#include "./bomba.h"

using namespace std;

void mover_jogador(int jogador_posicao[2], int bomba_posicao[2], ESTADO_BOMBA bomba_estado, int mapa[ALTURA][LARGURA], int tecla)
{
  int x = jogador_posicao[1];
  int y = jogador_posicao[0];

  if (tecla)
  {
    if (tecla == 72 || tecla == 119)
      y--;
    if (tecla == 80 || tecla == 115)
      y++;
    if (tecla == 75 || tecla == 97)
      x--;
    if (tecla == 77 || tecla == 100)
      x++;
  }

  if (!pode_mover(mapa, bomba_posicao, bomba_estado, x, y))
    return;

  jogador_posicao[1] = x;
  jogador_posicao[0] = y;
}

void coloca_bomba(int jogador_posicao[2], int bomba_posicao[2], ESTADO_BOMBA &bomba_estado, int &bomba_tempo, int tecla)
{
  if (bomba_ativa(bomba_estado))
    return;

  if (tecla)
  {
    if (tecla == 32)
    {
      bomba_posicao[0] = jogador_posicao[0];
      bomba_posicao[1] = jogador_posicao[1];
      bomba_estado = ESTADO_BOMBA::ATIVA;
      bomba_tempo = GetTickCount();
    }
  }
}

void atualiza_jogador(Jogador &jogador, Bomba &bomba, int mapa[ALTURA][LARGURA], int tecla)
{
  mover_jogador(jogador.posicao, bomba.posicao, bomba.estado, mapa, tecla);
  coloca_bomba(jogador.posicao, bomba.posicao, bomba.estado, bomba.tempo, tecla);
}
