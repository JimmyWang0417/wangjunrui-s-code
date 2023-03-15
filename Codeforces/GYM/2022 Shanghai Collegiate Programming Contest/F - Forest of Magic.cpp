/**
 *    name:     B. 大仇得报
 *    author:   whitepaperdog (蒟蒻wjr)
 *    located:  Xuanwu District, Nanjing City, Jiangsu Province, China
 *    created:  2023.03.11 周六 16:40:51 (Asia/Shanghai)
 *    unicode:  UTF-8
 *    standard: c++23
 **/
#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <vector>
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
    constexpr inline bool operator==(const modint &rhs) const
    {
        return x == rhs.x;
    }
    constexpr inline bool operator!=(const modint &rhs) const
    {
        return x != rhs.x;
    }
    constexpr inline int &data()
    {
        return x;
    }
};
using IO::INPUT::read;
using IO::OUTPUT::write;
using namespace std;
constexpr int N = 2e5 + 5;
int n, m, type;
struct
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
int Log[N], dep[N];
int fa[N][20];
int rk[N];
int dfn[N], low[N], dfstime;
inline void init(int u, int _fa)
{
    rk[dfn[u] = ++dfstime] = u;
    dep[u] = dep[fa[u][0] = _fa] + 1;
    for (int i = 0; i < Log[dep[u]]; ++i)
        fa[u][i + 1] = fa[fa[u][i]][i];
    for (int i = head[u]; i; i = edge[i].next)
    {
        int v = edge[i].to;
        if (v == _fa)
            continue;
        init(v, u);
    }
    low[u] = dfstime;
}
inline void dfs(int u, int _fa)
{
    rk[dfn[u] = ++dfstime] = u;
    for (int i = head[u]; i; i = edge[i].next)
    {
        int v = edge[i].to;
        if (v == _fa)
            continue;
        dfs(v, u);
    }
    low[u] = dfstime;
}
inline int getlca(int u, int v)
{
    if (dep[u] < dep[v])
        swap(u, v);
    for (int i = Log[dep[u] - dep[v] + 1]; i >= 0; --i)
        if (dep[fa[u][i]] >= dep[v])
            u = fa[u][i];
    if (u == v)
        return u;
    for (int i = Log[dep[u]]; i >= 0; --i)
        if (fa[u][i] != fa[v][i])
        {
            u = fa[u][i];
            v = fa[v][i];
        }
    return fa[u][0];
}
struct node
{
    int u, c, k;
    node(int _u = 0, int _c = 0, int _k = 0) : u(_u), c(_c), k(_k) {}
    inline bool operator<(const node &rhs) const
    {
        return dfn[u] < dfn[rhs.u];
    }
} p[N * 2];
vector<pair<int, int>> g[N];
struct Tree
{
    int l, r;
    ll sum, ans;
} tree[N * 50];
#define lc(rt) tree[rt].l
#define rc(rt) tree[rt].r
int root[N], cnt;
inline void update(int &rt, int l, int r, int pos, int val1, ll val2)
{
    tree[++cnt] = tree[rt];
    rt = cnt;
    tree[rt].sum += val1;
    tree[rt].ans += val2;
    if (l == r)
        return;
    int mid = (l + r) >> 1;
    if (pos <= mid)
        update(lc(rt), l, mid, pos, val1, val2);
    else
        update(rc(rt), mid + 1, r, pos, val1, val2);
}
inline pair<ll, ll> operator+(const pair<ll, ll> &x, const pair<ll, ll> &y)
{
    return make_pair(x.first + y.first, x.second + y.second);
}
inline pair<ll, ll> &operator+=(pair<ll, ll> &x, const pair<ll, ll> &y)
{
    x.first += y.first;
    x.second += y.second;
    return x;
}
inline pair<ll, ll> query(int pre, int rt, int l, int r, int x, int y)
{
    if (r < x || l > y)
        return make_pair(0, 0);
    if (x <= l && r <= y)
        return make_pair(tree[rt].sum - tree[pre].sum, tree[rt].ans - tree[pre].ans);
    int mid = (l + r) >> 1;
    return query(lc(pre), lc(rt), l, mid, x, y) + query(rc(pre), rc(rt), mid + 1, r, x, y);
}
inline pair<ll, ll> calc(int u, int _fa, int c)
{
    pair<ll, ll> res = make_pair(0, 0);
    for (auto [_c, k] : g[u])
        if (_c <= c)
            res += make_pair(k, (ll)k * dep[u]);
    for (int i = head[u]; i; i = edge[i].next)
    {
        int v = edge[i].to;
        if (v == _fa)
            continue;
        res += calc(v, u, c);
    }
    return res;
}
int fuck[N], ccf;
signed main()
{
    read(n, m);
    for (int i = 1; i < n; ++i)
    {
        int u, v;
        read(u, v);
        add_edge(u, v);
        add_edge(v, u);
    }
    Log[0] = -1;
    for (int i = 1; i <= 2 * n; ++i)
        Log[i] = Log[i >> 1] + 1;
    int block = (int)sqrt(n * log2(n)) * 12;
    init(1, 0);
    int lastans = 0;
    for (int l = 1, r; l <= m; l = r + 1)
    {
        r = min(l + block - 1, m);
        int tot = 0;
        int qwq = n;
        int wdnmd = ccf;
        for (int kase = l; kase <= r; ++kase)
        {
            int _u, _v, __c, _k;
            int opt, u, v, c, k, lca;
            read(opt, _u);
            u = (int)(_u ^ lastans);
            if (opt == 1)
            {
                ++qwq;
                dep[qwq] = dep[fa[qwq][0] = u] + 1;
                for (int i = 0; i < Log[dep[qwq]]; ++i)
                    fa[qwq][i + 1] = fa[fa[qwq][i]][i];
                dfn[qwq] = dfn[fa[qwq][0]];
                add_edge(qwq, u);
                add_edge(u, qwq);
            }
            else if (opt == 2)
            {
                read(_v, __c, _k);
                v = (int)(_v ^ lastans);
                c = (int)(__c ^ lastans);
                k = (int)(_k ^ lastans);
                lca = getlca(u, v);
                p[++tot] = node(u, c, k), g[u].emplace_back(c, k);
                p[++tot] = node(v, c, k), g[v].emplace_back(c, k);
                p[++tot] = node(lca, c, -k), g[lca].emplace_back(c, -k);
                if (fa[lca][0])
                    p[++tot] = node(fa[lca][0], c, -k), g[fa[lca][0]].emplace_back(c, -k);
                fuck[++wdnmd] = c;
            }
            else
            {
                read(__c);
                c = (int)(__c ^ lastans);
                pair<ll, ll> res;
                if (u <= n)
                {
                    res = query(root[dfn[u] - 1], root[low[u]], 1, ccf, 1,
                                (int)(upper_bound(fuck + 1, fuck + 1 + ccf, c) - fuck - 1));
                    for (int i = 1; i <= tot; ++i)
                    {
                        v = p[i].u, k = p[i].k;
                        int _c = p[i].c;
                        if (dfn[u] <= dfn[v] && dfn[v] <= low[u] && _c <= c)
                            res += make_pair(k, (ll)k * dep[v]);
                    }
                }
                else
                    res = calc(u, fa[u][0], c);
                write(res.second - res.first * (dep[u] - 1), '\n');
                lastans = (int)((res.second - res.first * (dep[u] - 1)) & ((1ll << 31) - 1));
            }
        }
        if (r < m)
        {
            dfstime = 0;
            dfs(1, 0);
            n = qwq;
            cnt = 0;
            sort(fuck + ccf + 1, fuck + wdnmd + 1);
            inplace_merge(fuck + 1, fuck + ccf + 1, fuck + wdnmd + 1);
            ccf = wdnmd;
            for (int i = 1; i <= n; ++i)
            {
                root[i] = root[i - 1];
                for (auto [c, k] : g[rk[i]])
                    update(root[i], 1, ccf, (int)(lower_bound(fuck + 1, fuck + 1 + ccf, c) - fuck), k, (ll)k * dep[rk[i]]);
            }
        }
    }
#ifdef FAST_OUT
    IO::OUTPUT::flush();
#endif
    return 0;
}