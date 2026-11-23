#include "software_sim.hpp"

#include <algorithm>
#include <functional>
#include <iostream>
#include <limits>
#include <string>
#include <vector>
#include <vector>
#include <numeric>
#include <stdint.h>

const static std::string col_sel_kernel = R"(
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
)";


int main()
{
    uint64_t row_count = 10000;
    uint64_t column_count = 100;
    int* table = new int[row_count*column_count];
    std::vector<int> columns_of_interest = {4,33,77,99};
    /*
        We will pre-init the table
    */
    for (int i = 0; i < row_count; i++)
    {
        for (int j = 0; j < column_count; j++)
        {
            table[i*column_count + j] = j;
        }
    }


    /*
        Just pass in the kernel that you want to use
    */
    DTL::DTUSimulatedView<int32_t> view(col_sel_kernel);

    /*
        By default the simulator will go ahead and allocate a backing region,
        but we can replace it with our own using this call.
    */
    view.SwapBackingStore(table);



    /*
        We can now iterate over the declared logical object, and ensure that
        we get back the correct data
    */
    for (int row = 0; row < row_count; row++)
    {
        for (int col = 0; col < columns_of_interest.size(); col++)
        {
            int read_val = view[row*columns_of_interest.size() + col];
            assert(read_val == columns_of_interest[col]);
        }
    }

    printf("Example.cpp passes\n");




    return 0;
}