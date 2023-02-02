/**
 *    unicode: UTF-8
 *    name:    A. 寄蒜挤河
 *    author:  whitepaperdog (蒟蒻wjr)
 *    located: Changle District, Fuzhou City, Fujian Province, China
 *    created: 2023.02.02 周四 08:28:38 (Asia/Shanghai)
 **/
#include <algorithm>
#include <cmath>
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
constexpr int N = 4e5 + 5;
constexpr long double pi = M_PIl;
constexpr long double eps = 1e-18;
int n;
long double a[N], b[N];
struct Tree
{
    int size;
    int add;
    ll sum;
    inline void update(int val)
    {
        add += val;
        sum += (ll)size * val;
    }
} tree[N * 4];
#define lc (rt << 1)
#define rc (rt << 1 | 1)
inline void pushup(int rt)
{
    tree[rt].sum = tree[lc].sum + tree[rc].sum;
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
    tree[rt].sum = tree[rt].add = tree[rt].size = 0;
    if (l == r)
        return;
    int mid = (l + r) >> 1;
    build(lc, l, mid);
    build(rc, mid + 1, r);
    pushup(rt);
}
inline void update(int rt, int l, int r, int pos)
{
    ++tree[rt].size;
    if (l == r)
    {
        tree[rt].sum = tree[rt].add;
        return;
    }
    int mid = (l + r) >> 1;
    pushdown(rt);
    if (pos <= mid)
        update(lc, l, mid, pos);
    else
        update(rc, mid + 1, r, pos);
    pushup(rt);
}
inline void update(int rt, int l, int r, int x, int y)
{
    if (r < x || l > y)
        return;
    if (x <= l && r <= y)
        return tree[rt].update(1);
    int mid = (l + r) >> 1;
    pushdown(rt);
    update(lc, l, mid, x, y);
    update(rc, mid + 1, r, x, y);
    pushup(rt);
}
inline int querysize(int rt, int l, int r, int x, int y)
{
    if (r < x || l > y)
        return 0;
    if (x <= l && r <= y)
        return tree[rt].size;
    int mid = (l + r) >> 1;
    pushdown(rt);
    return querysize(lc, l, mid, x, y) + querysize(rc, mid + 1, r, x, y);
}
inline ll querysum(int rt, int l, int r, int x, int y)
{
    if (r < x || l > y)
        return 0;
    if (x <= l && r <= y)
        return tree[rt].sum;
    int mid = (l + r) >> 1;
    pushdown(rt);
    return querysum(lc, l, mid, x, y) + querysum(rc, mid + 1, r, x, y);
}
inline int query(int rt, int l, int r, int pos)
{
    if (l == r)
        return tree[rt].add;
    int mid = (l + r) >> 1;
    pushdown(rt);
    if (pos <= mid)
        return query(lc, l, mid, pos);
    else
        return query(rc, mid + 1, r, pos);
}
int p[N], q[N];
inline long double oppsite(long double x)
{
    return x <= 0 ? x + pi : x - pi;
}
ll answer[N];
signed main()
{
#ifdef PAPERDOG
    freopen("project.in", "r", stdin);
    freopen("project.out", "w", stdout);
#else
    freopen("geometry.in", "r", stdin);
    freopen("geometry.out", "w", stdout);
#endif
    read(n);
    for (int i = 1; i <= n; ++i)
    {
        int x, y;
        read(x, y);
        a[i] = atan2l(y, x);
        p[i] = i;
    }
    sort(p + 1, p + 1 + n, [](int x, int y)
         { return a[x] < a[y]; });
    for (int i = 1; i <= n; ++i)
        b[q[p[i]] = i] = a[p[i]];
    for (int i = 1; i <= n; ++i)
    {
        if (a[i] <= 0)
        {
            int l = (int)(upper_bound(b + 1, b + 1 + n, a[i]) - b);
            int r = (int)(lower_bound(b + 1, b + 1 + n, oppsite(a[i])) - b - 1);
            answer[i] = querysum(1, 1, n, l, r) -
                        (ll)(query(1, 1, n, l - 1) +
                             querysize(1, 1, n, (int)(lower_bound(b + 1, b + 1 + n, oppsite(a[i])) - b),
                                       (int)(upper_bound(b + 1, b + 1 + n, oppsite(a[i])) - b - 1))) *
                            querysize(1, 1, n, l, r);
        }
        update(1, 1, n, q[i]);
        update(1, 1, n, (int)(upper_bound(b + 1, b + 1 + n, oppsite(a[i])) - b), n);
    }
    build(1, 1, n);
    for (int i = 1; i <= n; ++i)
        a[i] = oppsite(a[i]);
    sort(p + 1, p + 1 + n, [](int x, int y)
         { return a[x] < a[y]; });
    for (int i = 1; i <= n; ++i)
        b[q[p[i]] = i] = a[p[i]];
    for (int i = 1; i <= n; ++i)
    {
        if (a[i] < 0)
        {
            int l = (int)(upper_bound(b + 1, b + 1 + n, a[i]) - b);
            int r = (int)(lower_bound(b + 1, b + 1 + n, oppsite(a[i])) - b - 1);
            answer[i] = querysum(1, 1, n, l, r) -
                        (ll)(query(1, 1, n, l - 1) +
                             querysize(1, 1, n, (int)(lower_bound(b + 1, b + 1 + n, oppsite(a[i])) - b),
                                       (int)(upper_bound(b + 1, b + 1 + n, oppsite(a[i])) - b - 1))) *
                            querysize(1, 1, n, l, r);
        }
        update(1, 1, n, q[i]);
        update(1, 1, n, (int)(upper_bound(b + 1, b + 1 + n, oppsite(a[i])) - b), n);
    }
    for (int i = 1; i <= n; ++i)
        write(answer[i] += answer[i - 1], '\n');
#ifdef FAST_OUT
    IO::OUTPUT::flush();
#endif
    return 0;
}