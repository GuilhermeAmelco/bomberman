#include <iostream>
#include <windows.h>
#include "../config/regras.h"
#include "./player.h"
#include "./bomba.h"

using namespace std;

void mover_jogador(Jogador &jogador, Bomba bombas[2], int mapa[ALTURA][LARGURA], int id)
{
  // Cooldown de 120ms para que o personagem não "voe" pelo mapa
  if (GetTickCount() - jogador.tempo_movimento < 120)
    return;

  int x = jogador.posicao[1];
  int y = jogador.posicao[0];
  bool moveu = false;

  if (id == 0)
  {
    if (GetAsyncKeyState(0x57) & 0x8000)
    {
      y--;
      moveu = true;
    } // W
    else if (GetAsyncKeyState(0x53) & 0x8000)
    {
      y++;
      moveu = true;
    } // S
    else if (GetAsyncKeyState(0x41) & 0x8000)
    {
      x--;
      moveu = true;
    } // A
    else if (GetAsyncKeyState(0x44) & 0x8000)
    {
      x++;
      moveu = true;
    } // D

    if (!modo_multiplayer && !moveu)
    {
      if (GetAsyncKeyState(VK_UP) & 0x8000)
      {
        y--;
        moveu = true;
      }
      else if (GetAsyncKeyState(VK_DOWN) & 0x8000)
      {
        y++;
        moveu = true;
      }
      else if (GetAsyncKeyState(VK_LEFT) & 0x8000)
      {
        x--;
        moveu = true;
      }
      else if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
      {
        x++;
        moveu = true;
      }
    }
  }
  else if (id == 1 && modo_multiplayer)
  {
    if (GetAsyncKeyState(VK_UP) & 0x8000)
    {
      y--;
      moveu = true;
    }
    else if (GetAsyncKeyState(VK_DOWN) & 0x8000)
    {
      y++;
      moveu = true;
    }
    else if (GetAsyncKeyState(VK_LEFT) & 0x8000)
    {
      x--;
      moveu = true;
    }
    else if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
    {
      x++;
      moveu = true;
    }
  }

  if (moveu)
  {
    if (pode_mover(mapa, bombas, x, y))
    {
      jogador.posicao[1] = x;
      jogador.posicao[0] = y;
    }
    jogador.tempo_movimento = GetTickCount(); // Reseta o tempo após mover
  }
}

void coloca_bomba(Jogador &jogador, Bomba &bomba, int tecla, int id)
{
  if (bomba_ativa(bomba.estado))
    return;

  bool planta = false;

  bool eh_cedilha = (tecla == 135 || tecla == 128 || tecla == 199 || tecla == 231 || tecla == 'c' || tecla == 'C');

  if (id == 0)
  {
    if ((GetAsyncKeyState(VK_SPACE) & 0x8000) || tecla == 32)
      planta = true;
    if (!modo_multiplayer && eh_cedilha)
      planta = true;
  }
  else if (id == 1 && modo_multiplayer)
  {
    if (eh_cedilha)
      planta = true;
    // Pega as teclas nativas do Ç em layouts ABNT2 simultaneamente (códigos 186, 191 ou 220)
    if ((GetAsyncKeyState(186) & 0x8000) || (GetAsyncKeyState(191) & 0x8000) || (GetAsyncKeyState(220) & 0x8000))
      planta = true;
  }

  if (planta)
  {
    bomba.posicao[0] = jogador.posicao[0];
    bomba.posicao[1] = jogador.posicao[1];
    bomba.estado = ESTADO_BOMBA::ATIVA;
    bomba.tempo = GetTickCount();
  }
}

void atualiza_jogador(Jogador &jogador, Bomba bombas[2], int mapa[ALTURA][LARGURA], int tecla, int id)
{
  if (!jogador.vivo)
    return;
  mover_jogador(jogador, bombas, mapa, id);
  coloca_bomba(jogador, bombas[id], tecla, id);
}