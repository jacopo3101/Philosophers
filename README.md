# Philosophers

## Score
![project score](/assets/score.png)

## Introduction

The Philosophers Multithreading Project is an implementation of the classic dining philosophers problem using multithreading in the C programming language. The project explores the concepts of concurrency, thread management, and synchronization using mutexes.

## Overview

The project simulates a scenario where a group of philosophers sit at a round table and alternates between eating, thinking, and sleeping. Each philosopher is represented as a thread, and they must share a fixed number of forks placed between them on the table. To prevent conflicts and ensure proper synchronization, mutexes are used to control access to the forks and prevent deadlocks.

## Features

- Each philosopher is implemented as a separate thread.
- Mutexes are used to control access to shared resources such as forks.
- Proper synchronization techniques are employed to prevent deadlocks and race conditions.
- The program takes command-line arguments to specify the number of philosophers, time constraints for eating, sleeping, and thinking, and the optional number of times each philosopher must eat before the simulation ends.

## Usage

To compile the program, use the provided Makefile:

```bash
make
```

To run the program, execute the compiled binary with the required command-line arguments:

```bash
./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]
```