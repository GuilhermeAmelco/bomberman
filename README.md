# 📄 Documentação do Projeto

## 1. O que é

Este projeto é um trabalho para a disciplina de Algoritmos 2, que consiste na implementação de um sistema simples de renderização e movimentação em um mapa utilizando C++ no terminal (console).

A ideia principal é simular um jogo estilo grid (semelhante ao Bomberman), onde:

- Existe um mapa representado por uma matriz
- Um personagem controlado pelo teclado
- Regras simples de movimentação e colisão
- Renderização usando caracteres no console

---

## 2. Como iniciar o projeto

### Requisitos

- Sistema operacional Windows (usa windows.h e conio.h)
- Compilador C++ (ex: MinGW, MSVC)

### Compilar

g++ main.cpp -o jogo

### Executar

./jogo

---

## 3. Regras estabelecidas

### Representação do mapa

O mapa é uma matriz 2D de inteiros:

int mapa[LARGURA][ALTURA];

Cada número representa um elemento:

0 - Parede dura  
1 - Parede frágil  
2 - Bomba  
3 - Explosão  
4 - Inimigo  
5 - Personagem  
9 - Espaço vazio

---

### Movimentação

O jogador se move usando as setas do teclado:

↑ - 72 | w - 119
↓ - 80 | s - 115
← - 75 | a - 97
→ - 77 | d - 100

---

### Regras de colisão

O jogador não pode se mover para:

- Fora do mapa
- Parede dura (0)
- Parede frágil (1)
- Bomba (2)

Essa lógica está na função `pode_mover`.

---

## 4. Arquitetura

O código está dividido em blocos bem definidos, cada um com uma responsabilidade:

---

### INPUT

int escuta_tecla()

- Captura a tecla pressionada sem travar o loop
- Usa \_kbhit() e getch()
- Retorna -1 se nenhuma tecla foi pressionada

---

### REGRAS

bool pode_mover(...)

- Verifica se uma posição é válida
- Garante limites do mapa
- Aplica regras de colisão

---

### LÓGICA DO JOGADOR

void mover_jogador(...)

- Interpreta a tecla pressionada
- Calcula nova posição
- Usa pode_mover antes de atualizar

---

### RENDER

void desenhar(...)

- Percorre o mapa
- Desenha cada elemento no console
- O jogador é desenhado por cima do mapa
- Usa cores com SetConsoleTextAttribute

---

### LOOP PRINCIPAL (MAIN)

while (true)

Responsável por:

1. Resetar o cursor (simula limpar tela)
2. Desenhar o mapa
3. Capturar input
4. Atualizar o jogador
