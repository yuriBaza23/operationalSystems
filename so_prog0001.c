// Esse código toma como base o código do livro
// "Sistemas Operacionais: Conceitos e Mecanismos"
// de Carlos Maziero, 2019.

// Assunto: Concorrência e Sincronização

#include <stdio.h>
#include <stdlib.h>

// #include "fn_prog0001a.c" <- Descomente essa linha para testar
// #include "fn_prog0001b.c" <- Descomente essa linha para testar
#include "fn_prog0001c.c"

// Função utilizada para aumentar o valor de uma variável.
void depositar(long int *saldo, long int valor) {
  *saldo += valor;
}

// O problema de concorrência ocorre quando duas ou mais
// threads tentam acessar a mesma variável ao mesmo tempo.
// para resolver esse problema, utilizamos o conceito de
// Exclusão Mútua.

// Exclusão Mútua é um mecanismo que garante que apenas
// uma thread por vez possa acessar uma determinada
// variável.

// A parte do código que deve ser executada por apenas
// uma thread por vez é chamada de Região Crítica.

// Função utilizada para aumentar o valor de uma variável.
// Aqui foi usada duas primitivas de exclusão mútua:
// enter e leave.
// enter: bloqueia o acesso de outras threads a região crítica.
// leave: libera o acesso de outras threads a região crítica.
void depositarComExcMutua(long conta, long int *saldo, long int valor) {
  enter(conta);
  *saldo += valor;
  leave(conta);
}

// Para que seja possível a criação das primitivas de exclusão mútua
// é necessário seguir alguns critérios como:
// 1) A região crítica deve ser acessada apenas por uma thread por vez.
// 2) A thread que aguarda para acessar a região crítica deve ter seu 
//    acesso garantido em um limite de tempo finito.
// 3) A decisão do uso da região crítica deve ser feita somente pelas
//    threads que estão aguardando para acessá-la.
// 4) Deve haver independência de fatores físicos.
// Ou seja, exlcusão mútua (1), espera limitada (2), independência entre
// threads (3) e independência de fatores físicos (4).

// As primitivas descritas no código fn_prog0001a.c não funcionam devido
// a atribuição de valores a variável busy e seu teste são feitos em
// momentos diferentes, o que pode causar uma condição de corrida ou disputa.
// Outro erro é que o teste da variável busy é feito continuamente, o que pode
// causar o que chamamos de espera ocupada (busy wait).

// As primitivas descritas no código fn_prog0001b.c não funcionam devido
// a não possuir independência entre as tarefas. Se uma das tarefas não desejar
// acessar a região crítica, ela não poderá passar o acesso para a próxima tarefa.
// Ou seja, há a independência de fatores externos e há a exclusão mútua, mas 
// não há a espera limitada e nem a independência entre as threads.

// As primitivas descritas no código fn_prog0001c.c são uma solução para o problema
// de concorrência. Elas possuem a exclusão mútua, a espera limitada, a independência
// entre as threads e a independência de fatores externos.

// OBSERVAÇÕES IMPORTANTES:
// 1) Há como fazer primitivas usando operações atômicas, mas isso não é garantido
// em todas as arquiteturas. Instruções como a TSL (Test and Set Lock) e a XCHG
// (Exchange) são instruções atômicas que são executadas pelo processador.
// 2) Todas as soluções apresentadas apresentam ineficiência, injustiça (a não ser
// a solução de alternância de uso).
// 3) Busy wait não otimiza o uso do processador.