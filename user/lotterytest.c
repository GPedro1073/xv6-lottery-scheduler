#include "kernel/types.h"
#include "user/user.h"

struct resultado {
  int tickets;
  uint64 contador;
};

void
trabalhar(int tickets, int fd)
{
  struct resultado r;
  volatile uint64 contador = 0;

  if(settickets(tickets) < 0) {
    printf("Erro ao definir tickets\n");
    exit(1);
  }

  r.tickets = tickets;

  // Executa trabalho durante 300 ticks
  int inicio = uptime();

  while(uptime() - inicio < 300) {
    for(int i = 0; i < 10000; i++) {
      contador++;
    }
  }

  r.contador = contador;

  write(fd, &r, sizeof(r));
  close(fd);

  exit(0);
}

int
main(void)
{

  printf("Testando valores invalidos...\n");

  if(settickets(0) == -1)
    printf("PASSOU: 0 tickets rejeitado\n");
  else
    printf("FALHOU: 0 tickets aceito\n");

  if(settickets(-5) == -1)
    printf("PASSOU: -5 tickets rejeitado\n");
  else
    printf("FALHOU: -5 tickets aceito\n");

  int pipeA[2];
  int pipeB[2];

  if(pipe(pipeA) < 0 || pipe(pipeB) < 0) {
    printf("Erro ao criar pipes\n");
    exit(1);
  }

  int pidA = fork();

  if(pidA < 0) {
    printf("Erro ao criar processo A\n");
    exit(1);
  }

  if(pidA == 0) {
    close(pipeA[0]);
    close(pipeB[0]);
    close(pipeB[1]);

    trabalhar(50, pipeA[1]);
  }

  int pidB = fork();

  if(pidB < 0) {
    printf("Erro ao criar processo B\n");
    kill(pidA);
    exit(1);
  }

  if(pidB == 0) {
    close(pipeB[0]);
    close(pipeA[0]);
    close(pipeA[1]);

    trabalhar(50, pipeB[1]);
  }

  close(pipeA[1]);
  close(pipeB[1]);

  struct resultado a, b;

  read(pipeA[0], &a, sizeof(a));
  read(pipeB[0], &b, sizeof(b));

  close(pipeA[0]);
  close(pipeB[0]);

  wait(0);
  wait(0);

  printf("\n===== RESULTADO DA LOTERIA =====\n");

  printf("Processo A: %d tickets\n", a.tickets);
  printf("Operacoes A: %ld\n", a.contador);

  printf("\nProcesso B: %d tickets\n", b.tickets);
  printf("Operacoes B: %ld\n", b.contador);

  if(a.contador > 0) {
    int proporcao = (int)(b.contador / a.contador);

    printf("\nProporcao aproximada: %d vezes\n", proporcao);
  }

  printf("===============================\n");

  exit(0);
}
