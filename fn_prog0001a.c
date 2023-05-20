// Código de solução trivial sobre o problema de concorrência
// descrito no arquivo so_prog0001.c

#include <stdio.h>
#include <stdlib.h>

// Marca-se a seção crítica como livre inicialmente.
int busy = 0;

// Prmitiva enter.
// Espera enquanto a seção crítica estiver ocupada.
// Marca a sessão crítica como ocupada.
void enter() {
  while(busy) {};
  busy = 1;
}

// Primitiva leave.
// Marca a seção crítica como livre.
void leave() {
  busy = 0;
}