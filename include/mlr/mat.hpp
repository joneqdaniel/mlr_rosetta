#pragma once

#include "vec.hpp"

/* linear algebra matrix storage type using buffer of vector type */
template<typename T, size_t N, size_t M = N, enum alg A = alg::std>
struct mat : buf<vec<T,N,A>,M,A>
{
	mat() = default;
	mat(std::initializer_list<vec<T,N,A>> il) { std::move(il.begin(),il.end(),this->begin()); }
        /* calculate minor of matrix */
        constexpr mat<T,N-1,M-1,A> minor(size_t x, size_t y) const requires(N > 0)
        {
                mat<T,N-1,M-1,A> result;
                for (size_t i = 0; i < N-1; i++)
                        for (size_t j = 0; j < N-1; j++)
                                result[i][j] = (i <  x && j <  y) ? (*this)[i    ][j    ] :
                                               (i >= x && j <  y) ? (*this)[i + 1][j    ] :
                                               (i <  x && j >= y) ? (*this)[i    ][j + 1] :
                                                                    (*this)[i + 1][j + 1] ;
                return result;
        }
        /* calculate determinant using laplace expansion */
        template<bool SIGN = true>
        constexpr flt det() const requires(N > 1)
        {
                flt sum = 0;
                bool sign = true;

                for (size_t i = 0; i < this->size(); i++)
                        sum += flt((sign += -1) && SIGN ? -1 : 1)
                             * flt((*this)[0][i])
                             * this->minor(0,i).template det<SIGN>();
                return sum;
        }
        /* leaf node of det */
        template<bool SIGN = true>
        inline constexpr flt det () const requires(N == 1) { return flt((*this)[0][0]); }
        /* calculate permanent using det without sign */
        inline constexpr flt perm() const requires(N  > 0) { return this->det<false>(); }
	void print(FILE* stream = stdout)
	{
		for(size_t i = 0; i < M; i++)
			(*this)[i].println("","",N,stream);
	}
	void println(FILE* stream = stdout)
	{
		print(stream);
		fputs("", stream);
	}
	static constexpr mat<T,M,M> ne()
	{
		return {};
	}
	static constexpr mat<T,M,M,A> id(ssize_t n = M)
	{
		mat<T,M,M,A> dst;
		if(n < 0) dst.fill(vec<T,M,A>::id());
		else for(size_t i = 0; i < n; i++) dst[i][i] = (T)1;
		return dst;
	}
	template<size_t N_I>
	mat<T,M,N,A> transposed() const
	{
		mat<T,M,N,A> dst;
		for(size_t i = 0; i < M; i++)
			for(size_t j = 0; j < N; j++)
				dst[j][i] = (*this)[i][j];
		return dst;
	}
	template<typename T_O>
	vec<T,M,A> operator*(const vec<T_O,N,A>& rhs)
	{
		vec<T,M,A> dst;
		for(size_t i = 0; i < M; i++)
			dst[i] = dot((*this)[i], rhs);
		return dst;
	}
	template<typename T_O>
	mat<T,N,M,A>& operator*=(const mat<T_O,N,M,A>& rhs)
	{
		mat<T_O,M,N,A> tp = rhs.transposed();
		for(size_t i = 0; i < M; i++)
		{
			vec<T,N,A> row = (*this)[i];
			for(size_t j = 0; j < N; j++)
				(*this)[i][j] = dot(row, tp[j]);
		}
		return (*this);
	}
	template<typename T_O>
	mat<T,N,M,A> operator*(const mat<T_O,N,M,A>& rhs) const
	{
		mat<T,N,M,A> dst = (*this);
		return (dst *= rhs);
	}
};

/* 4-dimensional cross/vector product using laplacian expansion (specialization of n-dimensional hodge dual/star operator) */
template<typename T_A, size_t N_A, typename T_B, size_t N_B, typename T_C, size_t N_C, enum alg A_A = alg::std, enum alg A_B = alg::std, enum alg A_C = alg::std, typename T_DST = decltype((T_A)1 * (T_B)1 * (T_C)1 - (T_A)1 * (T_B)1 * (T_C)1)>
inline constexpr vec<T_DST,4> cross4(const vec<T_A,N_A,A_A>& a, const vec<T_B,N_B,A_B>& b, const vec<T_C,N_C,A_C>& c)
{
	return vec<T_DST,4>{ -mat<T_DST,3,3>{ a.permute(1,2,3), b.permute(1,2,3), c.permute(1,2,3) }.det(),
	                     +mat<T_DST,3,3>{ a.permute(0,2,3), b.permute(0,2,3), c.permute(0,2,3) }.det(),
	                     -mat<T_DST,3,3>{ a.permute(0,1,3), b.permute(0,1,3), c.permute(0,1,3) }.det(),
	                     +mat<T_DST,3,3>{ a.permute(0,1,2), b.permute(0,1,2), c.permute(0,1,2) }.det() };
}

