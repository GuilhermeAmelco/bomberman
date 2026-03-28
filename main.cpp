#include <iostream>
#include <windows.h>
#include <conio.h>
using namespace std;

/*
O que precisa ser definido antes do loop infinito:
1. Mapa

O que precisa ser reenderizado a cada loop:
1. Posição do personagem
2. Bomba
3. Inimigos

Decidir aqui:
1. O que cada número vai significar;

0 - parede dura
1 - parede frágil
2 - bomba
3 - explosão
4 - inimigo
5 - personagem

2. O simbolo para cada item;
*/

const int LARGURA = 3;
const int ALTURA = 3;

void desenhar(int mapa[LARGURA][ALTURA], int player_position[2])
{
  // função responsável por desenhar: mapa, jogador, bomba, inimigos;

  // desenha o mapa
  for (int i = 0; i < LARGURA; i++)
  {
    for (int j = 0; j < ALTURA; j++)
    {
      // fazer logica para printar o player

      if (player_position[0] == i && player_position[1] == j)
      {
        cout << 5 << " ";
        continue;
      }
      cout << mapa[i][j] << " ";
    }
    cout << endl;
  }
}

void alterna_posicao(int player_position[2])
{
  if (_kbhit())
  {
    int tecla = getch();

    // fazer um osquestrador que separa o que cada tecla faz
  }
}

int main()
{
  HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);
  CONSOLE_CURSOR_INFO cursorInfo;
  GetConsoleCursorInfo(out, &cursorInfo);
  cursorInfo.bVisible = false;
  SetConsoleCursorInfo(out, &cursorInfo);
  short int CX = 0, CY = 0;
  COORD coord;
  coord.X = CX;
  coord.Y = CY;

  int mapa[LARGURA][ALTURA] = {
      {0, 0, 0},
      {0, 0, 0},
      {0, 0, 0}};

  int player_position[2] = {0, 0};

  while (true)
  {
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord); // limpa primeiro

    // desenhar(mapa, player_position, coord);
    alterna_posicao(player_position);
  }

  return 0;
}