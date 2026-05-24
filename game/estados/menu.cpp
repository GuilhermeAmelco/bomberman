#include "estados.h"

#include <iostream>
#include <conio.h>
#include <windows.h>

using namespace std;

void desenhar_opcao(string texto, bool selecionado)
{
  if (selecionado)
  {
    SetConsoleTextAttribute(
        GetStdHandle(STD_OUTPUT_HANDLE),
        10);

    cout << "> " << texto << "\n";
  }
  else
  {
    SetConsoleTextAttribute(
        GetStdHandle(STD_OUTPUT_HANDLE),
        15);

    cout << "  " << texto << "\n";
  }
}

void limpar_tela()
{
  system("cls");
}

ESTADO_JOGO menu_loop(
    TIPO_MENU tipo)
{
  int opcao = 0;

  int total_opcoes;

  string opcoes[4];

  switch (tipo)
  {
  case MENU_INICIAL:
  case MENU_FINAL:
  {
    total_opcoes = 4;

    opcoes[0] = "Iniciar";
    opcoes[1] = "Pontuacao";
    opcoes[2] = "Como jogar";
    opcoes[3] = "Sair";

    break;
  }

  case MENU_PAUSE:
  {
    total_opcoes = 4;

    opcoes[0] = "Voltar";
    opcoes[1] = "Pontuacao";
    opcoes[2] = "Desistir";
    opcoes[3] = "Sair";

    break;
  }
  }

  while (true)
  {
    limpar_tela();

    SetConsoleTextAttribute(
        GetStdHandle(STD_OUTPUT_HANDLE),
        11);

    cout << "===== BOMBERMAN =====\n\n";

    for (int i = 0; i < total_opcoes; i++)
    {
      desenhar_opcao(
          opcoes[i],
          opcao == i);
    }

    int tecla = _getch();

    // seta especial
    if (tecla == 224)
    {
      tecla = _getch();

      // seta cima
      if (tecla == 72)
      {
        opcao--;

        if (opcao < 0)
          opcao = total_opcoes - 1;
      }

      // seta baixo
      if (tecla == 80)
      {
        opcao++;

        if (opcao >= total_opcoes)
          opcao = 0;
      }
    }

    // W
    if (tecla == 'w' || tecla == 'W')
    {
      opcao--;

      if (opcao < 0)
        opcao = total_opcoes - 1;
    }

    // S
    if (tecla == 's' || tecla == 'S')
    {
      opcao++;

      if (opcao >= total_opcoes)
        opcao = 0;
    }

    // ENTER
    if (tecla == 13)
    {
      switch (tipo)
      {
      case MENU_INICIAL:
      case MENU_FINAL:
      {
        switch (opcao)
        {
        case 0:
          return JOGANDO;

        case 1:
        {
          limpar_tela();

          cout << "Pontuacao ainda nao implementada.\n";

          system("pause");

          break;
        }

        case 2:
        {
          limpar_tela();

          cout << "WASD para mover.\n";
          cout << "ESPACO para bomba.\n";
          cout << "ESC para pause.\n";

          system("pause");

          break;
        }

        case 3:
          return SAIR;
        }

        break;
      }

      case MENU_PAUSE:
      {
        switch (opcao)
        {
        case 0:
          return JOGANDO;

        case 1:
        {
          limpar_tela();

          cout << "Pontuacao ainda nao implementada.\n";

          system("pause");

          break;
        }

        case 2:
          return DERROTA;

        case 3:
          return SAIR;
        }

        break;
      }
      }
    }
  }
}

ESTADO_JOGO estado_menu()
{
  return menu_loop(MENU_INICIAL);
}