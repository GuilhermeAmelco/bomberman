#include <iostream>
#include <windows.h>
#include <conio.h>
#include <string.h>

using namespace std;

/*
MAPA (valores):
0 - parede dura
1 - parede frágil
2 - bomba
3 - explosão
4 - inimigo
5 - personagem
*/

const char BLOCO = 219;
const char BLOCO_CLARO = 176;
const int LARGURA = 15;
const int ALTURA = 11;

// estados
const string ESTADO_ATIVA = "ATIVA";
const string ESTADO_DESATIVADA = "INATIVA";
const string ESTADO_EXPLODINDO = "EXPLODINDO";

/* =========================
   INPUT
========================= */

int escuta_tecla()
{
  if (_kbhit())
    return getch();

  return -1;
}

/* =========================
   REGRAS
========================= */

bool pode_mover(int mapa[ALTURA][LARGURA], int bomba_posicao[2], string bomba_estado, int x, int y)
{
  if (x < 0 || x >= LARGURA)
    return false;

  if (y < 0 || y >= ALTURA)
    return false;

  if (mapa[y][x] == 0 || mapa[y][x] == 1)
    return false;

  if (bomba_posicao[0] == y && bomba_posicao[1] == x && bomba_estado == ESTADO_ATIVA)
    return false;

  return true;
}

bool bomba_ativa(string bomba_estado)
{
  return bomba_estado == ESTADO_ATIVA;
}

/* =========================
   LÓGICA DAS ENTIDADES
========================= */

void mover_jogador(int jogador_posicao[2], int bomba_posicao[2], string bomba_estado, int mapa[ALTURA][LARGURA], int tecla)
{
  int x = jogador_posicao[1];
  int y = jogador_posicao[0];

  if (tecla)
  {
    if (tecla == 72 || tecla == 119)
      y--;
    if (tecla == 80 || tecla == 115)
      y++;
    if (tecla == 75 || tecla == 97)
      x--;
    if (tecla == 77 || tecla == 100)
      x++;
  }

  if (!pode_mover(mapa, bomba_posicao, bomba_estado, x, y))
    return;

  jogador_posicao[1] = x;
  jogador_posicao[0] = y;
}

void coloca_bomba(int jogador_posicao[2], int bomba_posicao[2], string &bomba_estado, int &bomba_tempo, int tecla)
{
  if (bomba_ativa(bomba_estado))
    return;

  if (tecla)
  {
    if (tecla == 32)
    {
      bomba_posicao[0] = jogador_posicao[0];
      bomba_posicao[1] = jogador_posicao[1];
      bomba_estado = ESTADO_ATIVA;
      bomba_tempo = clock();
    }
  }
}

void explodir_bomba(string &bomba_estado, int &bomba_tempo)
{
  int tempo_passado = clock() - bomba_tempo;

  if (tempo_passado < 3000)
    return; // nao passou 3s

  bomba_estado = ESTADO_DESATIVADA;
  bomba_tempo = 0;
}

/* =========================
   RENDER
========================= */

void atualiza_jogador(int jogador_posicao[2], int bomba_posicao[2], string &bomba_estado, int &bomba_tempo, int mapa[ALTURA][LARGURA], int tecla)
{
  mover_jogador(jogador_posicao, bomba_posicao, bomba_estado, mapa, tecla);
  coloca_bomba(jogador_posicao, bomba_posicao, bomba_estado, bomba_tempo, tecla);
}

void atualiza_bomba(int bomba_posicao[2], string &bomba_estado, int &bomba_tempo, int mapa[ALTURA][LARGURA])
{
  if (bomba_estado == ESTADO_ATIVA)
    explodir_bomba(bomba_estado, bomba_tempo);
}

void desenhar(
    int mapa[ALTURA][LARGURA],
    int jogador_posicao[2],
    int bomba_posicao[2], string bomba_estado,
    HANDLE out)
{
  for (int i = 0; i < ALTURA; i++)
  {
    for (int j = 0; j < LARGURA; j++)
    {
      bool isBomb = (bomba_posicao[0] == i && bomba_posicao[1] == j && bomba_estado == ESTADO_ATIVA);
      bool isPlayer = (jogador_posicao[0] == i && jogador_posicao[1] == j);

      if (isBomb)
      {
        SetConsoleTextAttribute(out, 5);
        cout << BLOCO << BLOCO;
        continue;
      }

      // desenha jogador por cima do mapa
      if (isPlayer)
      {
        SetConsoleTextAttribute(out, 10);
        cout << BLOCO << BLOCO;
        continue;
      }

      int valor = mapa[i][j];

      switch (valor)
      {
      case 0: // bloco
        SetConsoleTextAttribute(out, 3);
        cout << BLOCO << BLOCO;
        break;
      case 1: // bloco-fragil
        SetConsoleTextAttribute(out, 3);
        cout << BLOCO_CLARO << BLOCO_CLARO;
        break;
      case 9: // vazio
        SetConsoleTextAttribute(out, 0);
        cout << BLOCO << BLOCO;
        break;
      }
    }
    cout << endl;
  }
}

/* =========================
   MAIN
========================= */

int main()
{
  // configuração do console
  HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE); // pega o acesso ao console para poder manipulá-lo

  CONSOLE_CURSOR_INFO cursorInfo;         // cria uma variavel com as info do cursor
  GetConsoleCursorInfo(out, &cursorInfo); // pega as info do cursor
  cursorInfo.bVisible = false;            // seta o cursor como invisível
  SetConsoleCursorInfo(out, &cursorInfo); // aplica as alterações

  COORD coord; // coordenadas do console
  coord.X = 0;
  coord.Y = 0;

  // mapa
  int mapa[ALTURA][LARGURA] = {
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
      {0, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 0},
      {0, 9, 0, 9, 0, 9, 0, 9, 0, 9, 0, 9, 0, 9, 0},
      {0, 1, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 0},
      {0, 9, 0, 9, 0, 9, 0, 9, 0, 9, 0, 9, 0, 9, 0},
      {0, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 0},
      {0, 9, 0, 9, 0, 9, 0, 9, 0, 9, 0, 9, 0, 9, 0},
      {0, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 0},
      {0, 9, 0, 9, 0, 9, 0, 9, 0, 9, 0, 9, 0, 9, 0},
      {0, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 0},
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}};

  // jogador
  int jogador_posicao[2] = {1, 1};

  // bomba(s)
  int bomba_posicao[2];
  string bomba_estado = ESTADO_DESATIVADA; // pode ser inativa, ativa e explodindo
  int bomba_tempo = 0;

  int tecla;

  // logica tempo
  const int FPS = 60;
  int tempo_por_segundo = 1000 / FPS;

  while (true)
  {
    int tempo_inicio = clock();

    // limpa tela (reposiciona cursor)
    SetConsoleCursorPosition(out, coord);

    desenhar(
        mapa,
        jogador_posicao,
        bomba_posicao, bomba_estado,
        out);

    tecla = escuta_tecla();

    // funcionalidades do jogador
    atualiza_jogador(jogador_posicao, bomba_posicao, bomba_estado, bomba_tempo, mapa, tecla);

    // funcionalidades da bomba
    atualiza_bomba(bomba_posicao, bomba_estado, bomba_tempo, mapa);

    // logica fps
    int tempo_executado = clock() - tempo_inicio;
    if (tempo_por_segundo > tempo_executado)
    {
      Sleep(tempo_por_segundo - tempo_executado);
    }
  }

  return 0;
}