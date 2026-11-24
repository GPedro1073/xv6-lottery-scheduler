# XV6 Lottery Scheduler

[🇧🇷 Português](README.md) | [🇺🇸 English](README_EN.md)

## Sobre o projeto

Este projeto apresenta a implementação de um **Escalonador de Loteria (Lottery Scheduler)** no sistema operacional educacional XV6, desenvolvido originalmente pelo MIT.

O objetivo é substituir o escalonamento Round-Robin por um algoritmo probabilístico, no qual cada processo recebe uma quantidade de tickets que determina sua probabilidade de ser escolhido para utilizar a CPU.

O projeto foi desenvolvido como trabalho acadêmico da disciplina de Sistemas Operacionais.

## Tecnologias utilizadas

- Linguagem C
- XV6 (RISC-V)
- Ubuntu 24.04 com WSL 2
- QEMU
- Git e GitHub

## Funcionalidades implementadas

- Armazenamento da quantidade de tickets em cada processo.
- Inicialização dos processos com tickets padrão.
- Herança de tickets entre processos pai e filho através de `fork()`.
- Implementação da chamada de sistema `settickets(int number)`.
- Geração de números pseudoaleatórios por meio de um LCG.
- Seleção probabilística de processos prontos para execução.
- Programas para testar a distribuição do processamento entre processos.

## Funcionamento

O escalonador percorre os processos no estado `RUNNABLE` e soma seus tickets.

Em seguida, gera um número pseudoaleatório e percorre novamente os processos, acumulando os tickets até identificar o vencedor.

Quanto maior a quantidade de tickets de um processo, maior sua probabilidade de ser escolhido.

## Dependências e compilação

No Ubuntu 24.04, instale as ferramentas se estiverem faltando. O Makefile requer QEMU 7.2 ou superior.

```bash
sudo apt update
sudo apt install git build-essential gcc-riscv64-linux-gnu binutils-riscv64-linux-gnu qemu-system-misc perl bc
git clone https://github.com/GPedro1073/xv6-lottery-scheduler.git
cd xv6-lottery-scheduler
make kernel/kernel fs.img
make qemu CPUS=1
```

O kernel dá 10 tickets a processos recém-alocados. Um filho herda os tickets do pai via `fork()`. A chamada `settickets(n)` altera os tickets do processo atual e retorna `-1` quando `n < 1`.

## Testes no xv6

No prompt do xv6, execute `lotterytest` e `lottery3` em sequência. Para sair do QEMU, pressione `Ctrl+A` e depois `X`.

- `lotterytest` deve imprimir `PASSOU` para 0 e -5 tickets. Os dois processos com 50 tickets devem realizar quantidades semelhantes de operações.
- `lottery3` usa 30, 25 e 90 tickets. Os valores de referência são 20,7%, 17,2% e 62,1% dos sorteios enquanto os três processos estão prontos.

Use uma CPU virtual para que os processos concorram pelo mesmo núcleo. Repita o teste e compare os contadores brutos de operações. A distribuição é probabilística e as razões impressas pelos programas usam divisão inteira.

### Resultado histórico

Uma execução registrada durante o desenvolvimento usou a configuração anterior de 10, 30 e 60 tickets.

| Processo | Tickets | Operações |
|---|---:|---:|
| A | 10 | 1.178.090.000 |
| B | 30 | 3.501.700.000 |
| C | 60 | 5.418.330.000 |

## Limitações

O projeto foi experimentado durante o desenvolvimento com uma e duas CPUs virtuais. Com várias CPUs, o conjunto de processos prontos pode mudar entre a soma dos tickets e a seleção do vencedor.

## Créditos

O XV6 é um sistema operacional educacional desenvolvido pelo MIT.

Este repositório contém uma adaptação acadêmica do XV6, preservando os créditos e a licença do projeto original.

O desenvolvimento contou com auxílio de ferramentas de inteligência artificial para orientação técnica, implementação assistida e depuração, além de testes práticos realizados durante a construção do projeto.
