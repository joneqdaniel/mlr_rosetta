#include "mat.hpp"

template<typename T, size_t N, size_t M = N, enum alg A = alg::std>
constexpr inline void test(mat<T,N,M,A>& src)
{
	src.println();
	printf("  permanent: %+e\n",               (flt)src.perm());
	printf("determinant: %+e\n",                (flt)src.det());
	printf(" align/size: %zu/%zu\n", alignof(src), sizeof(src));
	puts("");
}

int main()
{
	mat<int,2> A =
	{
		{ 1, 2},
		{ 3, 4}
	};
	mat<int,3,3> B =
	{
		{-2, 2,-3},
		{-1, 1, 3},
		{ 2, 0,-1}
	};
	mat<int,4,4> C =
	{
		{ 1, 2, 3, 4},
		{ 4, 5, 6, 7},
		{ 7, 8, 9,10},
		{10,11,12,13}
	};
	mat<int,5> D =
	{
		{ 0,  1,  2,  3,  4},
		{ 5,  6,  7,  8,  9},
		{10, 11, 12, 13, 14},
		{15, 16, 17, 18, 19},
		{20, 21, 22, 23, 24}
	};

	test(A);
	test(B);
	test(C);
	test(D);

	mat<float,2> E = { vec<float,2>{ cosf(  M_PIf/6), sinf(  M_PIf/6) } * 3,
	                   vec<float,2>{ cosf(2*M_PIf/3), sinf(2*M_PIf/3) } * 5  };

	(E[0]       ).println();
	(E[1]       ).println();
	(E[0] + E[1]).println();
	(E[0] - E[1]).println();
	(E[0] * 3   ).println();
	(E[1] / 2.5 ).println();

	return EXIT_SUCCESS;
}
