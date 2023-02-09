// LUOGU_RID: 100880523
/**
 *    unicode: UTF-8
 *    name:    C. 天气之子
 *    author:  whitepaperdog (蒟蒻wjr)
 *    located: Changle District, Fuzhou City, Fujian Province, China
 *    created: 2023.01.30 周一 14:10:02 (Asia/Shanghai)
 **/
#include <algorithm>
#include <cstdio>
#define ll long long
#define lll __int128
#define ull unsigned ll
#define lowbit(_x) (_x & (-_x))

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
constexpr int N = 2e5 + 5, M = 455;
int n, q;
int a[N], b[N];
struct Edge
{
    int next, to;
} edge[N];
int head[N], num_edge;
inline void add_edge(int from, int to)
{
    edge[++num_edge].next = head[from];
    edge[num_edge].to = to;
    head[from] = num_edge;
}
int dfn[N], low[N], rk[N], dfstime;
inline void dfs(int u, int _fa)
{
    a[u] += a[_fa];
    b[u] += b[_fa];
    rk[dfn[u] = ++dfstime] = u;
    for (int i = head[u]; i; i = edge[i].next)
    {
        int v = edge[i].to;
        dfs(v, u);
    }
    low[u] = dfstime;
}
int block, num;
int belong[N];
struct node
{
    int L, R;
    int st1[M], top1;
    int st2[M], top2;
    int tag;
    int p[M], tot;
    int head, tail;
#define X(x) (b[x])
#define Y(x) ((ll)a[x] * b[x])
    inline void rebuild()
    {
        top1 = 0, top2 = 0;
        for (int i = 1; i <= tot; ++i)
        {
            while (top1 > 1 &&
                   (X(st1[top1 - 1]) - X(st1[top1])) * (Y(p[i]) - Y(st1[top1])) <=
                       (Y(st1[top1 - 1]) - Y(st1[top1])) * (X(p[i]) - X(st1[top1])))
                --top1;
            st1[++top1] = p[i];
        }
        for (int i = 1; i <= tot; ++i)
        {
            while (top2 > 1 &&
                   (X(st2[top2 - 1]) - X(st2[top2])) * (Y(p[i]) - Y(st2[top2])) >=
                       (Y(st2[top2 - 1]) - Y(st2[top2])) * (X(p[i]) - X(st2[top2])))
                --top2;
            st2[++top2] = p[i];
        }
        head = 1, tail = top2;
    }
    inline void build()
    {
        for (int i = L; i <= R; ++i)
            p[++tot] = rk[i];
        sort(p + 1, p + 1 + tot, [](int x, int y)
             { return b[x] < b[y]; });
        rebuild();
    }
    inline ll query()
    {
        while (head < top1 && (ll)(a[st1[head]] + tag) * b[st1[head]] <
                                  (ll)(a[st1[head + 1]] + tag) * b[st1[head + 1]])
            ++head;
        while (tail > 1 && (ll)(a[st2[tail]] + tag) * b[st2[tail]] >
                               (ll)(a[st2[tail - 1]] + tag) * b[st2[tail - 1]])
            --tail;
        return max((ll)(a[st1[head]] + tag) * b[st1[head]],
                   -(ll)(a[st2[tail]] + tag) * b[st2[tail]]);
    }
    inline ll _query()
    {
        ll res = -1e18;
        // for (int i = 1; i <= tot; ++i)
        //     ckmax(res, (ll)abs(a[p[i]] + tag) * b[p[i]]);
        for (int i = 1; i <= top1; ++i)
            ckmax(res, (ll)(a[st1[i]] + tag) * b[st1[i]]);
        // for (int i = 1; i <= top2; ++i)
        //     ckmax(res, (ll)abs(a[st2[i]] + tag) * b[st2[i]]);
        return res;
    }
    inline void print()
    {
        printf("%d:\n", top1);
        for (int i = 1; i <= top1; ++i)
            printf("%d,%lld\n", X(st1[i]), Y(st1[i]));
    }
#undef X
#undef Y
} c[M];
inline void update(int l, int r, int val)
{
    if (belong[l] == belong[r])
    {
        for (int i = l; i <= r; ++i)
            a[rk[i]] += val;
        c[belong[l]].rebuild();
        return;
    }
    for (int i = l; i <= c[belong[l]].R; ++i)
        a[rk[i]] += val;
    c[belong[l]].rebuild();
    for (int i = belong[l] + 1; i < belong[r]; ++i)
        c[i].tag += val;
    for (int i = c[belong[r]].L; i <= r; ++i)
        a[rk[i]] += val;
    c[belong[r]].rebuild();
}
inline ll query(int l, int r)
{
    if (belong[l] == belong[r])
    {
        ll res = -1e18;
        for (int i = l; i <= r; ++i)
            ckmax(res, (ll)abs(a[rk[i]] + c[belong[i]].tag) * b[rk[i]]);
        return res;
    }
    ll res = -1e18;
    for (int i = l; i <= c[belong[l]].R; ++i)
        ckmax(res, (ll)abs(a[rk[i]] + c[belong[i]].tag) * b[rk[i]]);
    for (int i = belong[l] + 1; i < belong[r]; ++i)
        ckmax(res, c[i].query());
    for (int i = c[belong[r]].L; i <= r; ++i)
        ckmax(res, (ll)abs(a[rk[i]] + c[belong[i]].tag) * b[rk[i]]);
    return res;
}
signed main()
{
    read(n, q);
    for (int i = 2; i <= n; ++i)
    {
        int _fa;
        read(_fa);
        add_edge(_fa, i);
    }
    for (int i = 1; i <= n; ++i)
        read(a[i]);
    for (int i = 1; i <= n; ++i)
        read(b[i]);
    dfs(1, 0);
    for (int i = 1; i <= n; ++i)
        if (b[i] < 0)
            b[i] = -b[i];
    block = (int)__builtin_sqrt(n);
    num = (n - 1) / block + 1;
    for (int i = 1; i <= num; ++i)
    {
        c[i].L = c[i - 1].R + 1;
        c[i].R = c[i - 1].R + block;
    }
    c[num].R = n;
    for (int i = 1; i <= num; ++i)
    {
        c[i].build();
        for (int j = c[i].L; j <= c[i].R; ++j)
            belong[j] = i;
    }
    for (int i = 1; i <= q; ++i)
    {
        int opt, x, y;
        read(opt, x);
        if (opt == 1)
        {
            read(y);
            update(dfn[x], low[x], y);
        }
        else
            write(query(dfn[x], low[x]), '\n');
    }
#ifdef FAST_OUT
    IO::OUTPUT::flush();
#endif
    return 0;
}