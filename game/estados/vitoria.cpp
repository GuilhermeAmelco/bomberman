#include "estados.h"
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

ESTADO_JOGO estado_vitoria(
    int mapa[ALTURA][LARGURA], Jogador jogadores[2], Inimigo inimigos[], Bomba bombas[2], HANDLE out)
{
    system("cls");
    cout << "===========================\n";
    cout << "        VOCE VENCEU!       \n";
    cout << "===========================\n\n";

    cout << "Sua pontuacao: " << pontuacao_atual << "\n\n";

    ofstream file("ranking.txt", ios::app);
    if (file.is_open())
    {
        if (modo_multiplayer)
        {
            string nome1, nome2;
            cin.clear();
            cout << "Insira o nome do primeiro jogador (sem espacos): ";
            cin >> nome1;
            cout << "Insira o nome do segundo jogador (sem espacos): ";
            cin >> nome2;

            file << nome1 << " & " << nome2 << " - " << pontuacao_atual << " pts (Venceu)\n";
        }
        else
        {
            string nome;
            cin.clear();
            cout << "Digite seu nome para o Ranking (sem espacos): ";
            cin >> nome;

            file << nome << " - " << pontuacao_atual << " pts (Venceu)\n";
        }
        file.flush();
        file.close();
    }

    return MENU;
}