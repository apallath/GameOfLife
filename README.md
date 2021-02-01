# Game of Life

C++ implementation of Conway's Game of Life, with OpenMP and MPI parallelization (TODO).

## Status

[![Actions Status](https://img.shields.io/github/workflow/status/apallath/GameOfLife/CMake)](https://github.com/apallath/GameOfLife/actions)
[![Open Issues](https://img.shields.io/github/issues-raw/apallath/GameOfLife)](https://github.com/apallath/GameOfLife/issues)
[![Closed Issues](https://img.shields.io/github/issues-closed-raw/apallath/GameOfLife)](https://github.com/apallath/GameOfLife/issues)

## Requirements
- [Boost C++ Libraries](https://www.boost.org/)

## Building from source
Generate makefiles and build using CMake by running the build bash script:

```sh
./build.sh
```

## Usage
To run a simulation:

```sh
./GameOfLife path/to/config/file
```

# Examples:

![](acorn.gif)
(Acorn)

![](pulsar.gif)
(Pulsar)

Configuration files for both these examples are in the `examples/` directory.

## Testing
To run integration tests run

```sh
ctest
```

in the build directory.

To view test output, run ctest in verbose mode:

```sh
ctest -VV
```
