# agu_dtl

## Run the tests locally

The software simulator tests run on a Linux host with a C++17 compiler,
GNU Make, Flex, and Bison 3.0 or newer. On Ubuntu or Debian, install them with:

```sh
sudo apt-get install build-essential flex bison
```

From the root of your DTL checkout:

```sh
make test-run
```

This builds and runs `tests/software_sim_test` using `g++`. It needs no FireSim
checkout, RISC-V toolchain, DTU hardware, or runtime driver submodule. A failed
test returns a nonzero exit status. To select another host compiler:

```sh
make test-run CXX_X86=clang++
```

To build and run `tests/example.cpp` separately:

```sh
make example-run
```

This uses the same host compiler and builds the executable at `tests/example`.

Add simulator tests in `tests/software_sim_test.cpp`. To rebuild from scratch:

```sh
make -C src clean
make test-run
```
