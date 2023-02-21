/**
 *    name:     #13417. 「20230218」拍劣
 *    author:   whitepaperdog (蒟蒻wjr)
 *    located:  Changle District, Fuzhou City, Fujian Province, China
 *    created:  2023.02.20 周一 13:08:53 (Asia/Shanghai)
 *    unicode:  UTF-8
 *    standard: c++23
 **/
#include <bits/stl_pair.h>
#include <cstdio>
#include <random>
typedef long long ll;
typedef unsigned long long ull;
__extension__ typedef __int128 int128;
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
constexpr int N = 1e5 + 5;
int n, q;
int p[N];
struct Tree
{
    int ch[2], fa;
    long unsigned int key;
    int val;
    int size;
} tree[N];
#define lc(x) tree[x].ch[0]
#define rc(x) tree[x].ch[1]
#define fa(x) tree[x].fa
int root;
mt19937 rnd((random_device())());
inline int newnode(int val)
{
    int now = val;
    tree[now].val = val;
    tree[now].key = rnd();
    tree[now].size = 1;
    lc(now) = rc(now) = fa(now) = 0;
    return now;
}
inline void pushup(int x)
{
    tree[x].size = tree[lc(x)].size + tree[rc(x)].size + 1;
    if (lc(x))
        fa(lc(x)) = x;
    if (rc(x))
        fa(rc(x)) = x;
}
inline void split(int now, int sze, int &x, int &y)
{
    if (!now)
        x = y = 0;
    else
    {
        if (tree[lc(now)].size < sze)
        {
            x = now;
            split(rc(x), sze - tree[lc(x)].size - 1, rc(x), y);
            pushup(x);
        }
        else
        {
            y = now;
            split(lc(y), sze, x, lc(y));
            pushup(y);
        }
    }
}
inline int merge(int x, int y)
{
    if (!x || !y)
        return x | y;
    if (tree[x].key > tree[y].key)
    {
        rc(x) = merge(rc(x), y);
        pushup(x);
        return x;
    }
    else
    {
        lc(y) = merge(x, lc(y));
        pushup(y);
        return y;
    }
}
pair<int, int> answer[N * 2];
int answertot;
inline void swap(int x, int y)
{
    answer[++answertot] = make_pair(x, y);
    int a, b, c;
    split(root, x, a, b);
    split(b, n - x - y, b, c);
    root = merge(c, merge(b, a));
}
inline int query(int x)
{
    int res = 1 + tree[lc(x)].size;
    while (fa(x))
    {
        if (x == rc(fa(x)))
            res += tree[lc(fa(x))].size + 1;
        x = fa(x);
    }
    return res;
}
inline void solve0()
{
    int x = query(n), y = query(n - 1);
    if (x == n)
        swap(1 + (y == 1), 1);
    else if (x == n - 1)
    {
        if (y == 1)
            swap(1, 1);
        swap(1, 2);
    }
    else
    {
        swap(x, 1);
        swap(1 + (y == n), 1);
    }
}
inline void solve1()
{
    for (int i = n - 1; i >= 4; --i)
    {
        int pos = query(i);
        swap(n - i, n - pos);
        swap(1 + (query(i - 1) == 1), n - i + 1);
    }
}
inline void solve2()
{
    int pos = query(3);
    swap(n - 3, n - pos);
    if (query(2) == 1)
    {
        swap(1, n - 2);
        swap(1, 1);
        swap(n - 2, 1);
        swap(2, n - 3);
        swap(n - 3, 1);
    }
}
inline void _main()
{
    read(n, q);
    for (int i = 1; i <= n; ++i)
    {
        int x;
        read(x);
        root = merge(root, newnode(x));
    }
    if (n == 3)
    {
        if (query(1) > query(3))
            swap(1, 1);
    }
    else
    {
        solve0();
        solve1();
        solve2();
    }
    write(answertot, '\n');
    for (int i = 1; i <= answertot; ++i)
        write(answer[i].first, ' ', answer[i].second, '\n');
    root = answertot = 0;
}
signed main()
{
#ifdef PAPERDOG
    freopen("project.in", "r", stdin);
    freopen("project.out", "w", stdout);
#else
    freopen("permutation.in", "r", stdin);
    freopen("permutation.out", "w", stdout);
#endif
    int T = 1;
    read(T);
    while (T--)
        _main();
#ifdef FAST_OUT
    IO::OUTPUT::flush();
#endif
    return 0;
}