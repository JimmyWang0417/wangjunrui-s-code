/**
 *    name:     nanoGPT
 *    author:   whitepaperdog (蒟蒻wjr)
 *    located:  Xuanwu District, Nanjing City, Jiangsu Province, China
 *    created:  2023.03.15 周三 15:25:17 (Asia/Shanghai)
 *    unicode:  UTF-8
 *    standard: c++23
 **/
#include <cstdio>
#include <ext/pb_ds/priority_queue.hpp>
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
int n, m;
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
int a[N];
ll b[N], c[N];
int d[N], e[N];
ll f[N], g[N];
struct can_can_need
{
    priority_queue<ll, vector<ll>, greater<ll>> p, p1;
    priority_queue<ll, vector<ll>, less<ll>> q, q1;
    ll sum = 0;
    inline void update()
    {
        while (!p1.empty() && p1.top() == p.top())
        {
            p.pop();
            p1.pop();
        }
        while (!q1.empty() && q1.top() == q.top())
        {
            q.pop();
            q1.pop();
        }
    }
    inline void insert(ll x)
    {
        update();
        if ((int)(p.size() - p1.size()) < m)
        {
            p.push(x);
            sum += x;
        }
        else
        {
            if (p.top() < x)
            {
                sum -= p.top();
                q.push(p.top());
                p.pop();
                p.push(x);
                sum += x;
            }
            else
                q.push(x);
        }
    }
    inline void erase(ll x)
    {
        update();
        if (!(q.size() == q1.size()) && q.top() >= x)
            q1.push(x);
        else
        {
            sum -= x;
            p1.push(x);
            update();
            if (!(q.size() == q1.size()))
            {
                sum += q.top();
                p.push(q.top());
                q.pop();
            }
        }
    }
} que;
inline void init(int u, int _fa)
{
    b[u] = a[u];
    c[u] = 0;
    e[u] = d[u] = 0;
    for (int i = head[u]; i; i = edge[i].next)
    {
        int v = edge[i].to;
        if (v == _fa)
            continue;
        init(v, u);
        b[u] += b[v];
        c[u] += c[v];
        if (f[d[u]] < f[v])
        {
            e[u] = d[u];
            d[u] = v;
        }
        else if (f[e[u]] < f[v])
            e[u] = v;
    }
    c[u] += b[u];
    f[u] = f[d[u]] + b[u];
    for (int i = head[u]; i; i = edge[i].next)
    {
        int v = edge[i].to;
        if (v == _fa || v == d[u])
            continue;
        que.insert(f[v]);
    }
}
ll h[N], dp[N];
ll st[N];
int top;
inline void dfs(int u, int _fa, ll pref)
{
    if (_fa)
    {
        // printf("%d %d %lld %d\n", u, _fa, pref, d[u]);
        h[u] = h[_fa] + b[1] - b[u] * 2;
        ll res = 0;
        if (pref > f[d[u]])
        {
            que.insert(f[d[u]]);
            res = pref + b[1];
        }
        else
        {
            que.insert(pref);
            res = f[d[u]] + b[1];
        }
        que.insert(res);
        dp[u] = h[u] - que.sum;
        que.erase(res);
        if (pref > f[d[u]])
            que.erase(f[d[u]]);
        else
            que.erase(pref);
    }
    for (int i = head[u]; i; i = edge[i].next)
    {
        int v = edge[i].to;
        if (v == _fa)
            continue;
        if (v == d[u])
        {
            if (pref > f[e[u]])
                dfs(v, u, pref + b[1] - b[v]);
            else
            {
                if (pref)
                    que.insert(pref);
                if (e[u])
                    que.erase(f[e[u]]);
                dfs(v, u, f[e[u]] + b[1] - b[v]);
                if (e[u])
                    que.insert(f[e[u]]);
                if (pref)
                    que.erase(pref);
            }
        }
        else
        {
            if (pref > f[d[u]])
            {
                que.erase(f[v]);
                que.insert(f[d[u]]);
                dfs(v, u, pref + b[1] - b[v]);
                que.erase(f[d[u]]);
                que.insert(f[v]);
            }
            else
            {
                if (pref)
                    que.insert(pref);
                que.erase(f[v]);
                dfs(v, u, f[d[u]] + b[1] - b[v]);
                que.insert(f[v]);
                if (pref)
                    que.erase(pref);
            }
        }
    }
}
signed main()
{
#ifdef PAPERDOG
    freopen("project.in", "r", stdin);
    freopen("project.out", "w", stdout);
#else
    freopen("shootluo.in", "r", stdin);
    freopen("shootluo.out", "w", stdout);
#endif
    read(n, m);
    for (int i = 1; i <= n; ++i)
        read(a[i]);
    for (int i = 1; i < n; ++i)
    {
        int u, v;
        read(u, v);
        add_edge(u, v);
        add_edge(v, u);
    }
    init(1, 0);
    que.insert(f[1]);
    h[1] = c[1];
    dp[1] = h[1] - que.sum;
    que.erase(f[1]);
    dfs(1, 0, 0);
    for (int i = 1; i <= n; ++i)
        write(dp[i], '\n');
#ifdef FAST_OUT
    IO::OUTPUT::flush();
#endif
    return 0;
}