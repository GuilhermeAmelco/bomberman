#pragma once

#include <windows.h>

#include "../../config/config.h"
#include "../../entidades/player.h"
#include "../../entidades/bomba.h"
#include "../../entidades/inimigo.h"

// Variáveis globais compartilhadas entre os arquivos
extern int dificuldade_atual;
extern int pontuacao_atual;

enum ESTADO_JOGO
{
    MENU,
    JOGANDO,
    VITORIA,
    DERROTA,
    SAIR
};

enum TIPO_MENU
{
    MENU_INICIAL,
    MENU_PAUSE,
    MENU_FINAL
};

ESTADO_JOGO estado_menu();

ESTADO_JOGO estado_jogando(
    int mapa[ALTURA][LARGURA],
    Jogador jogadores[2],
    Inimigo inimigos[],
    Bomba bombas[2],
    HANDLE out);

ESTADO_JOGO estado_vitoria(
    int mapa[ALTURA][LARGURA],
    Jogador jogadores[2],
    Inimigo inimigos[],
    Bomba bombas[2],
    HANDLE out);

ESTADO_JOGO estado_derrota(
    int mapa[ALTURA][LARGURA],
    Jogador jogadores[2],
    Inimigo inimigos[],
    Bomba bombas[2],
    HANDLE out);

ESTADO_JOGO menu_loop(TIPO_MENU tipo);