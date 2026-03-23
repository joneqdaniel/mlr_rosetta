#pragma once

/* arithmetic type */
template<typename T>
struct ari
{
        template<typename T_O>
        friend T operator+(const T& lhs, const T_O& other) requires(!sca<T_O>)
        {
                T dst;
                std::transform(lhs.cbegin(),lhs.cend(),other.cbegin(),dst.begin(), std::plus<>{});
                return dst;
        }

        template<typename T_O>
        friend T operator+(const T& lhs, const T_O& other) requires(sca<T_O>)
        {
                T dst;
                dst.fill(other);
                std::transform(lhs.cbegin(),lhs.cend(),dst.cbegin(),dst.begin(), std::plus<>{});
                return dst;
        }
        template<typename T_O>
        friend T operator+(const T_O& other, const T& rhs) requires(sca<T_O>)
        {
                T dst;
                dst.fill(other);
                std::transform(dst.cbegin(),dst.cend(),rhs.cbegin(),dst.begin(), std::plus<>{});
                return dst;
        }
        template<typename T_O>
        friend T operator-(const T& lhs, const T_O& other) requires(!sca<T_O>)
        {
                T dst;
                std::transform(lhs.cbegin(),lhs.cend(),other.cbegin(),dst.begin(), std::minus<>{});
                return dst;
        }

        template<typename T_O>
        friend T operator-(const T& lhs, const T_O& other) requires(sca<T_O>)
        {
                T dst;
                dst.fill(other);
                std::transform(lhs.cbegin(),lhs.cend(),dst.cbegin(),dst.begin(), std::minus<>{});
                return dst;
        }
        template<typename T_O>
        friend T operator-(const T_O& other, const T& rhs) requires(sca<T_O>)
        {
                T dst;
                dst.fill(other);
                std::transform(dst.cbegin(),dst.cend(),rhs.cbegin(),dst.begin(), std::minus<>{});
                return dst;
        }
        template<typename T_O>
        friend T operator*(const T& lhs, const T_O& other) requires(!sca<T_O>)
        {
                T dst;
                std::transform(lhs.cbegin(),lhs.cend(),other.cbegin(),dst.begin(), std::multiplies<>{});
                return dst;
        }

        template<typename T_O>
        friend T operator*(const T& lhs, const T_O& other) requires(sca<T_O>)
        {
                T dst;
                dst.fill(other);
                std::transform(lhs.cbegin(),lhs.cend(),dst.cbegin(),dst.begin(), std::multiplies<>{});
                return dst;
        }
        template<typename T_O>
        friend T operator*(const T_O& other, const T& rhs) requires(sca<T_O>)
        {
                T dst;
                dst.fill(other);
                std::transform(dst.cbegin(),dst.cend(),rhs.cbegin(),dst.begin(), std::multiplies<>{});
                return dst;
        }

        template<typename T_O>
        friend T operator/(const T& lhs, const T_O& other) requires(!sca<T_O>)
        {
                T dst;
                std::transform(lhs.cbegin(),lhs.cend(),other.cbegin(),dst.begin(), std::divides<>{});
                return dst;
        }

        template<typename T_O>
        friend T operator/(const T& lhs, const T_O& other) requires(sca<T_O>)
        {
                T dst;
                dst.fill(other);
                std::transform(lhs.cbegin(),lhs.cend(),dst.cbegin(),dst.begin(), std::divides<>{});
                return dst;
        }
        template<typename T_O>
        friend T operator/(const T_O& other, const T& rhs) requires(sca<T_O>)
        {
                T dst;
                dst.fill(other);
                std::transform(dst.cbegin(),dst.cend(),rhs.cbegin(),dst.begin(), std::divides<>{});
                return dst;
        }
        template<typename T_O>
        T& operator+=(const T_O& other) requires(!sca<T_O>)
        {
                T& dst = (*(T*)this);
                std::transform(dst.cbegin(), dst.cend(), other.cbegin(), dst.begin(), std::plus<>{});
                return dst;
        }
        template<typename T_O>
        T& operator-=(const T_O& other) requires(!sca<T_O>)
        {
                T& dst = (*(T*)this);
                std::transform(dst.cbegin(), dst.cend(), other.cbegin(), dst.begin(), std::minus<>{});
                return dst;
        }
        template<typename T_O>
        T& operator*=(const T_O& other) requires(!sca<T_O>)
        {
                T& dst = (*(T*)this);
                std::transform(dst.cbegin(), dst.cend(), other.cbegin(), dst.begin(), std::multiplies<>{});
                return dst;
        }
        template<typename T_O>
        T& operator/=(const T_O& other) requires(!sca<T_O>)
        {
                T& dst = (*(T*)this);
                std::transform(dst.cbegin(), dst.cend(), other.cbegin(), dst.begin(), std::divides<>{});
                return dst;
        }
        template<typename T_O>
        T& operator+=(const T_O& other) requires(sca<T_O>)
        {
                T& dst = (*(T*)this);
                std::array<T_O, ((const T*)this)->size()> src;
                src.fill(other);
                std::transform(dst.cbegin(), dst.cend(), src.cbegin(), dst.begin(), std::plus<>{});
                return dst;
        }
        template<typename T_O>
        T& operator-=(const T_O& other) requires(sca<T_O>)
        {
                T& dst = (*(T*)this);
                std::array<T_O, ((const T*)this)->size()> src;
                src.fill(other);
                std::transform(dst.cbegin(), dst.cend(), src.cbegin(), dst.begin(), std::minus<>{});
                return dst;
        }
        template<typename T_O>
        T& operator*=(const T_O& other) requires(sca<T_O>)
        {
                T& dst = (*(T*)this);
                std::array<T_O, ((const T*)this)->size()> src;
                src.fill(other);
                std::transform(dst.cbegin(), dst.cend(), src.cbegin(), dst.begin(), std::multiplies<>{});
                return dst;
        }
        template<typename T_O>
        T& operator/=(const T_O& other) requires(sca<T_O>)
        {
                T& dst = (*(T*)this);
                std::array<T_O, ((const T*)this)->size()> src;
                src.fill(other);
                std::transform(dst.cbegin(), dst.cend(), src.cbegin(), dst.begin(), std::divides<>{});
                return dst;
        }
};
