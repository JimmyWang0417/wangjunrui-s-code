/**
 *    name:     B. 最短路
 *    author:   whitepaperdog (蒟蒻wjr)
 *    located:  Xuanwu District, Nanjing City, Jiangsu Province, China
 *    created:  2023.02.27 周一 15:08:54 (Asia/Shanghai)
 *    unicode:  UTF-8
 *    standard: c++23
 **/
#include <cstdio>
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
constexpr int N = 5e4 + 5;
constexpr int M = 1e5 + 5;
int n, m, q;
struct Edge
{
    int next, to;
} edge[N * 2];
int head[2][N], num_edge;
inline void add_edge(int from, int to, bool col)
{
    edge[++num_edge].next = head[col][from];
    edge[num_edge].to = to;
    head[col][from] = num_edge;
}
struct node
{
    int x, y;
    node(int _x = 0, int _y = 0) : x(_x), y(_y) {}
    inline bool operator<(const node &rhs) const
    {
        return x == rhs.x ? y < rhs.y : x < rhs.x;
    }
    inline node calc0() const
    {
        return node(x + 1, y);
    }
    inline node calc1() const
    {
        return node(x, y + 1);
    }
    inline node operator-(const node &rhs) const
    {
        return node(x - rhs.x, y - rhs.y);
    }
    inline ll operator*(const node &rhs) const
    {
        return (ll)x * rhs.y - (ll)y * rhs.x;
    }
};
typedef vector<node> vec;
vec g[N];
node st[N];
int top;
inline void merge0(vec &u, const vec &v)
{
    int i = 0, j = 0;
    while (i < (int)u.size() && j < (int)v.size())
    {
        node x;
        if (u[i] < v[j].calc0())
            x = u[i++];
        else
            x = v[j++].calc0();
        while (top > 1 && (st[top - 1] - st[top]) * (x - st[top]) >= 0)
            --top;
        st[++top] = x;
    }
    while (i < (int)u.size())
    {
        node x = u[i++];
        while (top > 1 && (st[top - 1] - st[top]) * (x - st[top]) >= 0)
            --top;
        st[++top] = x;
    }
    while (j < (int)v.size())
    {
        node x = v[j++].calc0();
        while (top > 1 && (st[top - 1] - st[top]) * (x - st[top]) >= 0)
            --top;
        st[++top] = x;
    }
    u.resize(top);
    for (i = 0; i < top; ++i)
        u[i] = st[i + 1];
    top = 0;
}
inline void merge1(vec &u, const vec &v)
{
    int i = 0, j = 0;
    while (i < (int)u.size() && j < (int)v.size())
    {
        node x;
        if (u[i] < v[j].calc1())
            x = u[i++];
        else
            x = v[j++].calc1();
        while (top > 1 && (st[top - 1] - st[top]) * (x - st[top]) >= 0)
            --top;
        st[++top] = x;
    }
    while (i < (int)u.size())
    {
        node x = u[i++];
        while (top > 1 && (st[top - 1] - st[top]) * (x - st[top]) >= 0)
            --top;
        st[++top] = x;
    }
    while (j < (int)v.size())
    {
        node x = v[j++].calc1();
        while (top > 1 && (st[top - 1] - st[top]) * (x - st[top]) >= 0)
            --top;
        st[++top] = x;
    }
    u.resize(top);
    for (i = 0; i < top; ++i)
        u[i] = st[i + 1];
    top = 0;
}
signed main()
{
    read(n, m);
    for (int i = 1; i <= m; ++i)
    {
        int u, v, w;
        read(u, v, w);
        add_edge(u, v, w);
    }
    g[1].emplace_back(0, 0);
    for (int u = 1; u <= n; ++u)
    {
        for (int i = head[0][u]; i; i = edge[i].next)
        {
            int v = edge[i].to;
            merge0(g[v], g[u]);
        }
        for (int i = head[1][u]; i; i = edge[i].next)
        {
            int v = edge[i].to;
            merge1(g[v], g[u]);
        }
    }
    read(q);
    for (int i = 1; i <= q; ++i)
    {
        int a, b, x;
        read(a, b, x);
        int minn = 0x7fffffff;
        for (auto j : g[x])
            ckmin(minn, a * j.x + b * j.y);
        write(minn, '\n');
    }
#ifdef FAST_OUT
    IO::OUTPUT::flush();
#endif
    return 0;
}