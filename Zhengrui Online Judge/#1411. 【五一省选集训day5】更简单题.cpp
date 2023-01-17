/**
 *    unicode: UTF-8
 *    name:    #1411. 【五一省选集训day5】更简单题
 *    author:  whitepaperdog (蒟蒻wjr)
 *    located: Changle District, Fuzhou City, Fujian Province, China
 *    created: 2023.01.16 周一 09:18:14 (Asia/Shanghai)
 **/
#include <cstdio>
#include <cstring>
#define ll long long
#define lll __int128
#define ull unsigned ll
#define lowbit(_x) (_x & (-_x))

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
template <typename _T, const _T _mod>
struct modint
{
    _T x;
    modint(_T _x = 0) : x(_x) {}
    inline modint operator+() const
    {
        return *this;
    }
    inline modint operator-() const
    {
        return !x ? 0 : _mod - x;
    }
    inline modint &operator++()
    {
        ++x;
        if (x >= _mod)
            x -= _mod;
        return *this;
    }
    inline modint &operator--()
    {
        --x;
        if (x < 0)
            x += _mod;
        return *this;
    }
    inline modint operator++(_T)
    {
        int res = x;
        if (x >= _mod)
            x -= _mod;
        return res;
    }
    inline modint operator--(_T)
    {
        int res = x;
        if (x < 0)
            x += _mod;
        return res;
    }
    inline modint operator+(const modint &rhs) const
    {
        _T res = x;
        res += rhs.x;
        if (res >= _mod)
            res -= _mod;
        return res;
    }
    inline modint operator-(const modint &rhs) const
    {
        _T res = x;
        res -= rhs.x;
        if (res < 0)
            res += _mod;
        return res;
    }
    inline modint operator*(const modint &rhs) const
    {
        return (_T)((ll)x * rhs.x % _mod);
    }
    inline modint &operator+=(const modint &rhs)
    {
        x += rhs.x;
        if (x >= _mod)
            x -= _mod;
        return *this;
    }
    inline modint &operator-=(const modint &rhs)
    {
        x -= rhs.x;
        if (x < 0)
            x += _mod;
        return *this;
    }
    inline modint &operator*=(const modint &rhs)
    {
        x = (_T)((ll)x * rhs.x % _mod);
        return *this;
    }
    template <typename _G>
    inline modint operator^(_G rhs) const
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
    inline modint inv()
    {
        return this->pow(_mod - 2);
    }
    inline modint operator/(const modint &rhs) const
    {
        return (*this) * rhs.inv();
    }
    inline modint &operator/=(const modint &rhs)
    {
        return (*this) *= rhs.inv();
    }
    inline modint &operator==(const modint &rhs)
    {
        return x == rhs.x;
    }
    inline _T &data()
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
constexpr int N = 3e6 + 5;
int n, d, m;
char str[N];
int a[N];
struct Matrix
{
    mutable double g[10];
    Matrix() { memset(g, 0, sizeof(g)); }
    inline Matrix operator*(const Matrix &rhs) const
    {
        Matrix res;
        for (int i = 0; i < d; ++i)
        {
            for (int j = 0; i + j < d; ++j)
                res.g[i + j] += g[i] * rhs.g[j];
            for (int j = d - i; j < d; ++j)
                res.g[i + j - d] += g[i] * rhs.g[j];
        }
        return res;
    }
    inline void clear()
    {
        memset(g, 0, sizeof(g));
    }
    inline double& operator[](int x) const
    {
        return g[x];
    }
    inline void print()
    {
        for (int i = 0; i < d; ++i)
            printf("%.6lf ", g[i]);
        write('\n');
    }
} A, B;
double cnt[11][11];
double answer[10];
signed main()
{
    read(n, d, m, str);
    for (int k = d; k <= n; k += d)
    {
        for (int i = k - d; i < k; ++i)
        {
            int c = str[i] - '0';
            auto calc = [](auto x)
            {
                x %= d;
                return x < 0 ? x + d : x;
            };
            cnt[c][calc(c - i)] += i + 1;
        }
        A[0] = 1;
        B[1] += 1. / k, B[d - 1] += 1. / k, B[0] += (k - 2.) / k;
        int power = m;
        while (power)
        {
            if (power & 1)
                A = A * B;
            B = B * B;
            power >>= 1;
        }
        for (int i = 0; i < d; ++i)
            for (int j = 0; j < d; ++j)
                answer[i] += cnt[i][j] * A[j];
        A.clear(), B.clear();
    }
    for (int i = 0; i < d; ++i)
        printf("%.6lf\n", answer[i]);
#ifdef FAST_OUT
    IO::OUTPUT::flush();
#endif
    return 0;
}