// Esse código toma como base o código do livro
// "Sistemas Operacionais: Conceitos e Mecanismos"
// de Carlos Maziero, 2019.

// Assunto: Mecanismos de coordenação
// SEMAFOROS

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

// É o mecanismo mais utilizado para sincronização de threads.
// Pode ser visto como uma estrutura que comporta uma fila
// de tarefas (que inicia vazia) e um contador (que depende de
// como o semáforo foi criado/seu uso).
// O conteúdo interno do semáforo não é diretamente acessível
// pelo programador, apenas as funções que o manipulam.
// Essas funções são:
// up(s): incrementa o contador do semáforo s.
// down(s): decrementa o contador do semáforo s.

// Uma função init é utilizada para inicializar o semáforo.

// As operações de acesso aos semáforos são geralmente implementadas pelo
// kernel. Elas tevem ser atomicas para evitar condições de disputa. Nesse
// caso, a espera ocupada não seria um problema.

// int sem_init(sem_t *sem, int pshared, unsigned int value) é Equivalente a função init(s, 1);
// int sem_post(sem_t *sem) é Equivalente a função up(s);
// int sem_wait(sem_t *sem) é Equivalente a função down(s);

// Buffer que simboliza a conta bancária.
long int saldo = 0;
long int data = 0;

// Cria o semáforo.
sem_t mutex;

void *depositar() {
  sem_wait(&mutex); // Pede acesso a região crítica.
  data++;
  saldo += data;  // Acessa a região crítica.
  sem_post(&mutex); // Libera o acesso a região crítica.
}

int main() {
  // Cria duas threads.
  pthread_t t1, t2;

  // Inicializa o semáforo.
  sem_init(&mutex, 0, 1);

  // Cria as threads.
  pthread_create(&t1, NULL, depositar, NULL);
  pthread_create(&t2, NULL, depositar, NULL);

  // Espera as threads terminarem.
  pthread_join(t1, NULL);
  pthread_join(t2, NULL);

  // Imprime o saldo.
  printf("Saldo: %ld\n", saldo);

  return 0;
}