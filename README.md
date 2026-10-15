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

## Como executar

O projeto utiliza a arquitetura RISC-V e requer as ferramentas de compilação apropriadas, além do QEMU.

Para iniciar o XV6 com uma CPU virtual:

```bash
make qemu CPUS=1
```

Dentro do XV6, execute:

```bash
lotterytest
```

Ou, para testar três processos:

```bash
lottery3
```

Para sair do QEMU, pressione `Ctrl + A`, solte e pressione `X`.

## Resultados dos testes

Foram realizados testes com diferentes quantidades de tickets.

### Teste com três processos

| Processo | Tickets | Operações realizadas |
|---|---:|---:|
| A | 10 | 1.178.090.000 |
| B | 30 | 3.501.700.000 |
| C | 60 | 5.418.330.000 |

Os resultados demonstraram que os processos com mais tickets realizaram mais operações durante o intervalo de teste.

Também foram realizados testes com dois processos e com valores inválidos na chamada `settickets()`.

Os testes representam uma avaliação inicial do escalonador, não uma garantia de distribuição exata de CPU em todas as condições.

## Limitações

A implementação foi validada em cenários acadêmicos com uma e duas CPUs virtuais. Ainda existem pontos de sincronização e concorrência que podem ser aprimorados para garantir maior robustez.

## Créditos

O XV6 é um sistema operacional educacional desenvolvido pelo MIT.

Este repositório contém uma adaptação acadêmica do XV6, preservando os créditos e a licença do projeto original.

O desenvolvimento contou com auxílio de ferramentas de inteligência artificial para orientação técnica, implementação assistida e depuração, além de testes práticos realizados durante a construção do projeto.
