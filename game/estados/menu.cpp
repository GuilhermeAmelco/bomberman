#include "estados.h"

#include <iostream>
#include <conio.h>

using namespace std;

ESTADO_JOGO estado_menu()
{
  SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);

  cout << "===== BOMBERMAN =====\n";
  cout << "1 - Jogar\n";
  cout << "2 - Sair\n";

  int tecla = _getch();

  if (tecla == '1')
    return JOGANDO;

  if (tecla == '2')
    return SAIR;

  return MENU;
}