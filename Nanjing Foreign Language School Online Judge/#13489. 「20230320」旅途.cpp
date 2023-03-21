/**
 *    name:     B. 旅途
 *    author:   whitepaperdog (蒟蒻wjr)
 *    located:  Xuanwu District, Nanjing City, Jiangsu Province, China
 *    created:  2023.03.20 周一 16:54:24 (Asia/Shanghai)
 *    unicode:  UTF-8
 *    standard: c++23
 **/
#include <bits/move.h>
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
using IO::INPUT::read;
using IO::OUTPUT::write;
using namespace std;
constexpr int N = 305;
int n, v, mod, a[N];
struct modint
{
    int x;
    modint(int _x = 0) : x(_x) {}
    inline modint operator+() const
    {
        return *this;
    }
    inline modint operator-() const
    {
        return !x ? 0 : mod - x;
    }
    inline modint &operator++()
    {
        ++x;
        if (x >= mod)
            x -= mod;
        return *this;
    }
    inline modint &operator--()
    {
        --x;
        if (x < 0)
            x += mod;
        return *this;
    }
    inline modint operator++(int)
    {
        int res = x;
        if (x >= mod)
            x -= mod;
        return res;
    }
    inline modint operator--(int)
    {
        int res = x;
        if (x < 0)
            x += mod;
        return res;
    }
    inline modint operator+(const modint &rhs) const
    {
        int res = x;
        res += rhs.x;
        if (res >= mod)
            res -= mod;
        return res;
    }
    inline modint operator-(const modint &rhs) const
    {
        int res = x;
        res -= rhs.x;
        if (res < 0)
            res += mod;
        return res;
    }
    inline modint operator*(const modint &rhs) const
    {
        return (int)((ll)x * rhs.x % mod);
    }
    inline modint &operator+=(const modint &rhs)
    {
        x += rhs.x;
        if (x >= mod)
            x -= mod;
        return *this;
    }
    inline modint &operator-=(const modint &rhs)
    {
        x -= rhs.x;
        if (x < 0)
            x += mod;
        return *this;
    }
    inline modint &operator*=(const modint &rhs)
    {
        x = (int)((ll)x * rhs.x % mod);
        return *this;
    }
    template <typename _G>
    inline modint operator^(_G rhs) const
    {
        modint _a = x, res = 1;
        while (rhs)
        {
            if (rhs & 1)
                res *= _a;
            _a *= _a;
            rhs >>= 1;
        }
        return res;
    }
    inline modint inv() const
    {
        return *this ^ (mod - 2);
    }
    inline modint operator/(const modint &rhs) const
    {
        return (*this) * rhs.inv();
    }
    inline modint &operator/=(const modint &rhs)
    {
        return (*this) *= rhs.inv();
    }
    inline bool operator==(const modint &rhs) const
    {
        return x == rhs.x;
    }
    inline bool operator!=(const modint &rhs) const
    {
        return x != rhs.x;
    }
    inline int &data()
    {
        return x;
    }
};
modint fac[N], ifac[N];
int tot;
modint buf[2][N];
auto F = buf[0], G = buf[1];
namespace SOLVE
{
    modint pre[N], suf[N];
    inline modint solve(modint x)
    {
        pre[0] = 1;
        for (int i = 1; i <= tot; ++i)
            pre[i] = pre[i - 1] * (x - i);
        suf[tot + 1] = 1;
        for (int i = tot; i >= 1; --i)
            suf[i] = suf[i + 1] * (x - i);
        modint ans = 0;
        for (int i = 1; i <= tot; ++i)
        {
            auto times = ifac[i - 1] * ifac[tot - i] * pre[i - 1] * suf[i + 1];
            if ((tot - i) & 1)
                times = -times;
            ans += times * G[i];
        }
        return ans;
    }
}
using SOLVE::solve;
signed main()
{
#ifdef PAPERDOG
    freopen("project.in", "r", stdin);
    freopen("project.out", "w", stdout);
#else
    freopen("tour.in", "r", stdin);
    freopen("tour.out", "w", stdout);
#endif
    read(n, v, mod);
    fac[0] = 1;
    for (int i = 1; i <= n; ++i)
        fac[i] = fac[i - 1] * i;
    ifac[n] = fac[n].inv();
    for (int i = n; i >= 1; --i)
        ifac[i - 1] = ifac[i] * i;
    for (int i = 1; i <= n; ++i)
        read(a[i]);
    tot = 2;
    F[1] = 1, F[2] = 2;
    for (int i = 2; i <= n; ++i)
    {
        swap(F, G);
        for (int j = 1; j <= i + 1; ++j)
            F[j] = F[j - 1] + solve((int)((ll)a[i] * j % mod));
        ++tot;
    }
    swap(F, G);
    write(solve(v).data(), '\n');
#ifdef FAST_OUT
    IO::OUTPUT::flush();
#endif
    return 0;
}