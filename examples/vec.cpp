/*
 * CXXFLAGS=-march=native -O3 -std=<c|gnu>++23 -mfpmath=<your SIMD implementation>
 * compatible with every compiler and any SIMD platform.
 * Based on aligned vector type using cstdout not iostream.
 */
#include "vec.hpp"

using f32x2  = vec<float,2>;
using f32x3  = vec<float,3>;
using f32x3a = vec<float,3,alg::vec>;
using f32x4u = vec<float,4,alg::num>;
using f32x4  = vec<float,4>;

int main(int argc, char** argv)
{
    f32x2  a = f32x2{ cosf(  M_PIf/6), sinf(  M_PIf/6) } * 3;
    f32x2  b = f32x2{ cosf(2*M_PIf/3), sinf(2*M_PIf/3) } * 5;
    f32x2  c = a + b;
    f32x2  d = a - b;
    f32x2  e = a * 3;
    f32x2  f = b / 2.5f;

    a.print(); fputs(" + ", stdout); b.print(); fputs(" = ", stdout); c.println();
    a.print(); fputs(" - ", stdout); b.print(); fputs(" = ", stdout); c.println();

    a.print(); fputs(" * 3                              = ", stdout); e.println();
    b.print(); fputs(" / 2.5                            = ", stdout); f.println();

    exit(EXIT_SUCCESS);
}
