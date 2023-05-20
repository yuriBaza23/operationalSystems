// Código de Petterson (para 2 threads) sobre o problema de concorrência
// descrito no arquivo so_prog0001.c

#include <stdio.h>
#include <stdlib.h>

// Indica qual tarefa pode acessar a região crítica.
int turn = 0;
// Indica se a tarefa quer acessar a região crítica.
int wants[2] = {0, 0};

// Prmitiva enter.
// Indica qual a outra tarefa.
// Diz que a tarefa atual quer acessar a região crítica.
void enter(int task) {
  int outro = 1 - task;
  wants[task] = 1;
  turn = outro;
  while(wants[outro] && turn == outro) {}; // Espera ocupada.
}

// Primitiva leave.
// Libera o acesso da região crítica.
void leave(int task) {
  wants[task] = 0;
}