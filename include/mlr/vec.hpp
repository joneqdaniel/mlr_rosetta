#pragma once
#include <algorithm>
#include <numeric>
#include <cstdio>
#include <cmath>

#include "buf.hpp"
#include "ari.hpp"

template<typename T, size_t N, enum alg A = alg::std, size_t N_POW2 = std::bit_ceil<size_t>(N)>
struct vec : buf<T,N,A>, ari<vec<T,N,A>>
{
	/* cast to different alignment modes */
	template<enum alg A_DST = alg::std>
	operator vec<T,N,A_DST>() { return *reinterpret_cast<vec<T,N,A_DST>*>(this); }

	/* copy assign from another vector */
	template<typename T_O, size_t N_O, enum alg A_O = alg::std>
	vec<T,N,A>& operator=(const vec<T_O,N_O,A_O>& other)
	{
		std::copy(other.cbegin(), other.cend(), this->begin());
		return (*this);
	}
	vec<T,N,A> operator-()
	{
		vec<T,N,A> dst;
		std::transform(this->cbegin(), this->cend(), dst.begin(), std::negate<>{});
		return dst;
	}

	/* permute vector according to input indices */
	template<typename... I>
	inline constexpr vec<T, sizeof...(I),A> permute(const I... args) const { return vec<T,sizeof...(I),A>{ (*this)[args % N]... }; }

	vec<vec<T,N/2,A>,N/2,A>& split()
	{
		return *reinterpret_cast<vec<vec<T,N/2,A>,N/2,A>*>(this);
	}

	static inline constexpr vec<T,N,A> id(ssize_t i = -1)
	{		
		vec<T,N,A> dst = ne();
		if(i < 0)
			dst.fill((T)1);
		else
			dst[i % N] = (T)1;
		return dst;
	}
	static inline constexpr vec<T,N,A> ne() { return {}; }

	/* horizontal accumulate the vector to default floating point type */
	flt inline constexpr sum() { return (flt)std::accumulate(this->cbegin(), this->cend(), (T)0); }
	/* sign manipulations */
	inline constexpr vec<T,N,A>& negate(size_t mod = 2, size_t val = 0)
	{
		for(size_t i = 0; i < N; i++)
			(*this)[i] = i % mod == val ? -(*this)[i] : (*this)[i];
		return (*this);
	}

	/* print vector to stdio C stream */
	void print(FILE* stream = stdout)
	{
		fputs("[", stream);
		for(size_t i = 0; i < N; i++)
		{
			fprintf(stream, "%+e", (flt)(*this)[i]);
			if(i != N-1) fputs(", ", stream);
		}
		fputs("]", stream);
	}
	/* print vector to stdio C stream terminating with new line */
	void println(FILE* stream = stdout)
	{
		print(stream);
		fputs("\n", stream);
	}
};

/* n-dimensional dot/scalar product */
template<typename T, size_t N, typename T_O, size_t N_O, enum alg A = alg::std, enum alg A_O = alg::std>
inline constexpr flt dot(const vec<T,N,A>& a, const vec<T_O,N_O,A_O>& b) { return (a * b).sum(); }

/* 3-dimensional cross/vector product (specialization of n-dimensional hodge dual/star operator) */
template<typename T, size_t N, typename T_O, size_t N_O, enum alg A = alg::std, enum alg A_O = alg::std, typename T_DST = decltype((T)1 * (T_O)1 - (T)1 * (T_O)1)>
inline constexpr vec<T_DST,3,alg::vec> cross3(const vec<T,N,A>& a, const vec<T_O,N_O,A_O>& b)
{
	return vec<T_DST,3,alg::vec>{ a.permute(1,2,0) * b.permute(2,0,1)
	                            - b.permute(1,2,0) * a.permute(2,0,1) };

}

/* type products hodge/cross/laplace */
template<typename T, size_t N, enum alg A = alg::std>
inline constexpr vec<T,2,alg::vec> cross2(const vec<T,N,A>& src, unsigned int winding = 0x0901)
{
	return vec<T,2,alg::vec>::id().negate(2,1 - (winding % 2)) * src.permute(1,0);
}
