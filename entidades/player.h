#ifndef PLAYER_H
#define PLAYER_H

#include "../config/config.h"
#include "./bomba.h"

struct Jogador
{
    int posicao[2] = {1, 1};
    bool vivo = true;
    int tempo_movimento = 0;
};

void mover_jogador(
    Jogador &jogador,
    Bomba bombas[2],
    int mapa[ALTURA][LARGURA],
    int id);

void coloca_bomba(
    Jogador &jogador,
    Bomba &bomba,
    int tecla,
    int id);

void atualiza_jogador(
    Jogador &jogador, Bomba bombas[2], int mapa[ALTURA][LARGURA], int tecla, int id);

#endif