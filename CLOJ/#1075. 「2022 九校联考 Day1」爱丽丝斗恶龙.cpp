/**
 *    unicode: UTF-8
 *    name:    dragon
 *    author:  whitepaperdog (蒟蒻wjr)
 *    located: Changle District, Fuzhou City, Fujian Province, China
 *    created: 2022.09.17 周六 15:20:35 (Asia/Shanghai)
 **/
#include <algorithm>
#include <cstdio>
#include <cstring>
#include <functional>
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
constexpr int N = 1e5 + 5;
int n, m, a[N];
int pre[N * 3];
bool f[N];
int g[N];
inline void work()
{
    read(n, m);
    for (int i = 0; i < n; ++i)
        read(a[i]);
    sort(a, a + n, greater<int>());
    m -= a[0];
    if (m <= 0)
    {
        for (int i = 0; i < n; ++i)
            write(n, ' ');
        write('\n');
        return;
    }
    pre[1] = 1;
    for (int i = 1, sum = 0; i < n; ++i)
    {
    	sum += a[i];
        if (sum + 1 >= m * 3)
            break;
        pre[sum + 1] = i + 1;
    }
    for (int i = 1; i < m * 3; ++i)
        ckmax(pre[i], pre[i - 1]);
    int ans = n;
    f[0] = true;
    for (int l = 1, r; l < n && l < ans; l = r)
    {
        r = l + 1;
        while (r < n && a[l] == a[r])
            ++r;
        for (int i = (int)(max(0ll, m - (ll)a[l] * (r - l))); i < m; ++i)
            if (f[i])
            {
                int now = (int)((m - i - 1) / a[l] + 1);
                ckmin(ans, max(l + now, pre[i + (ll)a[l] * now + m]));
            }
        for (int i = a[l]; i < m; ++i)
        {
            g[i % a[l]] += f[i - a[l]];
            if (i - (ll)a[l] * (r - l + 1) >= 0)
                g[i % a[l]] -= f[i - (ll)a[l] * (r - l + 1)];
            if (g[i % a[l]])
                f[i] = true;
        }
        memset(g, 0, sizeof(int) * a[l]);
    }
    for (int i = 0; i < n; ++i)
        write(max(max((n - 1) - (ans - 2), max(i, n - i - 1) - (pre[m] - 1)), 0), ' ');
    write('\n');
    memset(f, 0, sizeof(bool) * n);
    memset(pre, 0, sizeof(int) * m * 3);
}
signed main()
{
    freopen("dragon.in", "r", stdin);
    freopen("dragon.out", "w", stdout);
    int T;
    read(T);
    while (T--)
        work();
#ifdef FAST_OUT
    flush();
#endif
    return 0;
}
