// Esse código toma como base o código dos slides
// do professor Rodrigo Campiolo e Rogério A. Gonçalves
// 2021.

// Assunto: Sinais

// São sinais enviados para um processo para indicar
// algum evento que ocorreu. Esses sinais são utilizados
// pelo núcleo do sistema operacional para determinar como
// o processo alvo lidará com sua recepção.

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

// Função que trata o sinal.
// Aqui ela espera um sinal de interrupção (SIGINT).
// Ao invés de ter um comportamento padrão, ela imprime
// uma mensagem.
void sig_handler(int signo) {
  if (signo == SIGINT) {
    printf("O SIGINT foi recebido.\n");
  }
}

int main() {
  // Registra o sinal e a função que o trata.
  if (signal(SIGINT, sig_handler) == SIG_ERR) {
    printf("\nNão foi possível capturar o sinal SIGINT\n");
  }

  // Mostra o PID do processo.
  printf("O meu PID é %d.\n", getpid());

  // Um loop infinito para manter o programa rodando.
  while(1) {
    sleep(1);
  }

  return 0;
}

// É importante ressaltar que o sinal SIGINT é disparado pelo comando Ctrl+C.