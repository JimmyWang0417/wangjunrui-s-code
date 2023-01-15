/**
 *    unicode: UTF-8
 *    name:    #1345. 【20省选集训day2】调兵遣将
 *    author:  whitepaperdog (蒟蒻wjr)
 *    located: Changle District, Fuzhou City, Fujian Province, China
 *    created: 2022.12.04 周日 08:02:50 (Asia/Shanghai)
 **/
#include <algorithm>
#include <cstdio>
#include <cstring>
#include <map>
#include <vector>
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
    modint(_T _x = 0)
    {
        x = _x % _mod;
        if (x < 0)
            x += _mod;
    }
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
constexpr int N = 5e4 + 5;
constexpr int mod = 998244353;
typedef modint<int, mod> node;
int n, m, a[N];
int qwq[N], tot;
struct tree_array
{
    node c1[N], c2[N];
    inline void update(int pos, int val)
    {
        for (int i = pos; i <= n; i += lowbit(i))
        {
            c1[i] += val;
            c2[i] += (node)pos * val;
        }
    }
    inline node query(int pos)
    {
        node res;
        for (int i = pos; i; i -= lowbit(i))
            res += c1[i] * (pos + 1) - c2[i];
        return res;
    }
    inline void update(int l, int r, int val)
    {
        update(l, val);
        update(r + 1, -val);
    }
    inline node query(int l, int r)
    {
        return query(r) - query(l - 1);
    }
    inline void clear(int pos)
    {
        for (int i = pos; i <= n; i += lowbit(i))
            c1[i] = c2[i] = 0;
    }
    inline void clear(int l, int r)
    {
        clear(l);
        clear(r + 1);
    }
    inline void clear()
    {
        for (int i = 1; i <= n; ++i)
            c1[i] = c2[i] = 0;
    }
} tree;
node L[N], R[N];
map<int, int> mp;
pair<int, int> _buf[2][N];
struct Query
{
    int x, l, r;
    Query(int _x = 0, int _l = 0, int _r = 0) : x(_x), l(_l), r(_r) {}
};
vector<Query> g[N], h[N];
node answer[N];
signed main()
{
#ifdef PAPERDOG
    freopen("project.in", "r", stdin);
    freopen("project.out", "w", stdout);
#endif
    read(n);
    auto p = _buf[0], q = _buf[1];
    int totp = 0, totq = 0;
    for (int i = 1; i <= n; ++i)
    {
        read(a[i]);
        q[totq = 1] = make_pair(i, a[i]);
        for (int j = 1; j <= totp; ++j)
        {
            int tmp = __gcd(a[i], p[j].second);
            if (tmp == q[totq].second)
                continue;
            q[++totq] = make_pair(p[j].first, tmp);
        }
        swap(p, q), totp = totq;
        p[totp + 1].first = 0;
        for (int j = 1; j <= totp; ++j)
            g[mp[p[j].second] ? mp[p[j].second] : mp[p[j].second] = ++m].emplace_back(i, p[j + 1].first + 1, p[j].first);
    }
    totp = 0;
    for (int i = n; i >= 1; --i)
    {
        q[totq = 1] = make_pair(i, a[i]);
        for (int j = 1; j <= totp; ++j)
        {
            int tmp = __gcd(a[i], p[j].second);
            if (tmp == q[totq].second)
                continue;
            q[++totq] = make_pair(p[j].first, tmp);
        }
        swap(p, q), totp = totq;
        p[totp + 1].first = n + 1;
        for (int j = 1; j <= totp; ++j)
            h[mp[p[j].second] ? mp[p[j].second] : mp[p[j].second] = ++m].emplace_back(i, p[j].first, p[j + 1].first - 1);
    }
    node all;
    for (int kase = 1; kase <= m; ++kase)
    {
        tot = 0;
        auto r = h[kase].rbegin();
        for (auto l = g[kase].begin(); l != g[kase].end(); ++l)
        {
            while (r != h[kase].rend() && r->x <= l->x)
            {
                if (qwq[tot] != r->x)
                    qwq[++tot] = r->x;
                ++r;
            }
            if (qwq[tot] != l->x)
                qwq[++tot] = l->x;
        }
        while (r != h[kase].rend())
        {
            if (qwq[tot] != r->x)
                qwq[++tot] = r->x;
            ++r;
        }
        tree.update(1, 1);
        for (auto i : g[kase])
            tree.update(i.x + 1, (L[lower_bound(qwq + 1, qwq + 1 + tot, i.x) - qwq] = tree.query(i.l, i.r)).data());
        tree.clear(1);
        for (auto i : g[kase])
            tree.clear(i.x + 1);
        tree.update(1, 1);
        for (auto i : h[kase])
            tree.update(1, i.x - 1, (R[lower_bound(qwq + 1, qwq + 1 + tot, i.x) - qwq] = tree.query(i.l, i.r)).data());
        tree.clear(1);
        for (auto i : h[kase])
            tree.clear(1, i.x - 1);
        for (int i = 2; i <= tot; ++i)
            L[i] += L[i - 1];
        for (int i = tot - 1; i >= 1; --i)
            R[i] += R[i + 1];
        all += L[tot];
        for (int i = 1; i <= tot; ++i)
        {
            auto tmp = L[i - 1] * R[i + 1] + L[i - 1] + R[i + 1];
            answer[qwq[i]] += tmp;
            answer[qwq[i] + 1] -= tmp;
        }
        answer[1] += R[1];
        answer[qwq[1]] -= R[1];
        for (int i = 1; i < tot; ++i)
        {
            auto tmp = L[i] * R[i + 1] + L[i] + R[i + 1];
            answer[qwq[i] + 1] += tmp;
            answer[qwq[i + 1]] -= tmp;
        }
        answer[qwq[tot] + 1] += L[tot];
        for (int i = 1; i <= tot; ++i)
            L[i] = R[i] = 0;
    }
    for (int i = 2; i <= n; ++i)
        answer[i] += answer[i - 1];
    for (int i = 1; i <= n; ++i)
        write((all - answer[i]).data(), ' ');
#ifdef FAST_OUT
    IO::OUTPUT::flush();
#endif
    return 0;
}