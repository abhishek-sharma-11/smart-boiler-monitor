# Smart Boiler Monitor

A multithreaded industrial boiler monitoring simulator built in C using POSIX threads on Linux.

## Features

* Real-time boiler temperature monitoring
* Steam pressure monitoring
* Multithreading using pthreads
* Mutex synchronization
* Emergency shutdown system
* Alert logging system
* Colored terminal dashboard

## Technologies Used

* C Programming
* POSIX Threads (pthreads)
* Linux
* GCC Compiler

## How to Run

Compile the program:

```bash
gcc boiler_monitor.c -o boiler_monitor -pthread
```

Run the program:

```bash
./boiler_monitor
```

## Project Output

The system continuously monitors:

* boiler temperature
* steam pressure

and triggers emergency shutdown when safety limits are exceeded.

## Concepts Used

* Multithreading
* Mutex locks
* Shared resources
* Thread synchronization
* Industrial monitoring simulation
* Linux terminal programming
