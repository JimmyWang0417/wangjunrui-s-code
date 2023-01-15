/**
 *    unicode: UTF-8
 *    name:    toohard
 *    author:  whitepaperdog (蒟蒻wjr)
 *    located: Changle District, Fuzhou City, Fujian Province, China
 *    created: 2022.09.18 周日 12:43:18 (Asia/Shanghai)
 **/
#include <algorithm>
#include <cstdio>
#include <cstring>
#include <vector>
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
using namespace IO::INPUT;
using namespace IO::OUTPUT;
using namespace std;
constexpr int N = 2e5 + 5;
int n, m;
struct Edge
{
    int next, to;
} edge[N * 2];
int head[N], num_edge = 1;
inline void add_edge(int from, int to)
{
    edge[++num_edge].next = head[from];
    edge[num_edge].to = to;
    head[from] = num_edge;
}
int fa[N][20], dep[N][20], cnt[N];
int sze[N], maxsize[N], sum, root;
bool vis[N];
inline void getroot(int u, int _fa)
{
    sze[u] = 1;
    maxsize[u] = 0;
    for (int i = head[u]; i; i = edge[i].next)
    {
        int v = edge[i].to;
        if (v == _fa || vis[v])
            continue;
        getroot(v, u);
        sze[u] += sze[v];
        ckmax(maxsize[u], sze[v]);
    }
    ckmax(maxsize[u], sum - sze[u]);
    if (maxsize[root] > maxsize[u])
        root = u;
}
struct Tree
{
    int limit;
    vector<int> p;
    vector<int> sum;
    inline void init()
    {
        sort(p.begin(), p.end());
        limit = (int)p.size();
        sum.resize(limit + 1);
    }
    inline int calc(int pos)
    {
        return (int)(lower_bound(p.begin(), p.end(), pos) - p.begin() + 1);
    }
    inline void add(int pos)
    {
        for (int i = calc(pos); i; i -= lowbit(i))
            ++sum[i];
    }
    inline void del(int pos)
    {
        for (int i = calc(pos); i; i -= lowbit(i))
            --sum[i];
    }
    inline int query(int pos)
    {
        int res = 0;
        for (int i = calc(pos); i <= limit; i += lowbit(i))
            res += sum[i];
        return res;
    }
} tree1[N], tree2[N];
inline void dfs(int u, int _fa, int _dep)
{
    fa[u][++cnt[u]] = root;
    dep[u][cnt[u]] = _dep;
    sze[u] = 1;
    for (int i = head[u]; i; i = edge[i].next)
    {
        int v = edge[i].to;
        if (v == _fa || vis[v])
            continue;
        dfs(v, u, _dep + 1);
        sze[u] += sze[v];
    }
    ckmax(maxsize[u], sum - sze[u]);
}
inline void solve(int u)
{
    getroot(u, 0);
    u = root;
    dfs(u, 0, 0);
    vis[u] = true;
    for (int i = head[u]; i; i = edge[i].next)
    {
        int v = edge[i].to;
        if (vis[v])
            continue;
        maxsize[root = 0] = sum = sze[v];
        solve(v);
    }
}
pair<int, int> q[N * 3];
int f[N][20], g[N][20];
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
    for (int i = 1; i <= m; ++i)
        read(q[i].first, q[i].second);
    maxsize[root = 0] = sum = n;
    solve(1);
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j < cnt[i]; ++j)
            f[i][j] = 0x7fffffff;
    for (int kase = m; kase >= 1; --kase)
    {
        if (q[kase].first == 2)
        {
            int u = edge[q[kase].second << 1].to, v = edge[q[kase].second << 1 | 1].to;
            for (int i = 1; i <= cnt[u] && i <= cnt[v] && fa[u][i] == fa[v][i]; ++i)
            {
                if (dep[u][i] > dep[v][i])
                    swap(u, v);
                if (dep[u][i] == 0)
                    f[v][i] = kase;
                else
                    ckmin(f[v][i], f[u][i]);
                tree1[fa[u][i]].p.push_back(kase);
                if (i < cnt[u] && i < cnt[v] && fa[u][i + 1] == fa[v][i + 1])
                    tree2[fa[u][i + 1]].p.push_back(kase);
            }
        }
    }
    for (int i = 1; i <= n; ++i)
    {
        tree1[i].init();
        tree2[i].init();
    }
    for (int kase = 1; kase <= m; ++kase)
    {
        if (q[kase].first == 2)
        {
            int u = edge[q[kase].second << 1].to, v = edge[q[kase].second << 1 | 1].to;
            for (int i = 1; i <= cnt[u] && i <= cnt[v] && fa[u][i] == fa[v][i]; ++i)
            {
                if (dep[u][i] > dep[v][i])
                    swap(u, v);

                if (g[v][i])
                {
                    tree1[fa[u][i]].del(g[v][i]);
                    if (i < cnt[u] && i < cnt[v] && fa[u][i + 1] == fa[v][i + 1])
                        tree2[fa[u][i + 1]].del(g[v][i]);
                }

                if (dep[u][i] == 0)
                    g[v][i] = kase;
                else
                    ckmax(g[v][i], g[u][i]);

                if (g[v][i])
                {
                    tree1[fa[u][i]].add(g[v][i]);
                    if (i < cnt[u] && i < cnt[v] && fa[u][i + 1] == fa[v][i + 1])
                        tree2[fa[u][i + 1]].add(g[v][i]);
                }
            }
        }
        else
        {
            int u = q[kase].second;
            int res = tree1[u].query(0) + 1;
            for (int i = 1; i < cnt[u]; ++i)
                res += tree1[fa[u][i]].query(f[u][i]) - tree2[fa[u][i + 1]].query(f[u][i]);
            write(res, '\n');
        }
    }
#ifdef FAST_OUT
    flush();
#endif
    return 0;
}
