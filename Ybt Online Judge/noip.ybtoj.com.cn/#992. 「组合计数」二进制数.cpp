/**
 *    name:     B. 二进制数
 *    author:   whitepaperdog (蒟蒻wjr)
 *    located:  Changle District, Fuzhou City, Fujian Province, China
 *    created:  2023.02.10 周五 10:40:15 (Asia/Shanghai)
 *    unicode:  UTF-8
 *    standard: c++23
 **/
#include <cstdio>
#include <cstring>
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
constexpr int mod = 1e9 + 7;
typedef modint<mod> node;
char A[N], B[N];
int lenA, lenB;
node fac[N], ifac[N];
inline node C(int _x, int _y)
{
    if (_x < _y || _y < 0)
        return 0;
    return fac[_x] * ifac[_y] * ifac[_x - _y];
}
inline node dfs(int pos, int a, int b, int c, int d, bool before, bool limit, bool zero, char *str, int ed)
{
    if (pos == ed)
        return a == 0 && b == 0 && c == 0 && d == 0;
    if (a < 0 || b < 0 || c < 0 || d < 0)
        return 0;
    if (!limit && !zero)
    {
        node res = 0;
        int other = ed - pos;
        if (!before)
            --b;
        else
            --d;
        if ((other - a - d) & 1)
        {
            int x = (other - a - d) / 2 + a, y = other - x;
            auto now = C(x - 1, x - 1 - a) * C(y - 1, y - 1 - d);
            if (x - a == b && x - a == c)
                res += now;
        }
        else
        {
            int x = (other - a - d) / 2 + a, y = other - x;
            auto now = C(x - 1, x - 1 - a) * C(y - 1, y - 1 - d);
            if (x - a - 1 == b && x - a == c)
                res += now;
        }
        if (!a && !b && !c && other == d + 1)
            ++res;
        if (!before)
            ++b;
        else
            ++d;
        if (!before)
            --a;
        else
            --c;
        if ((other - a - d) & 1)
        {
            int x = (other - a - d + 1) / 2 + a, y = other - x;
            auto now = C(x - 1, x - 1 - a) * C(y - 1, y - 1 - d);
            if (y - d == b && y - d == c)
                res += now;
        }
        else
        {
            int x = (other - a - d + 1) / 2 + a, y = other - x;
            auto now = C(x - 1, x - 1 - a) * C(y - 1, y - 1 - d);
            if (x - a == b && x - a - 1 == c)
                res += now;
        }
        if (!b && !c && !d && other == a + 1)
            ++res;
        if (!before)
            ++a;
        else
            ++c;
        return res; 
    }
    node res = 0;
    int maxx = limit ? str[pos] - '0' : 1;
    for (int i = maxx; i >= 0; --i)
    {
        int _a = a, _b = b, _c = c, _d = d;
        if (!zero)
        {
            if (!before)
            {
                if (!i)
                    --_a;
                else
                    --_b;
            }
            else
            {
                if (!i)
                    --_c;
                else
                    --_d;
            }
        }
        res += dfs(pos + 1, _a, _b, _c, _d, i, limit && i == maxx, zero && i == 0, str, ed);
    }
    return res;
}
inline bool check(char *str, int ed, int a, int b, int c, int d)
{
    for (int i = 1; i < ed; ++i)
    {
        int u = str[i - 1] - '0', v = str[i] - '1';
        if (!u)
        {
            if (!v)
                --a;
            else
                --b;
        }
        else
        {
            if (!v)
                --c;
            else
                --d;
        }
    }
    return a == 0 && b == 0 && c == 0 && d == 0;
}
signed main()
{
#ifdef PAPERDOG
    freopen("project.in", "r", stdin);
    freopen("project.out", "w", stdout);
#else
    freopen("binary.in", "r", stdin);
    freopen("binary.out", "w", stdout);
#endif
    int a, b, c, d;
    read(A, B);
    read(a, b, c, d);
    lenA = (int)strlen(A);
    lenB = (int)strlen(B);
    fac[0] = 1;
    for (int i = 1; i <= lenB; ++i)
        fac[i] = fac[i - 1] * i;
    ifac[lenB] = fac[lenB].inv();
    for (int i = lenB; i >= 1; --i)
        ifac[i - 1] = ifac[i] * i;
    write((dfs(0, a, b, c, d, false, true, true, B, lenB) -
           dfs(0, a, b, c, d, false, true, true, A, lenA) +
           check(A, lenA, a, b, c, d))
              .data(),
          '\n');
#ifdef FAST_OUT
    IO::OUTPUT::flush();
#endif
    return 0;
}