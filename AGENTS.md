# AGENTS.md

## What this is
A personal C99 learning repository (notes + runnable examples following
wangdoc.com/clang). It is not a shipped product: there are no tests, linters,
formatters, or CI. Don't expect a `test` or `lint` command.

## Build & run
The only verification is compile + run via VS Code's F5 workflow:

- Open the `.c` file you want to run as the active editor tab, then press **F5**.
- `launch.json` builds via `preLaunchTask: cmake: build` and runs the binary at
  `build/<chapter-dir>/<file-basename>` (mirrors the source path).
- Manual build:
  ```
  cmake -S . -G Ninja -B build -DCMAKE_C_COMPILER=gcc -DCMAKE_EXPORT_COMPILE_COMMANDS=ON
  cmake --build build
  ```

## CMake architecture (non-obvious)
- Root `CMakeLists.txt` auto-discovers directories matching `[0-9]*` and
  `add_subdirectory`s any that contain their own `CMakeLists.txt`. A new chapter
  must be named `NN_<name>` and include a `CMakeLists.txt`, or it is ignored.
- Chapter `CMakeLists.txt` files are one-liners that `include()` one of two
  templates in `.cmake/`:
  - `.cmake/mult_exec_template.cmake` — globs every `*.c` in the dir and makes
    each an executable named after the file stem. Files named `utils.c` are
    skipped (not built as standalone executables). Recurses into subdirs that
    have their own `CMakeLists.txt`.
  - `.cmake/sing_proj_template.cmake` — single project with `include/` + `src/`;
    builds one executable from the top-level `.c` file plus all `src/*.c`.
- The executable target name always equals the source file basename.

## Debugging: per-file CLI args
To pass command-line args when debugging a file, put a Doxygen comment in that
file with an `@args` line (see `08_function/function.c`):

    /**
     * @args: --port 8080 --mode "production"
     */

The `rioj7.command-variable` extension reads this and sets gdb args via
`-gdb-set args`. Default is `--help` when the line is absent.

## Environment
- The dev container (Ubuntu noble) runs `.devcontainer/setup.sh` on create,
  installing gdb, cmake, ninja, gcc-multilib, and glibc source (extracted at
  `/usr/src/glibc/glibc-2.39`, used by `launch.json` `sourceFileMap` to step into
  libc). clangd is configured (`--compile-commands-dir=build`) but its install
  step in `setup.sh` is commented out.
- `compile_commands.json` is generated into `build/`; both are gitignored.
- `.vscode/settings.json` contains macOS/OrbStack host-specific paths.
