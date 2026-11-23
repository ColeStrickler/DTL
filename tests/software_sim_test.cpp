#include "software_sim.hpp"

#include <algorithm>
#include <functional>
#include <iostream>
#include <limits>
#include <string>
#include <vector>
#include <vector>
#include <numeric>
using Element = uint32_t;
using SimView = DTL::DTUSimulatedView<Element>;

// expected contains one known-good value for each logical index to read, starting
// at zero. initialize can populate child backing buffers or external metadata.
// Exceptions and mismatches are failures, including unimplemented simulator code.
bool RunTest(const std::string& name,
             const std::string& kernel,
             const std::vector<Element>& backing,
             const std::vector<Element>& expected,
             const std::function<void(SimView&)>& initialize = {})
{
    std::string stage = "constructing view";
    try {
        if (expected.empty())
            throw std::invalid_argument("expected output must not be empty");
        if (expected.size() > uint64_t(std::numeric_limits<uint32_t>::max()) + 1)
            throw std::invalid_argument("expected output exceeds the simulator index range");

        SimView view(kernel);
        stage = "initializing backing buffers";
        if (backing.size() > view.GetBackingSize() / sizeof(Element))
            throw std::invalid_argument("input backing data exceeds the kernel's declared byte size");
        std::copy(backing.begin(), backing.end(), view.GetBackingRegion());
        if (initialize)
            initialize(view);

        std::size_t mismatches = 0;
        for (std::size_t i = 0; i < expected.size(); ++i) {
            stage = "reading logical index " + std::to_string(i);
            const Element actual = view[static_cast<uint32_t>(i)];
            if (actual != expected[i]) {
                std::cerr << "[FAIL] " << name << " index " << i
                          << ": expected " << +expected[i]
                          << ", got " << +actual << '\n';
                ++mismatches;
            }
        }

        if (mismatches != 0) {
            std::cerr << "[FAIL] " << name << ": " << mismatches << " / "
                      << expected.size() << " values differ\n";
            return false;
        }
        std::cout << "[PASS] " << name << " (" << expected.size() << " values)\n";
        return true;
    } catch (const std::exception& error) {
        std::cerr << "[FAIL] " << name << " while " << stage
                  << ": " << error.what() << '\n';
        return false;
    }
}

bool RunBoundsTest(const std::string& name, const std::function<void()>& read)
{
    try {
        read();
        std::cerr << "[FAIL] " << name << ": expected out_of_range\n";
    } catch (const std::out_of_range&) {
        std::cout << "[PASS] " << name << '\n';
        return true;
    } catch (const std::exception& error) {
        std::cerr << "[FAIL] " << name << ": " << error.what() << '\n';
    }
    return false;
}

int main()
{
    // Add tests here: DTL source, backing values, and independently known output.
    // DTL<N> declares backing bytes; RunTest compares element values via view[i].
    // Build and run from the DTL repository root: make test-run
    unsigned passed = 0;
    unsigned total = 0;

    const std::string strideKernel = R"(
DTL<32> stride = {
    for (int i = 0; i < 4; i++) {
        out = 2 * i;
    }
}
active stride;
)";
    ++total;
    passed += RunTest("stride by two", strideKernel,
                      {100, 101, 102, 103, 104, 105, 106, 107},
                      {100, 102, 104, 106});

    const std::string nestedKernel = R"(
DTL<32> indices = {
    for (int i = 0; i < 4; i++) {
        out = 2 * i;
    }
}
DTL<16> gather : indices = {
    metadata_stream<4, indices> selected;
    for (int i = 0; i < 4; i++) {
        out = selected[i];
    }
}
active gather;
)";
    ++total;
    passed += RunTest("nested gather", nestedKernel,
                      {10, 20, 30, 40}, {40, 20, 30, 10},
                      [](SimView& view) {
                          // indices[i] loads 3, 1, 2, 0 from its backing buffer.
                          const std::vector<Element> indices = {3, 99, 1, 99, 2, 99, 0, 99};
                          auto& child = view.GetDependency("indices");
                          if (indices.size() > child.GetBackingSize() / sizeof(Element))
                              throw std::invalid_argument("child backing data is too large");
                          std::copy(indices.begin(), indices.end(), child.GetBackingRegion());
                          // External metadata can also be initialized here using
                          // GetMetadataRegion(name) and GetMetadataRegionSize(name).
                      });

    ++total;
    passed += RunTest("constant scalar and array", R"(
DTL<32> lookup = {
    int step = 2;
    int offsets = {3, 1, 0, 2};
    for (int i = 0; i < 4; i++) { out = step * offsets[i]; }
}
active lookup;
)", {100, 101, 102, 103, 104, 105, 106, 107}, {106, 102, 100, 104});

    // Exercise byte widths and unsigned values above the range of smaller widths.
    const std::vector<std::vector<unsigned char>> metadataBytes = {
        {2, 0, 3, 1},
        {2, 1, 0, 1, 3, 1, 1, 1},
        {2, 0, 0, 128, 0, 0, 0, 128, 3, 0, 0, 128, 1, 0, 0, 128}
    };
    // The parser accepts signed 32-bit literals; subtract 2^30 twice for width 4.
    const std::vector<uint32_t> bases = {0, 256, 1073741824u};
    for (size_t test = 0; test < metadataBytes.size(); ++test) {
        const unsigned width = 1u << test;
        const std::string program =
            "DTL<16> external = { metadata_stream<" + std::to_string(width) +
            ", " + std::to_string(metadataBytes[test].size()) + "> selected; "
            "int base = " + std::to_string(bases[test]) + "; "
            "for (int i = 0; i < 4; i++) { out = selected[i] - base" +
            (width == 4 ? " - base" : "") + "; } } active external;";
        ++total;
        passed += RunTest("external metadata width " + std::to_string(width), program,
                          {10, 20, 30, 40}, {30, 10, 40, 20}, [&](SimView& view) {
                              std::copy(metadataBytes[test].begin(), metadataBytes[test].end(),
                                        view.GetMetadataRegion("selected"));
                          });
    }

    const std::string chainKernel = R"(
DTL<16> leaf = {
    int factor = 2;
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) { out = j * factor + i; }
    }
}
DTL<16> middle : leaf = {
    metadata_stream<4, leaf> data;
    for (int i = 0; i < 4; i++) { out = data[i]; }
}
DTL<16> root : middle = {
    int factor = 1;
    metadata_stream<4, middle> data;
    for (int i = 0; i < 4; i++) { out = data[i] + i * factor; }
}
active root;
)";
    ++total;
    passed += RunTest("three levels with independent coordinates", chainKernel,
                      {10, 20, 30, 40}, {30, 30, 40, 40}, [](SimView& view) {
                          const std::vector<Element> leaf = {2, 0, 3, 1};
                          const std::vector<Element> middle = {1, 0, 2, 1};
                          std::copy(leaf.begin(), leaf.end(), view.GetDependency("leaf").GetBackingRegion());
                          std::copy(middle.begin(), middle.end(), view.GetDependency("middle").GetBackingRegion());
                      });

    ++total;
    passed += RunBoundsTest("logical bounds", [&] {
        SimView view(strideKernel);
        (void)view[4];
    });
    ++total;
    passed += RunBoundsTest("backing bounds", [&] {
        SimView view(nestedKernel);
        view.GetDependency("indices").GetBackingRegion()[0] = 4;
        (void)view[0];
    });
    ++total;
    passed += RunBoundsTest("external metadata bounds", [] {
        SimView view(R"(
DTL<16> small = {
    metadata_stream<4, 4> data;
    for (int i = 0; i < 4; i++) { out = data[i]; }
}
active small;
)");
        (void)view[1];
    });
    ++total;
    passed += RunBoundsTest("nested view logical bounds", [] {
        SimView view(R"(
DTL<16> small = {
    for (int i = 0; i < 1; i++) { out = i; }
}
DTL<16> root : small = {
    metadata_stream<4, small> data;
    for (int i = 0; i < 4; i++) { out = data[i]; }
}
active root;
)");
        (void)view[1];
    });



    uint32_t dim = 100;
    std::vector<Element> matrix(dim*dim);
    std::vector<Element> matrix_transposed(dim*dim);
    for (int i = 0; i < dim*dim; i++)
        matrix[i] = i;

    int x = 0;
    for (int col = 0; col < dim; col++)
        for (int row = 0; row < dim; row++)
            matrix_transposed[x++] = matrix[row*dim + col];


    std::string transpose_kernel = R"(
        DTL<40000> transpose = {
            for (int col = 0; col < 100; col++){
               for (int row = 0; row < 100; row++)
               {
                    out = row*100 + col;
               }
            }
        }
        active transpose;
    )";

    passed += RunTest("transpose_test", transpose_kernel, matrix, matrix_transposed);
    total++;


    std::string rev_kernel = R"(

        DTL<400> rev = {
            metadata_stream<4, 400> data;
            for (int i = 0; i < 100; i++){
                out = data[i];
            }
        }
        active rev;
    )";



    std::vector<uint32_t> base_Rev(100);
    std::vector<uint32_t> rev(100);

    std::iota(base_Rev.begin(), base_Rev.end(), 0);  // 0 to 99
    std::iota(rev.rbegin(), rev.rend(), 0);            // 99 to 0
    passed += RunTest("rev_test", rev_kernel, base_Rev, rev, [](SimView& view) {
        int x = 0;
        for (int i = 99; i >= 0; i--)
        {
            view.WriteMetadata("data", x, i);
            x++;
        }
    });
    total++;



    /*
        We need to test some metadata kernels

        and more nested kernels
    */


    {
        int channels_in = 2;
        int ksize = 3;
        int height = 400;
        int width = 500;
        int stride = 1;
        int pad = 0;

        int out_height = (height + 2 * pad - ksize) / stride + 1;
        int out_width = (width + 2 * pad - ksize) / stride + 1;
        uint32_t in_data_size = height * width * channels_in;
        uint32_t im2col_matsize =
            channels_in * (height - ksize + 1) * (width - ksize + 1) * ksize * ksize;
        std::vector<Element> in_data(in_data_size);
        std::vector<Element> im2col_cpu_matrix(im2col_matsize);
        std::iota(in_data.begin(), in_data.end(), 0);

        // CPU reference from im2col_cpu, with stride = 1 and pad = 0.
        for (int c = 0; c < channels_in * ksize * ksize; ++c) {
            int w_offset = c % ksize;
            int h_offset = (c / ksize) % ksize;
            int c_im = c / ksize / ksize;
            for (int h = 0; h < out_height; ++h) {
                for (int w = 0; w < out_width; ++w) {
                    int im_row = h_offset + h * stride;
                    int im_col = w_offset + w * stride;
                    int col_index = (c * out_height + h) * out_width + w;
                    im2col_cpu_matrix[col_index] = in_data[im_col + width*(im_row + height*c_im)];
                }
            }
        }

        // Same stencil as bench_wrapper_im2col, with hardcoded parameters.
        std::string im2col_kernel = R"(
        DTL<1600000> kernel = {
            int height = 400;
            int width = 500;
            int data_size = 4;
                for (int c_im = 0; c_im < 2; c_im++) {
                    for (int kh = 0; kh < 3; kh++) {
                        for (int kw = 0; kw < 3; kw++) {
                            for (int h = 0; h < 398; h++) {
                                for (int w = 0; w < 498; w++) {
                                    out = c_im*(height*width) + (h + kh)*(width) + (w + kw);
                                }
                            }
                        }
                    }
                }
        }
        active kernel;
        )";

        passed += RunTest("im2col_test", im2col_kernel, in_data, im2col_cpu_matrix);
        total++;
    }

    std::cout << passed << " / " << total << " tests passed\n";
    return passed == total ? 0 : 1;
}
