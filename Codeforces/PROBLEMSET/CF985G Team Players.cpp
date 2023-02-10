/**
 *    name:     CF985G Team Players
 *    author:   whitepaperdog (蒟蒻wjr)
 *    located:  Changle District, Fuzhou City, Fujian Province, China
 *    created:  2023.02.10 周五 15:56:02 (Asia/Shanghai)
 *    unicode:  UTF-8
 *    standard: C++23
 **/
#include <algorithm>
#include <bits/move.h>
#include <cstdio>
#include <vector>
typedef long long ll;
typedef unsigned long long ull;
__extension__ typedef __int128 int128;
constexpr auto lowbit = [](const auto &u)
{ return u & (-u); };

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
#define putchar(C) (_now - _buf == FAST_OUT_BUFFER_SIZE ? flush(), *_now++ = C : *_now++ = C)
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
    int u;
    constexpr modint(int _x = 0) : u(_x) {}
    constexpr inline modint operator+() const
    {
        return *this;
    }
    constexpr inline modint operator-() const
    {
        return !u ? 0 : _mod - u;
    }
    constexpr inline modint &operator++()
    {
        ++u;
        if (u >= _mod)
            u -= _mod;
        return *this;
    }
    constexpr inline modint &operator--()
    {
        --u;
        if (u < 0)
            u += _mod;
        return *this;
    }
    constexpr inline modint operator++(int)
    {
        int res = u;
        if (u >= _mod)
            u -= _mod;
        return res;
    }
    constexpr inline modint operator--(int)
    {
        int res = u;
        if (u < 0)
            u += _mod;
        return res;
    }
    constexpr inline modint operator+(const modint &rhs) const
    {
        int res = u;
        res += rhs.u;
        if (res >= _mod)
            res -= _mod;
        return res;
    }
    constexpr inline modint operator-(const modint &rhs) const
    {
        int res = u;
        res -= rhs.u;
        if (res < 0)
            res += _mod;
        return res;
    }
    constexpr inline modint operator*(const modint &rhs) const
    {
        return (int)((ll)u * rhs.u % _mod);
    }
    constexpr inline modint &operator+=(const modint &rhs)
    {
        u += rhs.u;
        if (u >= _mod)
            u -= _mod;
        return *this;
    }
    constexpr inline modint &operator-=(const modint &rhs)
    {
        u -= rhs.u;
        if (u < 0)
            u += _mod;
        return *this;
    }
    constexpr inline modint &operator*=(const modint &rhs)
    {
        u = (int)((ll)u * rhs.u % _mod);
        return *this;
    }
    template <typename _G>
    constexpr inline modint operator^(_G rhs) const
    {
        modint A = u, res = 1;
        while (rhs)
        {
            if (rhs & 1)
                res *= A;
            A *= A;
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
    constexpr inline modint &operator==(const modint &rhs)
    {
        return u == rhs.u;
    }
    constexpr inline int &data()
    {
        return u;
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
constexpr int N = 2e5 + 5;
int n, m;
ull A, B, C;
vector<int> g[N], h[N];
struct Edge
{
    int next, to;
} edge[N * 2];
int head[N], num_edge;
inline void add_edge(int from, int to)
{
    edge[++num_edge].next = head[from];
    edge[num_edge].to = to;
    head[from] = num_edge;
}
struct node
{
    int u, v;
} e[N];
int deg[N];
int vis[N], vistime;
inline ull calc(int l, int r)
{
    return (ull)(l + r) * (r - l + 1) / 2;
};
inline ull solve0()
{
    ull res = 0;
    for (int i = 1; i <= n; ++i)
    {
        res += A * (n - i) * (n - i - 1) / 2 * (i - 1);
        res += B * (i - 1) * (n - i) * (i - 1);
        res += C * (i - 1) * (i - 2) / 2 * (i - 1);
    }
    return res;
}
inline ull solve1()
{
    ull res = 0;
    for (int i = 1; i <= m; ++i)
    {
        auto [u, v] = e[i];
        res += A * (n - u - 1) * (u - 1);
        res += B * (u - 1) * (u - 1);
        res += B * (n - v) * (v - 1);
        res += C * (v - 2) * (v - 1);
        res += A * (u - 2) * (u - 1) / 2;
        res += B * (u + v - 2) * (v - u - 1) / 2;
        res += C * (v + n - 1) * (n - v) / 2;
    }
    return res;
}
inline ull solve2()
{
    ull res = 0;
    for (int i = 1; i <= n; ++i)
    {
        g[i].push_back(i);
        sort(g[i].begin(), g[i].end());
        for (int j = 0; j < (int)g[i].size(); ++j)
        {
            int u = g[i][j];
            if (u != i)
            {
                if (u < i)
                {
                    res += A * (g[i].size() - j - 2) * (u - 1);
                    res += B * j * (u - 1);
                }
                else
                {
                    res += B * (g[i].size() - j - 1) * (u - 1);
                    res += C * (j - 1) * (u - 1);
                }
            }
            else
            {
                res += C * j * (j - 1) / 2 * (u - 1);
                res += B * j * (g[i].size() - j - 1) * (u - 1);
                res += A * (g[i].size() - j - 1) * (g[i].size() - j - 2) / 2 * (u - 1);
            }
        }
    }
    return res;
}
inline ull solve3()
{
    ull res = 0;
    for (int i = 1; i <= n; ++i)
    {
        ++vistime;
        for (int j : h[i])
            vis[j] = vistime;
        for (int j : h[i])
            for (int k : h[j])
                if (vis[k] == vistime)
                {
                    if (i < j)
                    {
                        if (j < k)
                            res += A * i + B * j + C * k;
                        else if (i < k)
                            res += A * i + B * k + C * j;
                        else
                            res += A * k + B * i + C * j;
                    }
                    else
                    {
                        if (j > k)
                            res += A * k + B * j + C * i;
                        else if (i > k)
                            res += A * j + B * k + C * i;
                        else
                            res += A * j + B * i + C * k;
                    }
                    res -= A + B + C;
                }
    }
    return res;
}
signed main()
{
    read(n, m);
    read(A, B, C);
    for (int i = 1; i <= m; ++i)
    {
        auto &[u, v] = e[i];
        read(u, v);
        ++u, ++v;
        if (u > v)
            swap(u, v);
        g[u].push_back(v);
        g[v].push_back(u);
        ++deg[u], ++deg[v];
    }
    for (int i = 1; i <= m; ++i)
    {
        auto [u, v] = e[i];
        if (deg[u] > deg[v] || (deg[u] == deg[v] && u > v))
            swap(u, v);
        h[u].push_back(v);
    }
    write(solve0() - solve1() + solve2() - solve3(), '\n');
#ifdef FAST_OUT
    IO::OUTPUT::flush();
#endif
    return 0;
}