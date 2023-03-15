/**
 *    name:     CF1439D INOI Final Contests
 *    author:   whitepaperdog (蒟蒻wjr)
 *    located:  Xuanwu District, Nanjing City, Jiangsu Province, China
 *    created:  2023.03.12 周日 20:58:33 (Asia/Shanghai)
 *    unicode:  UTF-8
 *    standard: c++23
 **/
#include <cstdio>
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
using IO::INPUT::read;
using IO::OUTPUT::write;
using namespace std;
constexpr int N = 505;
int n, m, mod;
struct modint
{
    int x;
    modint(int _x = 0) : x(_x) {}
    inline modint operator+() const
    {
        return *this;
    }
    inline modint operator-() const
    {
        return !x ? 0 : mod - x;
    }
    inline modint &operator++()
    {
        ++x;
        if (x >= mod)
            x -= mod;
        return *this;
    }
    inline modint &operator--()
    {
        --x;
        if (x < 0)
            x += mod;
        return *this;
    }
    inline modint operator++(int)
    {
        int res = x;
        if (x >= mod)
            x -= mod;
        return res;
    }
    inline modint operator--(int)
    {
        int res = x;
        if (x < 0)
            x += mod;
        return res;
    }
    inline modint operator+(const modint &rhs) const
    {
        int res = x;
        res += rhs.x;
        if (res >= mod)
            res -= mod;
        return res;
    }
    inline modint operator-(const modint &rhs) const
    {
        int res = x;
        res -= rhs.x;
        if (res < 0)
            res += mod;
        return res;
    }
    inline modint operator*(const modint &rhs) const
    {
        return (int)((ll)x * rhs.x % mod);
    }
    inline modint &operator+=(const modint &rhs)
    {
        x += rhs.x;
        if (x >= mod)
            x -= mod;
        return *this;
    }
    inline modint &operator-=(const modint &rhs)
    {
        x -= rhs.x;
        if (x < 0)
            x += mod;
        return *this;
    }
    inline modint &operator*=(const modint &rhs)
    {
        x = (int)((ll)x * rhs.x % mod);
        return *this;
    }
    template <typename _G>
    inline modint operator^(_G rhs) const
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
    inline modint inv() const
    {
        return *this ^ (mod - 2);
    }
    inline modint operator/(const modint &rhs) const
    {
        return (*this) * rhs.inv();
    }
    inline modint &operator/=(const modint &rhs)
    {
        return (*this) *= rhs.inv();
    }
    inline bool operator==(const modint &rhs) const
    {
        return x == rhs.x;
    }
    inline bool operator!=(const modint &rhs) const
    {
        return x != rhs.x;
    }
    inline int &data()
    {
        return x;
    }
};
modint f[N][N], g[N][N], C[N][N];
signed main()
{
    read(n, m, mod);
    g[0][0] = 1;
    auto calc = [](int x)
    {
        return (int)((ll)x * (x + 1) / 2);
    };
    C[0][0] = 1;
    for (int i = 1; i <= n; ++i)
    {
        C[i][0] = 1;
        for (int j = 1; j <= i; ++j)
            C[i][j] = C[i - 1][j] + C[i - 1][j - 1];
    }
    for (int i = 1; i <= n; ++i)
    {
        for (int j = 1; j <= i; ++j)
        {
            modint s = f[j - 1][j - 1] * g[i - j][i - j] + f[i - j][i - j] * g[j - 1][j - 1];
            modint t = g[j - 1][j - 1] * g[i - j][i - j] * C[i - 1][j - 1];
            g[i][i] += t * (i + 1);
            f[i][i] += t * (calc(j - 1) + calc(i - j)) + C[i - 1][j - 1] * (i + 1) * s;
        }
    }
    for (int i = 1; i <= n; ++i)
    {
        for (int j = 0; j < i; ++j)
        {
            f[i][j] = f[i - 1][j];
            g[i][j] = g[i - 1][j];
            for (int k = 1; k <= j; k++)
            {
                g[i][j] += g[k][k] * g[i - k - 1][j - k] * C[j][k];
                f[i][j] += (f[i - k - 1][j - k] * g[k][k] + f[k][k] * g[i - k - 1][j - k]) * C[j][k];
            }
        }
    }
    write(f[n][m].data(), '\n');
#ifdef FAST_OUT
    IO::OUTPUT::flush();
#endif
    return 0;
}