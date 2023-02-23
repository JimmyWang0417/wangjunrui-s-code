/**
 *    name:     knight
 *    author:   whitepaperdog (蒟蒻wjr)
 *    located:  Changle District, Fuzhou City, Fujian Province, China
 *    created:  2023.02.23 周四 14:03:19 (Asia/Shanghai)
 *    unicode:  UTF-8
 *    standard: c++23
 **/
#include <cstdio>
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
#define getchar()                                                                                       \
    (_now == _end && (_end = (_now = _buf) + fread(_buf, 1, FAST_OUT_BUFFER_SIZE, stdin), _now == _end) \
         ? EOF                                                                                          \
         : *_now++)
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
    } // namespace INPUT
    namespace OUTPUT
    {
#ifdef FAST_OUT
#ifndef FAST_OUT_BUFFER_SIZE
#define FAST_OUT_BUFFER_SIZE (1 << 21)
#endif
        char _buf[FAST_OUT_BUFFER_SIZE], *_now = _buf;
        inline void flush() { fwrite(_buf, 1, _now - _buf, stdout), _now = _buf; }
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
    } // namespace OUTPUT
} // namespace IO
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
    constexpr inline modint operator+() const { return *this; }
    constexpr inline modint operator-() const { return !x ? 0 : _mod - x; }
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
    constexpr inline modint operator*(const modint &rhs) const { return (int)((ll)x * rhs.x % _mod); }
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
    constexpr inline modint inv() const { return *this ^ (_mod - 2); }
    constexpr inline modint operator/(const modint &rhs) const { return (*this) * rhs.inv(); }
    constexpr inline modint &operator/=(const modint &rhs) { return (*this) *= rhs.inv(); }
    constexpr inline modint &operator==(const modint &rhs) { return x == rhs.x; }
    constexpr inline int &data() { return x; }
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
constexpr int N = 1000 * 1000 + 5;
int n, m;
struct node
{
    int x1, y1, x2, y2;
    node(int _x1 = 0, int _y1 = 0, int _x2 = 0, int _y2 = 0) : x1(_x1), y1(_y1), x2(_x2), y2(_y2) {}
} answer[N];
int answertot;
inline void add(int x1, int y1, int x2, int y2) { answer[++answertot] = node(x1, y1, x2, y2); }
inline void solve(int _x, int _y, int _n, int _m)
{
    if (_n == 3 && _m == 3)
    {
        answer[++answertot] = node(_x + 1, _y + 1, _x + 3, _y + 2);
        answer[++answertot] = node(_x + 1, _y + 3, _x + 2, _y + 1);
        answer[++answertot] = node(_x + 2, _y + 3, _x + 3, _y + 1);
        answer[++answertot] = node(_x + 1, _y + 2, _x + 3, _y + 3);
        return;
    }
    if (_n == 3 && _m == 4)
    {
        answer[++answertot] = node(_x + 1, _y + 1, _x + 3, _y + 2);
        answer[++answertot] = node(_x + 2, _y + 3, _x + 3, _y + 1);
        answer[++answertot] = node(_x + 1, _y + 2, _x + 2, _y + 4);
        answer[++answertot] = node(_x + 1, _y + 3, _x + 3, _y + 4);
        answer[++answertot] = node(_x + 2, _y + 1, _x + 3, _y + 3);
        answer[++answertot] = node(_x + 1, _y + 4, _x + 2, _y + 2);
        return;
    }
    if (_n == 3 && _m == 5)
    {
        answer[++answertot] = node(_x + 1, _y + 1, _x + 3, _y + 2);
        answer[++answertot] = node(_x + 1, _y + 2, _x + 2, _y + 4);
        answer[++answertot] = node(_x + 2, _y + 3, _x + 3, _y + 1);
        answer[++answertot] = node(_x + 1, _y + 5, _x + 3, _y + 4);
        answer[++answertot] = node(_x + 1, _y + 4, _x + 2, _y + 2);
        answer[++answertot] = node(_x + 1, _y + 3, _x + 2, _y + 1);
        answer[++answertot] = node(_x + 2, _y + 5, _x + 3, _y + 3);
        return;
    }
    if (_n == 3 && _m == 6)
    {
        answer[++answertot] = node(_x + 1, _y + 1, _x + 3, _y + 2);
        answer[++answertot] = node(_x + 1, _y + 6, _x + 3, _y + 5);
        answer[++answertot] = node(_x + 2, _y + 1, _x + 3, _y + 3);
        answer[++answertot] = node(_x + 1, _y + 3, _x + 2, _y + 5);
        answer[++answertot] = node(_x + 1, _y + 2, _x + 3, _y + 1);
        answer[++answertot] = node(_x + 1, _y + 5, _x + 2, _y + 3);
        answer[++answertot] = node(_x + 2, _y + 4, _x + 3, _y + 6);
        answer[++answertot] = node(_x + 1, _y + 4, _x + 2, _y + 2);
        answer[++answertot] = node(_x + 2, _y + 6, _x + 3, _y + 4);
        return;
    }
    if (_n == 3 && _m == 7)
    {
        answer[++answertot] = node(_x + 1, _y + 1, _x + 3, _y + 2);
        answer[++answertot] = node(_x + 1, _y + 7, _x + 3, _y + 6);
        answer[++answertot] = node(_x + 2, _y + 1, _x + 3, _y + 3);
        answer[++answertot] = node(_x + 1, _y + 2, _x + 3, _y + 1);
        answer[++answertot] = node(_x + 1, _y + 6, _x + 2, _y + 4);
        answer[++answertot] = node(_x + 2, _y + 5, _x + 3, _y + 7);
        answer[++answertot] = node(_x + 1, _y + 3, _x + 3, _y + 4);
        answer[++answertot] = node(_x + 1, _y + 4, _x + 2, _y + 2);
        answer[++answertot] = node(_x + 1, _y + 5, _x + 2, _y + 3);
        answer[++answertot] = node(_x + 2, _y + 7, _x + 3, _y + 5);
        return;
    }
    if (_n == 4 && _m == 3)
    {
        answer[++answertot] = node(_x + 1, _y + 1, _x + 3, _y + 2);
        answer[++answertot] = node(_x + 1, _y + 3, _x + 2, _y + 1);
        answer[++answertot] = node(_x + 2, _y + 3, _x + 4, _y + 2);
        answer[++answertot] = node(_x + 1, _y + 2, _x + 3, _y + 1);
        answer[++answertot] = node(_x + 3, _y + 3, _x + 4, _y + 1);
        answer[++answertot] = node(_x + 2, _y + 2, _x + 4, _y + 3);
        return;
    }
    if (_n == 4 && _m == 4)
    {
        answer[++answertot] = node(_x + 1, _y + 1, _x + 3, _y + 2);
        answer[++answertot] = node(_x + 2, _y + 3, _x + 4, _y + 4);
        answer[++answertot] = node(_x + 1, _y + 3, _x + 3, _y + 4);
        answer[++answertot] = node(_x + 2, _y + 1, _x + 4, _y + 2);
        answer[++answertot] = node(_x + 1, _y + 4, _x + 3, _y + 3);
        answer[++answertot] = node(_x + 2, _y + 2, _x + 4, _y + 1);
        answer[++answertot] = node(_x + 1, _y + 2, _x + 3, _y + 1);
        answer[++answertot] = node(_x + 2, _y + 4, _x + 4, _y + 3);
        return;
    }
    if (_n == 4 && _m == 5)
    {
        answer[++answertot] = node(_x + 1, _y + 1, _x + 3, _y + 2);
        answer[++answertot] = node(_x + 1, _y + 5, _x + 3, _y + 4);
        answer[++answertot] = node(_x + 1, _y + 3, _x + 2, _y + 1);
        answer[++answertot] = node(_x + 2, _y + 3, _x + 4, _y + 2);
        answer[++answertot] = node(_x + 2, _y + 5, _x + 4, _y + 4);
        answer[++answertot] = node(_x + 3, _y + 1, _x + 4, _y + 3);
        answer[++answertot] = node(_x + 1, _y + 4, _x + 3, _y + 5);
        answer[++answertot] = node(_x + 2, _y + 2, _x + 4, _y + 1);
        answer[++answertot] = node(_x + 1, _y + 2, _x + 3, _y + 3);
        answer[++answertot] = node(_x + 2, _y + 4, _x + 4, _y + 5);
        return;
    }
    if (_n == 4 && _m == 6)
    {
        answer[++answertot] = node(_x + 1, _y + 1, _x + 3, _y + 2);
        answer[++answertot] = node(_x + 1, _y + 6, _x + 3, _y + 5);
        answer[++answertot] = node(_x + 3, _y + 3, _x + 4, _y + 1);
        answer[++answertot] = node(_x + 1, _y + 2, _x + 3, _y + 1);
        answer[++answertot] = node(_x + 1, _y + 4, _x + 2, _y + 2);
        answer[++answertot] = node(_x + 2, _y + 4, _x + 4, _y + 3);
        answer[++answertot] = node(_x + 2, _y + 6, _x + 4, _y + 5);
        answer[++answertot] = node(_x + 2, _y + 1, _x + 4, _y + 2);
        answer[++answertot] = node(_x + 1, _y + 3, _x + 3, _y + 4);
        answer[++answertot] = node(_x + 2, _y + 5, _x + 4, _y + 6);
        answer[++answertot] = node(_x + 1, _y + 5, _x + 3, _y + 6);
        answer[++answertot] = node(_x + 2, _y + 3, _x + 4, _y + 4);
        return;
    }
    if (_n == 4 && _m == 7)
    {
        answer[++answertot] = node(_x + 1, _y + 1, _x + 3, _y + 2);
        answer[++answertot] = node(_x + 1, _y + 7, _x + 3, _y + 6);
        answer[++answertot] = node(_x + 3, _y + 3, _x + 4, _y + 1);
        answer[++answertot] = node(_x + 1, _y + 2, _x + 3, _y + 1);
        answer[++answertot] = node(_x + 2, _y + 1, _x + 4, _y + 2);
        answer[++answertot] = node(_x + 1, _y + 3, _x + 3, _y + 4);
        answer[++answertot] = node(_x + 1, _y + 5, _x + 2, _y + 3);
        answer[++answertot] = node(_x + 2, _y + 5, _x + 4, _y + 4);
        answer[++answertot] = node(_x + 2, _y + 7, _x + 4, _y + 6);
        answer[++answertot] = node(_x + 2, _y + 2, _x + 4, _y + 3);
        answer[++answertot] = node(_x + 1, _y + 4, _x + 3, _y + 5);
        answer[++answertot] = node(_x + 2, _y + 6, _x + 4, _y + 7);
        answer[++answertot] = node(_x + 1, _y + 6, _x + 3, _y + 7);
        answer[++answertot] = node(_x + 2, _y + 4, _x + 4, _y + 5);
        return;
    }
    if (_n == 5 && _m == 3)
    {
        answer[++answertot] = node(_x + 1, _y + 1, _x + 3, _y + 2);
        answer[++answertot] = node(_x + 1, _y + 3, _x + 2, _y + 1);
        answer[++answertot] = node(_x + 2, _y + 3, _x + 4, _y + 2);
        answer[++answertot] = node(_x + 4, _y + 3, _x + 5, _y + 1);
        answer[++answertot] = node(_x + 2, _y + 2, _x + 4, _y + 1);
        answer[++answertot] = node(_x + 1, _y + 2, _x + 3, _y + 1);
        answer[++answertot] = node(_x + 3, _y + 3, _x + 5, _y + 2);
        return;
    }
    if (_n == 5 && _m == 4)
    {
        answer[++answertot] = node(_x + 1, _y + 1, _x + 3, _y + 2);
        answer[++answertot] = node(_x + 4, _y + 3, _x + 5, _y + 1);
        answer[++answertot] = node(_x + 1, _y + 2, _x + 2, _y + 4);
        answer[++answertot] = node(_x + 1, _y + 3, _x + 3, _y + 4);
        answer[++answertot] = node(_x + 4, _y + 1, _x + 5, _y + 3);
        answer[++answertot] = node(_x + 1, _y + 4, _x + 2, _y + 2);
        answer[++answertot] = node(_x + 2, _y + 1, _x + 4, _y + 2);
        answer[++answertot] = node(_x + 3, _y + 3, _x + 5, _y + 4);
        answer[++answertot] = node(_x + 2, _y + 3, _x + 4, _y + 4);
        answer[++answertot] = node(_x + 3, _y + 1, _x + 5, _y + 2);
        return;
    }
    if (_n == 5 && _m == 5)
    {
        answer[++answertot] = node(_x + 1, _y + 1, _x + 3, _y + 2);
        answer[++answertot] = node(_x + 4, _y + 3, _x + 5, _y + 1);
        answer[++answertot] = node(_x + 3, _y + 4, _x + 5, _y + 5);
        answer[++answertot] = node(_x + 1, _y + 5, _x + 2, _y + 3);
        answer[++answertot] = node(_x + 1, _y + 3, _x + 2, _y + 1);
        answer[++answertot] = node(_x + 4, _y + 2, _x + 5, _y + 4);
        answer[++answertot] = node(_x + 1, _y + 4, _x + 3, _y + 5);
        answer[++answertot] = node(_x + 2, _y + 2, _x + 4, _y + 1);
        answer[++answertot] = node(_x + 4, _y + 5, _x + 5, _y + 3);
        answer[++answertot] = node(_x + 1, _y + 2, _x + 2, _y + 4);
        answer[++answertot] = node(_x + 3, _y + 1, _x + 5, _y + 2);
        answer[++answertot] = node(_x + 2, _y + 5, _x + 3, _y + 3);
        return;
    }
    if (_n == 5 && _m == 6)
    {
        answer[++answertot] = node(_x + 1, _y + 1, _x + 3, _y + 2);
        answer[++answertot] = node(_x + 4, _y + 3, _x + 5, _y + 1);
        answer[++answertot] = node(_x + 1, _y + 6, _x + 3, _y + 5);
        answer[++answertot] = node(_x + 4, _y + 4, _x + 5, _y + 6);
        answer[++answertot] = node(_x + 3, _y + 3, _x + 5, _y + 2);
        answer[++answertot] = node(_x + 1, _y + 2, _x + 3, _y + 1);
        answer[++answertot] = node(_x + 1, _y + 4, _x + 2, _y + 2);
        answer[++answertot] = node(_x + 4, _y + 1, _x + 5, _y + 3);
        answer[++answertot] = node(_x + 2, _y + 1, _x + 4, _y + 2);
        answer[++answertot] = node(_x + 1, _y + 5, _x + 2, _y + 3);
        answer[++answertot] = node(_x + 4, _y + 6, _x + 5, _y + 4);
        answer[++answertot] = node(_x + 1, _y + 3, _x + 2, _y + 5);
        answer[++answertot] = node(_x + 2, _y + 4, _x + 4, _y + 5);
        answer[++answertot] = node(_x + 2, _y + 6, _x + 3, _y + 4);
        answer[++answertot] = node(_x + 3, _y + 6, _x + 5, _y + 5);
        return;
    }
    if (_n == 5 && _m == 7)
    {
        answer[++answertot] = node(_x + 1, _y + 1, _x + 3, _y + 2);
        answer[++answertot] = node(_x + 4, _y + 3, _x + 5, _y + 1);
        answer[++answertot] = node(_x + 1, _y + 7, _x + 3, _y + 6);
        answer[++answertot] = node(_x + 4, _y + 5, _x + 5, _y + 7);
        answer[++answertot] = node(_x + 1, _y + 6, _x + 2, _y + 4);
        answer[++answertot] = node(_x + 1, _y + 2, _x + 3, _y + 1);
        answer[++answertot] = node(_x + 3, _y + 7, _x + 5, _y + 6);
        answer[++answertot] = node(_x + 4, _y + 4, _x + 5, _y + 2);
        answer[++answertot] = node(_x + 4, _y + 1, _x + 5, _y + 3);
        answer[++answertot] = node(_x + 2, _y + 2, _x + 3, _y + 4);
        answer[++answertot] = node(_x + 4, _y + 7, _x + 5, _y + 5);
        answer[++answertot] = node(_x + 1, _y + 4, _x + 2, _y + 6);
        answer[++answertot] = node(_x + 1, _y + 3, _x + 2, _y + 1);
        answer[++answertot] = node(_x + 1, _y + 5, _x + 2, _y + 3);
        answer[++answertot] = node(_x + 4, _y + 2, _x + 5, _y + 4);
        answer[++answertot] = node(_x + 2, _y + 5, _x + 3, _y + 3);
        answer[++answertot] = node(_x + 2, _y + 7, _x + 3, _y + 5);
        return;
    }
    if (_n == 6 && _m == 3)
    {
        answer[++answertot] = node(_x + 1, _y + 1, _x + 3, _y + 2);
        answer[++answertot] = node(_x + 1, _y + 3, _x + 2, _y + 1);
        answer[++answertot] = node(_x + 1, _y + 2, _x + 3, _y + 1);
        answer[++answertot] = node(_x + 2, _y + 3, _x + 4, _y + 2);
        answer[++answertot] = node(_x + 3, _y + 3, _x + 5, _y + 2);
        answer[++answertot] = node(_x + 5, _y + 3, _x + 6, _y + 1);
        answer[++answertot] = node(_x + 5, _y + 1, _x + 6, _y + 3);
        answer[++answertot] = node(_x + 2, _y + 2, _x + 4, _y + 1);
        answer[++answertot] = node(_x + 4, _y + 3, _x + 6, _y + 2);
        return;
    }
    if (_n == 6 && _m == 4)
    {
        answer[++answertot] = node(_x + 1, _y + 1, _x + 3, _y + 2);
        answer[++answertot] = node(_x + 1, _y + 3, _x + 3, _y + 4);
        answer[++answertot] = node(_x + 1, _y + 4, _x + 3, _y + 3);
        answer[++answertot] = node(_x + 2, _y + 1, _x + 4, _y + 2);
        answer[++answertot] = node(_x + 5, _y + 4, _x + 6, _y + 2);
        answer[++answertot] = node(_x + 5, _y + 3, _x + 6, _y + 1);
        answer[++answertot] = node(_x + 2, _y + 2, _x + 4, _y + 1);
        answer[++answertot] = node(_x + 1, _y + 2, _x + 3, _y + 1);
        answer[++answertot] = node(_x + 2, _y + 3, _x + 4, _y + 4);
        answer[++answertot] = node(_x + 2, _y + 4, _x + 4, _y + 3);
        answer[++answertot] = node(_x + 5, _y + 1, _x + 6, _y + 3);
        answer[++answertot] = node(_x + 5, _y + 2, _x + 6, _y + 4);
        return;
    }
    if (_n == 6 && _m == 5)
    {
        answer[++answertot] = node(_x + 1, _y + 1, _x + 3, _y + 2);
        answer[++answertot] = node(_x + 1, _y + 5, _x + 3, _y + 4);
        answer[++answertot] = node(_x + 1, _y + 3, _x + 2, _y + 1);
        answer[++answertot] = node(_x + 2, _y + 5, _x + 4, _y + 4);
        answer[++answertot] = node(_x + 5, _y + 3, _x + 6, _y + 5);
        answer[++answertot] = node(_x + 4, _y + 2, _x + 6, _y + 1);
        answer[++answertot] = node(_x + 2, _y + 3, _x + 3, _y + 1);
        answer[++answertot] = node(_x + 1, _y + 2, _x + 3, _y + 3);
        answer[++answertot] = node(_x + 5, _y + 2, _x + 6, _y + 4);
        answer[++answertot] = node(_x + 2, _y + 4, _x + 4, _y + 5);
        answer[++answertot] = node(_x + 1, _y + 4, _x + 3, _y + 5);
        answer[++answertot] = node(_x + 5, _y + 4, _x + 6, _y + 2);
        answer[++answertot] = node(_x + 2, _y + 2, _x + 4, _y + 1);
        answer[++answertot] = node(_x + 4, _y + 3, _x + 5, _y + 1);
        answer[++answertot] = node(_x + 5, _y + 5, _x + 6, _y + 3);
        return;
    }
    if (_n == 6 && _m == 6)
    {
        answer[++answertot] = node(_x + 1, _y + 1, _x + 3, _y + 2);
        answer[++answertot] = node(_x + 1, _y + 6, _x + 3, _y + 5);
        answer[++answertot] = node(_x + 5, _y + 1, _x + 6, _y + 3);
        answer[++answertot] = node(_x + 5, _y + 6, _x + 6, _y + 4);
        answer[++answertot] = node(_x + 5, _y + 3, _x + 6, _y + 1);
        answer[++answertot] = node(_x + 4, _y + 6, _x + 6, _y + 5);
        answer[++answertot] = node(_x + 5, _y + 4, _x + 6, _y + 6);
        answer[++answertot] = node(_x + 4, _y + 3, _x + 6, _y + 2);
        answer[++answertot] = node(_x + 3, _y + 3, _x + 4, _y + 1);
        answer[++answertot] = node(_x + 1, _y + 2, _x + 3, _y + 1);
        answer[++answertot] = node(_x + 4, _y + 4, _x + 5, _y + 2);
        answer[++answertot] = node(_x + 1, _y + 3, _x + 2, _y + 5);
        answer[++answertot] = node(_x + 2, _y + 1, _x + 4, _y + 2);
        answer[++answertot] = node(_x + 1, _y + 5, _x + 2, _y + 3);
        answer[++answertot] = node(_x + 1, _y + 4, _x + 2, _y + 2);
        answer[++answertot] = node(_x + 2, _y + 4, _x + 4, _y + 5);
        answer[++answertot] = node(_x + 2, _y + 6, _x + 3, _y + 4);
        answer[++answertot] = node(_x + 3, _y + 6, _x + 5, _y + 5);
        return;
    }
    if (_n == 6 && _m == 7)
    {
        answer[++answertot] = node(_x + 1, _y + 1, _x + 3, _y + 2);
        answer[++answertot] = node(_x + 1, _y + 7, _x + 3, _y + 6);
        answer[++answertot] = node(_x + 5, _y + 1, _x + 6, _y + 3);
        answer[++answertot] = node(_x + 5, _y + 7, _x + 6, _y + 5);
        answer[++answertot] = node(_x + 5, _y + 3, _x + 6, _y + 1);
        answer[++answertot] = node(_x + 5, _y + 5, _x + 6, _y + 7);
        answer[++answertot] = node(_x + 1, _y + 2, _x + 3, _y + 1);
        answer[++answertot] = node(_x + 1, _y + 3, _x + 3, _y + 4);
        answer[++answertot] = node(_x + 1, _y + 5, _x + 2, _y + 3);
        answer[++answertot] = node(_x + 2, _y + 1, _x + 4, _y + 2);
        answer[++answertot] = node(_x + 2, _y + 7, _x + 4, _y + 6);
        answer[++answertot] = node(_x + 1, _y + 6, _x + 3, _y + 5);
        answer[++answertot] = node(_x + 2, _y + 4, _x + 4, _y + 3);
        answer[++answertot] = node(_x + 2, _y + 2, _x + 4, _y + 1);
        answer[++answertot] = node(_x + 5, _y + 4, _x + 6, _y + 2);
        answer[++answertot] = node(_x + 1, _y + 4, _x + 3, _y + 3);
        answer[++answertot] = node(_x + 2, _y + 5, _x + 4, _y + 4);
        answer[++answertot] = node(_x + 5, _y + 2, _x + 6, _y + 4);
        answer[++answertot] = node(_x + 3, _y + 7, _x + 5, _y + 6);
        answer[++answertot] = node(_x + 2, _y + 6, _x + 4, _y + 5);
        answer[++answertot] = node(_x + 4, _y + 7, _x + 6, _y + 6);
        return;
    }
    if (_n == 7 && _m == 3)
    {
        answer[++answertot] = node(_x + 1, _y + 1, _x + 3, _y + 2);
        answer[++answertot] = node(_x + 1, _y + 3, _x + 2, _y + 1);
        answer[++answertot] = node(_x + 1, _y + 2, _x + 3, _y + 1);
        answer[++answertot] = node(_x + 2, _y + 3, _x + 4, _y + 2);
        answer[++answertot] = node(_x + 2, _y + 2, _x + 4, _y + 1);
        answer[++answertot] = node(_x + 3, _y + 3, _x + 5, _y + 2);
        answer[++answertot] = node(_x + 4, _y + 3, _x + 6, _y + 2);
        answer[++answertot] = node(_x + 6, _y + 3, _x + 7, _y + 1);
        answer[++answertot] = node(_x + 5, _y + 1, _x + 7, _y + 2);
        answer[++answertot] = node(_x + 5, _y + 3, _x + 6, _y + 1);
        return;
    }
    if (_n == 7 && _m == 4)
    {
        answer[++answertot] = node(_x + 1, _y + 1, _x + 3, _y + 2);
        answer[++answertot] = node(_x + 1, _y + 3, _x + 3, _y + 4);
        answer[++answertot] = node(_x + 1, _y + 4, _x + 3, _y + 3);
        answer[++answertot] = node(_x + 2, _y + 1, _x + 4, _y + 2);
        answer[++answertot] = node(_x + 1, _y + 2, _x + 3, _y + 1);
        answer[++answertot] = node(_x + 2, _y + 3, _x + 4, _y + 4);
        answer[++answertot] = node(_x + 2, _y + 4, _x + 4, _y + 3);
        answer[++answertot] = node(_x + 2, _y + 2, _x + 4, _y + 1);
        answer[++answertot] = node(_x + 5, _y + 1, _x + 7, _y + 2);
        answer[++answertot] = node(_x + 6, _y + 3, _x + 7, _y + 1);
        answer[++answertot] = node(_x + 5, _y + 2, _x + 6, _y + 4);
        answer[++answertot] = node(_x + 5, _y + 3, _x + 7, _y + 4);
        answer[++answertot] = node(_x + 6, _y + 1, _x + 7, _y + 3);
        answer[++answertot] = node(_x + 5, _y + 4, _x + 6, _y + 2);
        return;
    }
    if (_n == 7 && _m == 5)
    {
        answer[++answertot] = node(_x + 1, _y + 1, _x + 3, _y + 2);
        answer[++answertot] = node(_x + 1, _y + 5, _x + 3, _y + 4);
        answer[++answertot] = node(_x + 1, _y + 3, _x + 2, _y + 1);
        answer[++answertot] = node(_x + 2, _y + 5, _x + 4, _y + 4);
        answer[++answertot] = node(_x + 6, _y + 5, _x + 7, _y + 3);
        answer[++answertot] = node(_x + 5, _y + 3, _x + 6, _y + 1);
        answer[++answertot] = node(_x + 6, _y + 3, _x + 7, _y + 1);
        answer[++answertot] = node(_x + 5, _y + 4, _x + 7, _y + 5);
        answer[++answertot] = node(_x + 2, _y + 3, _x + 4, _y + 2);
        answer[++answertot] = node(_x + 3, _y + 5, _x + 4, _y + 3);
        answer[++answertot] = node(_x + 5, _y + 1, _x + 7, _y + 2);
        answer[++answertot] = node(_x + 5, _y + 5, _x + 7, _y + 4);
        answer[++answertot] = node(_x + 4, _y + 1, _x + 6, _y + 2);
        answer[++answertot] = node(_x + 1, _y + 4, _x + 2, _y + 2);
        answer[++answertot] = node(_x + 2, _y + 4, _x + 4, _y + 5);
        answer[++answertot] = node(_x + 5, _y + 2, _x + 6, _y + 4);
        answer[++answertot] = node(_x + 1, _y + 2, _x + 3, _y + 1);
        return;
    }
    if (_n == 7 && _m == 6)
    {
        answer[++answertot] = node(_x + 1, _y + 1, _x + 3, _y + 2);
        answer[++answertot] = node(_x + 1, _y + 6, _x + 3, _y + 5);
        answer[++answertot] = node(_x + 6, _y + 3, _x + 7, _y + 1);
        answer[++answertot] = node(_x + 5, _y + 1, _x + 7, _y + 2);
        answer[++answertot] = node(_x + 5, _y + 6, _x + 7, _y + 5);
        answer[++answertot] = node(_x + 6, _y + 4, _x + 7, _y + 6);
        answer[++answertot] = node(_x + 1, _y + 2, _x + 3, _y + 1);
        answer[++answertot] = node(_x + 1, _y + 3, _x + 3, _y + 4);
        answer[++answertot] = node(_x + 1, _y + 5, _x + 3, _y + 6);
        answer[++answertot] = node(_x + 2, _y + 1, _x + 4, _y + 2);
        answer[++answertot] = node(_x + 2, _y + 3, _x + 4, _y + 4);
        answer[++answertot] = node(_x + 2, _y + 4, _x + 4, _y + 3);
        answer[++answertot] = node(_x + 5, _y + 5, _x + 7, _y + 4);
        answer[++answertot] = node(_x + 2, _y + 2, _x + 4, _y + 1);
        answer[++answertot] = node(_x + 5, _y + 4, _x + 6, _y + 2);
        answer[++answertot] = node(_x + 4, _y + 5, _x + 6, _y + 6);
        answer[++answertot] = node(_x + 1, _y + 4, _x + 2, _y + 6);
        answer[++answertot] = node(_x + 2, _y + 5, _x + 4, _y + 6);
        answer[++answertot] = node(_x + 3, _y + 3, _x + 5, _y + 2);
        answer[++answertot] = node(_x + 5, _y + 3, _x + 6, _y + 1);
        answer[++answertot] = node(_x + 6, _y + 5, _x + 7, _y + 3);
        return;
    }
    if (_n == 7 && _m == 7)
    {
        answer[++answertot] = node(_x + 1, _y + 1, _x + 3, _y + 2);
        answer[++answertot] = node(_x + 1, _y + 7, _x + 3, _y + 6);
        answer[++answertot] = node(_x + 6, _y + 3, _x + 7, _y + 1);
        answer[++answertot] = node(_x + 5, _y + 1, _x + 7, _y + 2);
        answer[++answertot] = node(_x + 6, _y + 5, _x + 7, _y + 7);
        answer[++answertot] = node(_x + 5, _y + 7, _x + 7, _y + 6);
        answer[++answertot] = node(_x + 1, _y + 2, _x + 3, _y + 1);
        answer[++answertot] = node(_x + 1, _y + 3, _x + 3, _y + 4);
        answer[++answertot] = node(_x + 1, _y + 5, _x + 2, _y + 3);
        answer[++answertot] = node(_x + 2, _y + 1, _x + 4, _y + 2);
        answer[++answertot] = node(_x + 2, _y + 7, _x + 4, _y + 6);
        answer[++answertot] = node(_x + 6, _y + 1, _x + 7, _y + 3);
        answer[++answertot] = node(_x + 6, _y + 7, _x + 7, _y + 5);
        answer[++answertot] = node(_x + 1, _y + 6, _x + 3, _y + 5);
        answer[++answertot] = node(_x + 2, _y + 4, _x + 4, _y + 3);
        answer[++answertot] = node(_x + 2, _y + 2, _x + 4, _y + 1);
        answer[++answertot] = node(_x + 1, _y + 4, _x + 3, _y + 3);
        answer[++answertot] = node(_x + 2, _y + 5, _x + 4, _y + 4);
        answer[++answertot] = node(_x + 5, _y + 2, _x + 6, _y + 4);
        answer[++answertot] = node(_x + 3, _y + 7, _x + 5, _y + 6);
        answer[++answertot] = node(_x + 2, _y + 6, _x + 4, _y + 5);
        answer[++answertot] = node(_x + 5, _y + 3, _x + 7, _y + 4);
        answer[++answertot] = node(_x + 4, _y + 7, _x + 5, _y + 5);
        answer[++answertot] = node(_x + 5, _y + 4, _x + 6, _y + 2);
        return;
    }
}
inline void work()
{
    read(n, m);
    if (n == 1 || m == 1)
        ;
    else if (n == 2)
    {
        for (int i = 1; i + 2 <= m; ++i)
        {
            if (i % 4 == 3 || i % 4 == 0)
                continue;
            add(1, i, 2, i + 2);
            add(2, i, 1, i + 2);
        }
    }
    else if (m == 2)
    {
        for (int i = 1; i + 2 <= n; ++i)
        {
            if (i % 4 == 3 || i % 4 == 0)
                continue;
            add(i, 1, i + 2, 2);
            add(i, 2, i + 2, 1);
        }
    }
    else
    {
        for (int i = 0;; i += 4)
        {
            int x, y;
            if (n - i <= 7)
                x = n - i;
            else
                x = 4;
            for (int j = 0;; j += 4)
            {
                if (m - j <= 7)
                    y = m - j;
                else
                    y = 4;
                solve(i, j, x, y);
                if (m - j <= 7)
                    break;
            }
            if (n - i <= 7)
                break;
        }
    }
    write(answertot, '\n');
    for (int i = 1; i <= answertot; ++i)
        write(answer[i].x1, ' ', answer[i].y1, ' ', answer[i].x2, ' ', answer[i].y2, '\n');
    answertot = 0;
}
signed main()
{
#ifdef PAPERDOG
    freopen("project.in", "r", stdin);
    freopen("project.out", "w", stdout);
#else
    freopen("knight.in", "r", stdin);
    freopen("knight.out", "w", stdout);
#endif
    int T = 1;
    read(T);
    while (T--)
        work();
#ifdef FAST_OUT
    IO::OUTPUT::flush();
#endif
    return 0;
}