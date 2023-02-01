/**
 *    unicode: UTF-8
 *    name:    #509. 「状压 DP」网格染色
 *    author:  whitepaperdog (蒟蒻wjr)
 *    located: Changle District, Fuzhou City, Fujian Province, China
 *    created: 2023.01.31 周二 14:30:23 (Asia/Shanghai)
 **/
#include <bits/move.h>
#include <cstdio>
typedef long long ll;
typedef unsigned long long ull;
constexpr auto lowbit = [](const auto &x)
{ return x & (-x); };

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
            while (!((_s >= 0x0a && _s <= 0x0d) || (_s == 0x09) || (_s == 0x20)))
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
    constexpr inline modint inv()
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
    constexpr inline modint &operator==(const modint &rhs)
    {
        return x == rhs.x;
    }
    constexpr inline int &data()
    {
        return x;
    }
};
template <typename _T, const int MAXN, const int MAXM>
struct Graph
{
    struct Edge
    {
        int next;
        _T to;
    } edge[MAXM];
    int head[MAXN], num_edge;
    inline void add_edge(int from, _T to)
    {
        edge[++num_edge].next = head[from];
        edge[num_edge].to = to;
        head[from] = num_edge;
    }
#define foreach(i, graph, u) for (int i = graph.head[u]; i; i = graph.edge[i].next)
};
using IO::INPUT::read;
using IO::OUTPUT::write;
using namespace std;
constexpr int N = 1.5e4 + 5;
constexpr int M = N * 6;
constexpr int mod = 998244353;
typedef modint<mod> node;
constexpr node inv3 = ((node)3).inv();
int n, m;
int rk[M], limit, len;
int pop[8];
inline void NTT(node *dp)
{
    for (int i = 0; i < limit; ++i)
        if (i < rk[i])
            swap(dp[i], dp[rk[i]]);
    for (int mid = 1; mid < limit; mid <<= 1)
    {
        node gn = (node)3 ^ ((mod - 1) / (mid << 1));
        for (int i = 0; i < limit; i += mid << 1)
        {
            node g = 1;
            for (int j = 0; j < mid; ++j, g *= gn)
            {
                node x = dp[i + j], y = dp[i + j + mid] * g;
                dp[i + j] = x + y;
                dp[i + j + mid] = x - y;
            }
        }
    }
}
inline void INTT(node *dp)
{
    for (int i = 0; i < limit; ++i)
        if (i < rk[i])
            swap(dp[i], dp[rk[i]]);
    for (int mid = 1; mid < limit; mid <<= 1)
    {
        node gn = inv3 ^ ((mod - 1) / (mid << 1));
        for (int i = 0; i < limit; i += mid << 1)
        {
            node g = 1;
            for (int j = 0; j < mid; ++j, g *= gn)
            {
                node x = dp[i + j], y = dp[i + j + mid] * g;
                dp[i + j] = x + y;
                dp[i + j + mid] = x - y;
            }
        }
    }
    auto inv = ((node)limit).inv();
    for (int i = 0; i < limit; ++i)
        dp[i] *= inv;
}
node fuck[4][M];
struct Matrix
{
    node g[8][8][M];
} A, B, C;
int a[3];
signed main()
{
#ifdef PAPERDOG
    freopen("project.in", "r", stdin);
    freopen("project.out", "w", stdout);
#else
    freopen("final.in", "r", stdin);
    freopen("final.out", "w", stdout);
#endif
    read(n, m);
    for (int i = 0; i < 3; ++i)
        for (int j = 0; j < 3; ++j)
        {
            int x;
            read(x);
            a[i] |= x << j;
        }
    a[1] ^= 2;
    len  = 0, limit = 1;
    while (limit <= 3 * n)
    {
        limit <<= 1;
        ++len;
    }
    for (int i = 0; i < limit; ++i)
        rk[i] = (rk[i >> 1] >> 1) | ((i & 1) << (len - 1));
    for (int i = 0; i < 3; ++i)
        for (int j = 0; j < (1 << i); ++j)
            pop[1 << i | j] = pop[j] + 1;
    for (int i = 0; i <= 3; ++i)
    {
        fuck[i][i] = 1;
        NTT(fuck[i]);
    }
    for (int i = 0; i < 8; ++i)
    {
        if (i & 1 && a[1] >> 1 & i)
            continue;
        if (i >> 1 & 1 && a[1] & i)
            continue;
        if (i >> 2 & 1 && a[1] << 1 & i)
            continue;
        for (int j = 0; j < 8; ++j)
        {
            if (i & 1 && a[2] >> 1 & j)
                continue;
            if (i >> 1 & 1 && a[2] & j)
                continue;
            if (i >> 2 & 1 && a[2] << 1 & j)
                continue;
            if (j & 1 && a[1] >> 1 & j)
                continue;
            if (j >> 1 & 1 && a[1] & j)
                continue;
            if (j >> 2 & 1 && a[1] << 1 & j)
                continue;
            if (j & 1 && a[0] >> 1 & i)
                continue;
            if (j >> 1 & 1 && a[0] & i)
                continue;
            if (j >> 2 & 1 && a[0] << 1 & i)
                continue;
            for (int k = 0; k < limit; ++k)
                A.g[i][j][k] = fuck[pop[j]][k];
        }
    }
    for (int i = 0; i < limit; ++i)
        B.g[0][0][i] = fuck[0][i];
    int power = n;
    while (power)
    {
        if (power & 1)
        {
            for (int i = 0; i < 8; ++i)
                for (int k = 0; k < 8; ++k)
                    for (int j = 0; j < 8; ++j)
                        for (int l = 0; l < limit; ++l)
                            C.g[i][j][l] += B.g[i][k][l] * A.g[k][j][l];
            for (int i = 0; i < 8; ++i)
                for (int j = 0; j < 8; ++j)
                    for (int k = 0; k < limit; ++k)
                    {
                        B.g[i][j][k] = C.g[i][j][k];
                        C.g[i][j][k] = 0;
                    }
        }
        for (int i = 0; i < 8; ++i)
            for (int k = 0; k < 8; ++k)
                for (int j = 0; j < 8; ++j)
                    for (int l = 0; l < limit; ++l)
                        C.g[i][j][l] += A.g[i][k][l] * A.g[k][j][l];
        for (int i = 0; i < 8; ++i)
            for (int j = 0; j < 8; ++j)
                for (int k = 0; k < limit; ++k)
                {
                    A.g[i][j][k] = C.g[i][j][k];
                    C.g[i][j][k] = 0;
                }
        power >>= 1;
    }
    node ans = 0;
    for (int i = 0; i < 8; ++i)
    {
        INTT(B.g[0][i]);
        ans += B.g[0][i][m];
    }
    write(ans.data(), '\n');
#ifdef FAST_OUT
    IO::OUTPUT::flush();
#endif
    return 0;
}