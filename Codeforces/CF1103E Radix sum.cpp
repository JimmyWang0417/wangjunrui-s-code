/**
 *    unicode: UTF-8
 *    name:    CF1103E Radix sum
 *    author:  whitepaperdog (蒟蒻wjr)
 *    located: Changle District, Fuzhou City, Fujian Province, China
 *    created: 2023.02.02 周四 19:35:42 (Asia/Shanghai)
 **/
#include <cstdio>
typedef long long ll;
typedef unsigned long long ull;
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
    constexpr inline modint inv()
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
constexpr ull inv5 = 14757395258967641293ull;
int n;
int limit, len;
struct node
{
    ull g[10];
    node() : g() {}
    inline ull operator[](int x) const
    {
        return g[x];
    }
    inline ull &operator[](int x)
    {
        return g[x];
    }
    inline node operator+(const node &rhs) const
    {
        node res;
        for (int i = 0; i < 10; ++i)
            res[i] = g[i] + rhs[i];
        return res;
    }
    inline void operator+=(const node &rhs)
    {
        for (int i = 0; i < 10; ++i)
            g[i] += rhs[i];
    }
    inline node operator*(const node &rhs) const
    {
        node res;
        for (int i = 0; i < 10; ++i)
            for (int j = 0; j < 10; ++j)
                res[(i + j) % 10] += g[i] * rhs[j];
        return res;
    }
    inline void operator*=(const ull &rhs)
    {
        for (int i = 0; i < 10; ++i)
            g[i] *= rhs;
    }
    inline node operator^(int power)
    {
        node res, _a = (*this);
        res[0] = 1;
        while (power)
        {
            if (power & 1)
                res = res * _a;
            _a = _a * _a;
            power >>= 1;
        }
        return res;
    }
    inline node right(int x) const
    {
        node res;
        for (int i = 0; i < 10; ++i)
            res[(i + x) % 10] = g[i];
        return res;
    }
    inline node left(int x) const
    {
        return right(10 - x % 10);
    }
} A[N], B;
inline void FWT(node *dp)
{
    for (int mid = 1; mid < limit; mid *= 10)
        for (int i = 0; i < limit; i += mid * 10)
            for (int j = 0; j < mid; ++j)
            {
                static node x[10], y[10];
                for (int k = 0; k < 10; k++)
                {
                    x[k] = dp[i + j + k * mid];
                    y[k] = node();
                }
                for (int k = 0; k < 10; ++k)
                    for (int l = 0; l < 10; ++l)
                        y[k] += x[l].right(k * l);
                for (int k = 0; k < 10; ++k)
                    dp[i + j + k * mid] = y[k];
            }
}
inline void IFWT(node *dp)
{
    for (int mid = 1; mid < limit; mid *= 10)
        for (int i = 0; i < limit; i += mid * 10)
            for (int j = 0; j < mid; ++j)
            {
                static node x[10], y[10];
                for (int k = 0; k < 10; k++)
                {
                    x[k] = dp[i + j + k * mid];
                    y[k] = node();
                }
                for (int k = 0; k < 10; ++k)
                    for (int l = 0; l < 10; ++l)
                        y[k] += x[l].left(k * l);
                for (int k = 0; k < 10; ++k)
                    dp[i + j + k * mid] = y[k];
            }
    ull inv = 1;
    for (int i = 1; i <= len; ++i)
        inv *= inv5;
    for (int i = 0; i < limit; ++i)
        dp[i] *= inv;
}
inline ull calc(node dp)
{
    for (int i = 9; i >= 4; --i)
    {
        for (int j = 1; j <= 4; ++j)
            dp[i - j] -= dp[i] * B[4 - j];
    }
    return (dp[0] >> len) & ((1ull << 58) - 1);
}
signed main()
{
    read(n);
    int maxx = n - 1;
    for (int i = 1; i <= n; ++i)
    {
        int x;
        read(x);
        ++A[x][0];
        ckmax(maxx, x);
    }
    limit = 1, len = 0;
    while (limit <= maxx)
    {
        limit *= 10;
        ++len;
    }
    FWT(A);
    for (int i = 0; i < limit; ++i)
        A[i] = A[i] ^ n;
    IFWT(A);
    B[0] = 1, B[1] = -1, B[2] = 1, B[3] = -1, B[4] = 1;
    for (int i = 0; i < n; ++i)
        write(calc(A[i]), '\n');
    write('\n');
#ifdef FAST_OUT
    IO::OUTPUT::flush();
#endif
    return 0;
}