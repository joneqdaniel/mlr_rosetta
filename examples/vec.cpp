/*
 * CXXFLAGS=-march=native -O3 -std=<c|gnu>++23 -mfpmath=<your SIMD implementation>
 * compatible with every compiler and any SIMD platform.
 * Based on aligned vector type using cstdout not iostream.
 */
#include "vec.hpp"

using f32   = float;
using f32x2 = vec<f32,2>;

inline bool print_test(f32x2 a, f32x2 b);

int main(int argc, char** argv)
{
    f32x2  a = f32x2{ cosf(  M_PIf/6), sinf(  M_PIf/6) } * 3;
    f32x2  b = f32x2{ cosf(2*M_PIf/3), sinf(2*M_PIf/3) } * 5;

    exit(print_test(a,b) ? EXIT_SUCCESS : EXIT_FAILURE);
}

inline bool print_test(f32x2 a, f32x2 b)
{
    a.print(""," + "); b.print(""," = "); (a + b).println();
    a.print("", " - "); b.print("", " = "); (a - b).println();

    a.print("", " * 3                             = "); (a * 3.0f).println();
    b.print("", " / 2.5                           = "); (b / 2.5f).println();
    return true;
}
