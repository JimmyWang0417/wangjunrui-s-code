/**
 *    name:     B. 马可波罗
 *    author:   whitepaperdog (蒟蒻wjr)
 *    located:  Changle District, Fuzhou City, Fujian Province, China
 *    created:  2023.02.09 周四 17:03:05 (Asia/Shanghai)
 *    unicode:  UTF-8
 *    standard: c++23
 **/
#include <algorithm>
#include <cstdio>
typedef long long ll;
typedef unsigned long long ull;
__extension__ typedef __int128 int128;
constexpr auto lowbit = [](const auto &mod)
{ return mod & (-mod); };

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
    int mod;
    constexpr modint(int _x = 0) : mod(_x) {}
    constexpr inline modint operator+() const
    {
        return *this;
    }
    constexpr inline modint operator-() const
    {
        return !mod ? 0 : _mod - mod;
    }
    constexpr inline modint &operator++()
    {
        ++mod;
        if (mod >= _mod)
            mod -= _mod;
        return *this;
    }
    constexpr inline modint &operator--()
    {
        --mod;
        if (mod < 0)
            mod += _mod;
        return *this;
    }
    constexpr inline modint operator++(int)
    {
        int res = mod;
        if (mod >= _mod)
            mod -= _mod;
        return res;
    }
    constexpr inline modint operator--(int)
    {
        int res = mod;
        if (mod < 0)
            mod += _mod;
        return res;
    }
    constexpr inline modint operator+(const modint &rhs) const
    {
        int res = mod;
        res += rhs.mod;
        if (res >= _mod)
            res -= _mod;
        return res;
    }
    constexpr inline modint operator-(const modint &rhs) const
    {
        int res = mod;
        res -= rhs.mod;
        if (res < 0)
            res += _mod;
        return res;
    }
    constexpr inline modint operator*(const modint &rhs) const
    {
        return (int)((ll)mod * rhs.mod % _mod);
    }
    constexpr inline modint &operator+=(const modint &rhs)
    {
        mod += rhs.mod;
        if (mod >= _mod)
            mod -= _mod;
        return *this;
    }
    constexpr inline modint &operator-=(const modint &rhs)
    {
        mod -= rhs.mod;
        if (mod < 0)
            mod += _mod;
        return *this;
    }
    constexpr inline modint &operator*=(const modint &rhs)
    {
        mod = (int)((ll)mod * rhs.mod % _mod);
        return *this;
    }
    template <typename _G>
    constexpr inline modint operator^(_G rhs) const
    {
        modint a = mod, res = 1;
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
        return mod == rhs.mod;
    }
    constexpr inline int &data()
    {
        return mod;
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
constexpr int N = 1e6 + 5;
int n, m;
bool sum[N];
bool dp[23][N];
signed main()
{
#ifdef PAPERDOG
    freopen("project.in", "r", stdin);
    freopen("project.out", "w", stdout);
#else
    freopen("stone.in", "r", stdin);
    freopen("stone.out", "w", stdout);
#endif
    read(n);
    m = __lg(n);
    for (int i = 1; i <= n; ++i)
    {
        int mod;
        read(mod);
        sum[mod] ^= 1;
    }
    for (int i = 2; i <= n; ++i)
        sum[i] ^= sum[i - 1];
    for (int j = 0; j <= m; ++j)
        for (int i = n; i >= 0; i--)
        {
            if (i + (1 << j) <= n)
                dp[j][i] = sum[i + (1 << j) - 1] ^ sum[min(n, i + (1 << (j + 1)) - 1)];
            if (i + (1 << (j + 1)) <= n)
                dp[j][i] ^= dp[j][i + (1 << (j + 1))];
        }
    for (int mod = 2; mod <= n + 1; ++mod)
    {
        int res = 0;
        for (int j = 0; j <= m; j++)
        {
            for (int k = 0; k <= n / mod; k++)
            {
                int l = mod * k, r = min(n, mod * (k + 1) - 1), z = (r - l) / (2 << j);
                int cur = dp[j][l];
                if (l + (z + 1) * (2 << j) <= n)
                    cur ^= dp[j][l + (z + 1) * (2 << j)];
                if (l + z * (2 << j) + (1 << j) <= n)
                    cur ^= (sum[min(n, l + (z + 1) * (2 << j) - 1)] ^ sum[max(r, l + z * (2 << j) + (1 << j) - 1)]);
                res ^= cur;
            }
            if (res)
                break;
        }
        if (res)
            write("Alice ");
        else
            write("Bob ");
    }
    write('\n');
#ifdef FAST_OUT
    IO::OUTPUT::flush();
#endif
    return 0;
}