/**
 *    name:     P5642 人造情感（emotion）
 *    author:   whitepaperdog (蒟蒻wjr)
 *    located:  Xuanwu District, Nanjing City, Jiangsu Province, China
 *    created:  2023.03.01 周三 21:56:23 (Asia/Shanghai)
 *    unicode:  UTF-8
 *    standard: c++23
 **/
#include <algorithm>
#include <cstdio>
#include <list>
#include <stack>
#include <tuple>
#include <vector>
typedef long long ll;
typedef unsigned long long ull;
// __extension__ typedef __int128 int128;
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
constexpr int N = 3e5 + 5;
constexpr ll inf = 1e18;
constexpr int mod = 998244353;
int n, m;
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
int fa[N], dep[N];
int sze[N], son[N];
int top[N];
int dfn[N], rk[N], dfstime;
inline void dfs1(int u, int _fa)
{
    dep[u] = dep[fa[u] = _fa] + 1;
    sze[u] = 1;
    for (int i = head[u]; i; i = edge[i].next)
    {
        int v = edge[i].to;
        if (v == _fa)
            continue;
        dfs1(v, u);
        sze[u] += sze[v];
        if (sze[son[u]] < sze[v])
            son[u] = v;
    }
}
inline void dfs2(int u, int topf)
{
    top[u] = topf;
    rk[dfn[u] = ++dfstime] = u;
    if (son[u])
        dfs2(son[u], topf);
    for (int i = head[u]; i; i = edge[i].next)
    {
        int v = edge[i].to;
        if (dfn[v])
            continue;
        dfs2(v, v);
    }
}
inline int getlca(int u, int v)
{
    while (top[u] != top[v])
    {
        if (dep[top[u]] < dep[top[v]])
            swap(u, v);
        u = fa[top[u]];
    }
    if (dep[u] > dep[v])
        swap(u, v);
    return u;
}
inline int jump(int u, int p)
{
    int v = 0;
    while (top[u] != top[p])
    {
        v = top[u];
        u = fa[top[u]];
    }
    return u == p ? v : rk[dfn[p] + 1];
}
struct
{
    ll tree[N];
    inline void update(int pos, ll val)
    {
        for (int i = pos; i <= n; i += lowbit(i))
            tree[i] += val;
    }
    inline void update(int l, int r, ll val)
    {
        update(l, val);
        update(r + 1, -val);
    }
    inline ll query(int pos)
    {
        ll res = 0;
        for (int i = pos; i; i -= lowbit(i))
            res += tree[i];
        return res;
    }
} indexed;
vector<tuple<int, int, int>> que[N];
vector<tuple<ll, int, int>> qwq[N];
struct
{
    struct
    {
        ll max, tag;
        inline void update(ll val)
        {
            ckmax(max, val);
            ckmax(tag, val);
        }
    } tree[N * 4];
#define lc (rt << 1)
#define rc (rt << 1 | 1)
    inline void pushup(int rt)
    {
        tree[rt].max = max(tree[lc].max, tree[rc].max);
    }
    inline void pushdown(int rt)
    {
        if (tree[rt].tag != -inf)
        {
            tree[lc].update(tree[rt].tag);
            tree[rc].update(tree[rt].tag);
            tree[rt].tag = -inf;
        }
    }
    inline void build(int rt, int l, int r)
    {
        tree[rt].max = tree[rt].tag = -inf;
        if (l == r)
            return;
        int mid = (l + r) >> 1;
        build(lc, l, mid);
        build(rc, mid + 1, r);
    }
    inline void update(int rt, int l, int r, int x, int y, ll val)
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
    inline ll query(int rt, int l, int r, int pos)
    {
        if (l == r)
            return tree[rt].max;
        int mid = (l + r) >> 1;
        pushdown(rt);
        if (pos <= mid)
            return query(lc, l, mid, pos);
        else
            return query(rc, mid + 1, r, pos);
    }
    inline void update(int u, int v, ll w)
    {
        int las = 0;
        while (top[u] != top[v])
        {
            update(1, 1, n, dfn[top[u]], dfn[u] - 1, w);
            qwq[u].emplace_back(w, las, 0);
            u = fa[las = top[u]];
        }
        qwq[u].emplace_back(w, las, 0);
        update(1, 1, n, dfn[v], dfn[u] - 1, w);
    }
} seg;
ll f[N], g[N], h[N], c[N], d[N];
inline void dfs(int u, int _fa)
{
    for (int i = head[u]; i; i = edge[i].next)
    {
        int v = edge[i].to;
        if (v == _fa)
            continue;
        dfs(v, u);
        g[u] += f[v];
    }
    f[u] = g[u];
    ll res = 0;
    for (auto [x, y, w] : que[u])
        ckmax(res, indexed.query(dfn[x]) + indexed.query(dfn[y]) + w);
    f[u] = g[u] + res;
    c[u] = -res;
    indexed.update(dfn[u], dfn[u] + sze[u] - 1, c[u]);
}
inline void dfs0(int u, int _fa)
{
    d[u] = d[_fa] + c[u];
    for (int i = head[u]; i; i = edge[i].next)
    {
        int v = edge[i].to;
        if (v == _fa)
            continue;
        dfs0(v, u);
    }
}
inline void dfs3(int u, int _fa)
{
    for (auto [x, y, w] : que[u])
    {
        if (dep[x] > dep[y])
            swap(x, y);
        if (x == u)
        {
            if (y == u)
                qwq[u].emplace_back(h[u] + c[u] + w, 0, 0);
            else
                seg.update(y, x, h[u] + d[y] - d[fa[x]] + w);
        }
        else
        {
            int _x = jump(x, u), _y = jump(y, u);
            ll val = h[u] + d[x] + d[y] - d[u] - d[fa[u]] + w;
            qwq[u].emplace_back(val, _x, _y);
            seg.update(x, _x, val);
            seg.update(y, _y, val);
        }
    }
    qwq[u].emplace_back(seg.query(1, 1, n, dfn[u]), son[u], 0);
    sort(qwq[u].begin(), qwq[u].end());
    for (int i = head[u]; i; i = edge[i].next)
    {
        int v = edge[i].to;
        if (v == _fa)
            continue;
        h[v] = h[u] + c[u];
        stack<tuple<ll, int, int>> st;
        while (!qwq[u].empty() && (get<1>(qwq[u].back()) == v || get<2>(qwq[u].back()) == v))
        {
            st.push(qwq[u].back());
            qwq[u].pop_back();
        }
        if (!qwq[u].empty())
            ckmax(h[v], get<0>(qwq[u].back()));
        while (!st.empty())
        {
            qwq[u].push_back(st.top());
            st.pop();
        }
        dfs3(v, u);
    }
}
signed main()
{
#ifdef PAPERDOG
    freopen("project.in", "r", stdin);
    freopen("project.out", "w", stdout);
#else
    freopen("emotion.in", "r", stdin);
    freopen("emotion.out", "w", stdout);
#endif
    read(n, m);
    for (int i = 1; i < n; ++i)
    {
        int u, v;
        read(u, v);
        add_edge(u, v);
        add_edge(v, u);
    }
    dfs1(1, 0);
    dfs2(1, 1);
    seg.build(1, 1, n);
    for (int i = 1; i <= m; ++i)
    {
        int u, v, w;
        read(u, v, w);
        que[getlca(u, v)].emplace_back(u, v, w);
    }
    dfs(1, 0);
    dfs0(1, 0);
    h[1] = f[1];
    dfs3(1, 0);
    ll ans = f[1] % mod * n % mod * n % mod;
    for (int u = 1; u <= n; ++u)
    {
        ll res = (ll)sze[u] * sze[u] % mod;
        for (int i = head[u]; i; i = edge[i].next)
        {
            int v = edge[i].to;
            if (v == fa[u])
                continue;
            (res -= (ll)sze[v] * sze[v]) %= mod;
        }
        (ans -= res * ((h[u] + c[u]) % mod)) %= mod;
        (ans -= 2 * c[u] % mod * sze[u] % mod * (n - sze[u])) %= mod;
    }
    write((ans + mod) % mod, '\n');
#ifdef FAST_OUT
    IO::OUTPUT::flush();
#endif
    return 0;
}