# XV6 Lottery Scheduler

[🇧🇷 Português](README.md) | [🇺🇸 English](README_EN.md)

## About the Project

This project implements a **Lottery Scheduler** in xv6, an educational operating system originally developed by MIT.

The objective is to replace the default Round-Robin scheduler with a probabilistic scheduling algorithm in which each process receives a number of tickets that determines its probability of being selected to use the CPU.

The project was developed as an academic assignment for an Operating Systems course.

## Technologies

- C Programming Language
- xv6 (RISC-V)
- Ubuntu 24.04 with WSL 2
- QEMU
- Git and GitHub

## Implemented Features

- Ticket storage for each process.
- Default ticket allocation for newly created processes.
- Ticket inheritance from parent to child processes using `fork()`.
- Custom `settickets(int number)` system call.
- Pseudorandom number generation using a Linear Congruential Generator (LCG).
- Ticket-based probabilistic process selection.
- Test programs to evaluate CPU scheduling behavior.

## How It Works

The scheduler iterates through all processes in the `RUNNABLE` state and calculates the total number of tickets.

It then generates a pseudorandom number and iterates through the process table again, accumulating tickets until the winning process is identified.

Processes with more tickets have a higher probability of being selected.

## Dependencies and build

On Ubuntu 24.04, install any missing tools. The Makefile requires QEMU 7.2 or later.

```bash
sudo apt update
sudo apt install git build-essential gcc-riscv64-linux-gnu binutils-riscv64-linux-gnu qemu-system-misc perl bc
git clone https://github.com/GPedro1073/xv6-lottery-scheduler.git
cd xv6-lottery-scheduler
make kernel/kernel fs.img
make qemu CPUS=1
```

The kernel gives newly allocated processes 10 tickets. Children inherit their parent's tickets through `fork()`. The `settickets(n)` system call updates the current process's tickets and returns `-1` when `n < 1`.

## xv6 tests

At the xv6 prompt, run `lotterytest` and `lottery3` in sequence. To exit QEMU, press `Ctrl+A` and then `X`.

- `lotterytest` should print `PASSOU` for 0 and -5 tickets. The two processes with 50 tickets should complete similar numbers of operations.
- `lottery3` uses 30, 25, and 90 tickets. Expected lottery win shares are 20.7%, 17.2%, and 62.1% while all three processes are runnable.

Use one virtual CPU so the processes compete for the same core. Repeat the test and compare the raw operation counts. The distribution is probabilistic, and the ratios printed by the programs use integer division.

### Historical result

One run recorded during development used the earlier 10, 30, and 60 ticket configuration.

| Process | Tickets | Operations |
|---|---:|---:|
| A | 10 | 1,178,090,000 |
| B | 30 | 3,501,700,000 |
| C | 60 | 5,418,330,000 |

## Limitations

The project was exercised during development with one and two virtual CPUs. With multiple CPUs, the set of runnable processes can change between summing tickets and selecting a winner.

## Credits and Acknowledgments

xv6 is an educational operating system developed by MIT.

This repository contains an academic adaptation of xv6 and retains the original project's credits and license.

AI tools were used to assist with technical guidance, code implementation, debugging, and understanding operating system concepts. The implementation was also compiled and tested during development.
