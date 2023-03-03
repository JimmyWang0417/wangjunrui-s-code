/**
 *    name:     B. 嘉然和向晚又在玩游戏
 *    author:   whitepaperdog (蒟蒻wjr)
 *    located:  Xuanwu District, Nanjing City, Jiangsu Province, China
 *    created:  2023.03.02 Thu 16:20:37 (Asia/Shanghai)
 *    unicode:  UTF-8
 *    standard: c++23
 **/
#include <algorithm>
#include <cstdio>
#include <vector>
typedef long long ll;
typedef unsigned long long ull;
// __extension__ typedef __int128 int128;
#define lowbit(x) ((x) & (-(x)))
#define int ll

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
template <const int N, const int M>
struct Graph
{
    struct Edge
    {
        int next, to;
        bool vis;
    } edge[M];
    int head[N], num_edge;
    inline void add_edge(int from, int to)
    {
        edge[++num_edge].next = head[from];
        edge[num_edge].to = to;
        head[from] = num_edge;
    }
#define foreach(i, u, qwq) for (int i = qwq.head[u]; i; i = qwq.edge[i].next)
};
using IO::INPUT::read;
using IO::OUTPUT::write;
using namespace std;
constexpr int N = 1e5 + 5;
constexpr int M = 3e5 + 5;
int n, m, q;
int dfn[N], low[N], dfstime;
int st[N], top;
Graph<N, M * 2> G;
Graph<N * 2, N * 4> H;
bool ban[N * 2];
int color;
int a[N];
inline void tarjan(int u, int qwq)
{
    a[u] = qwq;
    dfn[u] = low[u] = ++dfstime;
    st[++top] = u;
    foreach (i, u, G)
    {
        int v = G.edge[i].to;
        if (!dfn[v])
        {
            tarjan(v, qwq ^ 1);
            ckmin(low[u], low[v]);
            if (dfn[u] == low[v])
            {
                H.add_edge(u, ++color);
                H.add_edge(color, u);
                while (st[top] != v)
                {
                    H.add_edge(st[top], color);
                    H.add_edge(color, st[top]);
                    ban[color] |= ban[st[top--]];
                }
                H.add_edge(st[top], color);
                H.add_edge(color, st[top]);
                ban[color] |= ban[st[top--]];
            }
        }
        else if (dfn[u] >= dfn[v])
        {
            if (a[u] == a[v])
                ban[u] = 1;
            ckmin(low[u], dfn[v]);
        }
    }
}
int fuck[N * 2], tot;
inline void dfs(int u, int _fa, int bel)
{
    fuck[u] = bel;
    foreach (i, u, H)
    {
        int v = H.edge[i].to;
        if (v == _fa)
            continue;
        if (u > n && ban[u])
            dfs(v, u, ++tot);
        else
            dfs(v, u, bel);
    }
}
int belong[N], block;
struct node
{
    int l, r, id;
    inline bool operator<(const node &rhs) const
    {
        return belong[l] == belong[rhs.l] ? (belong[l] & 1 ? r < rhs.r : r > rhs.r) : l < rhs.l;
    }
} que[N];
ll answer[N];
int cnt[N * 2];
signed main()
{
#ifdef PAPERDOG
    freopen("project.in", "r", stdin);
    freopen("project.out", "w", stdout);
#else
    freopen("game.in", "r", stdin);
    freopen("game.out", "w", stdout);
#endif
    read(n, m, q);
    for (int i = 1; i <= m; ++i)
    {
        int u, v;
        read(u, v);
        G.add_edge(u, v);
        G.add_edge(v, u);
    }
    color = n;
    for (int i = 1; i <= n; ++i)
        if (!dfn[i])
        {
            tarjan(i, 0);
            dfs(i, 0, ++tot);
        }
    block = (int)__builtin_sqrt(n);
    for (int i = 1; i <= n; ++i)
        belong[i] = (i - 1) / block + 1;
    for (int i = 1; i <= q; ++i)
    {
        auto &[l, r, id] = que[i];
        read(l, r);
        id = i;
    }
    sort(que + 1, que + 1 + q);
    int l = 1, r = 0;
    ll res = 0;
    for (int i = 1; i <= q; ++i)
    {
        auto [ql, qr, id] = que[i];
        auto add = [&res](int x)
        {
            res += cnt[x]++;
        };
        auto del = [&res](int x)
        {
            res -= --cnt[x];
        };
        while (l > ql)
            add(fuck[--l]);
        while (r < qr)
            add(fuck[++r]);
        while (l < ql)
            del(fuck[l++]);
        while (r > qr)
            del(fuck[r--]);
        answer[id] = res;
    }
    for (int i = 1; i <= q; ++i)
        write(answer[i], '\n');
#ifdef FAST_OUT
    IO::OUTPUT::flush();
#endif
    return 0;
}