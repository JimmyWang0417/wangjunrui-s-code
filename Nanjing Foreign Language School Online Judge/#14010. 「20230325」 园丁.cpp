/**
 *    name:     B. 园丁
 *    author:   whitepaperdog (蒟蒻wjr)
 *    located:  Xuanwu District, Nanjing City, Jiangsu Province, China
 *    created:  2023.03.26 周日 18:51:05 (Asia/Shanghai)
 *    unicode:  UTF-8
 *    standard: c++23
 **/
#include <algorithm>
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
constexpr int N = 1e6 + 5;
constexpr int INF = 0x3f3f3f3f;
int n;
struct node
{
    int l, r, id;
    inline bool operator<(const node &rhs) const
    {
        return l == rhs.l ? r > rhs.r : l < rhs.l;
    }
} a[N];
int p[N * 2], tot;
struct Tree
{
    int minn, minpos;

    int L, R;

    int ar, minr;
    bool exist;

    int lazy;

    inline void update(int val)
    {
        minn += val;
        lazy += val;
    }
} tree[N * 4];
#define lc (rt << 1)
#define rc (rt << 1 | 1)
inline void pushup(int rt)
{
    if (tree[lc].minn == tree[rc].minn ? a[tree[lc].minpos].id < a[tree[rc].minpos].id : tree[lc].minn < tree[rc].minn)
    {
        tree[rt].minn = tree[lc].minn;
        tree[rt].minpos = tree[lc].minpos;
    }
    else
    {
        tree[rt].minn = tree[rc].minn;
        tree[rt].minpos = tree[rc].minpos;
    }
    tree[rt].L = min(tree[lc].L, tree[rc].L);
    tree[rt].R = max(tree[lc].R, tree[rc].R);
    tree[rt].minr = min(tree[lc].minr, tree[rc].minr);
    tree[rt].exist = false, tree[rt].ar = INF;
    if (tree[rc].exist)
    {
        tree[rt].exist = true;
        tree[rt].ar = tree[rc].ar;
    }
    if (tree[lc].exist && tree[lc].ar < tree[rc].minr)
    {
        tree[rt].exist = true;
        ckmin(tree[rt].ar, tree[lc].ar);
    }
}
inline void pushdown(int rt)
{
    if (tree[rt].lazy)
    {
        tree[lc].update(tree[rt].lazy);
        tree[rc].update(tree[rt].lazy);
        tree[rt].lazy = 0;
    }
}
inline void build(int rt, int l, int r)
{
    if (l == r)
    {
        tree[rt].minn = INF, tree[rt].minpos = 0;
        tree[rt].L = INF, tree[rt].R = 0;
        tree[rt].minr = tree[rt].ar = a[l].r;
        tree[rt].exist = true;
        return;
    }
    int mid = (l + r) >> 1;
    build(lc, l, mid);
    build(rc, mid + 1, r);
    pushup(rt);
}
inline void add(int rt, int l, int r, int pos, int val)
{
    if (l == r)
    {
        tree[rt].minn = val, tree[rt].minpos = l;
        tree[rt].L = a[l].l, tree[rt].R = a[l].r;
        tree[rt].exist = false, tree[rt].ar = INF;
        return;
    }
    int mid = (l + r) >> 1;
    pushdown(rt);
    if (pos <= mid)
        add(lc, l, mid, pos, val);
    else
        add(rc, mid + 1, r, pos, val);
    pushup(rt);
}
inline void del(int rt, int l, int r, int pos)
{
    if (l == r)
    {
        tree[rt].minn = INF, tree[rt].minpos = 0;
        tree[rt].L = INF, tree[rt].R = 0;
        tree[rt].minr = INF;
        return;
    }
    int mid = (l + r) >> 1;
    pushdown(rt);
    if (pos <= mid)
        del(lc, l, mid, pos);
    else
        del(rc, mid + 1, r, pos);
    pushup(rt);
}
inline void update(int rt, int l, int r, int x, int y, int val)
{
    if (r < x || l > y)
        return;
    if (x <= l && r <= y)
        return tree[rt].update(val);
    int mid = (l + r) >> 1;
    pushdown(rt);
    update(lc, l, mid, x, y, val);
    update(rc, mid + 1, r, x, y, val);
    pushup(rt);
}
inline int query(int rt, int l, int r, int minr)
{
    if (l == r)
        return l;
    int mid = (l + r) >> 1;
    pushdown(rt);
    if (tree[rc].exist && minr > tree[rc].ar)
        return query(rc, mid + 1, r, minr);
    return query(lc, l, mid, min(minr, tree[rc].minr));
}
inline int queryl(int rt, int l, int r, int pos)
{
    if (l == r)
        return l;
    int mid = (l + r) >> 1;
    pushdown(rt);
    if (tree[rc].L <= pos)
        return queryl(rc, mid + 1, r, pos);
    else
        return queryl(lc, l, mid, pos);
}
inline int queryr(int rt, int l, int r, int pos)
{
    if (l == r)
        return l;
    int mid = (l + r) >> 1;
    pushdown(rt);
    if (tree[lc].R >= pos)
        return queryr(lc, l, mid, pos);
    else
        return queryr(rc, mid + 1, r, pos);
}
inline void solve(int x)
{
    update(1, 1, n, queryr(1, 1, n, x + 1), queryl(1, 1, n, x), -(p[x + 1] - p[x]));
}
int fa[N * 2];
inline int find(int x)
{
    return !fa[x] ? x : fa[x] = find(fa[x]);
}
int c[N * 2];
inline void update(int pos)
{
    int val = p[pos + 1] - p[pos];
    for (int i = pos; i <= tot; i += lowbit(i))
        c[i] += val;
}
inline int query(int pos)
{
    int res = 0;
    for (int i = pos; i; i -= lowbit(i))
        res += c[i];
    return res;
}
inline int querysegment(int pos)
{
    return (p[a[pos].r] - p[a[pos].l]) - (query(a[pos].r - 1) - query(a[pos].l - 1));
}
inline void updatesegment(int pos)
{
    for (int i = find(a[pos].l); i < a[pos].r; i = find(i))
    {
        solve(i);
        update(i);
        fa[i] = i + 1;
    }
}
signed main()
{
#ifdef PAPERDOG
    freopen("project.in", "r", stdin);
    freopen("project.out", "w", stdout);
#else
    freopen("gardener.in", "r", stdin);
    freopen("gardener.out", "w", stdout);
#endif
    read(n);
    for (int i = 1; i <= n; ++i)
    {
        read(a[i].l, a[i].r);
        a[i].id = i;
        p[++tot] = a[i].l, p[++tot] = a[i].r;
    }
    sort(a + 1, a + 1 + n);
    sort(p + 1, p + 1 + tot);
    tot = (int)(unique(p + 1, p + 1 + tot) - p - 1);
    for (int i = 1; i <= n; ++i)
    {
        a[i].l = (int)(lower_bound(p + 1, p + 1 + tot, a[i].l) - p);
        a[i].r = (int)(lower_bound(p + 1, p + 1 + tot, a[i].r) - p);
    }
    build(1, 1, n);
    while (tree[1].exist)
    {
        int x = query(1, 1, n, INF);
        add(1, 1, n, x, querysegment(x));
    }
    for (int i = 1; i <= n; ++i)
    {
        int x = tree[1].minpos;
        write(a[x].id, ' ');
        updatesegment(x);
        del(1, 1, n, x);
        while (tree[1].exist)
        {
            x = query(1, 1, n, INF);
            add(1, 1, n, x, querysegment(x));
        }
    }
#ifdef FAST_OUT
    IO::OUTPUT::flush();
#endif
    return 0;
}