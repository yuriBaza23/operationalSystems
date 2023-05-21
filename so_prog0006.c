// Esse código toma como base o código dos slides
// do professor Rodrigo Campiolo e Rogério A. Gonçalves
// 2021.

// Assunto: Pipes

// Pipes são mecanismos de comunicação entre processos.
// Eles não possuem nome e são utilizados para comunicação
// entre processos relacionados (pai e filho).
// Cria-se o pipe -> realiza-se o fork

// Ao fim do processo os pipes são fechados.
// Acesso por meio de descritores de arquivos.

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
  pid_t pid;
  int myPipe[2];
  char buffer[50];

  // Cria o pipe.
  if(pipe(myPipe)) {
    printf("Erro ao criar o pipe.\n");
    exit(1);
  }

  // Cria o processo filho.
  pid = fork();
  if(pid < 0) { // Pid negativo indica erro.
    printf("Erro ao criar o processo filho.\n");
    exit(1);
  } else if(pid == 0) {
    // Processo filho.
    close(myPipe[1]); // Fecha a escrita.
    read(myPipe[0], buffer, sizeof(buffer)); // Lê o pipe.
    printf("Filho: %s\n", buffer);
    fflush(stdout);
    exit(0);
  } else {
    // Processo pai.
    close(myPipe[0]); // Fecha a leitura.
    write(myPipe[1], "Olá filho!", 11); // Escreve no pipe.
    printf("Pai: escrevi no pipe.\n");
    wait(NULL); // Espera o filho terminar. Para evitar zumbis.
    exit(0);
  }
}

// Nos pipes, pipefd[0] é usado para leitura e pipefd[1] é usado para escrita.
// O pipe é unidirecional, ou seja, se você deseja enviar e receber dados, você precisa criar dois pipes.