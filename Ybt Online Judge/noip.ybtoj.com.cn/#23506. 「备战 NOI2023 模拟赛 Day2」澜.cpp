/**
 *    name:     C. 澜
 *    author:   whitepaperdog (蒟蒻wjr)
 *    located:  Xuanwu District, Nanjing City, Jiangsu Province, China
 *    created:  2023.03.05 周日 22:26:11 (Asia/Shanghai)
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
constexpr int N = 2e5 + 5;
constexpr int mod = 19260817;
int n, a[N], b[N], c[N];
struct Tree
{
    int l, r;
    int size;
} tree[N * 40];
#define lc(rt) tree[rt].l

#define rc(rt) tree[rt].r

int root[N], cnt;
inline void update(int pre, int &rt, int l, int r, int pos)
{
    tree[rt = ++cnt] = tree[pre];
    ++tree[rt].size;
    if (l == r)
        return;
    int mid = (l + r) >> 1;
    if (pos <= mid)
        update(lc(pre), lc(rt), l, mid, pos);
    else
        update(rc(pre), rc(rt), mid + 1, r, pos);
}
inline int query(int rt, int l, int r, int x, int y)
{
    if (r < x || l > y)
        return 0;
    if (x <= l && r <= y)
        return tree[rt].size;
    int mid = (l + r) >> 1;
    return query(lc(rt), l, mid, x, y) + query(rc(rt), mid + 1, r, x, y);
}
struct
{
    int tree[N];
    inline void update(int pos)
    {
        for (int i = pos; i; i -= lowbit(i))
            ++tree[i];
    }
    inline int query(int pos)
    {
        int res = 0;
        for (int i = pos; i <= n; i += lowbit(i))
            res += tree[i];
        return res;
    }
} index;
struct
{
    int next;
    ll key;
    int val;
} edge[N];
int head[mod + 5], num_edge;
inline int update(ll key, int val)
{
    int from = (int)(key % mod);
    for (int i = head[from]; i; i = edge[i].next)
        if (edge[i].key == key)
        {
            int res = edge[i].val;
            edge[i].val = val;
            return res;
        }
    edge[++num_edge].next = head[from];
    edge[num_edge].key = key;
    edge[num_edge].val = val;
    head[from] = num_edge;
    return 0;
}
int L[N];
int f[N], g[N];
struct
{
    int dp[25][N];
    int log[N];
    inline void init()
    {
        log[0] = -1;
        for (int i = 1; i <= n; ++i)
        {
            dp[0][i] = a[i];
            log[i] = log[i >> 1] + 1;
        }
        for (int j = 0; j < log[n]; ++j)
            for (int i = 1; i + (2 << j) - 1 <= n; ++i)
                dp[j + 1][i] = max(dp[j][i], dp[j][i + (1 << j)]);
    }
    inline int query(int l, int r)
    {
        int k = log[r - l + 1];
        return max(dp[k][l], dp[k][r - (1 << k) + 1]);
    }
} sparse_table;
int p[N], tot;
signed main()
{
#ifdef PAPERDOG
    freopen("project.in", "r", stdin);
    freopen("project.out", "w", stdout);
#else
    freopen("lan.in", "r", stdin);
    freopen("lan.out", "w", stdout);
#endif
    read(n);
    update(0, 1);
    ll sum = 0;
    for (int i = 1; i <= n; ++i)
    {
        read(a[i]);
        update(root[i - 1], root[i], 1, n, a[i]);
        b[i] = b[i - 1] + index.query(a[i] + 1);
        index.update(a[i]);
        L[i] = update(sum += a[i] - i, i + 1);
        c[a[i]] = i;
    }
    sparse_table.init();
    for (int i = 1; i <= n; ++i)
    {
        g[i] = g[i - 1];
        if (L[i])
        {
            int l = L[i], r = i;
            ll res = b[r] - b[l - 1];
            res -= (ll)(r - l + 1) * query(root[l - 1], 1, n, r, n);
            if (res == r - l && sparse_table.query(l, r) == r)
            {
                f[i] = f[g[l - 1]] + 1;
                if (f[g[i - 1]] < f[i])
                    g[i] = i;
            }
        }
    }
    int r = g[n];
    while (r)
    {
        int l = L[r];
        for (int i = r; i >= l; --i)
        {
            int x = c[i];
            for (int j = x; j < i; ++j)
            {
                swap(a[j], a[j + 1]);
                p[++tot] = j;
                c[a[j]] = j;
                c[a[j + 1]] = j + 1;
            }
        }
        r = g[l - 1];
    }
    write(tot, '\n');
    for (int i = 1; i <= tot; ++i)
        write(p[i], ' ');
    write('\n');
#ifdef FAST_OUT
    IO::OUTPUT::flush();
#endif
    return 0;
}