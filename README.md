# Pipex

 A small Unix piping utility (42-school style project).

 This repository implements `pipex`, a tiny program that mimics a simplified shell pipeline: it executes two or more commands and connects them with pipes, taking input from a file (or a here-document for the bonus) and writing the final output to a file.

 ## What this project does

 - Runs commands connected by pipes, using an input file and an output file.
 - Implements a bonus `here_doc` mode (see below) that reads from standard input until a limiter is reached.
 - Uses the included `libft` library (the Makefile builds it automatically).

 ## Requirements

 - A C compiler (the Makefile uses `clang` but `gcc` should work if available).
 - Make (the repository includes a `Makefile`).
 - A POSIX-like environment (Linux, macOS, WSL).

## Cloning the repository

This project includes an external library under `lib/libft` which is tracked as a Git submodule in the repository layout. When cloning the repo you should fetch submodules as well so the build succeeds. Use:

```
git clone --recursive <repo_url>
```

If you already cloned without `--recursive`, run:

```
git submodule update --init --recursive
```

This will ensure the `libft` sources are present for the `make` step.

 ## Building

 From the project root run:

 ```
 make
 ```

 This builds the mandatory `pipex` executable. The Makefile will also build the `libft` static library in `lib/libft` as needed.

 To build the bonus version (which replaces the mandatory binary with the bonus behavior), run:

 ```
 make bonus
 ```

 ## Usage

 Basic mandatory usage (two commands example):

 ```
 ./pipex infile "cmd1 [args]" "cmd2 [args]" outfile
 ```

 Examples:

 ```
 ./pipex infile "grep hello" "wc -l" outfile
 # Equivalent shell pipeline: < infile grep hello | wc -l > outfile

 ./pipex infile "cat" "sort -r" outfile
 ```

 Notes:
 - Commands must be provided as quoted strings so the program can parse each command and its arguments.
 - The program resolves commands using the environment `PATH`.

 ## Bonus: here_doc mode

 When built with the bonus target, `pipex` supports a here-document mode. The usage is:

 ```
 ./pipex here_doc LIMITER "cmd1" "cmd2" outfile
 ```

 Behavior:
 - The program reads from standard input until a line matching `LIMITER` is read.
 - The collected input is fed into the first command in the pipeline.

 Example:

 ```
 ./pipex here_doc EOF "tr a-z A-Z" "wc -c" outfile
 ```

 Type input lines, and finish by typing a line containing exactly `EOF` on its own line.