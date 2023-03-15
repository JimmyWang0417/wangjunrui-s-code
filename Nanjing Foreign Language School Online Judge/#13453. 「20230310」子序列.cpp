/**
 *    name:     C. 子序列
 *    author:   whitepaperdog (蒟蒻wjr)
 *    located:  Xuanwu District, Nanjing City, Jiangsu Province, China
 *    created:  2023.03.10 周五 13:57:54 (Asia/Shanghai)
 *    unicode:  UTF-8
 *    standard: c++23
 **/
#include <algorithm>
#include <cstdio>
#include <iostream>
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
constexpr int N = 2e5 + 5;
constexpr ll limit = (ll)1e18 + 114514;
int n, q;
int a[N], b[N];
struct Tree
{
    int l, r;
    int pos, val;
    ll size;
} tree[N * 100];
#define lc(rt) tree[rt].l
#define rc(rt) tree[rt].r
int root[N], cnt;
ll dp[N];
inline void pushup(int rt)
{
    if (!lc(rt) || !rc(rt))
    {
        tree[rt].size = tree[lc(rt) | rc(rt)].size;
        tree[rt].pos = tree[lc(rt) | rc(rt)].pos;
        tree[rt].val = tree[lc(rt) | rc(rt)].val;
        return;
    }
    tree[rt].size = min(tree[lc(rt)].size + tree[rc(rt)].size, limit);
    if (dp[tree[lc(rt)].val] >= dp[tree[rc(rt)].val])
    {
        tree[rt].pos = tree[lc(rt)].pos;
        tree[rt].val = tree[lc(rt)].val;
    }
    else
    {
        tree[rt].pos = tree[rc(rt)].pos;
        tree[rt].val = tree[rc(rt)].val;
    }
}
inline void update(int pre, int &rt, int l, int r, int pos, int val)
{
    rt = ++cnt;
    tree[rt] = tree[pre];
    if (l == r)
    {
        if (!tree[rt].val || tree[rt].val > val)
        {
            tree[rt].pos = l;
            tree[rt].size = min(dp[tree[rt].val = val] + 1, limit);
        }
        return;
    }
    int mid = (l + r) >> 1;
    if (pos <= mid)
        update(lc(pre), lc(rt), l, mid, pos, val);
    else
        update(rc(pre), rc(rt), mid + 1, r, pos, val);
    pushup(rt);
}
inline pair<int, int> query(int rt, int l, int r, ll &k_th)
{
    if (l == r)
        return make_pair(tree[rt].val, l);
    int mid = (l + r) >> 1;
    if (tree[lc(rt)].size >= k_th)
        return query(lc(rt), l, mid, k_th);
    else
        return query(rc(rt), mid + 1, r, k_th -= tree[lc(rt)].size);
}
inline ll query(int rt, int l, int r, int x, int y)
{
    if (r < x || l > y)
        return 0;
    if (x <= l && r <= y)
        return tree[rt].size;
    int mid = (l + r) >> 1;
    return min(query(lc(rt), l, mid, x, y) + query(rc(rt), mid + 1, r, x, y), limit);
}
int fa[N][20];
ll f[N][20], g[N][20];
inline void work()
{
    // int cnt = 0;
    ll k;
    read(k);
    int u = 1;
    ll res = 0;
    while (true)
    {
        for (int i = 19; i >= 0; --i)
            if (fa[u][i] && f[u][i] < k && k <= dp[fa[u][i]] + f[u][i])
            {
                k -= f[u][i];
                res += g[u][i];
                u = fa[u][i];
            }
        auto [v, w] = query(root[u], 1, n, k);
        // printf("%d %d\n", u, v);
        res += w;
        if (!--k)
            break;
        u = v;
        // ++cnt;
    }
    write(res, '\n');
}
signed main()
{
#ifdef PAPERDOG
    freopen("project.in", "r", stdin);
    freopen("project.out", "w", stdout);
#else
    freopen("subsequence.in", "r", stdin);
    freopen("subsequence.out", "w", stdout);
#endif
    read(n, q);
    for (int i = 1; i <= n; ++i)
        read(a[i]);
    for (int i = 1; i <= n; ++i)
        read(b[i]);
    for (int i = n; i >= 1; --i)
    {
        update(root[i + 1], root[i], 1, n, a[i], b[i] + 1);
        dp[i] = tree[root[i]].size;
        fa[i][0] = tree[root[i]].val;
        f[i][0] = min(query(root[i], 1, n, 1, tree[root[i]].pos - 1) + 1, limit);
        g[i][0] = tree[root[i]].pos;
        for (int j = 0; j < 19; ++j)
        {
            fa[i][j + 1] = fa[fa[i][j]][j];
            f[i][j + 1] = min(f[i][j] + f[fa[i][j]][j], limit);
            g[i][j + 1] = g[i][j] + g[fa[i][j]][j];
        }
    }
    // printf("%d\n", cnt);
    // for (int i = 1; i <= n; ++i)
    //     write(dp[i], ' ');
    // write('\n');
    // for (int i = 1; i <= n; ++i)
    //     write(fa[i][0], ' ');
    // write('\n');
    // for (int i = 1; i <= n; ++i)
    //     write(f[i][0], ' ');
    // write('\n');
    // for (int i = 1; i <= n; ++i)
    //     write(g[i][0], ' ');
    // write('\n');
    while (q--)
        work();
#ifdef FAST_OUT
    IO::OUTPUT::flush();
#endif
    return 0;
}