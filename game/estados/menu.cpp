#include "estados.h"

#include <iostream>
#include <conio.h>
#include <windows.h>
#include <fstream>
#include <string>

using namespace std;

void desenhar_opcao(string texto, bool selecionado, int cor_customizada = -1)
{
  if (cor_customizada != -1)
  {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), cor_customizada);
  }
  else
  {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), selecionado ? 10 : 15);
  }

  if (selecionado)
  {
    cout << "> " << texto << "\n";
  }
  else
  {
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
  int total_opcoes = 4;
  string opcoes[6]; // Agora precisa de 6 espaços

  while (true)
  {
    limpar_tela();

    switch (tipo)
    {
    case MENU_INICIAL:
    case MENU_FINAL:
    {
      total_opcoes = 6;

      string texto_dificuldade = "Medio";
      if (dificuldade_atual == 0)
        texto_dificuldade = "Facil";
      if (dificuldade_atual == 2)
        texto_dificuldade = "Dificil";

      opcoes[0] = "Single Player";
      opcoes[1] = "Multiplayer";
      opcoes[2] = "Dificuldade: < " + texto_dificuldade + " >";
      opcoes[3] = "Pontuacao";
      opcoes[4] = "Como jogar";
      opcoes[5] = "Sair";

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

    SetConsoleTextAttribute(
        GetStdHandle(STD_OUTPUT_HANDLE),
        11);

    cout << "===== BOMBERMAN =====\n\n";

    for (int i = 0; i < total_opcoes; i++)
    {
      // Renderiza a cor customizada caso seja a opção de dificuldade
      if ((tipo == MENU_INICIAL || tipo == MENU_FINAL) && i == 2)
      {
        int cor;
        if (i == opcao)
        {
          if (dificuldade_atual == 0)
            cor = 10; // Fácil = Verde
          else if (dificuldade_atual == 1)
            cor = 14; // Médio = Laranja/Amarelo
          else
            cor = 12; // Difícil = Vermelho
        }
        else
        {
          if (dificuldade_atual == 0)
            cor = 2; // Fácil Escuro
          else if (dificuldade_atual == 1)
            cor = 6; // Médio Escuro
          else
            cor = 4; // Difícil Escuro
        }

        desenhar_opcao(opcoes[i], i == opcao, cor);
      }
      else
      {
        desenhar_opcao(opcoes[i], i == opcao);
      }
    }

    int tecla = _getch();

    // Tratamento de setas do teclado
    if (tecla == 0 || tecla == 224)
    {
      tecla = _getch();
      if (tecla == 72) // Seta para Cima
      {
        opcao--;
        if (opcao < 0)
          opcao = total_opcoes - 1;
      }
      if (tecla == 80) // Seta para Baixo
      {
        opcao++;
        if (opcao >= total_opcoes)
          opcao = 0;
      }
      if (tecla == 75) // Seta para Esquerda (Lado que aumenta a dificuldade)
      {
        if ((tipo == MENU_INICIAL || tipo == MENU_FINAL) && opcao == 2)
        {
          dificuldade_atual++;
          if (dificuldade_atual > 2)
            dificuldade_atual = 0;
        }
      }
      if (tecla == 77) // Seta para Direita (Lado que diminui a dificuldade)
      {
        if ((tipo == MENU_INICIAL || tipo == MENU_FINAL) && opcao == 2)
        {
          dificuldade_atual--;
          if (dificuldade_atual < 0)
            dificuldade_atual = 2;
        }
      }
    }

    // Suporte alternativo para W / S
    if (tecla == 'w' || tecla == 'W')
    {
      opcao--;
      if (opcao < 0)
        opcao = total_opcoes - 1;
    }
    if (tecla == 's' || tecla == 'S')
    {
      opcao++;
      if (opcao >= total_opcoes)
        opcao = 0;
    }

    // Suporte alternativo A / D para a dificuldade
    if (tecla == 'a' || tecla == 'A')
    {
      if ((tipo == MENU_INICIAL || tipo == MENU_FINAL) && opcao == 2)
      {
        dificuldade_atual++; // Esquerda (Aumenta)
        if (dificuldade_atual > 2)
          dificuldade_atual = 0;
      }
    }
    if (tecla == 'd' || tecla == 'D')
    {
      if ((tipo == MENU_INICIAL || tipo == MENU_FINAL) && opcao == 2)
      {
        dificuldade_atual--; // Direita (Diminui)
        if (dificuldade_atual < 0)
          dificuldade_atual = 2;
      }
    }

    // Tecla ENTER
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
          modo_multiplayer = false;
          return JOGANDO;

        case 1:
          modo_multiplayer = true;
          return JOGANDO;

        case 2:
          // Permite que o ENTER também rotacione a dificuldade
          dificuldade_atual = (dificuldade_atual + 1) % 3;
          break;

        case 3:
        {
          limpar_tela();

          ifstream file("ranking.txt");
          if (file.is_open())
          {
            cout << "=== RANKING DOS JOGADORES ===\n\n";
            string linha;
            int contador = 1;
            while (getline(file, linha))
            {
              cout << contador << ". " << linha << "\n";
              contador++;
            }
            if (contador == 1)
            {
              cout << "Nenhum registro encontrado no momento.\n";
            }
            file.close();
          }
          else
          {
            cout << "=== RANKING DOS JOGADORES ===\n\n";
            cout << "Nenhum ranking registrado ainda.\n";
          }
          cout << "\n";
          system("pause");
          break;
        }

        case 4:
        {
          limpar_tela();

          cout << "SINGLE PLAYER:\n";
          cout << "WASD para mover e ESPACO para bomba.\n";
          cout << "SETAS para mover e C (Cedilha) para bomba.\n\n";
          cout << "MULTIPLAYER:\n";
          cout << "Jogador 1: WASD para mover, ESPACO para bomba.\n";
          cout << "Jogador 2: Setas para mover, C (Cedilha) para bomba.\n\n";
          cout << "ESC para pausar o jogo.\n";

          system("pause");
          break;
        }

        case 5:
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

          ifstream file("ranking.txt");
          if (file.is_open())
          {
            cout << "=== RANKING DOS JOGADORES ===\n\n";
            string linha;
            int contador = 1;
            while (getline(file, linha))
            {
              cout << contador << ". " << linha << "\n";
              contador++;
            }
            file.close();
          }
          else
          {
            cout << "=== RANKING DOS JOGADORES ===\n\n";
            cout << "Nenhum ranking registrado ainda.\n";
          }
          cout << "\n";
          system("pause");
          break;
        }

        case 2:
          return MENU;

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