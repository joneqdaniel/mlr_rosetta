#pragma once

/* 
 * CXXFLAGS=-march=native -O3 -std=<c|gnu>++23 -mfpmath=<your SIMD implementation>
 * compatible with every compiler and any SIMD platform
 * TODO:
 * - C++26 mdspan/submdspan slice/splice with operators and aligned accessors
 */
#include <array>
#include <bit>

#if defined(__clang__)
#pragma clang diagnostic ignored "-Wgnu-alignof-expression"
#endif

/* default floating point type */
using flt = double;

/* scalar type */
template<class T>
concept sca = std::integral<T> || std::floating_point<T>;

/* alignement mode type */
enum class alg
{
	unk = 0 << 0,
	num = 1 << 0,
	vec = 1 << 1,
	mat = 1 << 2,
	std = 1 << 3,
};

/* aligned fixed linear storage type of static extents (aligned if N equals power of 2) */
#pragma pack(push,1)
template<typename T, size_t N, enum alg A = alg::std, size_t N_POW2 = std::bit_ceil<size_t>(N)>
struct alignas(((N == N_POW2 && A != alg::num && A != alg::vec) || ((A == alg::vec && sca<T>) || (A == alg::mat)) ? N_POW2 : 1) * alignof(T)) buf : std::array<T,N>
{
	/* cast to different alignment modes */
	template<enum alg A_DST = alg::std>
	operator buf<T,N,A_DST>() { return *reinterpret_cast<buf<T,N,A_DST>*>(this); }

	/* copy assign from another vector */
	template<typename T_O, size_t N_O, enum alg A_O = alg::std>
	buf<T,N,A>& operator=(const buf<T_O,N_O,A_O>& other)
	{
		std::copy(other.cbegin(), other.cend(), this->begin());
		return (*this);
	}

	/* permute vector according to input indices */
	template<typename... I>
	inline constexpr buf<T, sizeof...(I),A> permute(const I... args) const { return buf<T,sizeof...(I),A>{ (*this)[args % N]... }; }
};
#pragma pack(pop)

