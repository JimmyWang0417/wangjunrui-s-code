/**
 *    name:     The Hanged Man
 *    author:   whitepaperdog (蒟蒻wjr)
 *    located:  Xuanwu District, Nanjing City, Jiangsu Province, China
 *    created:  2023.03.14 周二 23:51:14 (Asia/Shanghai)
 *    unicode:  UTF-8
 *    standard: c++23
 **/
#include <cstdio>
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
using IO::INPUT::read;
using IO::OUTPUT::write;
using namespace std;
constexpr int N = 137;
constexpr int M = 5005;
int n, m;
int a[N], b[N];
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
struct node
{
    int x;
    ll y;
    node(int _x = -0x3f3f3f3f, ll _y = 0) : x(_x), y(_y) {}
    inline node operator+(const node &rhs) const
    {
        node res = (*this);
        if (res.x < rhs.x)
            res = rhs;
        else if (res.x == rhs.x)
            res.y += rhs.y;
        return res;
    }
    inline node operator+(const int &rhs) const
    {
        return node(x + rhs, y);
    }
    inline void clear()
    {
        x = -0x3f3f3f3f;
        y = 0;
    }
} f[N][M], g[N][M];
int sze[N], son[N];
inline void dfs1(int u, int _fa)
{
    sze[u] = 1;
    for (int i = head[u]; i; i = edge[i].next)
    {
        int v = edge[i].to;
        if (v == _fa)
            continue;
        dfs1(v, u);
        sze[u] += sze[v];
        if (sze[v] > sze[son[u]])
            son[u] = v;
    }
}
int id[N], cnt;
inline void merge(int p)
{
    --cnt;
    for (int x = 0; x < (1 << (cnt - p)); x++)
        for (int y = 0; y < (1 << p); y++)
            for (int i = 0; i <= m; i++)
                g[(x << p) | y][i] = f[(x << (p + 1)) | (1 << p) | y][i] + f[(x << (p + 1)) | y][i];
    for (int s = 0; s < (1 << cnt); s++)
        for (int i = 0; i <= m; i++)
        {
            f[s][i] = g[s][i];
            g[s][i].clear();
        }
}
inline void dfs2(int u, int _fa)
{
    id[u] = 7;
    if (son[u])
        dfs2(son[u], u);
    id[u] = cnt++;
    for (int S = 0; S < (1 << id[u]); S++)
    {
        int T = S | (1 << id[u]);
        for (int i = 0; i < a[u]; i++)
            f[T][i].clear();
        if ((T >> id[_fa] & 1) || (T >> id[son[u]] & 1))
            for (int i = a[u]; i <= m; i++)
                f[T][i].clear();
        else
            for (int i = a[u]; i <= m; i++)
                f[T][i] = f[S][i - a[u]] + b[u];
    }
    if (son[u])
        merge(id[u] = id[son[u]]);
    for (int i = head[u]; i; i = edge[i].next)
    {
        int v = edge[i].to;
        if (v == _fa || v == son[u])
            continue;
        dfs2(v, u);
        merge(id[v]);
    }
}
signed main()
{
    int T;
    read(T);
    for (int kase = 1; kase <= T; ++kase)
    {
        read(n, m);
        for (int i = 1; i <= n; ++i)
            read(a[i], b[i]);
        for (int i = 1; i < n; ++i)
        {
            int u, v;
            read(u, v);
            add_edge(u, v);
            add_edge(v, u);
        }
        f[0][0] = node(0, 1);
        for (int i = 1; i <= m; i++)
            f[0][i].clear();
        id[0] = 7;
        dfs1(1, 0);
        dfs2(1, 0);
        merge(id[1]);
        write("Case ", kase, ":\n");
        for (int i = 1; i <= m; ++i)
        {
            write(f[0][i].y);
            if (i < m)
                write(' ');
        }
        write('\n');
        num_edge = 0;
        for (int i = 1; i <= n; ++i)
            head[i] = son[i] = 0;
    }
#ifdef FAST_OUT
    IO::OUTPUT::flush();
#endif
    return 0;
}