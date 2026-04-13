*Este projeto foi criado como parte da 42 por ilemos-c, csuomins.*

## Description

Minishell is a simple shell implementation inspired by bash. The project explores process management, file descriptors, signal handling, and command parsing. It supports command execution, pipes, redirections, environment variable expansion, and several built-in commands.

## Instructions

**Requirements:** gcc, make, readline library

**Compilation:**
```bash
make
```

**Run:**
```bash
./minishell
```

**Clean:**
```bash
make clean   # removes object files
make fclean  # removes object files and binary
make re      # full recompilation
```

## Resources

**References:**
- [Bash manual](https://www.gnu.org/software/bash/manual/bash.html) — used as the main reference for shell behavior
- [readline documentation](https://tiswww.case.edu/php/chet/readline/rltop.html) — for interactive input handling
- [Unix man pages](https://man7.org/linux/man-pages/) — for system calls (fork, execve, pipe, dup2, etc.)

**AI usage:**

AI tools were used to support content research, subject exploration, debugging assistance, and test creation. All suggestions were reviewed and validated by the team before being applied. AI was used strictly as a support tool to complement our understanding, not to replace it.