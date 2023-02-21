/**
 *    name:     #13428. 「20230221」图上旅行
 *    author:   whitepaperdog (蒟蒻wjr)
 *    located:  Changle District, Fuzhou City, Fujian Province, China
 *    created:  2023.02.21 周二 15:54:48 (Asia/Shanghai)
 *    unicode:  UTF-8
 *    standard: c++23
 **/
#include <algorithm>
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
using IO::INPUT::read;
using IO::OUTPUT::write;
using namespace std;
int n, k, mod;
namespace subtask1
{
    constexpr int N = 5e3 + 5;
    ll f[N], g[N];
    ll C[N][N];
    inline void main()
    {
        C[0][0] = 1;
        for (int i = 1; i <= n; ++i)
        {
            C[i][0] = 1;
            for (int j = 1; j <= i; ++j)
                C[i][j] = (C[i - 1][j] + C[i - 1][j - 1]) % mod;
        }
        f[1] = g[1] = 1;
        for (int i = 2; i <= n; ++i)
        {
            ll res = 0;
            for (int j = 0; j <= k; ++j)
                (res += C[i - 1][j]) %= mod;
            g[i] = g[i - 1] * res % mod;
            f[i] = g[i];
            for (int j = 1; j < i; ++j)
                (f[i] -= f[j] * g[i - j] % mod * C[i - 1][j - 1]) %= mod;
        }
        write((f[n] + mod) % mod, '\n');
    }
}
namespace subtask2
{
    inline void main()
    {
        ll res = 1;
        for (int i = 2; i < n; ++i)
            (res *= i) %= mod;
        write(res, '\n');
    }
}
namespace subtask3
{
    constexpr int N = 4e5 * 10 + 5;
    constexpr int mod = 924844033;
    typedef modint<mod> node;
    constexpr node g = 19260817;
    constexpr node invg = g.inv();
    int limit, len, rk[N];
    inline void init(int _n)
    {
        limit = 1, len = 0;
        while (limit <= _n)
        {
            limit <<= 1;
            ++len;
        }
        for (int i = 0; i < limit; ++i)
            rk[i] = (rk[i >> 1] >> 1) | ((i & 1) << (len - 1));
    }
    inline void NTT(node *dp)
    {
        for (int i = 0; i < limit; ++i)
            if (i < rk[i])
                swap(dp[i], dp[rk[i]]);
        for (int mid = 1; mid < limit; mid <<= 1)
        {
            node gn = g ^ ((mod - 1) / (mid << 1));
            for (int i = 0; i < limit; i += mid << 1)
            {
                node gg = 1;
                for (int j = 0; j < mid; ++j, gg *= gn)
                {
                    node x = dp[i + j], y = dp[i + j + mid] * gg;
                    dp[i + j] = x + y;
                    dp[i + j + mid] = x - y;
                }
            }
        }
    }
    inline void INTT(node *dp)
    {
        for (int i = 0; i < limit; ++i)
            if (i < rk[i])
                swap(dp[i], dp[rk[i]]);
        for (int mid = 1; mid < limit; mid <<= 1)
        {
            node gn = invg ^ ((mod - 1) / (mid << 1));
            for (int i = 0; i < limit; i += mid << 1)
            {
                node gg = 1;
                for (int j = 0; j < mid; ++j, gg *= gn)
                {
                    node x = dp[i + j], y = dp[i + j + mid] * gg;
                    dp[i + j] = x + y;
                    dp[i + j + mid] = x - y;
                }
            }
        }
        node inv = ((node)limit).inv();
        for (int i = 0; i < limit; ++i)
            dp[i] *= inv;
    }
    node fac[N], ifac[N];
    node dp[N];
    node A[N], B[N];
    node F[N], G[N];
    inline void solve(int _n)
    {
        if (_n == 1)
        {
            F[0] = A[0].inv();
            return;
        }
        solve((_n + 1) / 2);
        init(_n * 2);
        for (int i = 0; i < _n; ++i)
            G[i] = A[i];
        for (int i = _n; i < limit; ++i)
            G[i] = 0;
        NTT(F), NTT(G);
        for (int i = 0; i < limit; ++i)
            F[i] = (-F[i] * G[i] + 2) * F[i];
        INTT(F);
        for (int i = _n; i < limit; ++i)
            F[i] = 0;
    }
    inline node C(int _x, int _y)
    {
        if (_x < 0 || _x < _y)
            return 0;
        return fac[_x] * ifac[_y] * ifac[_x - _y];
    }
    node pre[N];
    inline void main()
    {
        fac[0] = 1;
        for (int i = 1; i <= n; ++i)
            fac[i] = fac[i - 1] * i;
        ifac[n] = fac[n].inv();
        for (int i = n; i >= 1; --i)
            ifac[i - 1] = ifac[i] * i;
        dp[0] = pre[0] = 1;
        for (int i = 1; i <= n; ++i)
        {
            pre[i] = pre[i - 1] * 2 - C(i - 1, k);
            dp[i] = dp[i - 1] * pre[i - 1];
        }
        dp[0] = 0;
        for (int i = 0; i <= n; ++i)
            A[i] = dp[i] * ifac[i];
        for (int i = 1; i <= n; ++i)
            B[i] = A[i] * i;
        ++A[0];
        solve(n + 1);
        init(n * 2);
        NTT(F), NTT(B);
        for (int i = 0; i < limit; ++i)
            A[i] = F[i] * B[i];
        INTT(A);
        write((A[n] * fac[n - 1]).data(), '\n');
    }
}
signed main()
{
#ifdef PAPERDOG
    freopen("project.in", "r", stdin);
    freopen("project.out", "w", stdout);
#else
    freopen("graph.in", "r", stdin);
    freopen("graph.out", "w", stdout);
#endif
    read(n, k, mod);
    if (n <= 5e3)
        subtask1::main();
    else if (k == 1)
        subtask2::main();
    else
        subtask3::main();
#ifdef FAST_OUT
    IO::OUTPUT::flush();
#endif
    return 0;
}