/**
 *    unicode: UTF-8
 *    name:    matrix
 *    author:  whitepaperdog (蒟蒻wjr)
 *    located: Changle District, Fuzhou City, Fujian Province, China
 *    created: 2022.09.11 周日 09:32:28 (Asia/Shanghai)
 **/
#include <cstdio>
#include <cstring>
#include <random>
#define ll long long
#define lll __int128
#define ull unsigned ll
#define lowbit(_x) (_x & (-_x))

//#define FAST_IO

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
        inline void read(char *_x)
        {
            char _s = (char)getchar();
            int _len = 0;
            while ((_s >= 0x0a && _s <= 0x0d) || (_s == 0x09) || (_s == 0x20))
                _s = (char)getchar();
            while (!((_s >= 0x0a && _s <= 0x0d) || (_s == 0x09) || (_s == 0x20)))
            {
                _x[_len++] = _s;
                _s = (char)getchar();
            }
            _x[_len] = '\0';
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
                _x = (_x << 1) + (_x << 3) + _s - '0';
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
using namespace IO::INPUT;
using namespace IO::OUTPUT;
using namespace std;
constexpr int N = 1000 + 5;
int n, mod;
struct Matrix
{
    int n, m;
    int g[N][N];
    Matrix(int _n = 0, int _m = 0) : n(_n), m(_m) { memset(g, 0, sizeof(g)); }
    inline bool operator==(const Matrix &rhs) const
    {
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < m; ++j)
                if (g[i][j] != rhs.g[i][j])
                    return false;
        return true;
    }
    inline bool operator!=(const Matrix &rhs) const
    {
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < m; ++j)
                if (g[i][j] != rhs.g[i][j])
                    return true;
        return false;
    }
};
inline void calc(Matrix &x, const Matrix &y, const Matrix &z)
{
    memset(x.g, 0, sizeof(x.g));
    x.n = y.n, x.m = z.m;
    for (int i = 0; i < x.n; ++i)
        for (int k = 0; k < y.m; ++k)
            for (int j = 0; j < x.m; ++j)
                x.g[i][j] = (int)((x.g[i][j] + (ll)y.g[i][k] * z.g[k][j] % mod) % mod);
}
Matrix a, b, c, d, e, f, g;
signed main()
{
    freopen("matrix.in", "r", stdin);
    freopen("matrix.out", "w", stdout);
    mt19937 rnd((random_device())());
    int T = 1;
    read(T);
    while (T--)
    {
        read(mod, n);
        a.n = a.m = n;
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < n; ++j)
                read(a.g[i][j]);
        b.n = b.m = n;
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < n; ++j)
                read(b.g[i][j]);
        c.n = c.m = n;
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < n; ++j)
                read(c.g[i][j]);
        if (n <= 300)
        {
            calc(d, a, b);
            write(d == c ? "Yes\n" : "No\n");
        }
        else
        {
            uniform_int_distribution<> range(0, mod - 1);
            d.n = 1, d.m = n;
            for (int i = 0; i < n; ++i)
                d.g[0][i] = range(rnd);
            calc(e, d, a);
            calc(f, e, b);
            calc(g, d, c);
            if (f != g)
                write("No\n");
            else
            {
                for (int i = 0; i < n; ++i)
                    d.g[0][i] = range(rnd);
                calc(e, d, a);
                calc(f, e, b);
                calc(g, d, c);
                if (f != g)
                    write("No\n");
                else
                    write("Yes\n");
            }
        }
    }
#ifdef FAST_OUT
    flush();
#endif
    return 0;
}
