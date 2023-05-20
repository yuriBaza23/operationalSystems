// Código de alternancia de uso sobre o problema de concorrência
// descrito no arquivo so_prog0001.c

#include <stdio.h>
#include <stdlib.h>

// Mostra o numero de tarefas.
int numTasks;
// Indica qual tarefa pode acessar a região crítica.
int turn = 0;

// Prmitiva enter.
// Espera enquanto a seção crítica estiver ocupada.
void enter(int task) {
  while(turn != task) {};
}

// Primitiva leave.
// Passa o acesso da região crítica para a próxima tarefa.
void leave(int task) {
  turn = (task + 1) % numTasks;
}