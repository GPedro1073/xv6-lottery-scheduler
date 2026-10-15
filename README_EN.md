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

## How to Run

The project requires a RISC-V toolchain and QEMU.

Start xv6 with one virtual CPU:

```bash
make qemu CPUS=1
```

Inside xv6, run:

```text
lotterytest
```

Or run the three-process test:

```text
lottery3
```

To exit QEMU, press `Ctrl + A`, release both keys, and press `X`.

## Test Results

Several tests were performed using different ticket distributions.

### Three-Process Test

| Process | Tickets | Operations |
|---|---:|---:|
| A | 10 | 1,178,090,000 |
| B | 30 | 3,501,700,000 |
| C | 60 | 5,418,330,000 |

The results showed that processes with more tickets generally performed more operations during the test interval.

Additional tests were performed using two processes and invalid ticket values.

These measurements provide initial evidence of proportional scheduling behavior but do not guarantee exact CPU distribution under all conditions.

## Known Limitations

The implementation was tested using one and two virtual CPUs. Further improvements to synchronization and concurrency handling may be necessary for greater robustness.

## Credits and Acknowledgments

xv6 is an educational operating system developed by MIT.

This repository contains an academic adaptation of xv6 and retains the original project's credits and license.

AI tools were used to assist with technical guidance, code implementation, debugging, and understanding operating system concepts. The implementation was also compiled and tested during development.
