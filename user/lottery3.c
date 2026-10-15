#include "kernel/types.h"
#include "user/user.h"

#define N 3
#define DURACAO 300

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

  int inicio = uptime();

  while(uptime() - inicio < DURACAO) {
    for(int j = 0; j < 10000; j++) {
      contador++;
    }
  }

  r.tickets = tickets;
  r.contador = contador;

  if(write(fd, &r, sizeof(r)) != sizeof(r)) {
    printf("Erro ao enviar resultado\n");
    exit(1);
  }

  close(fd);
  exit(0);
}

int
main(void)
{
  int tickets[N] = {10, 30, 60};
  int pipes[N][2];
  int filhos[N];
  struct resultado resultados[N];

  for(int i = 0; i < N; i++) {
    if(pipe(pipes[i]) < 0) {
      printf("Erro ao criar pipe\n");
      exit(1);
    }
  }

  for(int i = 0; i < N; i++) {
    filhos[i] = fork();

    if(filhos[i] < 0) {
      printf("Erro ao criar filho\n");
      exit(1);
    }

    if(filhos[i] == 0) {
      for(int j = 0; j < N; j++) {
        close(pipes[j][0]);

        if(j != i)
          close(pipes[j][1]);
      }

      trabalhar(tickets[i], pipes[i][1]);
    }
  }

  for(int i = 0; i < N; i++)
    close(pipes[i][1]);

  for(int i = 0; i < N; i++) {
    int recebido = read(pipes[i][0],
                        &resultados[i],
                        sizeof(struct resultado));

    if(recebido != sizeof(struct resultado)) {
      printf("Erro ao receber resultado\n");
      exit(1);
    }

    close(pipes[i][0]);
  }

  for(int i = 0; i < N; i++)
    wait(0);

  printf("\n===== LOTERIA COM 3 PROCESSOS =====\n");

  for(int i = 0; i < N; i++) {
    printf("Processo %d: %d tickets\n",
           i + 1, resultados[i].tickets);

    printf("Operacoes: %ld\n\n",
           resultados[i].contador);
  }

  uint64 a = resultados[0].contador;

  if(a > 0) {
    printf("Proporcao B/A: %ld vezes\n",
           resultados[1].contador / a);

    printf("Proporcao C/A: %ld vezes\n",
           resultados[2].contador / a);
  }

  printf("==================================\n");

  exit(0);
}
