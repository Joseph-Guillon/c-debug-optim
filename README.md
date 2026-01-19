# C Debug and Optimization Lab

This project is a C programming lab designed to teach debugging and optimization techniques. It implements a simple dataset generator and metrics calculator, with intentional bugs and performance issues for students to identify and fix using various tools.

## Project Structure

- `src/`: Source code files
  - `main.c`: Program entry point
  - `dataset.c`: Dataset generation and management
  - `metrics.c`: Statistical computations
- `include/`: Header files
- `build/`: Build artifacts (created during compilation)
- `bin/`: Executables (created during compilation)

## Building

The project uses a Makefile with multiple build targets for different debugging and profiling purposes:

### Available Targets

- `make debug`: Build with debug symbols for GDB debugging
- `make asan`: Build with AddressSanitizer for memory bug detection
- `make gprof`: Build with gprof profiling support
- `make all`: Show available targets
- `make clean`: Clean build artifacts

### Compilation Flags

- **Release**: Optimized build (`-O2`)
- **Debug**: Unoptimized with debug symbols (`-O0 -g`)
- **ASAN**: Debug build with AddressSanitizer (`-O0 -g -fsanitize=address`)
- **gprof**: Debug build with profiling (`-O0 -g -pg`)

## Running

After building, you can run the executables with different configurations:

### Debug Build
```bash
make debug
./bin/buglab_dbg [n] [repeat]
```

### ASAN Build
```bash
make asan
ASAN_OPTIONS=detect_leaks=1 ./bin/buglab_asan [n] [repeat]
```

### Profiling Build
```bash
make gprof
./bin/buglab_gprof [n] [repeat]
make profile  # View profiling results
```

### Convenience Targets
- `make run_dbg`: Run debug build with default parameters (2000, 3)
- `make run_asan`: Run ASAN build with default parameters (2000, 3)
- `make run_gprof`: Run gprof build with default parameters (4000, 3)

## Program Description

The program generates a synthetic dataset of `n` points with random x,y coordinates, then computes:

1. **Summary Statistics**: Mean and standard deviation for x and y coordinates
2. **Pairwise Score**: A computed metric based on pairwise differences, repeated `repeat` times

### Parameters
- `n`: Number of data points to generate (default: 2000)
- `repeat`: Number of times to repeat the pairwise computation (default: 3)

## Debugging Tools

### GDB (GNU Debugger)
Use the debug build to step through code, inspect variables, and identify logical errors.

```bash
make debug
gdb ./bin/buglab_dbg
```

### AddressSanitizer (ASAN)
Detects memory errors like leaks, buffer overflows, and use-after-free.

```bash
make asan
ASAN_OPTIONS=detect_leaks=1 ./bin/buglab_asan 2000 3
```

### gprof (Profiler)
Analyzes program performance and identifies bottlenecks.

```bash
make gprof
./bin/buglab_gprof 4000 3
gprof ./bin/buglab_gprof gmon.out | less
```

## Learning Objectives

This lab is designed to help you:
- Identify and fix memory management bugs
- Use debugging tools effectively
- Optimize performance bottlenecks
- Understand compilation flags and their impact
- Practice systematic debugging approaches

## Requirements

- GCC compiler
- GNU Make
- GDB (for debugging)

## Notes

- The code contains intentional bugs for educational purposes
- Different build configurations help isolate different types of issues
- Start with small values of `n` for debugging, larger values for profiling