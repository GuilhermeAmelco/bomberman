#include "render.h"

#include <iostream>

using namespace std;

void desenhar(
    int mapa[ALTURA][LARGURA],
    Jogador jogador,
    Inimigo inimigo,
    Bomba bomba,
    HANDLE out)
{
  for (int i = 0; i < ALTURA; i++)
  {
    for (int j = 0; j < LARGURA; j++)
    {
      bool isBomb =
          bomba.estado == ESTADO_BOMBA::ATIVA &&
          bomba.posicao[0] == i &&
          bomba.posicao[1] == j;

      bool isPlayer =
          jogador.posicao[0] == i &&
          jogador.posicao[1] == j;

      bool isEnemy =
          inimigo.vivo &&
          inimigo.posicao[0] == i &&
          inimigo.posicao[1] == j;

      if (isBomb)
      {
        SetConsoleTextAttribute(out, 5);
        cout << BLOCO << BLOCO;
        continue;
      }

      if (isEnemy)
      {
        SetConsoleTextAttribute(out, 12);
        cout << BLOCO << BLOCO;
        continue;
      }

      if (isPlayer)
      {
        SetConsoleTextAttribute(out, 10);
        cout << BLOCO << BLOCO;
        continue;
      }

      switch (mapa[i][j])
      {
      case 0:
      {
        SetConsoleTextAttribute(out, 3);
        cout << BLOCO << BLOCO;
        break;
      }

      case 1:
      {
        SetConsoleTextAttribute(out, 6);
        cout << BLOCO_CLARO << BLOCO_CLARO;
        break;
      }

      case 3:
      {
        SetConsoleTextAttribute(out, 12);
        cout << BLOCO << BLOCO;
        break;
      }

      case 9:
      {
        SetConsoleTextAttribute(out, 0);
        cout << BLOCO << BLOCO;
        break;
      }
      }
    }

    cout << endl;
  }
}