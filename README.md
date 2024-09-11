# The Shortest Vector Problem (SVP)

## Overview

This project implements a solution to the Shortest Vector Problem (SVP) in the domain of lattice-based cryptography, as part of my second year Durham Computer Science module, Systems Programming. SVP is a critical problem in computational mathematics, cryptography, and post-quantum cryptography, where the goal is to find the shortest non-zero vector within a lattice structure in n-dimensional Euclidean space.

## Getting Started

### Prerequisites

- Linux environment (Ubuntu 22.04 recommended)
- GCC for C compilation

### Installation & Compilation

1. Clone the repository:

    ```bash
    git clone <repo-url>
    cd svp
    ```

2. Compile the program using the provided Makefile:

    ```bash
    make all
    ```

### Usage

Run the executable with basis vectors as input:

```bash
./runme [1.0 0.0 0.0] [0.0 1.0 0.0] [0.0 0.0 1.0]
```

The program will output the Euclidean norm of the shortest vector and save the result in `result.txt`.

### Testing

Use the following command to run the test cases:

```bash
make test
```

### Cleaning

To clean the compiled files:

```bash
make clean
```

## Future Enhancements

- Implementation of advanced lattice reduction techniques.
- Support for larger, complex lattice structures.
