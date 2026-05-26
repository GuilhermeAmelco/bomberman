#include "estados.h"
#include "../../render/render.h"
#include <conio.h>

ESTADO_JOGO estado_jogando(
    int mapa[ALTURA][LARGURA],
    Jogador jogadores[2],
    Inimigo inimigos[],
    Bomba bombas[2],
    HANDLE out)
{
  desenhar(mapa, jogadores, inimigos, bombas, out);

  int tecla_bomba = -1;

  // Limpa todo o buffer de teclas pendentes no frame para não dar delay
  while (_kbhit())
  {
    int t = _getch();
    if (t == 27)
      return menu_loop(MENU_PAUSE);

    // Filtra para pegar apenas as teclas que usamos para plantar bomba
    if (t == 32 || t == 135 || t == 128 || t == 199 || t == 231 || t == 'c' || t == 'C')
    {
      tecla_bomba = t;
    }
  }

  for (int i = 0; i < 2; i++)
  {
    if (jogadores[i].vivo)
    {
      atualiza_jogador(jogadores[i], bombas, mapa, tecla_bomba, i);
      atualiza_bomba(bombas[i], mapa);

      if (mapa[jogadores[i].posicao[0]][jogadores[i].posicao[1]] == 3)
      {
        jogadores[i].vivo = false;
      }
    }
  }

  bool algum_inimigo_vivo = false;

  for (int i = 0; i < MAX_INIMIGOS; i++)
  {
    if (!inimigos[i].vivo)
      continue;

    algum_inimigo_vivo = true;

    atualiza_inimigo(inimigos[i], bombas, mapa, jogadores[0]);

    for (int j = 0; j < 2; j++)
    {
      if (jogadores[j].vivo && inimigos[i].vivo &&
          inimigos[i].posicao[0] == jogadores[j].posicao[0] &&
          inimigos[i].posicao[1] == jogadores[j].posicao[1])
      {
        jogadores[j].vivo = false;
      }
    }
  }

  bool todos_mortos = (!jogadores[0].vivo && (!modo_multiplayer || !jogadores[1].vivo));

  if (todos_mortos)
  {
    pontuacao_atual = 50 * (dificuldade_atual + 1);
    return DERROTA;
  }

  if (!algum_inimigo_vivo)
  {
    pontuacao_atual = 1000 * (dificuldade_atual + 1);
    return VITORIA;
  }

  return JOGANDO;
}