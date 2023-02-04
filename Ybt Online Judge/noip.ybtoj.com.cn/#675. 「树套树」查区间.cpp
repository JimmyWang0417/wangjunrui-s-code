/**
 *    unicode: UTF-8
 *    name:    打怪兽
 *    author:  whitepaperdog (蒟蒻wjr)
 *    located: Changle District, Fuzhou City, Fujian Province, China
 *    created: 2023.02.03 周五 13:39:47 (Asia/Shanghai)
 **/
#include <algorithm>
#include <cstdio>
#include <iostream>
#include <list>
typedef long long ll;
typedef unsigned long long ull;
constexpr auto lowbit = [](const auto &x)
{ return x & (-x); };

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
constexpr int N = 8e4 * 2 + 5;
constexpr int M = 405;
int n, m;
int a[N], b[N], c[N];
int p[N], tot;
struct Query
{
    int opt, l, r, x;
} q[N];
struct node
{
    int block, num;
    int L[M], R[M];
    int belong[N];
    inline void init(int _n)
    {
        block = (int)__builtin_sqrt(_n);
        num = (_n - 1) / block + 1;
        for (int i = 1; i <= num; ++i)
        {
            L[i] = R[i - 1] + 1;
            R[i] = min(R[i - 1] + block, _n);
            for (int j = L[i]; j <= R[i]; ++j)
                belong[j] = i;
        }
    }
    inline int left(int x)
    {
        return L[belong[x]];
    }
    inline int right(int x)
    {
        return R[belong[x]];
    }
} seq, value;
int cnt[M][N], cntblock[M][M];
list<int> have[M][M];
inline void _update(int _bel, int _val, int _add)
{
    for (int i = _bel; i <= seq.num; ++i)
    {
        cnt[i][_val] += _add;
        cntblock[i][value.belong[_val]] += _add;
    }
};
int vis[N], vistime;
int st[N], stcnt[N], where[N], top;
inline void updatein(int l, int r, int val)
{
    int bel = seq.belong[l];
    if (b[bel] > val)
    {
        int res = 0;
        ++vistime;
        for (int i = l; i <= r; ++i)
        {
            if (a[i] > val)
            {
                int v = min(a[i], b[bel]);
                if (v == b[bel])
                    --c[bel];
                else
                {
                    if (vis[v] != vistime)
                    {
                        st[where[v] = ++top] = v;
                        stcnt[top] = 1;
                        vis[v] = vistime;
                    }
                    else
                        ++stcnt[where[v]];
                }
                ++res;
                a[i] = val;
            }
        }
        if (res)
        {
            while (top)
            {
                _update(bel, st[top], -stcnt[top]);
                --top;
            }
            _update(bel, val, res);
            for (int i = 1; i <= value.num; ++i)
                for (auto it = have[bel][i].begin(); it != have[bel][i].end();)
                    if (cnt[bel][*it] - cnt[bel - 1][*it] == 0)
                        it = have[bel][i].erase(it);
                    else
                        ++it;
            auto &li = have[bel][value.belong[val]];
            bool flag = true;
            for (auto it = li.begin(); it != li.end(); ++it)
            {
                if (*it == val)
                {
                    flag = false;
                    break;
                }
                if (*it > val)
                {
                    li.insert(it, val);
                    flag = false;
                    break;
                }
            }
            if (flag)
                li.push_back(val);
        }
    }
}
inline void cover(int bel, int val)
{
    int &res = c[bel];
    for (int i = value.belong[val] + 1; i <= value.belong[b[bel]]; ++i)
    {
        res += cntblock[bel][i] - cntblock[bel - 1][i];
        for (int j : have[bel][i])
            _update(bel, j, cnt[bel - 1][j] - cnt[bel][j]);
        have[bel][i].clear();
    }
    auto &li = have[bel][value.belong[val]];
    while (!li.empty() && li.back() > val)
    {
        res += cnt[bel][li.back()] - cnt[bel - 1][li.back()];
        _update(bel, li.back(), cnt[bel - 1][li.back()] - cnt[bel][li.back()]);
        li.pop_back();
    }
    b[bel] = val;
}
inline void updateout(int l, int r, int val)
{
    for (int i = l; i <= r; ++i)
    {
        if (b[i] > val)
            cover(i, val);
    }
}
inline void update(int l, int r, int val)
{
    if (seq.belong[l] == seq.belong[r])
    {
        updatein(l, r, val);
        return;
    }
    updatein(l, seq.right(l), val);
    updateout(seq.belong[l] + 1, seq.belong[r] - 1, val);
    updatein(seq.left(r), r, val);
}
inline int _query(int l, int r, int k)
{
    for (int i = 1; i <= value.num; ++i)
    {
        int now = cntblock[r][i] - cntblock[l][i] + cntblock[0][i];
        if (k <= now)
        {
            for (int j = value.L[i]; j <= value.R[i]; ++j)
            {
                now = cnt[r][j] - cnt[l][j] + cnt[0][j];
                if (k <= now)
                    return j;
                else
                    k -= now;
            }
        }
        else
            k -= now;
    }
    return 0;
}
inline int query(int l, int r, int k)
{
    if (seq.belong[l] == seq.belong[r])
    {
        for (int i = l; i <= r; ++i)
        {
            int v = min(a[i], b[seq.belong[i]]);
            ++cnt[0][v];
            ++cntblock[0][value.belong[v]];
        }
        int res = _query(0, 0, k);
        for (int i = l; i <= r; ++i)
        {
            int v = min(a[i], b[seq.belong[i]]);
            --cnt[0][v];
            --cntblock[0][value.belong[v]];
        }
        return res;
    }
    for (int i = l; i <= seq.right(l); ++i)
    {
        int v = min(a[i], b[seq.belong[i]]);
        ++cnt[0][v];
        ++cntblock[0][value.belong[v]];
    }
    for (int i = seq.belong[l] + 1; i < seq.belong[r]; ++i)
    {
        cnt[0][b[i]] += c[i];
        cntblock[0][value.belong[b[i]]] += c[i];
    }
    for (int i = seq.left(r); i <= r; ++i)
    {
        int v = min(a[i], b[seq.belong[i]]);
        ++cnt[0][v];
        ++cntblock[0][value.belong[v]];
    }
    int res = _query(seq.belong[l], seq.belong[r] - 1, k);
    for (int i = l; i <= seq.right(l); ++i)
    {
        int v = min(a[i], b[seq.belong[i]]);
        --cnt[0][v];
        --cntblock[0][value.belong[v]];
    }
    for (int i = seq.belong[l] + 1; i < seq.belong[r]; ++i)
    {
        cnt[0][b[i]] -= c[i];
        cntblock[0][value.belong[b[i]]] -= c[i];
    }
    for (int i = seq.left(r); i <= r; ++i)
    {
        int v = min(a[i], b[seq.belong[i]]);
        --cnt[0][v];
        --cntblock[0][value.belong[v]];
    }
    return res;
}
signed main()
{
#ifdef PAPERDOG
    freopen("project.in", "r", stdin);
    freopen("project.out", "w", stdout);
#else
    freopen("segment.in", "r", stdin);
    freopen("segment.out", "w", stdout);
#endif
    read(n, m);
    for (int i = 1; i <= n; ++i)
    {
        read(a[i]);
        p[++tot] = a[i];
    }
    for (int i = 1; i <= m; ++i)
    {
        auto &[opt, l, r, x] = q[i];
        read(opt, l, r, x);
        if (opt == 1)
            p[++tot] = x;
    }
    sort(p + 1, p + 1 + tot);
    tot = (int)(unique(p + 1, p + 1 + tot) - p - 1);
    seq.init(n), value.init(tot);
    for (int i = 1; i <= seq.num; ++i)
    {
        b[i] = tot;
        for (int j = seq.L[i]; j <= seq.R[i]; ++j)
        {
            a[j] = (int)(lower_bound(p + 1, p + 1 + tot, a[j]) - p);
            ++cnt[i][a[j]];
            ++cntblock[i][value.belong[a[j]]];
        }
        for (int j = 1; j <= tot; ++j)
        {
            if (cnt[i][j])
                have[i][value.belong[j]].push_back(j);
            cnt[i][j] += cnt[i - 1][j];
        }
        for (int j = 1; j <= value.num; ++j)
            cntblock[i][j] += cntblock[i - 1][j];
    }
    for (int i = 1; i <= m; ++i)
    {
        auto [opt, l, r, x] = q[i];
        if (opt == 1)
        {
            x = (int)(lower_bound(p + 1, p + 1 + tot, x) - p);
            update(l, r, x);
        }
        else
            write(p[query(l, r, x)], '\n');
    }
#ifdef FAST_OUT
    IO::OUTPUT::flush();
#endif
    return 0;
}