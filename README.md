# mlr_rosetta

mlr - single-header-only [C++23][1] linear algebra math library including [rosettacode.org][5] examples

## About

mlr implements aligned array [buf<T,N,A>][3] based vector [vec<T,N,A>][4] type for N-dimensional linear algebra math.

# Dependencies

- [C++23][1]

## Building

```sh
cmake . --install-prefix=/usr
make install
```

### Optimization

Change `CMakeLists.txt` compile flags to fit your needs:
```sh
add_compile_options(-march=native -mfpmath=[your SIMD instruction set] -O3)
```

## Usage

[1]: https://isocpp.org/
[2]: https://github.com/KhronosGroup/OpenGL-Registry/blob/main/api/GL/glcorearb.h
[3]: https://github.com/jopadan/mlr_rosetta/blob/main/include/mlr/buf.hpp
[4]: https://github.com/jopadan/mlr_rosetta/blob/main/include/mlr/vec.hpp
[5]: https://rosettacode.org/
