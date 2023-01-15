/**
 *    unicode: UTF-8
 *    name:    #1346. 【20省选集训day2】一掷千金
 *    author:  whitepaperdog (蒟蒻wjr)
 *    located: Changle District, Fuzhou City, Fujian Province, China
 *    created: 2022.12.11 周日 10:19:35 (Asia/Shanghai)
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
int K, n, m, limit;
struct Tree
{
    int ch[2];
    int cnt;
    int len;
    int ans;
} tree[N * 100];
#define lc(rt) tree[rt].ch[0]
#define rc(rt) tree[rt].ch[1]
int root, cnt;
inline int solve(int l, int r)
{
    return lowbit(l) ^ ((r - l + 1) >> 1);
}
inline void pushup(int rt, int l, int r)
{
    if (tree[rt].cnt)
    {
        tree[rt].len = r - l + 1;
        tree[rt].ans = solve(l, r);
    }
    else
    {
        tree[rt].len = tree[lc(rt)].len + tree[rc(rt)].len;
        tree[rt].ans = tree[lc(rt)].ans ^ tree[rc(rt)].ans;
    }
}
inline void update(int &rt, int l, int r, int x, int y, int val)
{
    if (r < x || l > y)
        return;
    if (!rt)
        rt = ++cnt;
    if (x <= l && r <= y)
    {
        tree[rt].cnt += val;
        pushup(rt, l, r);
        return;
    }
    int mid = (l + r) >> 1;
    update(lc(rt), l, mid, x, y, val);
    update(rc(rt), mid + 1, r, x, y, val);
    pushup(rt, l, r);
}
inline int query(int rt, int l, int r, int x, int y)
{
    if (!rt || r < x || l > y)
        return 0;
    if (tree[rt].cnt)
        return min(y, r) - max(l, x) + 1;
    if (x <= l && r <= y)
        return tree[rt].len;
    int mid = (l + r) >> 1;
    return query(lc(rt), l, mid, x, y) + query(rc(rt), mid + 1, r, x, y);
}
inline int calc(int rt, int l, int r, int x, int y, bool tag = false)
{
    if (r < x || l > y)
        return 0;
    if (x <= l && r <= y)
        return tag ? solve(l, r) : tree[rt].ans;
    int mid = (l + r) >> 1;
    return calc(lc(rt), l, mid, x, y, tag || tree[rt].cnt) ^ calc(rc(rt), mid + 1, r, x, y, tag || tree[rt].cnt);
}
struct Query
{
    int x, l, r, type;
    Query(int _x = 0, int _l = 0, int _r = 0, int _type = 0) : x(_x), l(_l), r(_r), type(_type) {}
    inline bool operator<(const Query &rhs) const
    {
        return x < rhs.x;
    }
} a[N * 2];
int tot;
signed main()
{
#ifdef PAPERDOG
    freopen("project.in", "r", stdin);
    freopen("project.out", "w", stdout);
#endif
    read(K, n, m);
    for (int i = 1; i <= K; ++i)
    {
        int xl, xr, yl, yr;
        read(xl, yl, xr, yr);
        a[++tot] = Query(xl, yl, yr, 1);
        a[++tot] = Query(xr + 1, yl, yr, -1);
    }
    limit = 1;
    while (limit <= m)
        limit <<= 1;
    --limit;
    sort(a + 1, a + 1 + tot);
    int res = 0;
    for (int i = 1, j = 1; i <= n; ++i)
    {
        while (j <= tot && a[j].x <= i)
        {
            update(root, 0, limit, a[j].l, a[j].r, a[j].type);
            ++j;
        }
        if (query(root, 0, limit, 0, i) & 1)
            res ^= lowbit(i);
        res ^= calc(root, 0, limit, i + 1, limit);
    }
    write(res, '\n');
#ifdef FAST_OUT
    IO::OUTPUT::flush();
#endif
    return 0;
}