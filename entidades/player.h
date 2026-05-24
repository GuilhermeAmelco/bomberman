#ifndef PLAYER_H
#define PLAYER_H

#include "../config/config.h"
#include "./bomba.h"

struct Jogador
{
    int posicao[2] = {1, 1};
    bool vivo = true;
};

void mover_jogador(
    int jogador_posicao[2],
    int bomba_posicao[2],
    ESTADO_BOMBA bomba_estado,
    int mapa[ALTURA][LARGURA],
    int tecla);

void coloca_bomba(
    int jogador_posicao[2],
    int bomba_posicao[2],
    ESTADO_BOMBA &bomba_estado,
    int &bomba_tempo,
    int tecla);

void atualiza_jogador(
    Jogador &jogador, Bomba &bomba, int mapa[ALTURA][LARGURA], int tecla);

#endif