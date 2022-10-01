/**
 *    unicode: UTF-8
 *    name:    2209702937
 *    author:  wangjunrui (蒟蒻wjr)
 *    located: Changle District, Fuzhou City, Fujian Province, China
 *    created: 2022.09.30 周五 20:13:54 (Asia/Shanghai)
 **/
#include <algorithm>
#include <cstdio>
#include <cstring>
#include <vector>
#define ll long long
#define lll __int128
#define ull unsigned ll
#define lowbit(_x) (_x & (-_x))

//#define FAST_IO

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
using namespace IO::INPUT;
using namespace IO::OUTPUT;
using namespace std;
constexpr int N = 12e5 + 5;
int Log[N];
int where[N];
class suffix_array
{
private:
    int wa[N], wb[N], ws[N];

public:
    int n;
    int str[N];
    int sa[N], rk[N], height[N];
    int dp[N][20];
    inline void init(int m)
    {
        auto x = wa, y = wb;

        for (int i = 1; i <= n; ++i)
            ++ws[x[i] = str[i]];
        for (int i = 2; i <= m; ++i)
            ws[i] += ws[i - 1];
        for (int i = n; i >= 1; --i)
            sa[ws[x[i]]--] = i;
        for (int i = 1; i <= m; ++i)
            ws[i] = 0;

        for (int j = 1, p = 0; p < n; m = p, j <<= 1)
        {
            p = 0;
            for (int i = n - j + 1; i <= n; ++i)
                y[++p] = i;
            for (int i = 1; i <= n; ++i)
                if (sa[i] > j)
                    y[++p] = sa[i] - j;

            for (int i = 1; i <= n; ++i)
                ++ws[x[i]];
            for (int i = 2; i <= m; ++i)
                ws[i] += ws[i - 1];
            for (int i = n; i >= 1; --i)
                sa[ws[x[y[i]]]--] = y[i];
            for (int i = 1; i <= m; ++i)
                ws[i] = 0;

            swap(x, y);
            p = 0;
            auto compare = [&](int _x, int _y)
            {
                return y[_x] == y[_y] && y[_x + j] == y[_y + j];
            };
            for (int i = 1; i <= n; ++i)
                x[sa[i]] = compare(sa[i - 1], sa[i]) ? p : ++p;
        }

        for (int i = 1; i <= n; ++i)
            rk[sa[i]] = i;
        for (int i = 1, j = 0; i <= n; ++i)
        {
            if (j)
                --j;
            while (str[i + j] == str[sa[rk[i] - 1] + j])
                ++j;
            height[rk[i]] = j;
        }
        for (int i = 1; i <= n; ++i)
            dp[i][0] = height[i];
        for (int j = 1; j <= Log[n]; ++j)
            for (int i = 1; i + (1 << j) - 1 <= n; ++i)
                dp[i][j] = min(dp[i][j - 1], dp[i + (1 << (j - 1))][j - 1]);
    }
    inline int lcp(int x, int y)
    {
        x = rk[x], y = rk[y];
        if (x > y)
            swap(x, y);
        ++x;
        int k = Log[y - x + 1];
        return min(dp[x][k], dp[y - (1 << k) + 1][k]);
    }
    inline int calcl(int x, int len)
    {
        x = rk[x];
        int l = 1, r = x - 1;
        while (l <= r)
        {
            int mid = (l + r) >> 1;
            if (lcp(sa[mid], sa[x]) < len)
                l = mid + 1;
            else
                r = mid - 1;
        }
        return l;
    }
    inline int calcr(int x, int len)
    {
        x = rk[x];
        int l = x + 1, r = n;
        while (l <= r)
        {
            int mid = (l + r) >> 1;
            if (lcp(sa[x], sa[mid]) < len)
                r = mid - 1;
            else
                l = mid + 1;
        }
        return r;
    }
} pre, suf;
int n, m, k;
int p[N], tot;
char str[N];
vector<int> g[N];
struct Tree
{
    int l, r;
    int sum;
} tree[N * 40];
#define lc(rt) tree[rt].l
#define rc(rt) tree[rt].r
int root[N], cnt;
inline void pushup(int rt)
{
    tree[rt].sum = tree[lc(rt)].sum + tree[rc(rt)].sum;
}
inline void update(int &rt, int l, int r, int pos)
{
    ++cnt;
    tree[cnt] = tree[rt];
    ++tree[rt = cnt].sum;
    if (l == r)
        return;
    int mid = (l + r) >> 1;
    if (pos <= mid)
        update(lc(rt), l, mid, pos);
    else
        update(rc(rt), mid + 1, r, pos);
    pushup(rt);
}
inline int query(int rtl, int rtr, int l, int r, int x, int y)
{
    if (r < x || l > y)
        return 0;
    if (x <= l && r <= y)
        return tree[rtr].sum - tree[rtl].sum;
    int mid = (l + r) >> 1;
    return query(lc(rtl), lc(rtr), l, mid, x, y) + query(rc(rtl), rc(rtr), mid + 1, r, x, y);
}
int mp[N];
int answer[N];
signed main()
{
#ifdef PAPERDOG
    freopen("project.in", "r", stdin);
    freopen("project.out", "w", stdout);
#else
#ifdef ONLINE_JUDGE
    freopen("match.in", "r", stdin);
    freopen("match.out", "w", stdout);
#endif
#endif
    read(k, str);
    for (int i = 0; str[i]; ++i)
        pre.str[++pre.n] = str[i] - 'a' + 1;
    n = pre.n;
    read(m);
    for (int i = 1; i <= m; ++i)
    {
        pre.str[++pre.n] = 26 + i;
        read(str);
        where[i] = pre.n + 1;
        ++tot;
        for (int j = 0; str[j]; ++j)
        {
            pre.str[++pre.n] = str[j] - 'a' + 1;
            ++p[tot];
        }
        g[p[tot]].push_back(i);
    }
    sort(p + 1, p + 1 + tot);
    tot = (int)(unique(p + 1, p + 1 + tot) - p - 1);


    suf.n = pre.n;
    for (int i = 1; i <= pre.n; ++i)
        suf.str[i] = pre.str[pre.n - i + 1];

    Log[0] = -1;
    for (int i = 1; i <= pre.n; ++i)
        Log[i] = Log[i >> 1] + 1;

    pre.init(m + 26), suf.init(m + 26);
    for (int i = 1; i <= pre.n; ++i)
        if (pre.sa[i] <= n)
            mp[pre.sa[i]] = i;
    // for (int i = 1; i <= pre.n; ++i)
    //     printf("%d ", pre.str[i]);
    // putchar('\n');
    // for (int i = 1; i <= pre.n; ++i)
    //     printf("%d ", pre.rk[i]);
    // putchar('\n');
    // for (int i = 1; i <= pre.n; ++i)
    //     printf("%d ", pre.sa[i]);
    // putchar('\n');
    // for (int i = 1; i <= pre.n; ++i)
    //     printf("%d ", pre.height[i]);
    // putchar('\n');
    for (int kase = 1; kase <= tot; ++kase)
    {
        int len = p[kase];
        if (len <= k)
        {
            for (auto que : g[len])
                answer[que] = n - len + 1;
            continue;
        }
        for (int i = 1; i <= suf.n; ++i)
        {
            int u = suf.n - suf.sa[i] + 1;
            root[i] = root[i - 1];
            if (u > n)
                continue;
            u = u - len + 1;
            if (u >= 1)
                update(root[i], 1, pre.n, mp[u]);
        }
        for (auto que : g[len])
        {
            int l = 1, r = 0, ql, qr, qx, qy;
            for (int i = len - k; i >= 0; --i)
            {
                ql = pre.calcl(where[que], i);
                qr = pre.calcr(where[que], i);
                qx = suf.calcl(suf.n - (where[que] + len - 1) + 1, len - k - i);
                qy = suf.calcr(suf.n - (where[que] + len - 1) + 1, len - k - i);

                answer[que] += query(root[qx - 1], root[qy], 1, pre.n, ql, qr) -
                               query(root[qx - 1], root[qy], 1, pre.n, l, r);

                l = ql;
                r = qr;
            }
        }
        cnt = 0;
    }
    for (int i = 1; i <= m; ++i)
        write(answer[i], '\n');
#ifdef FAST_OUT
    flush();
#endif
    return 0;
}
