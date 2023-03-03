/**
 *    name:     送你匕首
 *    author:   whitepaperdog (蒟蒻wjr)
 *    located:  Xuanwu District, Nanjing City, Jiangsu Province, China
 *    created:  2023.03.03 周五 09:35:25 (Asia/Shanghai)
 *    unicode:  UTF-8
 *    standard: c++23
 **/
#include <algorithm>
#include <cstdio>
#include <cstring>
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
constexpr int N = 1e3 + 5;
int n, m, c[N], d[N];
struct Edge
{
    int next, to, dis;
} edge[N * 2];
int head[N], num_edge;
inline void add_edge(int from, int to, int dis)
{
    edge[++num_edge].next = head[from];
    edge[num_edge].to = to;
    edge[num_edge].dis = dis;
    head[from] = num_edge;
}
vector<pair<int, ll>> dp[N][2], buf[2];
inline void merge(int u, int v, int w)
{
    auto f = dp[u], g = dp[v], h = buf;
    for (auto [disu, fu] : f[0])
    {
        for (auto [disv, fv] : g[0])
        {
            disv = min(disv + w, m + 1);
            h[0].emplace_back(min(disu, disv), fu + fv);
        }
        for (auto [disv, fv] : g[1])
        {
            disv = disv - w;
            if (disu <= disv)
                h[0].emplace_back(disu, fu + fv);
            else
            {
                if (disv <= 0)
                    continue;
                h[1].emplace_back(disv, fu + fv);
            }
        }
    }
    for (auto [disu, fu] : f[1])
    {
        for (auto [disv, fv] : g[0])
        {
            disv = min(disv + w, m + 1);
            if (disu >= disv)
                h[0].emplace_back(disv, fu + fv);
            else
                h[1].emplace_back(disu, fu + fv);
        }
        for (auto [disv, fv] : g[1])
        {
            disv = disv - w;
            if (disv <= 0)
                continue;
            h[1].emplace_back(min(disu, disv), fu + fv);
        }
    }
    sort(h[0].begin(), h[0].end());
    f[0].clear();
    for (auto i : h[0])
    {
        if (!f[0].empty() && f[0].back().first == i.first)
            ckmin(f[0].back().second, i.second);
        else
            f[0].push_back(i);
    }
    h[0].clear();
    sort(h[1].begin(), h[1].end());
    f[1].clear();
    for (auto i : h[1])
    {
        if (!f[1].empty() && f[1].back().first == i.first)
            ckmin(f[1].back().second, i.second);
        else
            f[1].push_back(i);
    }
    h[1].clear();
}
inline void dfs(int u, int _fa)
{
    dp[u][0].emplace_back(0, c[u]);
    dp[u][1].emplace_back(d[u], 0);
    for (int i = head[u]; i; i = edge[i].next)
    {
        int v = edge[i].to;
        if (v == _fa)
            continue;
        dfs(v, u);
        merge(u, v, edge[i].dis);
    }
}
inline void work()
{
    read(n);
    for (int i = 1; i <= n; ++i)
        read(c[i]);
    for (int i = 1; i <= n; ++i)
    {
        read(d[i]);
        ckmax(m, d[i]);
    }
    for (int i = 1; i < n; ++i)
    {
        int u, v, w;
        read(u, v, w);
        add_edge(u, v, w);
        add_edge(v, u, w);
    }
    dfs(1, 0);
    ll res = 1e18;
    for (auto [dis, val] : dp[1][0])
        ckmin(res, val);
    write(res, '\n');
    num_edge = m = 0;
    for (int i = 1; i <= n; ++i)
    {
        head[i] = 0;
        dp[i][0].clear();
        dp[i][1].clear();
    }
}
signed main()
{
#ifdef PAPERDOG
    freopen("project.in", "r", stdin);
    freopen("project.out", "w", stdout);
#else
    freopen("dagger.in", "r", stdin);
    freopen("dagger.out", "w", stdout);
#endif
    int T = 1;
    read(T);
    while (T--)
        work();
#ifdef FAST_OUT
    IO::OUTPUT::flush();
#endif
    return 0;
}