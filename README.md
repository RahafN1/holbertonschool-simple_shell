# Simple Shell (hsh)

A simple UNIX shell written in C as part of our low-level programming projects.

---

## Description

`hsh` is a simple shell that reads commands from standard input (interactive or non-interactive), searches for them using the `PATH` environment variable, and executes them using `execve`. It was built as part of the Holberton School curriculum to understand how shells work.

---

## Installation

Clone the repository:

```bash
git clone https://github.com/RahafN1/holbertonschool-simple_shell.git
cd holbertonschool-simple_shell
```

Compile the project:

```bash
gcc -Wall -Werror -Wextra -pedantic -std=gnu89 *.c -o hsh
```

---

## Requirements

- Ubuntu 20.04 LTS
- GCC with flags: `-Wall -Werror -Wextra -pedantic -std=gnu89`
- No memory leaks
- Betty coding style compliant

---

## How It Works

1. Displays a prompt `($)` in interactive mode.
2. Reads a line of input using `getline`.
3. Tokenizes the line into arguments using `strtok`.
4. Searches for the command in `PATH` directories.
5. Forks a child process and calls `execve` to execute the command.
6. The parent waits for the child to finish, then loops back to step 1.

---

## Examples

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

## Testing

### Interactive Mode

```bash
$ ./hsh
($) /bin/ls
hsh main.c shell.c shell.h
($) /bin/pwd
/home/user/simple_shell
($) exit
$
```

### Non-Interactive Mode

```bash
$ echo "/bin/ls" | ./hsh
hsh main.c shell.c shell.h
$ echo "/bin/pwd" | ./hsh
/home/user/simple_shell
```

### Error Handling

```bash
($) qwerty
./hsh: 1: qwerty: not found
($) /bin/doesnotexist
./hsh: No such file or directory
```

---

## Built-in Commands

| Command | Description |
|---------|-------------|
| `exit` | Exit the shell |
| `env`  | Print the current environment variables |

---

## Error Handling

Errors follow the same format as `/bin/sh`, with the program name replaced by `argv[0]`:

```
./hsh: 1: qwerty: not found
```

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

## Learning Objectives

- How a shell works internally
- What PIDs and PPIDs are
- How `fork`, `execve`, and `wait` work
- How `PATH` is used to resolve commands
- Difference between functions and system calls
- How to manipulate the environment

---

## Authors

- Rahaf Alabdalh
- Wasaal Alquaydhb
