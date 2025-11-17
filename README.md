# mlr_rosetta

mlr_rosetta - single-header-only [C++23][1] linear algebra math library including [rosettacode.org][2] examples

## About

mlr_rosetta implements

- [buf<T,N,A>][4] aligned array
- [vec<T,N,A>][5] n-dim vector type based on buf
- [mat<T,N,M,A>][6] nxm-dim matrix type based on buf and vec

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
[2]: https://rosettacode.org/
[3]: https://github.com/KhronosGroup/OpenGL-Registry/blob/main/api/GL/glcorearb.h
[4]: https://github.com/jopadan/mlr_rosetta/blob/main/include/mlr/buf.hpp
[5]: https://github.com/jopadan/mlr_rosetta/blob/main/include/mlr/vec.hpp
[6]: https://github.com/jopadan/mlr_rosetta/blob/main/include/mlr/mat.hpp
