/**
 *    name:     A. 屑题
 *    author:   whitepaperdog (蒟蒻wjr)
 *    located:  Xuanwu District, Nanjing City, Jiangsu Province, China
 *    created:  2023.03.24 周五 08:07:54 (Asia/Shanghai)
 *    unicode:  UTF-8
 *    standard: c++23
 **/
#include <cstdio>
#include <vector>
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
namespace MODINT
{
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
}
using IO::INPUT::read;
using IO::OUTPUT::write;
using namespace std;
constexpr int N = 1e5 + 5;
constexpr int mod = 1e9 + 7;
typedef MODINT::modint<mod> modint;
int n, k, m;
modint C[15][15];
struct node
{
    modint a[15];
    inline node operator+(const node &rhs) const
    {
        node res;
        for (int i = 0; i <= k; ++i)
            res.a[i] = a[i] + rhs.a[i];
        return res;
    }
    inline node operator-(const node &rhs) const
    {
        node res;
        for (int i = 0; i <= k; ++i)
            res.a[i] = a[i] - rhs.a[i];
        return res;
    }
};
struct Tree
{
    int l, r;
    node L, R;
    modint len;
    int size;
} tree[N * 50];
#define lc(rt) tree[rt].l
#define rc(rt) tree[rt].r
vector<int> g[N];
int root[N], cnt;
inline void pushup(int rt)
{
    tree[rt].L = tree[lc(rt)].L + tree[rc(rt)].L;
    tree[rt].R = tree[lc(rt)].R + tree[rc(rt)].R;
    tree[rt].len = tree[lc(rt)].len + tree[rc(rt)].len;
    tree[rt].size = tree[lc(rt)].size + tree[rc(rt)].size;
}
inline void update(int &rt, int l, int r, int L, int pos, int val)
{
    tree[++cnt] = tree[rt];
    rt = cnt;
    if (l == r)
    {
        modint times = 1;
        for (int i = 0; i <= k; ++i, times *= mod - L)
            tree[rt].L.a[i] += times;
        times = 1;
        for (int i = 0; i <= k; ++i, times *= pos)
            tree[rt].R.a[i] += times;
        times = 1;
        for (int i = 1; i <= k; ++i)
            times *= val;
        tree[rt].len += times;
        ++tree[rt].size;
        return;
    }
    int mid = (l + r) >> 1;
    if (pos <= mid)
        update(lc(rt), l, mid, L, pos, val);
    else
        update(rc(rt), mid + 1, r, L, pos, val);
    pushup(rt);
}
inline node queryL(int rootl, int rootr, int l, int r, int x, int y)
{
    if (x <= l && r <= y)
        return tree[rootr].L - tree[rootl].L;
    int mid = (l + r) >> 1;
    if (y <= mid)
        return queryL(lc(rootl), lc(rootr), l, mid, x, y);
    if (x > mid)
        return queryL(rc(rootl), rc(rootr), mid + 1, r, x, y);
    return queryL(lc(rootl), lc(rootr), l, mid, x, y) + queryL(rc(rootl), rc(rootr), mid + 1, r, x, y);
}
inline node queryR(int rootl, int rootr, int l, int r, int x, int y)
{
    if (x <= l && r <= y)
        return tree[rootr].R - tree[rootl].R;
    int mid = (l + r) >> 1;
    if (y <= mid)
        return queryR(lc(rootl), lc(rootr), l, mid, x, y);
    if (x > mid)
        return queryR(rc(rootl), rc(rootr), mid + 1, r, x, y);
    return queryR(lc(rootl), lc(rootr), l, mid, x, y) + queryR(rc(rootl), rc(rootr), mid + 1, r, x, y);
}
inline modint querylen(int rootl, int rootr, int l, int r, int x, int y)
{
    if (x <= l && r <= y)
        return tree[rootr].len - tree[rootl].len;
    int mid = (l + r) >> 1;
    if (y <= mid)
        return querylen(lc(rootl), lc(rootr), l, mid, x, y);
    if (x > mid)
        return querylen(rc(rootl), rc(rootr), mid + 1, r, x, y);
    return querylen(lc(rootl), lc(rootr), l, mid, x, y) + querylen(rc(rootl), rc(rootr), mid + 1, r, x, y);
}
inline int querysize(int rootl, int rootr, int l, int r, int x, int y)
{
    if (x <= l && r <= y)
        return tree[rootr].size - tree[rootl].size;
    int mid = (l + r) >> 1;
    if (y <= mid)
        return querysize(lc(rootl), lc(rootr), l, mid, x, y);
    if (x > mid)
        return querysize(rc(rootl), rc(rootr), mid + 1, r, x, y);
    return querysize(lc(rootl), lc(rootr), l, mid, x, y) + querysize(rc(rootl), rc(rootr), mid + 1, r, x, y);
}
signed main()
{
#ifdef PAPERDOG
    freopen("project.in", "r", stdin);
    freopen("project.out", "w", stdout);
#else
    freopen("trash.in", "r", stdin);
    freopen("trash.out", "w", stdout);
#endif
    read(n, k, m);
    for (int i = 1; i <= n; ++i)
    {
        int l, r;
        read(l, r);
        g[l].push_back(r);
    }
    C[0][0] = 1;
    for (int i = 1; i <= k; ++i)
    {
        C[i][0] = 1;
        for (int j = 1; j <= i; ++j)
            C[i][j] = C[i - 1][j] + C[i - 1][j - 1];
    }
    for (int i = 1; i <= n; ++i)
    {
        root[i] = root[i - 1];
        for (int j : g[i])
            update(root[i], 1, n, i, j, j - i + 1);
    }
    for (int kase = 1; kase <= m; ++kase)
    {
        int l, r;
        read(l, r);
        modint ans = 0;
        auto res = queryR(root[0], root[l], 1, n, l, r);
        modint times = 1;
        for (int i = 0; i <= k; ++i, times *= mod - (l - 1))
            ans += C[k][i] * times * res.a[k - i];
        ans += querylen(root[l], root[r], 1, n, l, r);
        if (r < n)
        {
            times = 1;
            for (int i = 0; i < k; ++i)
                times *= r - l + 1;
            ans += times * querysize(root[0], root[l], 1, n, r + 1, n);
            res = queryL(root[l], root[r], 1, n, r + 1, n);
            times = 1;
            for (int i = 0; i <= k; ++i, times *= r + 1)
                ans += C[k][i] * times * res.a[k - i];
        }
        write(ans.data(), '\n');
    }
#ifdef FAST_OUT
    IO::OUTPUT::flush();
#endif
    return 0;
}