#pragma once

#include <windows.h>

#include "../config/config.h"

#include "../entidades/player.h"
#include "../entidades/bomba.h"
#include "../entidades/inimigo.h"

void desenhar(
    int mapa[ALTURA][LARGURA],
    Jogador jogador,
    Inimigo inimigo,
    Bomba bomba,
    HANDLE out);