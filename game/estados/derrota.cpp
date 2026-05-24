#include "estados.h"

ESTADO_JOGO estado_derrota(
    int mapa[ALTURA][LARGURA],
    Jogador jogador,
    Inimigo inimigo,
    Bomba bomba,
    HANDLE out)
{
    return menu_loop(MENU_FINAL);
}