#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <unistd.h>
#include <pthread.h>

#define NUM_PHILOSOPHERS 5                              // Define a quantidade de filósofos
#define THINKING 0                                      // Define o estado de pensamento
#define HUNGRY 1                                        // Define o estado de fome
#define EATING 2                                        // Define o estado de comer

sem_t mutex;                                            // Exclusão mútua para as regiões críticas
sem_t sem[NUM_PHILOSOPHERS];                            // Um semáforo para cada filósofo
int state[NUM_PHILOSOPHERS];                            // Estado de cada filósofo

struct philosophers {                                   // Struct para os filósofos
  int num;                                              // Número do filósofo
};

// Função verifica se o filósofo i pode comer           // ---------
// Se a condição for verdadeira, o filósofo i           // ---------
// é liberado e define seu estado como comendo          // ---------
void check(int i) {                            
  if (state[i] == HUNGRY && state[(i + NUM_PHILOSOPHERS - 1) % NUM_PHILOSOPHERS] != EATING && state[(i + 1) % NUM_PHILOSOPHERS] != EATING) {
    state[i] = EATING;                          
    sem_post(&sem[i]);                          
  }
}

void think(int i) {                                     // Função simula o pensamento
  printf("Filósofo %d está pensando\n", i);             // Imprime o pensamento do filósofo i
  sleep(rand() % 10);                                   // Espera um tempo aleatório
}

void eat(int i) {                                       // Função simula a refeição
  printf("Filósofo %d está comendo\n", i);              // Imprime a refeição do filósofo i
}

void take_hashis(int i) {                               // Função simula a tentativa de pegar os hashis
  sem_wait(&mutex);                                     // Entra na região crítica
  state[i] = HUNGRY;                                    // Define o estado do filósofo i como faminto
  check(i);                                             // Tenta pegar os hashis
  sem_post(&mutex);                                     // Sai da região crítica
  sem_wait(&sem[i]);                                    // Bloqueia se os hashis não foram pegos
}

void put_hashis(int i) {                                // Função simula a devolução dos hashis
  sem_wait(&mutex);                                     // Entra na região crítica
  state[i] = THINKING;                                  // Define o estado do filósofo i como pensando
  check((i + NUM_PHILOSOPHERS - 1) % NUM_PHILOSOPHERS); // Verifica se o filósofo da esquerda pode comer
  check((i + 1) % NUM_PHILOSOPHERS);                    // Verifica se o filósofo da direita pode comer
  sem_post(&mutex);                                     // Sai da região crítica
}

void* philosopher(int i) {                              // Função simula um filósofo
  while(1) {
    think(i);                                           // Filósofo i pensa
    take_hashis(i);                                     // Filósofo i tenta pegar os hashis
    eat(i);                                             // Filósofo i come
    put_hashis(i);
  }
}

int main() {
  printf("Funcionando!\n");
  pthread_t thread[NUM_PHILOSOPHERS];                   // Vetor de threads
  struct philosophers p[NUM_PHILOSOPHERS];              // Vetor de filósofos

  for (int i = 0; i < NUM_PHILOSOPHERS; i++) {          // Inicializa os semáforos
    sem_init(&sem[i], 0, 0);
  }

  for (int i = 0; i < NUM_PHILOSOPHERS; i++) {          // Inicializa os filósofos
    p[i].num = i;
    pthread_create(&thread[i], NULL, philosopher, i);
  }

  for (int i = 0; i < NUM_PHILOSOPHERS; i++) {          // Espera as threads terminarem
    pthread_join(thread[i], NULL);
  }

  sem_destroy(&mutex);                                  // Destrói os semáforos
  return 0;
}