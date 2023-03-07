/**
 *    name:     P7448 [Ynoi2007] rdiq
 *    author:   whitepaperdog (蒟蒻wjr)
 *    located:  Xuanwu District, Nanjing City, Jiangsu Province, China
 *    created:  2023.03.06 周一 16:52:53 (Asia/Shanghai)
 *    unicode:  UTF-8
 *    standard: c++23
 **/
#include <algorithm>
#include <cstdio>
#include <cstring>
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
constexpr int N = 1e5 + 5;
int n, m, a[N];
struct
{
    int l, r, id;
} q[N * 5];
int belong[N], block;
int belong1[N], block1;
int belong2[N], block2;
int L1[N], L2[N];
vector<tuple<int, int, int>> g[N], h[N];
ll answer[N * 5];
int c1[31][31], c2[401][31], c3[31][401], c4[401][401], c5[N];
#define ws _ws
int b[N], c[N], ws[N];
int prv[N], nxt[N];
int mp[N];
inline void add(int x)
{
    int y = b[x];
    for (int i = 1; i < belong2[x]; ++i)
        for (int j = 1; j < belong2[y]; ++j)
            ++c1[i][j];
    for (int i = L2[belong2[x]]; i < belong1[x]; ++i)
        for (int j = 1; j < belong2[y]; ++j)
            ++c2[i][j];
    for (int i = 1; i < belong2[x]; ++i)
        for (int j = L2[belong2[y]]; j < belong1[y]; ++j)
            ++c3[i][j];
    for (int i = L2[belong2[x]]; i < belong1[x]; ++i)
        for (int j = L2[belong2[y]]; j < belong1[y]; ++j)
            ++c4[i][j];
    for (int i = L1[belong1[x]]; i < x; ++i)
        if (b[i] < L1[belong1[y]])
            ++c5[i];
    for (int i = L1[belong1[y]]; i < y; ++i)
        if (c[i] < x)
            ++c5[c[i]];
}
inline void del(int x)
{
    int y = b[x];
    for (int i = 1; i < belong2[x]; ++i)
        for (int j = 1; j < belong2[y]; ++j)
            --c1[i][j];
    for (int i = L2[belong2[x]]; i < belong1[x]; ++i)
        for (int j = 1; j < belong2[y]; ++j)
            --c2[i][j];
    for (int i = 1; i < belong2[x]; ++i)
        for (int j = L2[belong2[y]]; j < belong1[y]; ++j)
            --c3[i][j];
    for (int i = L2[belong2[x]]; i < belong1[x]; ++i)
        for (int j = L2[belong2[y]]; j < belong1[y]; ++j)
            --c4[i][j];
    for (int i = L1[belong1[x]]; i < x; ++i)
        if (b[i] < L1[belong1[y]])
            --c5[i];
    for (int i = L1[belong1[y]]; i < y; ++i)
        if (c[i] < x)
            --c5[c[i]];
}
inline int query(int x)
{
    int y = b[x], _a = belong2[x], _b = belong1[x], _c = belong2[y], _d = belong1[y];
    return c1[_a][_c] + c2[_b][_c] + c3[_a][_d] + c4[_b][_d] + c5[x];
}
inline void solve(vector<tuple<int, int, int>> *dp)
{
    for (int i = 1; i <= n; ++i)
        ++ws[a[i]];
    for (int i = 2; i <= n; ++i)
        ws[i] += ws[i - 1];
    for (int i = 1; i <= n; ++i)
        c[b[i] = ws[a[i]]--] = i;
    memset(ws, 0, sizeof(ws));
    for (int i = 1; i <= n; ++i)
    {
        prv[i] = mp[a[i]];
        mp[a[i]] = i;
    }
    memset(mp, 0, sizeof(mp));
    for (int i = n; i >= 1; --i)
    {
        nxt[i] = mp[a[i]];
        mp[a[i]] = i;
    }
    memset(mp, 0, sizeof(mp));
    for (int i = 1; i <= n; ++i)
    {
        add(i);
        if (prv[i])
            del(prv[i]);
        for (auto [l, r, id] : dp[i])
        {
            int res = 0;
            for (int j = l; j <= r; ++j)
            {
                if (nxt[j] < i && nxt[j])
                    res -= query(nxt[j]);
                res += query(j);
            }
            if (id > 0)
                answer[id] += res;
            else 
                answer[-id] -= res;
        }
    }
    memset(c1, 0, sizeof(c1));
    memset(c2, 0, sizeof(c2));
    memset(c3, 0, sizeof(c3));
    memset(c4, 0, sizeof(c4));
    memset(c5, 0, sizeof(c5));
}
signed main()
{
#ifdef PAPERDOG
    freopen("project.in", "r", stdin);
    freopen("project.out", "w", stdout);
#endif
    read(n);
    for (int i = 1; i <= n; ++i)
        read(a[i]);
    read(m);
    for (int i = 1; i <= m; ++i)
    {
        read(q[i].l, q[i].r);
        q[i].id = i;
    }
    block = (int)(n / (int)__builtin_sqrt(m));
    int qwq = (int)__builtin_pow(n, 0.25) + 1;
    block1 = qwq * qwq;
    block2 = qwq * qwq * qwq;
    for (int i = 1; i <= n; ++i)
    {
        belong[i] = (i - 1) / block + 1;
        belong1[i] = (i - 1) / block1 + 1;
        belong2[i] = (i - 1) / block2 + 1;
    }
    for (int i = n; i >= 1; --i)
        L1[L2[belong2[i]] = belong1[i]] = i;
    sort(q + 1, q + 1 + m, [](auto x, auto y)
         { return belong[x.l] == belong[y.l] ? (belong[x.l] & 1 ? x.r < y.r : x.r > y.r) : x.l < y.l; });
    int l = 1, r = 0;
    for (int i = 1; i <= m; ++i)
    {
        if (r < q[i].r)
        {
            g[n + 1 - l].emplace_back(n + 1 - q[i].r, n - r, q[i].id);
            r = q[i].r;
        }
        if (l > q[i].l)
        {
            h[r].emplace_back(q[i].l, l - 1, q[i].id);
            l = q[i].l;
        }
        if (r > q[i].r)
        {
            g[n + 1 - l].emplace_back(n + 1 - r, n - q[i].r, -q[i].id);
            r = q[i].r;
        }
        if (l < q[i].l)
        {
            h[r].emplace_back(l, q[i].l - 1, -q[i].id);
            l = q[i].l;
        }
    }

    for (int i = 1; i <= n; ++i)
        a[i] = n + 1 - a[i];
    solve(h);

    for (int i = 1; i <= n; ++i)
        a[i] = n + 1 - a[i];
    reverse(a + 1, a + 1 + n);
    solve(g);

    for (int i = 2; i <= m; ++i)
        answer[q[i].id] += answer[q[i - 1].id];
    for (int i = 1; i <= m; ++i)
        write(answer[i], '\n');
#ifdef FAST_OUT
    IO::OUTPUT::flush();
#endif
    return 0;
}