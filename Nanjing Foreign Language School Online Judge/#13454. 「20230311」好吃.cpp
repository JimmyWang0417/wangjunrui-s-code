/**
 *    name:     A. 好吃
 *    author:   whitepaperdog (蒟蒻wjr)
 *    located:  Xuanwu District, Nanjing City, Jiangsu Province, China
 *    created:  2023.03.14 周二 08:14:10 (Asia/Shanghai)
 *    unicode:  UTF-8
 *    standard: c++23
 **/
#include <algorithm>
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
constexpr int N = 1e3 + 5;
int n, a[N], b[N];
struct Edge
{
    int next, to;
} edge[N * N];
int head[N], num_edge = 1;
inline void add_edge(int from, int to)
{
    edge[++num_edge].next = head[from];
    edge[num_edge].to = to;
    head[from] = num_edge;
}
int dfn[N], low[N], dfstime;
int st[N], top;
int belong[N], color;
vector<int> all[N];
vector<int> G[N];
inline void tarjan(int u)
{
    dfn[u] = low[u] = ++dfstime;
    st[++top] = u;
    for (int i = head[u]; i; i = edge[i].next)
    {
        int v = edge[i].to;
        if (!dfn[v])
        {
            tarjan(v);
            ckmin(low[u], low[v]);
        }
        else if (!belong[v])
            ckmin(low[u], dfn[v]);
    }
    if (dfn[u] == low[u])
    {
        belong[u] = ++color;
        all[color].push_back(u);
        while (st[top] != u)
        {
            all[color].push_back(st[top]);
            belong[st[top--]] = color;
        }
        --top;
    }
}
int in[N];
int f[N][N], g[N][N], h[N][N][2];
int buf[N], answer[N];
int sze[N];
struct
{
    int head, tail, q[N];
    inline void init()
    {
        head = 1, tail = 0;
    }
    inline void push(int x)
    {
        q[++tail] = x;
    }
    inline int front()
    {
        return q[head];
    }
    inline bool empty()
    {
        return head > tail;
    }
    inline void pop()
    {
        ++head;
    }
} que;
signed main()
{
#ifdef PAPERDOG
    freopen("project.in", "r", stdin);
    freopen("project.out", "w", stdout);
#else
    freopen("goodeat.in", "r", stdin);
    freopen("goodeat.out", "w", stdout);
#endif
    read(n);
    for (int i = 1; i <= n; ++i)
    {
        int cnt;
        read(b[i], a[i], cnt);
        while (cnt--)
        {
            int v;
            read(v);
            add_edge(i, v);
        }
    }
    for (int i = 1; i <= n; ++i)
        if (!dfn[i])
            tarjan(i);
    for (int u = 1; u <= n; ++u)
    {
        for (int i = head[u]; i; i = edge[i].next)
        {
            int v = edge[i].to;
            if (belong[u] == belong[v])
                continue;
            G[belong[u]].push_back(belong[v]);
            ++in[belong[v]];
        }
    }
    memset(h, 0x3f, sizeof(h));
    h[0][0][0] = 0;
    for (int kase = 1; kase <= color; ++kase)
    {
        for (int i = 0; i < (int)all[kase].size(); ++i)
        {
            int u = all[kase][i];
            for (int j = 0; j <= i; ++j)
            {
                ckmin(h[i + 1][j][0], h[i][j][0]);
                ckmin(h[i + 1][j][1], h[i][j][1]);
                ckmin(h[i + 1][j + 1][0], h[i][j][0] + b[u]);
                ckmin(h[i + 1][j + 1][1], h[i][j][0] + a[u]);
                ckmin(h[i + 1][j + 1][1], h[i][j][1] + b[u]);
            }
        }
        g[kase][0] = 0;
        for (int i = 1; i <= (int)all[kase].size(); ++i)
            g[kase][i] = h[all[kase].size()][i][1];
        // write(kase, ":\n");
        // for (int i = 0; i <= (int)all[kase].size(); ++i)
        //     write(g[kase][i], ' ');
        // write('\n');
        for (int i = 1; i <= (int)all[kase].size(); ++i)
            memset(h[i], 0x3f, sizeof(h[i]));
    }
    memset(f, 0x3f, sizeof(f));
    memset(buf, 0x3f, sizeof(buf));
    memset(answer, 0x3f, sizeof(answer));
    int len = 0;
    que.init();
    for (int i = 1; i <= color; ++i)
        if (!in[i])
            que.push(i);
    while (!que.empty())
    {
        int u = que.front();
        que.pop();
        f[u][0] = 0;
        for (int i = 0; i <= sze[u]; ++i)
            for (int j = 0; j <= (int)all[u].size(); ++j)
                ckmin(buf[i + j], f[u][i] + g[u][j]);
        for (int i = (sze[u] += (int)all[u].size()); i >= 0; --i)
        {
            ckmin(answer[i], f[u][i] = buf[i]);
            buf[i] = 0x3f3f3f3f;
        }
        ckmax(len, sze[u]);
        for (int v : G[u])
        {
            ckmax(sze[v], sze[u]);
            for (int i = 0; i <= sze[v]; ++i)
                ckmin(f[v][i], f[u][i]);
            if (!--in[v])
                que.push(v);
        }
    }
    for (int i = 1; i <= len; ++i)
        write(answer[i], '\n');
#ifdef FAST_OUT
    IO::OUTPUT::flush();
#endif
    return 0;
}