/**
 *    name:
 *    author:   whitepaperdog (蒟蒻wjr)
 *    located:  Xuanwu District, Nanjing City, Jiangsu Province, China
 *    created:  2023.03.09 周四 09:18:28 (Asia/Shanghai)
 *    unicode:  UTF-8
 *    standard: c++23
 **/
#include <algorithm>
#include <cstdio>
#include <set>
#include <tuple>
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
constexpr int N = 1e5 + 5;
int n, a[N];
int p[N], tot;
set<vector<int>> mp;
vector<int> G[N];
tuple<int, int, int> que[N];
int b[N], c[N], d[N], cnt;
inline bool dfs(int u, vector<int> g)
{
    if (u == -1)
        return true;
    if (a[u] > a[u + 1])
        return dfs(u - 1, g);
    sort(g.begin(), g.end());
    if (mp.count(g))
        return false;
    mp.insert(g);
    for (int i = 0; i < (int)g.size(); ++i)
    {
        int x = g[i];
        for (int j = 0; j < (int)(G[x].size() + 1) / 2; ++j)
        {
            int v = G[x][j], w = G[x][(int)G[x].size() - j - 1];
            if (a[u + 1] - p[x] + p[v] + p[w] == a[u])
            {
                vector<int> h;
                for (int k = 0; k < i; ++k)
                    h.push_back(g[k]);
                h.push_back(v), h.push_back(w);
                for (int k = i + 1; k < (int)g.size(); ++k)
                    h.push_back(g[k]);
                if (dfs(u - 1, h))
                {
                    que[u] = make_tuple(x, v, w);
                    return true;
                }
            }
        }
    }
    return false;
}
signed main()
{
    read(n);
    for (int i = 0; i < n; ++i)
        read(a[i]);
    p[0] = 1;
    for (int i = 2; i * i <= a[n - 1]; ++i)
        if (a[n - 1] % i == 0)
        {
            p[++tot] = i;
            if (i * i == a[n - 1])
                continue;
            p[++tot] = a[n - 1] / i;
        }
    p[++tot] = a[n - 1];
    sort(p + 1, p + 1 + tot);
    for (int i = 1; i <= tot; ++i)
        for (int j = i + 1; j <= tot; ++j)
        {
            if (p[j] % p[i] == 0)
                G[j].push_back(i);
        }
    for (int i = 1; i < n; ++i)
        if (a[i - 1] - a[i] > 1)
        {
            write("-1\n");
            return 0;
        }
    if (!dfs(n - 2, vector<int>(1, tot)))
        write("-1\n");
    else
    {
        b[cnt = 1] = tot;
        int r = n;
        for (int i = n - 2; i >= 0; --i)
        {
            if (a[i] > a[i + 1])
            {
                d[i] = --r;
                continue;
            }
            int _tot = cnt;
            cnt = 0;
            auto [u, v, w] = que[i];
            bool flag = true;
            for (int j = 1; j <= _tot; ++j)
            {
                if (b[j] == u && flag)
                {
                    c[d[i] = ++cnt] = v;
                    c[++cnt] = w;
                    for (int k = i + 1; k <= n - 2; ++k)
                        if (b[d[k]] && d[k] >= j)
                            ++d[k];
                    flag = false;
                }
                else
                    c[++cnt] = b[j];
            }
            for (int j = 1; j <= cnt; ++j)
                b[j] = c[j];
            // printf("%d %d:\n", i, d[i]);
            // for (int j = 1; j <= cnt; ++j)
            //     write(p[b[j]], ' ');
            // write('\n');
        }
        for (int i = 1; i <= n; ++i)
            write(p[b[i]], ' ');
        write('\n');
        for (int i = 0; i <= n - 2; ++i)
            write(d[i], '\n');
    }
#ifdef FAST_OUT
    IO::OUTPUT::flush();
#endif
    return 0;
}