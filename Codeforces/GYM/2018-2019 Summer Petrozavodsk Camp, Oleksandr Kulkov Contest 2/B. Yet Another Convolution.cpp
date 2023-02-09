/**
 *    name:     B. Yet Another Convolution
 *    author:   whitepaperdog (蒟蒻wjr)
 *    located:  Changle District, Fuzhou City, Fujian Province, China
 *    created:  2023.02.09 周四 20:56:31 (Asia/Shanghai)
 *    unicode:  UTF-8
 *    standard: c++23
 **/
#include <algorithm>
#include <cstdio>
#include <vector>
typedef long long ll;
typedef unsigned long long ull;
__extension__ typedef __int128 int128;
constexpr auto lowbit = [](const auto &x)
{ return x & (-x); };

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
constexpr int N = 1e5 + 5;
int _n, _a[N], _b[N];
int n, a[N], c[N];
pair<int, int> b[N];
vector<int> g[N];
int prime[N], tot;
int miu[N];
bool vis[N];
inline void init()
{
    miu[1] = 1;
    for (int i = 2; i <= _n; ++i)
    {
        if (!vis[i])
        {
            prime[++tot] = i;
            miu[i] = -1;
        }
        for (int j = 1; j <= tot; ++j)
        {
            if (i * prime[j] > _n)
                break;
            vis[i * prime[j]] = true;
            if (i % prime[j])
                miu[i * prime[j]] = -miu[i];
            else
                break;
        }
    }
}
int cnt[N];
inline void add(int pos)
{
    for (int i : g[pos])
        ++cnt[i];
}
inline void del(int pos)
{
    for (int i : g[pos])
        --cnt[i];
}
inline int query(int pos)
{
    int res = 0;
    for (int i : g[pos])
        res += miu[i] * cnt[i];
    return res;
}
inline void update(int qr)
{
    static int r = 0;
    while (r < qr)
        add(b[++r].second);
    while (r > qr)
        del(b[r--].second);
}
int p[N], q[N];
inline void solve(int l, int r, int x, int y)
{
    if (l > r)
        return;
    if (x == y)
    {
        for (int i = l; i <= r; ++i)
            c[q[i]] = x;
        return;
    }
    int mid = (x + y) >> 1;
    update(mid);
    int i = l - 1, j = r + 1;
    for (int k = l; k <= r; ++k)
        if (query(p[k]) > 0)
            q[++i] = p[k];
        else
            q[--j] = p[k];
    for (int k = l; k <= r; ++k)
        p[k] = q[k];
    solve(l, i, x, mid);
    solve(j, r, mid + 1, y);
}
inline int fuck_this_problem()
{
    sort(b + 1, b + 1 + n);
    for (int i = 1; i <= n; ++i)
        p[i] = i;
    solve(1, n, 1, n);
    int res = 0;
    for (int i = 1; i <= n; ++i)
        ckmax(res, abs(a[i] - b[c[i]].first));
    update(0);
    return res;
}
int answer[N];
inline void work()
{
    for (int i = 1; i <= _n; ++i)
    {
        for (int j = 1; i * j <= _n; ++j)
        {
            a[j] = _a[i * j];
            b[j] = make_pair(_b[i * j], j);
        }
        n = _n / i;
        ckmax(answer[i], fuck_this_problem());
    }
}
signed main()
{
    read(_n);
    init();
    for (int i = 1; i <= _n; ++i)
        read(_a[i]);
    for (int i = 1; i <= _n; ++i)
        read(_b[i]);
    for (int i = 1; i <= _n; ++i)
        for (int j = i; j <= _n; j += i)
            g[j].push_back(i);
    work();
    for (int i = 1; i <= _n; ++i)
    {
        _a[i] = -_a[i];
        _b[i] = -_b[i];
    }
    work();
    for (int i = 1; i <= _n; ++i)
        write(answer[i], ' ');
    write('\n');
#ifdef FAST_OUT
    IO::OUTPUT::flush();
#endif
    return 0;
}