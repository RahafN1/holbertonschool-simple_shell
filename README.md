# Simple Shell — hsh

A simple UNIX command line interpreter written in C, replicating the behavior of `/bin/sh`.

---

## Description

`hsh` is a simple shell that reads commands from standard input (interactive or non-interactive), searches for them using the `PATH` environment variable, and executes them using `execve`. It was built as part of the Holberton School curriculum to understand how shells work 

---

## How It Works

1. Displays a prompt `($)` in interactive mode.
2. Reads a line of input using `getline`.
3. Tokenizes the line into arguments using `strtok`.
4. Searches for the command in `PATH` directories.
5. Forks a child process and calls `execve` to execute the command.
6. The parent waits for the child to finish, then loops back to step 1.

---

## Usage

### Compilation

```bash
gcc -Wall -Werror -Wextra -pedantic -std=gnu89 *.c -o hsh
```

### Interactive Mode

```bash
$ ./hsh
($) /bin/ls
hsh main.c shell.c
($) exit
$
```

### Non-Interactive Mode

```bash
$ echo "/bin/ls" | ./hsh
hsh main.c shell.c
```

---

## Features

- Executes commands with full path (e.g. `/bin/ls`)
- Searches commands in `PATH` directories
- Handles `exit` built-in
- Handles `env` built-in (prints current environment)
- Works in both interactive and non-interactive mode
- Displays errors matching `/bin/sh` output format

---

## Built-in Commands

| Command | Description |
|---------|-------------|
| `exit` | Exit the shell |
| `env`  | Print the current environment variables |

---

## Files

| File | Description |
|------|-------------|
| `main.c` | Entry point, main loop |
| `shell.c` | Core shell logic |
| `shell.h` | Header file with prototypes and includes |
| `AUTHORS` | List of contributors |
| `README.md` | This file |
| `man_1_simple_shell` | Man page for hsh |

---

## Error Handling

Errors follow the same format as `/bin/sh`, with the program name replaced by `argv[0]`:

```
./hsh: 1: qwerty: not found
```

---

## Requirements

- Ubuntu 20.04 LTS
- GCC with flags: `-Wall -Werror -Wextra -pedantic -std=gnu89`
- No memory leaks
- Betty coding style compliant

---

## Learning Objectives

- How a shell works internally
- What PIDs and PPIDs are
- How `fork`, `execve`, and `wait` work
- How `PATH` is used to resolve commands
- Difference between functions and system calls
- How to manipulate the environment

---

## Authors

Rahaf Alabdalh 
Wasaal Alquaydhb 
