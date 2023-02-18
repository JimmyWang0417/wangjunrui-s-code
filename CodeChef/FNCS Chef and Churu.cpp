/**
 *    name:     FNCS Chef and Churu
 *    author:   whitepaperdog (蒟蒻wjr)
 *    located:  Changle District, Fuzhou City, Fujian Province, China
 *    created:  2023.02.10 周五 20:30:03 (Asia/Shanghai)
 *    unicode:  UTF-8
 *    standard: c++23
 **/
#include <cstdio>
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
constexpr int N = 1e5 + 5, M = 327;
int n, m, a[N];
int block, num;
int L[N], R[N], belong[N];
struct node
{
    int l, r;
} b[N];
int128 sum[N], sumblock[M], all[M];
int cnt[M][N];
inline int128 _query(int l, int r)
{
    if (belong[l] == belong[r])
    {
        int128 res = sum[r];
        if (belong[l - 1] == belong[l])
            res -= sum[l - 1];
        return res;
    }
    int128 res = sum[R[belong[l]]];
    if (belong[l - 1] == belong[l])
        res -= sum[l - 1];
    res += sumblock[belong[r] - 1] - sumblock[belong[l]];
    res += sum[r];
    return res;
}
inline int128 query(int l, int r)
{
    if (belong[l] == belong[r])
    {
        int128 res = 0;
        for (int i = l; i <= r; ++i)
            res += _query(b[i].l, b[i].r);
        return res;
    }
    int128 res = 0;
    for (int i = l; i <= R[belong[l]]; ++i)
        res += _query(b[i].l, b[i].r);
    for (int i = belong[l] + 1; i < belong[r]; ++i)
        res += all[i];
    for (int i = L[belong[r]]; i <= r; ++i)
        res += _query(b[i].l, b[i].r);
    return res;
}
inline void update(int pos, int val)
{
    for (int i = 1; i <= num; ++i)
        all[i] += (int128)cnt[i][pos] * val;
    int bel = belong[pos];
    for (int i = pos; i <= R[bel]; ++i)
        sum[i] += val;
    for (int i = bel; i <= num; ++i)
        sumblock[i] += val;
}
signed main()
{
#ifdef PAPERDOG
    freopen("project.in", "r", stdin);
    freopen("project.out", "w", stdout);
#endif
    read(n);
    block = (int)__builtin_sqrt(n);
    for (int i = 1; i <= n; ++i)
        read(a[i]);
    for (int i = 1; i <= n; ++i)
        read(b[i].l, b[i].r);
    num = (n - 1) / block + 1;
    for (int i = 1; i <= n; ++i)
    {
        L[i] = R[i - 1] + 1;
        R[i] = R[i - 1] + block;
    }
    R[num] = n;
    for (int i = 1; i <= num; ++i)
    {
        sumblock[i] = sumblock[i - 1];
        for (int j = L[i]; j <= R[i]; ++j)
        {
            belong[j] = i;
            sumblock[i] += a[j];
        }
        sum[L[i]] = a[L[i]];
        for (int j = L[i] + 1; j <= R[i]; ++j)
            sum[j] = sum[j - 1] + a[j];
    }
    for (int i = 1; i <= num; ++i)
    {
        for (int j = L[i]; j <= R[i]; ++j)
        {
            ++cnt[i][b[j].l];
            --cnt[i][b[j].r + 1];
            all[i] += _query(b[j].l, b[j].r);
        }
        for (int j = 2; j <= n; ++j)
            cnt[i][j] += cnt[i][j - 1];
    }
    read(m);
    for (int i = 1; i <= m; ++i)
    {
        int opt, x, y;
        read(opt, x, y);
        if (opt == 1)
        {
            update(x, y - a[x]);
            a[x] = y;
        }
        else
            write(query(x, y), '\n');
    }
#ifdef FAST_OUT
    IO::OUTPUT::flush();
#endif
    return 0;
}