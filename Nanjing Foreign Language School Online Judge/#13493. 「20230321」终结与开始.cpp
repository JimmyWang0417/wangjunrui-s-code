/**
 *    name:     takuji
 *    author:   whitepaperdog (蒟蒻wjr)
 *    located:  Xuanwu District, Nanjing City, Jiangsu Province, China
 *    created:  2023.03.21 周二 20:34:26 (Asia/Shanghai)
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
namespace MODINT
{
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
}
using IO::INPUT::read;
using IO::OUTPUT::write;
using namespace std;
constexpr int N = 1e6 + 5;
constexpr int mod = 1e9 + 7;
typedef MODINT::modint<mod> modint;
int n, key, fa[N];
int sze[N];
int col[N];
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
modint inv[N];
struct node
{
    modint k, b;
    node(modint _k = 0, modint _b = 0) : k(_k), b(_b) {}
    inline node operator+(const modint &rhs) const
    {
        return node(k, b + rhs);
    }
    inline node operator+(const node &rhs) const
    {
        return node(k + rhs.k, b + rhs.b);
    }
    inline node operator-(const modint &rhs) const
    {
        return node(k, b - rhs);
    }
    inline node operator-(const node &rhs) const
    {
        return node(k - rhs.k, b - rhs.b);
    }
    inline node operator*(const modint &rhs) const
    {
        return node(k * rhs, b * rhs);
    }
    inline node operator/(const int &rhs) const
    {
        return node(k * inv[rhs], b * inv[rhs]);
    }
};
node dp[N];
inline void dfs1(int u, node pre = node())
{
    if (u == key)
        dp[u] = node();
    if (fa[u])
        pre = pre + dp[fa[u]] * (sze[fa[u]] - sze[u]);
    int nxt = 0;
    node sum = node();
    for (int i = head[u]; i; i = edge[i].next)
    {
        int v = edge[i].to;
        if (col[v] == 2)
        {
            dp[v] = (pre + dp[u] * (sze[u] - sze[v]) + n) / (n - sze[v]);
            sum = sum + dp[v] * sze[v];
        }
        else if (col[v] == 1)
            nxt = v;
    }
    if (nxt)
    {
        dp[nxt] = (dp[u] * (sze[u] - sze[nxt] + n - 1) - sum) / n;
        dfs1(nxt, pre);
    }
}
ll answer;
inline void dfs2(int u, int res)
{
    answer += res ^ u;
    for (int i = head[u]; i; i = edge[i].next)
    {
        int v = edge[i].to;
        dfs2(v, res);
    }
}
signed main()
{
#ifdef PAPERDOG
    freopen("project.in", "r", stdin);
    freopen("project.out", "w", stdout);
#else
    freopen("takuji.in", "r", stdin);
    freopen("takuji.out", "w", stdout);
#endif
    read(n);
    inv[1] = 1;
    for (int i = 2; i <= n; ++i)
        inv[i] = -inv[mod % i] * (mod / i);
    for (int i = 2; i <= n; ++i)
    {
        read(fa[i]);
        add_edge(fa[i], i);
    }
    read(key);
    for (int i = n; i >= 1; --i)
        sze[fa[i]] += ++sze[i];
    for (int u = key; u; u = fa[u])
    {
        col[u] = 1;
        for (int i = head[u]; i; i = edge[i].next)
        {
            int v = edge[i].to;
            if (!col[v])
                col[v] = 2;
        }
    }
    dp[1] = node(1, 0);
    dfs1(1);
    if (key == 1)
    {
        answer = 1;
        for (int i = head[1]; i; i = edge[i].next)
        {
            int v = edge[i].to;
            dfs2(v, dp[v].b.data());
        }
    }
    else
    {
        node sum = node();
        for (int i = 1; i <= n; i++)
            if (col[i] == 1)
                sum = sum + dp[i];
            else if (col[i] == 2)
                sum = sum + dp[i] * sze[i];

        sum = (sum / n) + 1 - node(1, 0);
        modint X = (-sum.b) / sum.k;
        for (int i = 1; i <= n; i++)
        {
            if (col[i] == 0)
                continue;
            if (col[i] == 1)
                answer += ((dp[i].k * X + dp[i].b).data() ^ i);
            else if (col[i] == 2)
                dfs2(i, (dp[i].k * X + dp[i].b).data());
        }
    }
    write(answer, '\n');
#ifdef FAST_OUT
    IO::OUTPUT::flush();
#endif
    return 0;
}