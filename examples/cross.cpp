#include "mat.hpp"

template<typename T, size_t N, size_t M = N, enum alg A = alg::std>
constexpr inline bool test(mat<T,N,M,A>& src);

int main()
{
	vec<int,2> a[2] = { {1,0    },                       cross2(a[0]          ) };
	vec<int,3> b[3] = { {1,0,0  }, {0,1,0  },            cross3(b[0],b[1]     ) };
	vec<int,4> c[4] = { {1,0,0,0}, {0,1,0,0}, {0,0,1,0}, cross4(c[0],c[1],c[2]) };

	a[0].println(); a[1].println(); eol();
	b[0].println(); b[1].println(); b[2].println(); eol();
	c[0].println(); c[1].println(); c[2].println(); c[3].println();

	exit(EXIT_SUCCESS);
}
