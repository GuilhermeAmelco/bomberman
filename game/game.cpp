#include "game.h"
#include <windows.h>
#include <ctime>
#include <cstring>
#include "estados/estados.h"

using namespace std;

int dificuldade_atual = 1;
int pontuacao_atual = 0;
bool modo_multiplayer = false;

void iniciar_jogo()
{
  srand(time(NULL));

  HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);
  CONSOLE_CURSOR_INFO cursorInfo;
  GetConsoleCursorInfo(out, &cursorInfo);
  cursorInfo.bVisible = false;
  SetConsoleCursorInfo(out, &cursorInfo);

  COORD coord;
  coord.X = 0;
  coord.Y = 0;

  int mapa[ALTURA][LARGURA];
  Jogador jogadores[2];
  Inimigo inimigos[MAX_INIMIGOS];
  Bomba bombas[2];

  ESTADO_JOGO estado = MENU;

  while (estado != SAIR)
  {
    SetConsoleCursorPosition(out, coord);

    switch (estado)
    {
    case MENU:
    {
      estado = estado_menu();

      if (estado == JOGANDO)
      {
        int mapa_original[ALTURA][LARGURA] = {
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
            {0, 9, 9, 1, 9, 1, 9, 9, 9, 1, 9, 1, 9, 9, 0},
            {0, 9, 0, 9, 0, 9, 0, 9, 0, 9, 0, 9, 0, 9, 0},
            {0, 1, 9, 9, 9, 1, 9, 9, 9, 9, 9, 1, 9, 9, 0},
            {0, 9, 0, 9, 0, 9, 0, 1, 0, 9, 0, 9, 0, 9, 0},
            {0, 9, 9, 1, 9, 9, 9, 9, 9, 9, 9, 1, 9, 9, 0},
            {0, 9, 0, 9, 0, 9, 0, 9, 0, 1, 0, 9, 0, 9, 0},
            {0, 1, 9, 9, 9, 9, 9, 1, 9, 9, 9, 9, 9, 1, 0},
            {0, 9, 0, 9, 0, 1, 0, 9, 0, 9, 0, 9, 0, 9, 0},
            {0, 9, 9, 1, 9, 9, 9, 9, 9, 1, 9, 9, 9, 9, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}};

        memcpy(mapa, mapa_original, sizeof(mapa));

        jogadores[0] = Jogador();
        jogadores[0].posicao[0] = 1;
        jogadores[0].posicao[1] = 1;
        bombas[0] = Bomba();
        bombas[0].estado = ESTADO_BOMBA::INATIVA;

        jogadores[1] = Jogador();
        jogadores[1].posicao[0] = 9;
        jogadores[1].posicao[1] = 13; // Ajustado para canto oposto
        if (!modo_multiplayer)
          jogadores[1].vivo = false;
        bombas[1] = Bomba();
        bombas[1].estado = ESTADO_BOMBA::INATIVA;

        int num_inimigos = 3;
        if (dificuldade_atual == 1)
          num_inimigos = 5;
        if (dificuldade_atual == 2)
          num_inimigos = 7;

        for (int i = 0; i < MAX_INIMIGOS; i++)
          inimigos[i].vivo = false;

        inimigos[0].vivo = true;
        inimigos[0].is_boss = true;
        inimigos[0].vida = 3;
        inimigos[0].posicao[0] = 9;
        inimigos[0].posicao[1] = 1;

        for (int i = 1; i < num_inimigos; i++)
        {
          inimigos[i].vivo = true;
          inimigos[i].is_boss = false;
          inimigos[i].vida = 1;
          do
          {
            inimigos[i].posicao[0] = 1 + (rand() % (ALTURA - 2));
            inimigos[i].posicao[1] = 1 + (rand() % (LARGURA - 2));
          } while (mapa_original[inimigos[i].posicao[0]][inimigos[i].posicao[1]] != 9 ||
                   (inimigos[i].posicao[0] == 1 && inimigos[i].posicao[1] == 1) ||
                   (inimigos[i].posicao[0] == 9 && inimigos[i].posicao[1] == 13));
        }

        system("cls");
      }
      break;
    }

    case JOGANDO:
      estado = estado_jogando(mapa, jogadores, inimigos, bombas, out);
      break;

    case VITORIA:
      estado = estado_vitoria(mapa, jogadores, inimigos, bombas, out);
      break;

    case DERROTA:
      estado = estado_derrota(mapa, jogadores, inimigos, bombas, out);
      break;
    }
  }
}