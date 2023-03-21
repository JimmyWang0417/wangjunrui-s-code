/**
 *    name:     P1721 [NOI2016] 国王饮水记
 *    author:   whitepaperdog (蒟蒻wjr)
 *    located:  Xuanwu District, Nanjing City, Jiangsu Province, China
 *    created:  2023.03.19 周日 20:31:22 (Asia/Shanghai)
 *    unicode:  UTF-8
 *    standard: c++23
 **/
#include <algorithm>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <string>
typedef long long ll;
typedef unsigned long long ull;
#define lowbit(x) ((x) & (-(x)))

// #define FAST_IO

#if !defined(WIN32) && !defined(_WIN32)
#define getchar getchar_unlocked
#define putchar putchar_unlocked
#endif
namespace IO
{
#ifdef FAST_IO
#ifndef FAST_IN
#define FAST_IN
#endif
#ifndef FAST_OUT
#define FAST_OUT
#endif
#endif

    namespace INPUT
    {
#ifdef FAST_IN
#ifndef FAST_OUT_BUFFER_SIZE
#define FAST_OUT_BUFFER_SIZE (1 << 21)
#endif
        char _buf[FAST_OUT_BUFFER_SIZE], *_now = _buf, *_end = _buf;
#undef getchar
#define getchar() (_now == _end && (_end = (_now = _buf) + fread(_buf, 1, FAST_OUT_BUFFER_SIZE, stdin), _now == _end) ? EOF : *_now++)
#else
#if !defined(WIN32) && !defined(_WIN32)
#define getchar getchar_unlocked
#endif
#endif
        inline void read(char &_x)
        {
            char _s = (char)getchar();
            while ((_s >= 0x0a && _s <= 0x0d) || (_s == 0x09) || (_s == 0x20))
                _s = (char)getchar();
            _x = _s;
        }
        inline int read(char *_x)
        {
            char _s = (char)getchar();
            int _len = 0;
            while ((_s >= 0x0a && _s <= 0x0d) || (_s == 0x09) || (_s == 0x20))
                _s = (char)getchar();
            while (!((_s >= 0x0a && _s <= 0x0d) || (_s == 0x09) || (_s == 0x20)) && _s != EOF)
            {
                _x[_len++] = _s;
                _s = (char)getchar();
            }
            _x[_len] = '\0';
            return _len;
        }
        template <typename _T>
        inline void read(_T &_x)
        {
            _x = 0;
            char _s = (char)getchar();
            bool _f = false;
            while (!(_s >= '0' && _s <= '9'))
            {
                if (_s == '-')
                    _f = true;
                _s = (char)getchar();
            }
            while (_s >= '0' && _s <= '9')
            {
                _x = (_x << 1) + (_x << 3) + (_s - '0');
                _s = (char)getchar();
            }
            if (_f)
                _x = -_x;
        }
        template <typename _T, typename... _G>
        inline void read(_T &_x, _G &..._y)
        {
            read(_x);
            read(_y...);
        }
#ifdef FAST_IN
#undef getchar
#if !defined(WIN32) && !defined(_WIN32)
#define getchar getchar_unlocked
#endif
#endif
    }
    namespace OUTPUT
    {
#ifdef FAST_OUT
#ifndef FAST_OUT_BUFFER_SIZE
#define FAST_OUT_BUFFER_SIZE (1 << 21)
#endif
        char _buf[FAST_OUT_BUFFER_SIZE], *_now = _buf;
        inline void flush()
        {
            fwrite(_buf, 1, _now - _buf, stdout), _now = _buf;
        }
#undef putchar
#define putchar(c) (_now - _buf == FAST_OUT_BUFFER_SIZE ? flush(), *_now++ = c : *_now++ = c)
#else
#if !defined(WIN32) && !defined(_WIN32)
#define putchar putchar_unlocked
#endif
#endif
        inline void write(char _x)
        {
            putchar(_x);
        }
        inline void write(char *const _x)
        {
            for (int i = 0; _x[i]; ++i)
                putchar(_x[i]);
        }
        inline void write(const char *__restrict _x)
        {
            for (int i = 0; _x[i]; ++i)
                putchar(_x[i]);
        }
        template <typename _T>
        inline void write(_T _x)
        {
            static char dight[39];
            int _len = 0;
            if (_x == 0)
            {
                putchar('0');
                return;
            }
            bool flag = false;
            if (_x < 0)
            {
                _x = -_x;
                flag = true;
            }
            while (_x)
            {
                dight[_len++] = (char)(_x % 10) + '0';
                _x /= 10;
            }
            if (flag)
                putchar('-');
            while (_len--)
                putchar(dight[_len]);
        }
        template <typename _T, typename... _G>
        inline void write(_T _x, _G... _y)
        {
            write(_x);
            write(_y...);
        }
#ifdef FAST_OUT
#undef putchar
#if !defined(WIN32) && !defined(_WIN32)
#define putchar putchar_unlocked
#endif
#endif
    }
}
template <typename T>
inline void ckmin(T &_x, T _y)
{
    if (_x > _y)
        _x = _y;
}
template <typename T>
inline void ckmax(T &_x, T _y)
{
    if (_x < _y)
        _x = _y;
}
template <const int _mod>
struct modint
{
    int x;
    constexpr modint(int _x = 0) : x(_x) {}
    constexpr inline modint operator+() const
    {
        return *this;
    }
    constexpr inline modint operator-() const
    {
        return !x ? 0 : _mod - x;
    }
    constexpr inline modint &operator++()
    {
        ++x;
        if (x >= _mod)
            x -= _mod;
        return *this;
    }
    constexpr inline modint &operator--()
    {
        --x;
        if (x < 0)
            x += _mod;
        return *this;
    }
    constexpr inline modint operator++(int)
    {
        int res = x;
        if (x >= _mod)
            x -= _mod;
        return res;
    }
    constexpr inline modint operator--(int)
    {
        int res = x;
        if (x < 0)
            x += _mod;
        return res;
    }
    constexpr inline modint operator+(const modint &rhs) const
    {
        int res = x;
        res += rhs.x;
        if (res >= _mod)
            res -= _mod;
        return res;
    }
    constexpr inline modint operator-(const modint &rhs) const
    {
        int res = x;
        res -= rhs.x;
        if (res < 0)
            res += _mod;
        return res;
    }
    constexpr inline modint operator*(const modint &rhs) const
    {
        return (int)((ll)x * rhs.x % _mod);
    }
    constexpr inline modint &operator+=(const modint &rhs)
    {
        x += rhs.x;
        if (x >= _mod)
            x -= _mod;
        return *this;
    }
    constexpr inline modint &operator-=(const modint &rhs)
    {
        x -= rhs.x;
        if (x < 0)
            x += _mod;
        return *this;
    }
    constexpr inline modint &operator*=(const modint &rhs)
    {
        x = (int)((ll)x * rhs.x % _mod);
        return *this;
    }
    template <typename _G>
    constexpr inline modint operator^(_G rhs) const
    {
        modint a = x, res = 1;
        while (rhs)
        {
            if (rhs & 1)
                res *= a;
            a *= a;
            rhs >>= 1;
        }
        return res;
    }
    constexpr inline modint inv() const
    {
        return *this ^ (_mod - 2);
    }
    constexpr inline modint operator/(const modint &rhs) const
    {
        return (*this) * rhs.inv();
    }
    constexpr inline modint &operator/=(const modint &rhs)
    {
        return (*this) *= rhs.inv();
    }
    constexpr inline bool operator==(const modint &rhs) const
    {
        return x == rhs.x;
    }
    constexpr inline bool operator!=(const modint &rhs) const
    {
        return x != rhs.x;
    }
    constexpr inline int &data()
    {
        return x;
    }
};
namespace Bignum
{
    constexpr int PREC = 6000;

    class Decimal
    {
    public:
        Decimal();
        Decimal(const std::string &s);
        Decimal(const char *s);
        Decimal(int x);
        Decimal(long long x);
        Decimal(double x);

        bool is_zero() const;

        // p (p > 0) is the number of digits after the decimal point
        std::string to_string(int p) const;
        double to_double() const;

        friend Decimal operator+(const Decimal &a, const Decimal &b);
        friend Decimal operator+(const Decimal &a, int x);
        friend Decimal operator+(int x, const Decimal &a);
        friend Decimal operator+(const Decimal &a, long long x);
        friend Decimal operator+(long long x, const Decimal &a);
        friend Decimal operator+(const Decimal &a, double x);
        friend Decimal operator+(double x, const Decimal &a);

        friend Decimal operator-(const Decimal &a, const Decimal &b);
        friend Decimal operator-(const Decimal &a, int x);
        friend Decimal operator-(int x, const Decimal &a);
        friend Decimal operator-(const Decimal &a, long long x);
        friend Decimal operator-(long long x, const Decimal &a);
        friend Decimal operator-(const Decimal &a, double x);
        friend Decimal operator-(double x, const Decimal &a);

        friend Decimal operator*(const Decimal &a, int x);
        friend Decimal operator*(int x, const Decimal &a);

        friend Decimal operator/(const Decimal &a, int x);

        friend bool operator<(const Decimal &a, const Decimal &b);
        friend bool operator>(const Decimal &a, const Decimal &b);
        friend bool operator<=(const Decimal &a, const Decimal &b);
        friend bool operator>=(const Decimal &a, const Decimal &b);
        friend bool operator==(const Decimal &a, const Decimal &b);
        friend bool operator!=(const Decimal &a, const Decimal &b);

        Decimal &operator+=(int x);
        Decimal &operator+=(long long x);
        Decimal &operator+=(double x);
        Decimal &operator+=(const Decimal &b);

        Decimal &operator-=(int x);
        Decimal &operator-=(long long x);
        Decimal &operator-=(double x);
        Decimal &operator-=(const Decimal &b);

        Decimal &operator*=(int x);

        Decimal &operator/=(int x);

        friend Decimal operator-(const Decimal &a);

        // These can't be called
        friend Decimal operator*(const Decimal &a, double x);
        friend Decimal operator*(double x, const Decimal &a);
        friend Decimal operator/(const Decimal &a, double x);
        Decimal &operator*=(double x);
        Decimal &operator/=(double x);

    private:
        static const int len = PREC / 9 + 1;
        static const int mo = 1000000000;

        static void append_to_string(std::string &s, long long x);

        bool is_neg;
        long long integer;
        int data[len];

        void init_zero();
        void init(const char *s);
    };

    Decimal::Decimal()
    {
        this->init_zero();
    }

    Decimal::Decimal(const char *s)
    {
        this->init(s);
    }

    Decimal::Decimal(const std::string &s)
    {
        this->init(s.c_str());
    }

    Decimal::Decimal(int x)
    {
        this->init_zero();

        if (x < 0)
        {
            is_neg = true;
            x = -x;
        }

        integer = x;
    }

    Decimal::Decimal(long long x)
    {
        this->init_zero();

        if (x < 0)
        {
            is_neg = true;
            x = -x;
        }

        integer = x;
    }

    Decimal::Decimal(double x)
    {
        this->init_zero();

        if (x < 0)
        {
            is_neg = true;
            x = -x;
        }

        integer = (long long)x;
        x -= integer;

        for (int i = 0; i < len; i++)
        {
            x *= mo;
            if (x < 0)
                x = 0;
            data[i] = (int)x;
            x -= data[i];
        }
    }

    void Decimal::init_zero()
    {
        is_neg = false;
        integer = 0;
        memset(data, 0, len * sizeof(int));
    }

    bool Decimal::is_zero() const
    {
        if (integer)
            return false;
        for (int i = 0; i < len; i++)
        {
            if (data[i])
                return false;
        }
        return true;
    }

    void Decimal::init(const char *s)
    {
        this->init_zero();

        is_neg = false;
        integer = 0;

        // find the first digit or the negative sign
        while (*s != 0)
        {
            if (*s == '-')
            {
                is_neg = true;
                ++s;
                break;
            }
            else if (*s >= 48 && *s <= 57)
            {
                break;
            }
            ++s;
        }

        // read the integer part
        while (*s >= 48 && *s <= 57)
        {
            integer = integer * 10 + *s - 48;
            ++s;
        }

        // read the decimal part
        if (*s == '.')
        {
            int pos = 0;
            int x = mo / 10;

            ++s;
            while (pos < len && *s >= 48 && *s <= 57)
            {
                data[pos] += (*s - 48) * x;
                ++s;
                x /= 10;
                if (x == 0)
                {
                    ++pos;
                    x = mo / 10;
                }
            }
        }
    }

    void Decimal::append_to_string(std::string &s, long long x)
    {
        if (x == 0)
        {
            s.append(1, 48);
            return;
        }

        char _[30];
        int cnt = 0;
        while (x)
        {
            _[cnt++] = x % 10;
            x /= 10;
        }
        while (cnt--)
        {
            s.append(1, _[cnt] + 48);
        }
    }

    std::string Decimal::to_string(int p) const
    {
        std::string ret;

        if (is_neg && !this->is_zero())
        {
            ret = "-";
        }

        append_to_string(ret, this->integer);

        ret.append(1, '.');

        for (int i = 0; i < len; i++)
        {
            // append data[i] as "%09d"
            int x = mo / 10;
            int tmp = data[i];
            while (x)
            {
                ret.append(1, 48 + tmp / x);
                tmp %= x;
                x /= 10;
                if (--p == 0)
                {
                    break;
                }
            }
            if (p == 0)
                break;
        }

        if (p > 0)
        {
            ret.append(p, '0');
        }

        return ret;
    }

    double Decimal::to_double() const
    {
        double ret = integer;

        double k = 1.0;
        for (int i = 0; i < len; i++)
        {
            k /= mo;
            ret += k * data[i];
        }

        if (is_neg)
        {
            ret = -ret;
        }

        return ret;
    }

    bool operator<(const Decimal &a, const Decimal &b)
    {
        if (a.is_neg != b.is_neg)
        {
            return a.is_neg && (!a.is_zero() || !b.is_zero());
        }
        else if (!a.is_neg)
        {
            // a, b >= 0
            if (a.integer != b.integer)
            {
                return a.integer < b.integer;
            }
            for (int i = 0; i < Decimal::len; i++)
            {
                if (a.data[i] != b.data[i])
                {
                    return a.data[i] < b.data[i];
                }
            }
            return false;
        }
        else
        {
            // a, b <= 0
            if (a.integer != b.integer)
            {
                return a.integer > b.integer;
            }
            for (int i = 0; i < Decimal::len; i++)
            {
                if (a.data[i] != b.data[i])
                {
                    return a.data[i] > b.data[i];
                }
            }
            return false;
        }
    }

    bool operator>(const Decimal &a, const Decimal &b)
    {
        if (a.is_neg != b.is_neg)
        {
            return !a.is_neg && (!a.is_zero() || !b.is_zero());
        }
        else if (!a.is_neg)
        {
            // a, b >= 0
            if (a.integer != b.integer)
            {
                return a.integer > b.integer;
            }
            for (int i = 0; i < Decimal::len; i++)
            {
                if (a.data[i] != b.data[i])
                {
                    return a.data[i] > b.data[i];
                }
            }
            return false;
        }
        else
        {
            // a, b <= 0
            if (a.integer != b.integer)
            {
                return a.integer < b.integer;
            }
            for (int i = 0; i < Decimal::len; i++)
            {
                if (a.data[i] != b.data[i])
                {
                    return a.data[i] < b.data[i];
                }
            }
            return false;
        }
    }

    bool operator<=(const Decimal &a, const Decimal &b)
    {
        if (a.is_neg != b.is_neg)
        {
            return a.is_neg || (a.is_zero() && b.is_zero());
        }
        else if (!a.is_neg)
        {
            // a, b >= 0
            if (a.integer != b.integer)
            {
                return a.integer < b.integer;
            }
            for (int i = 0; i < Decimal::len; i++)
            {
                if (a.data[i] != b.data[i])
                {
                    return a.data[i] < b.data[i];
                }
            }
            return true;
        }
        else
        {
            // a, b <= 0
            if (a.integer != b.integer)
            {
                return a.integer > b.integer;
            }
            for (int i = 0; i < Decimal::len; i++)
            {
                if (a.data[i] != b.data[i])
                {
                    return a.data[i] > b.data[i];
                }
            }
            return true;
        }
    }

    bool operator>=(const Decimal &a, const Decimal &b)
    {
        if (a.is_neg != b.is_neg)
        {
            return !a.is_neg || (a.is_zero() && b.is_zero());
        }
        else if (!a.is_neg)
        {
            // a, b >= 0
            if (a.integer != b.integer)
            {
                return a.integer > b.integer;
            }
            for (int i = 0; i < Decimal::len; i++)
            {
                if (a.data[i] != b.data[i])
                {
                    return a.data[i] > b.data[i];
                }
            }
            return true;
        }
        else
        {
            // a, b <= 0
            if (a.integer != b.integer)
            {
                return a.integer < b.integer;
            }
            for (int i = 0; i < Decimal::len; i++)
            {
                if (a.data[i] != b.data[i])
                {
                    return a.data[i] < b.data[i];
                }
            }
            return true;
        }
    }

    bool operator==(const Decimal &a, const Decimal &b)
    {
        if (a.is_zero() && b.is_zero())
            return true;
        if (a.is_neg != b.is_neg)
            return false;
        if (a.integer != b.integer)
            return false;
        for (int i = 0; i < Decimal::len; i++)
        {
            if (a.data[i] != b.data[i])
                return false;
        }
        return true;
    }

    bool operator!=(const Decimal &a, const Decimal &b)
    {
        return !(a == b);
    }

    Decimal &Decimal::operator+=(long long x)
    {
        if (!is_neg)
        {
            if (integer + x >= 0)
            {
                integer += x;
            }
            else
            {
                bool last = false;
                for (int i = len - 1; i >= 0; i--)
                {
                    if (last || data[i])
                    {
                        data[i] = mo - data[i] - last;
                        last = true;
                    }
                    else
                    {
                        last = false;
                    }
                }
                integer = -x - integer - last;
                is_neg = true;
            }
        }
        else
        {
            if (integer - x >= 0)
            {
                integer -= x;
            }
            else
            {
                bool last = false;
                for (int i = len - 1; i >= 0; i--)
                {
                    if (last || data[i])
                    {
                        data[i] = mo - data[i] - last;
                        last = true;
                    }
                    else
                    {
                        last = false;
                    }
                }
                integer = x - integer - last;
                is_neg = false;
            }
        }
        return *this;
    }

    Decimal &Decimal::operator+=(int x)
    {
        return *this += (long long)x;
    }

    Decimal &Decimal::operator-=(int x)
    {
        return *this += (long long)-x;
    }

    Decimal &Decimal::operator-=(long long x)
    {
        return *this += -x;
    }

    Decimal &Decimal::operator/=(int x)
    {
        if (x < 0)
        {
            is_neg ^= 1;
            x = -x;
        }

        int last = integer % x;
        integer /= x;

        for (int i = 0; i < len; i++)
        {
            long long tmp = 1LL * last * mo + data[i];
            data[i] = tmp / x;
            last = tmp - 1LL * data[i] * x;
        }

        if (is_neg && integer == 0)
        {
            int i;
            for (i = 0; i < len; i++)
            {
                if (data[i] != 0)
                {
                    break;
                }
            }
            if (i == len)
            {
                is_neg = false;
            }
        }

        return *this;
    }

    Decimal &Decimal::operator*=(int x)
    {
        if (x < 0)
        {
            is_neg ^= 1;
            x = -x;
        }
        else if (x == 0)
        {
            init_zero();
            return *this;
        }

        int last = 0;
        for (int i = len - 1; i >= 0; i--)
        {
            long long tmp = 1LL * data[i] * x + last;
            last = tmp / mo;
            data[i] = tmp - 1LL * last * mo;
        }
        integer = integer * x + last;

        return *this;
    }

    Decimal operator-(const Decimal &a)
    {
        Decimal ret = a;
        // -0 = 0
        if (!ret.is_neg && ret.integer == 0)
        {
            int i;
            for (i = 0; i < Decimal::len; i++)
            {
                if (ret.data[i] != 0)
                    break;
            }
            if (i < Decimal::len)
            {
                ret.is_neg = true;
            }
        }
        else
        {
            ret.is_neg ^= 1;
        }
        return ret;
    }

    Decimal operator+(const Decimal &a, int x)
    {
        Decimal ret = a;
        return ret += x;
    }

    Decimal operator+(int x, const Decimal &a)
    {
        Decimal ret = a;
        return ret += x;
    }

    Decimal operator+(const Decimal &a, long long x)
    {
        Decimal ret = a;
        return ret += x;
    }

    Decimal operator+(long long x, const Decimal &a)
    {
        Decimal ret = a;
        return ret += x;
    }

    Decimal operator-(const Decimal &a, int x)
    {
        Decimal ret = a;
        return ret -= x;
    }

    Decimal operator-(int x, const Decimal &a)
    {
        return -(a - x);
    }

    Decimal operator-(const Decimal &a, long long x)
    {
        Decimal ret = a;
        return ret -= x;
    }

    Decimal operator-(long long x, const Decimal &a)
    {
        return -(a - x);
    }

    Decimal operator*(const Decimal &a, int x)
    {
        Decimal ret = a;
        return ret *= x;
    }

    Decimal operator*(int x, const Decimal &a)
    {
        Decimal ret = a;
        return ret *= x;
    }

    Decimal operator/(const Decimal &a, int x)
    {
        Decimal ret = a;
        return ret /= x;
    }

    Decimal operator+(const Decimal &a, const Decimal &b)
    {
        if (a.is_neg == b.is_neg)
        {
            Decimal ret = a;
            bool last = false;
            for (int i = Decimal::len - 1; i >= 0; i--)
            {
                ret.data[i] += b.data[i] + last;
                if (ret.data[i] >= Decimal::mo)
                {
                    ret.data[i] -= Decimal::mo;
                    last = true;
                }
                else
                {
                    last = false;
                }
            }
            ret.integer += b.integer + last;
            return ret;
        }
        else if (!a.is_neg)
        {
            // a - |b|
            return a - -b;
        }
        else
        {
            // b - |a|
            return b - -a;
        }
    }

    Decimal operator-(const Decimal &a, const Decimal &b)
    {
        if (!a.is_neg && !b.is_neg)
        {
            if (a >= b)
            {
                Decimal ret = a;
                bool last = false;
                for (int i = Decimal::len - 1; i >= 0; i--)
                {
                    ret.data[i] -= b.data[i] + last;
                    if (ret.data[i] < 0)
                    {
                        ret.data[i] += Decimal::mo;
                        last = true;
                    }
                    else
                    {
                        last = false;
                    }
                }
                ret.integer -= b.integer + last;
                return ret;
            }
            else
            {
                Decimal ret = b;
                bool last = false;
                for (int i = Decimal::len - 1; i >= 0; i--)
                {
                    ret.data[i] -= a.data[i] + last;
                    if (ret.data[i] < 0)
                    {
                        ret.data[i] += Decimal::mo;
                        last = true;
                    }
                    else
                    {
                        last = false;
                    }
                }
                ret.integer -= a.integer + last;
                ret.is_neg = true;
                return ret;
            }
        }
        else if (a.is_neg && b.is_neg)
        {
            // a - b = (-b) - (-a)
            return -b - -a;
        }
        else if (a.is_neg)
        {
            // -|a| - b
            return -(-a + b);
        }
        else
        {
            // a - -|b|
            return a + -b;
        }
    }

    Decimal operator+(const Decimal &a, double x)
    {
        return a + Decimal(x);
    }

    Decimal operator+(double x, const Decimal &a)
    {
        return Decimal(x) + a;
    }

    Decimal operator-(const Decimal &a, double x)
    {
        return a - Decimal(x);
    }

    Decimal operator-(double x, const Decimal &a)
    {
        return Decimal(x) - a;
    }

    Decimal &Decimal::operator+=(double x)
    {
        *this = *this + Decimal(x);
        return *this;
    }

    Decimal &Decimal::operator-=(double x)
    {
        *this = *this - Decimal(x);
        return *this;
    }

    Decimal &Decimal::operator+=(const Decimal &b)
    {
        *this = *this + b;
        return *this;
    }

    Decimal &Decimal::operator-=(const Decimal &b)
    {
        *this = *this - b;
        return *this;
    }
}
using IO::INPUT::read;
using IO::OUTPUT::write;
using Bignum::Decimal;
using namespace std;
constexpr int N = 1e5 + 5;
int n, m, k, p;
int h[N];
int pre[N];
double f[15][N];
int g[15][N];
struct node
{
    int x;
    double y;
    node(int _x = 0, double _y = 0) : x(_x), y(_y) {}
} point[N];
int q[N], head, tail;
inline double slope(node lhs, node rhs)
{
    return (lhs.y - rhs.y) / (lhs.x - rhs.x);
}
inline Decimal calc(int j, int i)
{
    if (!j)
        return h[1];
    return (calc(j - 1, g[j][i]) + pre[i] - pre[g[j][i]]) / (i - g[j][i] + 1);
}
signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);
    read(n, m, p, h[1]);
    int _n = 1;
    for (int i = 2; i <= n; ++i)
    {
        int x;
        read(x);
        if (x >= h[1])
            h[++_n] = x;
    }
    n = _n;
    ckmin(m, n);
    k = min(m, 14);
    sort(h + 2, h + 1 + n);
    for (int i = 1; i <= n; ++i)
    {
        pre[i] = pre[i - 1] + h[i];
        f[0][i] = h[1];
    }
    for (int j = 1; j <= k; ++j)
    {
        for (int i = 1; i <= n; ++i)
            point[i] = node(i - 1, pre[i] - f[j - 1][i]);
        head = 1, tail = 1;
        q[1] = 1;
        for (int i = 2; i <= n; ++i)
        {
            node u = node(i, pre[i]);
            while (head < tail && slope(u, point[q[head]]) < slope(u, point[q[head + 1]]))
                head++;
            f[j][i] = (f[j - 1][q[head]] + pre[i] - pre[q[head]]) / (i - q[head] + 1);
            g[j][i] = q[head];
            while (head < tail && slope(point[q[tail - 1]], point[q[tail]]) > slope(point[q[tail]], point[i]))
                tail--;
            q[++tail] = i;
        }
    }
    int o = n - m + k, u = 0;
    for (int i = 0; i <= k; i++)
        if (f[i][o] > f[u][o])
            u = i;
    Decimal ans = calc(u, o);
    for (int i = o + 1; i <= n; ++i)
        ans = (ans + h[i]) / 2;
    cout << ans.to_string(p << 1) << endl;
#ifdef FAST_OUT
    IO::OUTPUT::flush();
#endif
    return 0;
}