/*
 * CXXFLAGS=-march=native -O3 -std=<c|gnu>++23 -mfpmath=<your SIMD implementation>
 * compatible with every compiler and any SIMD platform.
 * Based on aligned vector type using cstdout not iostream.
 */
#include "vec.hpp"

using f32   = float;
using f32x4 = vec<f32,4>;

int main(int argc, char** argv)
{
    f32x4 a = { 0,1,2,3 };

    exit(print_test(a,b) ? EXIT_SUCCESS : EXIT_FAILURE);
}

inline constexpr bool print_test(f32x2 a, f32x2 b)
{
    a.print(); fputs(" + ", stdout); b.print(); fputs(" = ", stdout);
    (a + b).println();
    a.print(); fputs(" - ", stdout); b.print(); fputs(" = ", stdout);
    (a - b).println();

    a.print(); fputs(" * 3                              = ", stdout);
    (a * 3.0f).println();
    b.print(); fputs(" / 2.5                            = ", stdout);
    (b / 2.5f).println();
    return true;
}
