#include <iostream>
#include <windows.h>
#include <conio.h>
#include <string.h>
#include <ctime>

using namespace std;

/*
MAPA (valores):
0 - parede dura
1 - parede fragil
2 - bomba
3 - explosao
4 - inimigo
5 - personagem
*/

const unsigned char BLOCO = 219;
const unsigned char BLOCO_CLARO = 176;
const int LARGURA = 15;
const int ALTURA = 11;
const int TEMPO_BOMBA = 3000;
const int TEMPO_EXPLOSAO = 500;
const int TEMPO_INIMIGO = 500;

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
    return _getch();

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
   LOGICA DAS ENTIDADES
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
      bomba_tempo = GetTickCount();
    }
  }
}

void explodir_bomba(int mapa[ALTURA][LARGURA], int bomba_posicao[2], string &bomba_estado, int &bomba_tempo)
{
  int tempo_passado = GetTickCount() - bomba_tempo;

  if (tempo_passado < TEMPO_BOMBA)
    return;

  int dl[5] = {0, 0, 0, 1, -1};
  int dc[5] = {0, 1, -1, 0, 0};

  for (int i = 0; i < 5; i++)
  {
    int l = bomba_posicao[0] + dl[i];
    int c = bomba_posicao[1] + dc[i];

    if (l < 0 || l >= ALTURA || c < 0 || c >= LARGURA)
      continue;

    if (mapa[l][c] == 0)
      continue;

    mapa[l][c] = 3;
  }

  bomba_estado = ESTADO_EXPLODINDO;
  bomba_tempo = GetTickCount();
}

void limpar_explosao(int mapa[ALTURA][LARGURA], int bomba_posicao[2], string &bomba_estado, int &bomba_tempo)
{
  int tempo_passado = GetTickCount() - bomba_tempo;

  if (tempo_passado < TEMPO_EXPLOSAO)
    return;

  int dl[5] = {0, 0, 0, 1, -1};
  int dc[5] = {0, 1, -1, 0, 0};

  for (int i = 0; i < 5; i++)
  {
    int l = bomba_posicao[0] + dl[i];
    int c = bomba_posicao[1] + dc[i];

    if (l < 0 || l >= ALTURA || c < 0 || c >= LARGURA)
      continue;

    if (mapa[l][c] == 3)
      mapa[l][c] = 9;
  }

  bomba_estado = ESTADO_DESATIVADA;
  bomba_tempo = 0;
  bomba_posicao[0] = -1;
  bomba_posicao[1] = -1;
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
    explodir_bomba(mapa, bomba_posicao, bomba_estado, bomba_tempo);

  if (bomba_estado == ESTADO_EXPLODINDO)
    limpar_explosao(mapa, bomba_posicao, bomba_estado, bomba_tempo);
}

void atualiza_inimigo(int inimigo_posicao[2], bool &inimigo_vivo, int mapa[ALTURA][LARGURA], int bomba_posicao[2], string bomba_estado, int &tempo_inimigo)
{
  if (!inimigo_vivo)
    return;

  if (mapa[inimigo_posicao[0]][inimigo_posicao[1]] == 3)
  {
    inimigo_vivo = false;
    return;
  }

  if (GetTickCount() - tempo_inimigo < TEMPO_INIMIGO)
    return;

  tempo_inimigo = GetTickCount();

  int x = inimigo_posicao[1];
  int y = inimigo_posicao[0];
  int dir = rand() % 4;
  int passos = 1 + rand() % 3;

  for (int i = 0; i < passos; i++)
  {
    int novo_x = x;
    int novo_y = y;

    if (dir == 0)
      novo_y--;
    if (dir == 1)
      novo_y++;
    if (dir == 2)
      novo_x--;
    if (dir == 3)
      novo_x++;

    if (!pode_mover(mapa, bomba_posicao, bomba_estado, novo_x, novo_y))
      break;

    x = novo_x;
    y = novo_y;
  }

  inimigo_posicao[1] = x;
  inimigo_posicao[0] = y;
}

void desenhar(
    int mapa[ALTURA][LARGURA],
    int jogador_posicao[2],
    int inimigo_posicao[2], bool inimigo_vivo,
    int bomba_posicao[2], string bomba_estado,
    HANDLE out)
{
  for (int i = 0; i < ALTURA; i++)
  {
    for (int j = 0; j < LARGURA; j++)
    {
      bool isBomb = (bomba_posicao[0] == i && bomba_posicao[1] == j && bomba_estado == ESTADO_ATIVA);
      bool isPlayer = (jogador_posicao[0] == i && jogador_posicao[1] == j);
      bool isEnemy = (inimigo_vivo && inimigo_posicao[0] == i && inimigo_posicao[1] == j);

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

      int valor = mapa[i][j];

      switch (valor)
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

/* =========================
   MAIN
========================= */

int main()
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

  int mapa[ALTURA][LARGURA] = {
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

  int jogador_posicao[2] = {1, 1};
  bool jogador_vivo = true;

  int inimigo_posicao[2] = {1, 13};
  bool inimigo_vivo = true;
  int tempo_inimigo = GetTickCount();

  int bomba_posicao[2] = {-1, -1};
  string bomba_estado = ESTADO_DESATIVADA;
  int bomba_tempo = 0;

  const int FPS = 25;
  int tempo_por_segundo = 1000 / FPS;

  while (jogador_vivo)
  {
    SetConsoleCursorPosition(out, coord);

    int tempo_inicio = clock();

    desenhar(
        mapa,
        jogador_posicao,
        inimigo_posicao, inimigo_vivo,
        bomba_posicao, bomba_estado,
        out);

    int tecla = escuta_tecla();

    atualiza_jogador(jogador_posicao, bomba_posicao, bomba_estado, bomba_tempo, mapa, tecla);
    atualiza_bomba(bomba_posicao, bomba_estado, bomba_tempo, mapa);
    atualiza_inimigo(inimigo_posicao, inimigo_vivo, mapa, bomba_posicao, bomba_estado, tempo_inimigo);

    // logica da morte da explosao
    if (mapa[jogador_posicao[0]][jogador_posicao[1]] == 3)
      jogador_vivo = false;

    if (inimigo_vivo && mapa[inimigo_posicao[0]][inimigo_posicao[1]] == 3)
      inimigo_vivo = false;

    if (inimigo_vivo && inimigo_posicao[0] == jogador_posicao[0] && inimigo_posicao[1] == jogador_posicao[1])
      jogador_vivo = false;

    if (!inimigo_vivo)
      break;

    int tempo_passado = clock() - tempo_inicio;
    if (tempo_passado < tempo_por_segundo)
    {
      int tempo_adiantado = tempo_por_segundo - tempo_passado;
      Sleep(tempo_adiantado);
    }
  }

  SetConsoleCursorPosition(out, coord);
  desenhar(
      mapa,
      jogador_posicao,
      inimigo_posicao, inimigo_vivo,
      bomba_posicao, bomba_estado,
      out);

  SetConsoleTextAttribute(out, 15);
  if (jogador_vivo && !inimigo_vivo)
    cout << "\nVOCE VENCEU!\n";
  else
    cout << "\nVOCE PERDEU!\n";

  while (_kbhit())
    _getch();

  cout << "Pressione qualquer tecla para sair...";
  _getch();

  return 0;
}
