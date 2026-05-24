#pragma once

#include <windows.h>

#include "../../config/config.h"

#include "../../entidades/player.h"
#include "../../entidades/bomba.h"
#include "../../entidades/inimigo.h"

enum ESTADO_JOGO
{
    MENU,
    JOGANDO,
    VITORIA,
    DERROTA,
    SAIR
};

ESTADO_JOGO estado_menu();

ESTADO_JOGO estado_jogando(
    int mapa[ALTURA][LARGURA],
    Jogador &jogador,
    Inimigo &inimigo,
    Bomba &bomba,
    HANDLE out);

ESTADO_JOGO estado_vitoria(
    int mapa[ALTURA][LARGURA],
    Jogador jogador,
    Inimigo inimigo,
    Bomba bomba,
    HANDLE out);

ESTADO_JOGO estado_derrota(
    int mapa[ALTURA][LARGURA],
    Jogador jogador,
    Inimigo inimigo,
    Bomba bomba,
    HANDLE out);

enum TIPO_MENU
{
    MENU_INICIAL,
    MENU_PAUSE,
    MENU_FINAL
};

ESTADO_JOGO estado_menu();

ESTADO_JOGO menu_loop(
    TIPO_MENU tipo);