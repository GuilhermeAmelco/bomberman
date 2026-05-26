#include "render.h"
#include <iostream>

using namespace std;

void desenhar(int mapa[ALTURA][LARGURA], Jogador jogadores[2], Inimigo inimigos[], Bomba bombas[2], HANDLE out)
{
  for (int i = 0; i < ALTURA; i++)
  {
    for (int j = 0; j < LARGURA; j++)
    {
      bool isBomb = false;
      for (int k = 0; k < 2; k++)
      {
        if (bombas[k].estado == ESTADO_BOMBA::ATIVA && bombas[k].posicao[0] == i && bombas[k].posicao[1] == j)
          isBomb = true;
      }

      bool isPlayer1 = jogadores[0].vivo && jogadores[0].posicao[0] == i && jogadores[0].posicao[1] == j;
      bool isPlayer2 = jogadores[1].vivo && jogadores[1].posicao[0] == i && jogadores[1].posicao[1] == j;

      bool isEnemy = false;
      bool isBoss = false;

      for (int k = 0; k < MAX_INIMIGOS; k++)
      {
        if (inimigos[k].vivo && inimigos[k].posicao[0] == i && inimigos[k].posicao[1] == j)
        {
          isEnemy = true;
          if (inimigos[k].is_boss)
            isBoss = true;
        }
      }

      if (isBomb)
      {
        SetConsoleTextAttribute(out, 5);
        cout << BLOCO << BLOCO;
        continue;
      }

      if (isBoss)
      {
        SetConsoleTextAttribute(out, 13);
        cout << BLOCO << BLOCO;
        continue;
      }
      else if (isEnemy)
      {
        SetConsoleTextAttribute(out, 12);
        cout << BLOCO << BLOCO;
        continue;
      }

      if (isPlayer1)
      {
        SetConsoleTextAttribute(out, 10);
        cout << BLOCO << BLOCO;
        continue;
      }
      else if (isPlayer2)
      {
        SetConsoleTextAttribute(out, 11); // P2 = Ciano
        cout << BLOCO << BLOCO;
        continue;
      }

      switch (mapa[i][j])
      {
      case 0:
        SetConsoleTextAttribute(out, 3);
        cout << BLOCO << BLOCO;
        break;
      case 1:
        SetConsoleTextAttribute(out, 6);
        cout << BLOCO_CLARO << BLOCO_CLARO;
        break;
      case 3:
        SetConsoleTextAttribute(out, 12);
        cout << BLOCO << BLOCO;
        break;
      case 9:
        SetConsoleTextAttribute(out, 0);
        cout << BLOCO << BLOCO;
        break;
      }
    }
    cout << endl;
  }
}