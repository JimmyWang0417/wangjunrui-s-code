/**
 *    name:     CF1474F 1 2 3 4 ...
 *    author:   whitepaperdog (蒟蒻wjr)
 *    located:  Xuanwu District, Nanjing City, Jiangsu Province, China
 *    created:  2023.03.04 周六 18:01:32 (Asia/Shanghai)
 *    unicode:  UTF-8
 *    standard: c++23
 **/
#include <algorithm>
#include <cstdio>
#include <cstring>
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
constexpr int N = 55;
constexpr int mod = 998244353;
typedef modint<mod> node;
int n, m;
ll a[N];
ll p[N * 6], L[N], R[N];
int tot;
struct matrix
{
    node g[N][N];
    matrix() { memset(g, 0, sizeof(g)); }
    inline void clear()
    {
        memset(g, 0, sizeof(g));
    }
    inline auto operator[](int x)
    {
        return g[x];
    }
    inline auto operator[](int x) const
    {
        return g[x];
    }
    inline matrix operator*(const matrix &rhs) const
    {
        matrix res;
        for (int i = 0; i <= m; ++i)
            for (int k = 0; k <= m; ++k)
                for (int j = 0; j <= m; ++j)
                    res[i][j] += g[i][k] * rhs[k][j];
        return res;
    }
    template <typename T>
    inline matrix operator^(T power) const
    {
        matrix res, base = (*this);
        for (int i = 0; i <= m; ++i)
            res[i][i] = 1;
        while (power)
        {
            if (power & 1)
                res = res * base;
            base = base * base;
            power >>= 1;
        }
        return res;
    }
} A, B;
inline node solve(int l, int r, ll ans)
{
    ll sum = 0;
    m = 0;
    for (int i = l; i <= r; ++i)
    {
        ++m;
        if (a[i] > 0)
            L[m] = sum + 1;
        else
            L[m] = sum - 1;
        R[m] = (sum += a[i]);
        p[++tot] = L[m] - 1, p[++tot] = L[m], p[++tot] = L[m] + 1;
        p[++tot] = R[m] - 1, p[++tot] = R[m], p[++tot] = R[m] + 1;
    }
    L[1] = 0;
    sort(p + 1, p + 1 + tot);
    tot = (int)(unique(p + 1, p + 1 + tot) - p - 1);
    A[0][0] = 1;
    p[0] = -1;
    for (int i = 1; i <= tot && p[i] <= ans; ++i)
    {
        for (int j = 1; j <= m; j++)
            if (min(L[j], R[j]) <= p[i - 1] + 1 && max(L[j], R[j]) >= p[i])
            {
                for (int k = 0; k < j; k++)
                    B[k][j] = 1;
                if (L[j] < R[j])
                    B[j][j] = 1;
            }
        A = A * (B ^ (p[i] - p[i - 1]));
        B.clear();
    }
    node res = 0;
    for (int i = 0; i <= m; ++i)
        res += A[0][i];
    A.clear();
    return res;
}
signed main()
{
    read(n, m);
    for (int i = 1; i <= n; ++i)
    {
        read(a[i]);
        if (!a[i])
            --i, --n;
        if (i > 1 && (a[i - 1] < 0) == (a[i] < 0))
        {
            a[i - 1] += a[i];
            --i, --n;
        }
    }
    ll ans = 0;
    for (int i = 1; i <= n; ++i)
    {
        ll sum = a[i];
        for (int j = i; j <= n; sum += a[++j])
            ckmax(ans, sum);
    }
    if (!ans)
        write(ans + 1, ' ', (-a[1] + 1) % mod, '\n');
    else
    {
        node res = 0;
        for (int i = 1; i <= n; ++i)
        {
            int r = 0;
            ll sum = a[i];
            for (int j = i; j <= n; sum += a[++j])
                if (sum == ans)
                    r = j;
            if (i <= r)
            {
                res += solve(i, r, ans);
                i = r;
            }
        }
        write(ans + 1, ' ', res.data(), '\n');
    }
#ifdef FAST_OUT
    IO::OUTPUT::flush();
#endif
    return 0;
}