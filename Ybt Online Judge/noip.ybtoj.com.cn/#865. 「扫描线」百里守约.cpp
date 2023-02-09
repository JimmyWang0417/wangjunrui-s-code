/**
 *    name:     C. 百里守约
 *    author:   whitepaperdog (蒟蒻wjr)
 *    located:  Changle District, Fuzhou City, Fujian Province, China
 *    created:  2023.02.09 周四 19:48:20 (Asia/Shanghai)
 *    unicode:  UTF-8
 *    standard: c++23
 **/
#include <algorithm>
#include <bits/stl_pair.h>
#include <cstdio>
typedef long long ll;
typedef unsigned long long ull;
__extension__ typedef __int128 int128;
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
int n, m;
int fa[N];
inline int find(int x)
{
    return !fa[x] ? x : fa[x] = find(fa[x]);
}
struct Tree
{
    ll add;
    pair<ll, int> min[2];
    inline void update(ll _val)
    {
        add += _val;
        min[0].first += _val;
        min[1].first += _val;
    }
} tree[N * 4];
#define lc (rt << 1)
#define rc (rt << 1 | 1)
inline void pushup(int rt)
{
    if (tree[lc].min[0] < tree[rc].min[0])
    {
        tree[rt].min[0] = tree[lc].min[0];
        if (tree[rc].min[0].second != tree[rt].min[0].second)
            tree[rt].min[1] = min(tree[lc].min[1], tree[rc].min[0]);
        else
            tree[rt].min[1] = min(tree[lc].min[1], tree[rc].min[1]);
    }
    else
    {
        tree[rt].min[0] = tree[rc].min[0];
        if (tree[lc].min[0].second != tree[rt].min[0].second)
            tree[rt].min[1] = min(tree[lc].min[0], tree[rc].min[1]);
        else
            tree[rt].min[1] = min(tree[lc].min[1], tree[rc].min[1]);
    }
}
inline void pushdown(int rt)
{
    if (tree[rt].add)
    {
        tree[lc].update(tree[rt].add);
        tree[rc].update(tree[rt].add);
        tree[rt].add = 0;
    }
}
inline void build(int rt, int l, int r)
{
    tree[rt].add = 0;
    if (l == r)
    {
        tree[rt].min[0] = make_pair(0, find(l));
        tree[rt].min[1] = make_pair((ll)1e18, 0);
        return;
    }
    int mid = (l + r) >> 1;
    build(lc, l, mid);
    build(rc, mid + 1, r);
    pushup(rt);
}
inline void update(int rt, int l, int r, int x, int y, int val)
{
    if (r < x || l > y)
        return;
    if (x <= l && r <= y)
        return tree[rt].update(val);
    int mid = (l + r) >> 1;
    pushdown(rt);
    update(lc, l, mid, x, y, val);
    update(rc, mid + 1, r, x, y, val);
    pushup(rt);
}
struct node
{
    int x, l, r, w;
    node(int _x = 0, int _l = 0, int _r = 0, int _w = 0) : x(_x), l(_l), r(_r), w(_w) {}
    inline bool operator<(const node &rhs) const
    {
        return x < rhs.x;
    }
} e[N * 4];
pair<ll, int> a[N];
signed main()
{
#ifdef PAPERDOG
    freopen("project.in", "r", stdin);
    freopen("project.out", "w", stdout);
#else
    freopen("rect.in", "r", stdin);
    freopen("rect.out", "w", stdout);
#endif
    read(n, m);
    int _m = 0;
    for (int i = 1; i <= m; ++i)
    {
        int x1, x2, y1, y2, w;
        read(x1, x2, y1, y2, w);
        e[++_m] = node(x1, y1, y2, w);
        e[++_m] = node(y1, x1, x2, w);
        e[++_m] = node(x2 + 1, y1, y2, -w);
        e[++_m] = node(y2 + 1, x1, x2, -w);
    }
    m = _m;
    sort(e + 1, e + 1 + m);
    ll answer = 0;
    while (1)
    {
        bool flag = true;
        for (int i = 2; i <= n; ++i)
            if (find(1) != find(i))
            {
                flag = false;
                break;
            }
        if (flag)
            break;
        for (int i = 1; i <= n; ++i)
            a[i] = make_pair(1e18, 0);
        build(1, 1, n);
        for (int i = 1, j = 1; i <= n; ++i)
        {
            while (j <= m && e[j].x <= i)
            {
                update(1, 1, n, e[j].l, e[j].r, e[j].w);
                ++j;
            }
            int bel = find(i);
            if (bel != tree[1].min[0].second)
                ckmin(a[bel], tree[1].min[0]);
            else
                ckmin(a[bel], tree[1].min[1]);
        }
        for (int i = 1; i <= n; ++i)
            if (find(i) == i)
                if (i != find(a[i].second))
                {
                    fa[i] = a[i].second;
                    answer += a[i].first;
                }
    }
    write(answer, '\n');
#ifdef FAST_OUT
    IO::OUTPUT::flush();
#endif
    return 0;
}