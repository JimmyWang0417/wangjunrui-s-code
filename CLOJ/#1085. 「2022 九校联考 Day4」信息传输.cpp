/**
 *    unicode: UTF-8
 *    name:    trans
 *    author:  whitepaperdog (蒟蒻wjr)
 *    located: Changle District, Fuzhou City, Fujian Province, China
 *    created: 2022.09.24 周六 17:44:50 (Asia/Shanghai)
 **/
#include <cstdio>
#include <cstring>
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
constexpr int N = 105;
constexpr int mod = 1e9 + 7;
int n, m, k;
int a[N], tot;
bool b[N];
int c[N], cnt;
int col[N], color;
int dfn[N], dfstime;
ll f[N][N], g[N];
int mp[N][N];
ll diff[N], same[N];
ll fac[N];
Graph<int, N, N * 2> graph;
inline void dfs1(int u, int _fa)
{
    dfn[u] = ++dfstime;
    foreach (i, graph, u)
    {
        int v = graph.edge[i].to;
        if (v == _fa)
            continue;
        if (!dfn[v])
            dfs1(v, u);
        else if (dfn[v] > dfn[u])
            b[u] = true;
    }
    if (b[u])
        c[++cnt] = u;
}
bool vis[N];
inline void dfs2(int u, int _fa)
{
    for (int i = 0; i <= color; ++i)
        f[u][i] = (!b[u] || i == col[u]);
    vis[u] = true;
    foreach (i, graph, u)
    {
        int v = graph.edge[i].to;
        ll d = diff[mp[u][v]], s = same[mp[u][v]];
        if (v == _fa)
            continue;
        if (!vis[v])
        {
            dfs2(v, u);
            for (int j = 0; j <= color; ++j)
                (f[u][j] *= ((g[v] - f[v][j]) * d + f[v][j] * s) % mod) %= mod;
        }
        else
        {
            if (dfn[u] > dfn[v])
                for (int j = 0; j <= color; ++j)
                    (f[u][j] *= (j == col[v]) ? s : d) %= mod;
        }
    }
    g[u] = (k - color) * f[u][0] % mod;
    for (int i = 1; i <= color; i++)
        g[u] += f[u][i];
    g[u] %= mod;
}
ll answer;
inline void dfs3(int u)
{
    if (u == cnt + 1)
    {
        dfs2(1, 0);
        (answer += g[1] * fac[color]) %= mod;
        memset(vis, 0, sizeof(vis));
        return;
    }
    for (int i = 1; i <= color; ++i)
    {
        col[c[u]] = i;
        dfs3(u + 1);
    }
    if (color < k)
    {
        col[c[u]] = ++color;
        dfs3(u + 1);
        --color;
    }
}
signed main()
{
    freopen("trans.in", "r", stdin);
    freopen("trans.out", "w", stdout);
    int T = 1;
    read(T);
    while (T--)
    {
        read(n, m, k);
        for (int i = 1; i <= m; ++i)
        {
            int x, y, d, s;
            read(x, y, d, s);
            if (!mp[x][y])
            {
                graph.add_edge(x, y);
                graph.add_edge(y, x);
                diff[i] = d;
                same[i] = s;
                mp[x][y] = mp[y][x] = i;
            }
            else
            {
                (diff[mp[x][y]] *= d) %= mod;
                (same[mp[x][y]] *= s) %= mod;
            }
        }
        dfs1(1, 0);
        fac[0] = 1;
        for (int i = 1; i <= cnt; ++i)
            fac[i] = fac[i - 1] * (k - i + 1) % mod;
        dfs3(1);
        printf("%lld\n", (answer + mod) % mod);
        answer = 0;
        memset(graph.head, graph.num_edge = 0, sizeof(graph.head));
        memset(mp, 0, sizeof(mp));
        memset(b, 0, sizeof(b));
        memset(dfn, 0, sizeof(dfn));
        memset(col, 0, sizeof(col));
        tot = cnt = color = dfstime = 0;
    }
#ifdef FAST_OUT
    flush();
#endif
    return 0;
}
