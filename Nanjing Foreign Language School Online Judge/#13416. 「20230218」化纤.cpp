/**
 *    name:     #13416. 「20230218」化纤
 *    author:   whitepaperdog (蒟蒻wjr)
 *    located:  Changle District, Fuzhou City, Fujian Province, China
 *    created:  2023.02.20 周一 10:35:47 (Asia/Shanghai)
 *    unicode:  UTF-8
 *    standard: c++23
 **/
#include <algorithm>
#include <cstdio>
#include <set>
typedef long long ll;
typedef unsigned long long ull;
__extension__ typedef __int128 int128;
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
int n, w, h;
int a[N], b[N];
struct node
{
    ll x, y;
    node(ll _x = 1, ll _y = 1)
    {
        x = _x, y = _y;
        ll g = __gcd(x, y);
        x /= g, y /= g;
    }
    inline bool operator<(const node &rhs) const
    {
        return x * rhs.y < y * rhs.x;
    }
    inline node operator+(const node &rhs) const
    {
        return node(x * rhs.y + rhs.x * y, y * rhs.y);
    }
    inline node operator*(const ll &rhs) const
    {
        return node(x * rhs, y);
    }
    inline void print() const
    {
        write(x, '/', y);
    }
} c[N];
inline node inter(int x, int y)
{
    return node(a[x] - a[y], (b[y] - a[y]) - (b[x] - a[x]));
}
int dep[N], fa[N][23];
inline void init(int u, int _fa)
{
    c[u] = _fa ? inter(u, _fa) : node();
    dep[u] = dep[fa[u][0] = _fa] + 1;
    for (int i = 0; i < 20; ++i)
        fa[u][i + 1] = fa[fa[u][i]][i];
}
inline int getlca(int x, int y)
{
    if (dep[x] < dep[y])
        swap(x, y);
    for (int i = 20; i >= 0; --i)
        if (dep[fa[x][i]] >= dep[y])
            x = fa[x][i];
    if (x == y)
        return x;
    for (int i = 20; i >= 0; --i)
        if (fa[x][i] != fa[y][i])
        {
            x = fa[x][i];
            y = fa[y][i];
        }
    return fa[x][0];
}
inline int calc(int x, int y, int z)
{
    for (int i = 20; i >= 0; --i)
        if (dep[fa[y][i]] > dep[z])
        {
            node qwq = inter(fa[y][i], x);
            if (qwq.x < 0 || !qwq.y || c[fa[y][i]] < qwq)
                y = fa[y][i];
        }
    node qwq = inter(y, x);
    if (qwq.x < 0 || !qwq.y || c[y] < qwq)
        qwq = inter(x, y = fa[y][0]);
    if (qwq.x < 0 || !qwq.y || c[y] < qwq || dep[y] <= dep[z] || qwq.x > qwq.y)
        return 0;
    return y;
}
struct compare
{
    bool operator()(int x, int y)
    {
        return a[x] < a[y];
    }
};
set<int, compare> se;
signed main()
{
#ifdef PAPERDOG
    freopen("project.in", "r", stdin);
    freopen("project.out", "w", stdout);
#else
    freopen("painting.in", "r", stdin);
    freopen("painting.out", "w", stdout);
#endif
    read(n, w, h);
    a[n + 1] = b[n + 1] = h + 1;
    c[0] = c[n + 1] = node();
    se.insert(0), se.insert(n + 1);
    for (int i = 1; i <= n; ++i)
    {
        int opt;
        read(a[i], b[i], opt);
        auto it = se.lower_bound(i);
        int x = *prev(it), y = *it, z = getlca(x, y);
        int qwq;
        if (!(qwq = calc(i, x, z)))
        {
            if (!(qwq = calc(i, y, z)))
                qwq = z;
        }
        if (opt)
        {
            init(i, qwq);
            se.insert(i);
        }
        else
            c[i] = qwq ? inter(i, qwq) : node();
        write('(');
        (c[i] * w).print();
        write(',');
        (c[i] * b[i] + node(c[i].y - c[i].x, c[i].y) * a[i]).print();
        write(")\n");
    }
#ifdef FAST_OUT
    IO::OUTPUT::flush();
#endif
    return 0;
}