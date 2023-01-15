/**
 *    unicode: UTF-8
 *    name:    #1349. 【20省选集训day3】石子
 *    author:  whitepaperdog (蒟蒻wjr)
 *    located: Changle District, Fuzhou City, Fujian Province, China
 *    created: 2022.12.18 周日 08:24:17 (Asia/Shanghai)
 **/
#include <algorithm>
#include <cstdio>
#define ll long long
#define lll __int128
#define ull unsigned ll
#define lowbit(_x) (_x & (-_x))

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
        inline void read(char *_x)
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
                _x = (_x << 1) + (_x << 3) + _s - '0';
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
template <typename _T, const _T _mod>
struct modint
{
    _T x;
    modint(_T _x = 0) : x(_x) {}
    inline modint operator+(const modint &rhs) const
    {
        _T res = x;
        res += rhs.x;
        if (res >= _mod)
            res -= _mod;
        return res;
    }
    inline modint operator-(const modint &rhs) const
    {
        _T res = x;
        res -= rhs.x;
        if (res < 0)
            res += _mod;
        return res;
    }
    inline modint operator*(const modint &rhs) const
    {
        return (_T)((ll)x * rhs.x % _mod);
    }
    inline modint &operator+=(const modint &rhs)
    {
        x += rhs.x;
        if (x >= _mod)
            x -= _mod;
        return *this;
    }
    inline modint &operator-=(const modint &rhs)
    {
        x -= rhs.x;
        if (x < 0)
            x += _mod;
        return *this;
    }
    inline modint &operator*=(const modint &rhs)
    {
        x = (_T)((ll)x * rhs.x % _mod);
        return *this;
    }
    template <typename _G>
    inline modint operator^(_G rhs) const
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
    inline modint inv()
    {
        return this->pow(_mod - 2);
    }
    inline modint operator/(const modint &rhs) const
    {
        return (*this) * rhs.inv();
    }
    inline modint &operator/=(const modint &rhs)
    {
        return (*this) *= rhs.inv();
    }
    inline modint &operator==(const modint &rhs)
    {
        return x == rhs.x;
    }
    inline _T &data()
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
int n, k, q, T;
int a[N];
int c[N];
inline void add(int pos)
{
    for (int i = pos; i <= n; i += lowbit(i))
        ++c[i];
}
inline void del(int pos)
{
    for (int i = pos; i <= n; i += lowbit(i))
        --c[i];
}
inline int calc(int k_th)
{
    int res = 0;
    for (int i = 16; i >= 0; --i)
        if ((res | (1 << i)) <= n && c[res | (1 << i)] < k_th)
            k_th -= c[res |= (1 << i)];
    return res + 1;
}
inline int query(int pos)
{
    int res = 0;
    for (int i = pos; i; i -= lowbit(i))
        res += c[i];
    return res;
}
inline int query(int l, int r)
{
    return query(r) - query(l - 1);
}
bool exist[N];
struct Tree
{
    int min, max;
} tree[N * 4];
#define lc (rt << 1)
#define rc (rt << 1 | 1)
inline void pushup(int rt)
{
    tree[rt].min = min(tree[lc].min, tree[rc].min);
    tree[rt].max = max(tree[lc].max, tree[rc].max);
}
inline void build(int rt, int l, int r)
{
    if (l == r)
    {
        tree[rt].min = tree[rt].max = a[l];
        return;
    }
    int mid = (l + r) >> 1;
    build(lc, l, mid);
    build(rc, mid + 1, r);
    pushup(rt);
}
inline void update(int rt, int l, int r, int pos, int val)
{
    if (l == r)
    {
        tree[rt].min = tree[rt].max = val;
        return;
    }
    int mid = (l + r) >> 1;
    if (pos <= mid)
        update(lc, l, mid, pos, val);
    else
        update(rc, mid + 1, r, pos, val);
    pushup(rt);
}
namespace subtask1
{
    inline int queryl(int rt, int l, int r, int pos, int val)
    {
        if (tree[rt].min > val)
            return l;
        if (l == r)
            return l + 1;
        int mid = (l + r) >> 1;
        if (pos <= mid)
            return queryl(lc, l, mid, pos, val);
        int tmp = queryl(rc, mid + 1, r, pos, val);
        if (tmp == mid + 1)
            tmp = queryl(lc, l, mid, pos, val);
        return tmp;
    }
    inline int queryr(int rt, int l, int r, int pos, int val)
    {
        if (tree[rt].min > val)
            return r;
        if (l == r)
            return r - 1;
        int mid = (l + r) >> 1;
        if (pos > mid)
            return queryr(rc, mid + 1, r, pos, val);
        int tmp = queryr(lc, l, mid, pos, val);
        if (tmp == mid)
            tmp = queryr(rc, mid + 1, r, pos, val);
        return tmp;
    }
    inline int solve()
    {
        int where = calc((k + 1) >> 1);
        int l = 1, r = 1e9;
        while (l <= r)
        {
            int mid = (l + r) >> 1;
            int L = queryl(1, 1, n, where, mid);
            int R = queryr(1, 1, n, where, mid);
            if (L == R || query(L, R) <= (k >> 1))
                r = mid - 1;
            else
                l = mid + 1;
        }
        return l;
    }
}
namespace subtask2
{
    inline int queryl(int rt, int l, int r, int pos, int val)
    {
        if (tree[rt].max < val)
            return l;
        if (l == r)
            return l + 1;
        int mid = (l + r) >> 1;
        if (pos <= mid)
            return queryl(lc, l, mid, pos, val);
        int tmp = queryl(rc, mid + 1, r, pos, val);
        if (tmp == mid + 1)
            tmp = queryl(lc, l, mid, pos, val);
        return tmp;
    }
    inline int queryr(int rt, int l, int r, int pos, int val)
    {
        if (tree[rt].max < val)
            return r;
        if (l == r)
            return r - 1;
        int mid = (l + r) >> 1;
        if (pos > mid)
            return queryr(rc, mid + 1, r, pos, val);
        int tmp = queryr(lc, l, mid, pos, val);
        if (tmp == mid)
            tmp = queryr(rc, mid + 1, r, pos, val);
        return tmp;
    }
    inline int solve()
    {
        int where = calc((k + 1) >> 1);
        int l = 1, r = 1e9;
        while (l <= r)
        {
            int mid = (l + r) >> 1;
            int L = queryl(1, 1, n, where, mid);
            int R = queryr(1, 1, n, where, mid);
            if (L == R || query(L, R) <= (k >> 1))
                l = mid + 1;
            else
                r = mid - 1;
        }
        return r;
    }
}
inline int solve()
{
    return (k & 1) ? subtask1::solve() : subtask2::solve();
}
signed main()
{
#ifdef PAPERDOG
    freopen("project.in", "r", stdin);
    freopen("project.out", "w", stdout);
#endif
    read(n, k, q, T);
    for (int i = 1; i <= n; ++i)
        read(a[i]);
    for (int i = 1; i <= k; ++i)
    {
        int x;
        read(x);
        add(x);
        exist[x] = true;
    }
    build(1, 1, n);
    if (!T)
    {
        write(solve(), '\n');
        for (int i = 1; i <= q; ++i)
        {
            int opt, x, y;
            read(opt, x);
            if (opt == 1)
            {
                if (exist[x])
                {
                    del(x);
                    exist[x] = false;
                    --k;
                }
                else
                {
                    add(x);
                    exist[x] = true;
                    ++k;
                }
            }
            else
            {
                read(y);
                update(1, 1, n, x, y);
            }
            write(solve(), '\n');
        }
    }
    else
    {
        int lastans = solve();
        write(lastans, '\n');
        for (int i = 1; i <= q; ++i)
        {
            int opt, x, y;
            read(opt, x);
            x = (x - 1 + lastans) % n + 1;
            if (opt == 1)
            {
                if (exist[x])
                {
                    del(x);
                    exist[x] = false;
                    --k;
                }
                else
                {
                    add(x);
                    exist[x] = true;
                    ++k;
                }
            }
            else
            {
                read(y);
                update(1, 1, n, x, y);
            }
            write(lastans = solve(), '\n');
        }
    }

#ifdef FAST_OUT
    IO::OUTPUT::flush();
#endif
    return 0;
}