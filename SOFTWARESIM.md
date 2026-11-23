# Getting Started


## Clone the DTL repo and switch to `composability` branch
- git clone https://github.com/ColeStrickler/DTL.git
- cd DTL/
- git fetch origin
- git checkout origin/composability

## Run the tests. All of these should Pass
- make test-run

## Run the Walkthrough
- 
## Architecture
- `test/example.cpp` is a basic example/walkthrough of how to use the software simulator
- `tests/software_sim_test.cpp` contains the basic test suite and more examples
- `src/software_sim.cpp` and `src/software_sim.hpp` contain the actual simulator. 



## DTL Kernel Tutorial
The simulator should support all DTL functionality. So any valid DTL kernel, including composition should work. 

There are many example DTL kernels in `tests/software_sim_test.cpp`, but also another place to check out is https://github.com/ColeStrickler/dtl_benchmarks/blob/composition/src/dtl_stencils.hpp. 


The following will show you how to write a kernel for column selection in a database. This example is given once more in example.cpp but tied to the software simulator.

Imagine we have a backing store like so:
```cpp
    uint64_t row_count = 10000;
    uint64_t column_count = 100;
    int table[row_count][column_count];
```


Now assume that we have a few noncontiguous columns that we want to pack into a dense view
```cpp
    std::vector<uint16_t> columns_of_interest = {4,33,77,99};
```


We can write a DTL kernel that does this:
```cpp
    std::string kernel = R"(
        DTL<0x3D0900> col_sel = {
            int row_count = 10000;
            int column_count = 100;
            int columns_of_interest_count = 4;
            int columns_of_interest = {4,33,77,99};
            for (int row = 0; row < row_count; row++)
            {
                for (int col = 0; col < columns_of_interest_count; col++)
                {
                    out = row*column_count + columns_of_interest[col];
                }
            }
        }

        active col_sel;
    )"
```

We first declare a kernel with a backing positional object size `DTL<0x3D0900> col_sel = {`, where 0x3D0900 = row_count\*col_count\*sizeof(int). The internal allocators will handle these allocations for you. 

Next we declare some constants:
```
    int row_count = 10000;
    int column_count = 100;
    int columns_of_interest_count = 4;
    int columns_of_interest = {4,33,77,99};
```

And then we declare the iteration space:
```
    for (int row = 0; row < row_count; row++)
        for (int col = 0; col < columns_of_interest_count; col++)
```

The iteration space describes the coordinates of the logical object that the programmer will be working with. The size of the logical object is $(\prod_{i=1}^{n} dimension_i) * sizeof(element)$, which will determine the size of the virtual address space and shadow physical address space -- but neither of these are used inside the software simulator. 

The iteration space has some constraints, and cannot accomodate arbitrary computation. However, optimization passes in the compilation pipeline will allow certain things such as constant folding and propagation as seen here. Full details of the semantics of iteration space declaration are given in Section 5.2 of https://dl.acm.org/doi/epdf/10.1145/3845814.3850077. 




Next we declare an out statement. Each out statement is compiled separately, and the max number of out statements supported is restricted by provisioned hardware resources. Most kernels will only need one.

The out statement effectively maps each coordinate to a location in the backing object.

```
    out = row*column_count + columns_of_interest[col];
```


Finally, we set the kernel that we created to active:

```
    active col_sel;
```

This is mostly necessary for composition, which we do not utilize here. 
