/*
 * CXXFLAGS=-march=native -O3 -std=<c|gnu>++23 -mfpmath=<your SIMD implementation>
 * compatible with every compiler and any SIMD platform.
 * Based on aligned vector type using cstdout not iostream.
 */
#include "vec.hpp"

using f32    = float;
using f32x2  = vec<f32,2>;

int main(int argc, char** argv)
{
    f32x2 a = (f32x2){ cosf(  M_PIf/6), sinf(  M_PIf/6) } * 3.0f;
    f32x2 b = (f32x2){ cosf(2*M_PIf/3), sinf(2*M_PIf/3) } * 5.0f;

    a.print(); fputs(" + ", stdout); b.print();                    fputs(" = ", stdout);
    (a + b).println();
    a.print(); fputs(" - ", stdout); b.print();                    fputs(" = ", stdout);
    (a - b).println();
    a.print(); fputs(" * 3                             ", stdout); fputs(" = ", stdout);
    (a * 3.0f).println();
    a.print(); fputs(" / 2.5                           ", stdout); fputs(" = ", stdout);
    (b / 2.5f).println();
    exit(EXIT_SUCCESS);
}
