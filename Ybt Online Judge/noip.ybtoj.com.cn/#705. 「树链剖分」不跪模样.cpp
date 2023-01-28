/**
 *    unicode: UTF-8
 *    name:    B. 不跪模样
 *    author:  whitepaperdog (蒟蒻wjr)
 *    located: Changle District, Fuzhou City, Fujian Province, China
 *    created: 2023.01.28 周六 09:45:19 (Asia/Shanghai)
 **/
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
template <typename _T, const _T _mod>
struct modint
{
    _T x;
    modint(_T _x = 0) : x(_x) {}
    inline modint operator+() const
    {
        return *this;
    }
    inline modint operator-() const
    {
        return !x ? 0 : _mod - x;
    }
    inline modint &operator++()
    {
        ++x;
        if (x >= _mod)
            x -= _mod;
        return *this;
    }
    inline modint &operator--()
    {
        --x;
        if (x < 0)
            x += _mod;
        return *this;
    }
    inline modint operator++(_T)
    {
        int res = x;
        if (x >= _mod)
            x -= _mod;
        return res;
    }
    inline modint operator--(_T)
    {
        int res = x;
        if (x < 0)
            x += _mod;
        return res;
    }
    inline modint operator+(const modint &rhs) const
    {
        _T res = x;
        res += rhs.x;
        if (res >= _mod)
            res -= _mod;
        return res;
    }
    inline modint operator-(const modint &rhs) const
    {
        _T res = x;
        res -= rhs.x;
        if (res < 0)
            res += _mod;
        return res;
    }
    inline modint operator*(const modint &rhs) const
    {
        return (_T)((ll)x * rhs.x % _mod);
    }
    inline modint &operator+=(const modint &rhs)
    {
        x += rhs.x;
        if (x >= _mod)
            x -= _mod;
        return *this;
    }
    inline modint &operator-=(const modint &rhs)
    {
        x -= rhs.x;
        if (x < 0)
            x += _mod;
        return *this;
    }
    inline modint &operator*=(const modint &rhs)
    {
        x = (_T)((ll)x * rhs.x % _mod);
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
    inline modint inv()
    {
        return this->pow(_mod - 2);
    }
    inline modint operator/(const modint &rhs) const
    {
        return (*this) * rhs.inv();
    }
    inline modint &operator/=(const modint &rhs)
    {
        return (*this) *= rhs.inv();
    }
    inline modint &operator==(const modint &rhs)
    {
        return x == rhs.x;
    }
    inline _T &data()
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
constexpr int N = 3e5 + 5;
int n, q;
unsigned a[N], b[N], c[N], all[N];
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
int sze[N], son[N];
int dep[N], fa[N];
int dfn[N], rk[N], dfstime;
int top[N];
unsigned dep1[N], dep2[N], depdep[N], depdep2[N];
inline void dfs1(int u, int _fa)
{
    sze[u] = 1;
    dep[u] = dep[fa[u] = _fa] + 1;
    all[u] = a[u];
    b[u] = a[u] * 2;
    dep1[u] = dep2[u] = 1;
    depdep[u] = depdep2[u] = 2;
    for (int i = head[u]; i; i = edge[i].next)
    {
        int v = edge[i].to;
        dfs1(v, u);

        b[u] += all[u] * sze[v] + all[v] * sze[u];
        all[u] += all[v];

        depdep[u] += dep2[u] * sze[v] + sze[u] * dep1[v];
        depdep2[u] += dep1[u] * sze[v] + sze[u];
        ++dep1[u];
        dep2[u] += dep1[v];

        sze[u] += sze[v];
        if (sze[son[u]] < sze[v])
            son[u] = v;
    }
}
inline void dfs2(int u, int topf)
{
    rk[dfn[u] = ++dfstime] = u;
    top[u] = topf;
    if (son[u])
        dfs2(son[u], topf);
    for (int i = head[u]; i; i = edge[i].next)
    {
        int v = edge[i].to;
        if (v == son[u])
            continue;
        dfs2(v, v);
    }
}
struct Tree
{
    unsigned k, b, sum, ans;
    inline void updatek(unsigned _val)
    {
        k += _val;
        ans += _val * sum;
    }
    inline void updateb(unsigned _val)
    {
        b += _val;
        ans += _val;
    }
} tree[N * 4];
#define lc (rt << 1)
#define rc (rt << 1 | 1)
inline void pushup(int rt)
{
    tree[rt].ans = tree[lc].ans + tree[rc].ans;
}
inline void pushdown(int rt)
{
    if (tree[rt].k)
    {
        tree[lc].updatek(tree[rt].k);
        tree[rc].updatek(tree[rt].k);
        tree[rt].k = 0;
    }
    if (tree[rt].b)
    {
        tree[lc].updateb(tree[rt].b);
        tree[rc].updateb(tree[rt].b);
        tree[rt].b = 0;
    }
}
inline void build(int rt, int l, int r)
{
    if (l == r)
    {
        tree[rt].sum = sze[rk[l]] - sze[son[rk[l]]];
        return;
    }
    int mid = (l + r) >> 1;
    build(lc, l, mid);
    build(rc, mid + 1, r);
    tree[rt].sum = tree[lc].sum + tree[rc].sum;
}
inline void updatek(int rt, int l, int r, int x, int y, unsigned val)
{
    if (r < x || l > y)
        return;
    if (x <= l && r <= y)
        return tree[rt].updatek(val);
    int mid = (l + r) >> 1;
    pushdown(rt);
    updatek(lc, l, mid, x, y, val);
    updatek(rc, mid + 1, r, x, y, val);
    pushup(rt);
}
inline void updateb(int rt, int l, int r, int x, int y, unsigned val)
{
    if (r < x || l > y)
        return;
    if (x <= l && r <= y)
        return tree[rt].updateb(val);
    int mid = (l + r) >> 1;
    pushdown(rt);
    updateb(lc, l, mid, x, y, val);
    updateb(rc, mid + 1, r, x, y, val);
    pushup(rt);
}
inline unsigned query(int rt, int l, int r, int pos)
{
    if (l == r)
        return tree[rt].ans;
    int mid = (l + r) >> 1;
    pushdown(rt);
    if (pos <= mid)
        return query(lc, l, mid, pos);
    else
        return query(rc, mid + 1, r, pos);
}
inline void update(int x, unsigned v)
{
    b[x] += depdep[x] * v;
    c[x] += v;
    v *= dep2[x];
    while (top[x] != 1)
    {
        updatek(1, 1, n, dfn[top[x]], dfn[x] - 1, v);
        x = top[x];
        b[fa[x]] += (sze[fa[x]] - sze[x]) * v;
        x = fa[x];
    }
    updatek(1, 1, n, 1, dfn[x] - 1, v);
}
inline unsigned query(int x)
{
    auto res = b[x] + query(1, 1, n, dfn[x]);
    if (fa[x])
    {
        res += depdep2[x] * c[fa[x]];
        if (fa[fa[x]])
            res += (sze[x] + 1) * c[fa[fa[x]]];
    }
    return res;
}
inline void dfs(int u, int _fa)
{
    printf("%d %d\n", _fa, u);
    for (int i = head[u]; i; i = edge[i].next)
    {
        int v = edge[i].to;
        dfs(v, u);
    }
}
signed main()
{
#ifdef PAPERDOG
    freopen("project.in", "r", stdin);
    freopen("project.out", "w", stdout);
#else
    freopen("tree.in", "r", stdin);
    freopen("tree.out", "w", stdout);
#endif
    read(n, q);
    for (int i = 2; i <= n; ++i)
    {
        int _fa;
        read(_fa);
        add_edge(_fa, i);
    }
    for (int i = 1; i <= n; ++i)
        read(a[i]);
    dfs1(1, 0);
    dfs2(1, 1);
    build(1, 1, n);
    while (q--)
    {
        int opt, x;
        unsigned v;
        read(opt, x);
        if (opt == 1)
        {
            read(v);
            update(x, v);
        }
        else
            write(query(x), '\n');
    }
#ifdef FAST_OUT
    IO::OUTPUT::flush();
#endif
    return 0;
}