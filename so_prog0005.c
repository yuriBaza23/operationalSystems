// Assunto: Troca de mensagens

// Os processos podem se comunicar através de troca de mensagens
// sem o uso de variáveis compartilhadas.

// Para isso há duas operações básicas:
// send(mensagem): envia uma mensagem de tamanho fixo ou variável.
// receive(mensagem): recebe uma mensagem de tamanho fixo ou variável.
// Não avança até que receba a mensagem.

// Se P e Q querem se comunicar, eles precisam:
// 1. Estabelecer uma conexão de comunicação. -> enlace(link)
// 2. Trocar mensagens através da conexão estabelecida por meio de send e receive.