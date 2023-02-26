/**
 *    name:     marshmallow
 *    author:   whitepaperdog (蒟蒻wjr)
 *    located:  Xuanwu District, Nanjing City, Jiangsu Province, China
 *    created:  2023.02.26 周日 14:09:03 (Asia/Shanghai)
 *    unicode:  UTF-8
 *    standard: c++23
 **/
#include <algorithm>
#include <cmath>
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
constexpr int M = 337;
int n, k, mode;
int block, num;
int L[M], R[M], belong[N];
struct node
{
    int a, b;
    inline bool operator<(const node &rhs) const
    {
        return b == rhs.b ? a > rhs.a : b > rhs.b;
    }
} a[N];
struct
{
    ll a;
    int b;
} p[N];
int buf_st[M][M];
int buf_top[M];
bool exist[N];
ll add[M];
int cnt[M];
inline void pushup(int bel)
{
    auto st = buf_st[bel];
    auto &top = buf_top[bel];
    auto judge = [](int x, int y, int z)
    {
        auto x1 = p[x].b - p[y].b, x2 = p[z].b - p[y].b;
        auto y1 = p[y].a - p[x].a, y2 = p[y].a - p[z].a;
        return x1 * y2 <= x2 * y1;
    };
    top = 0;
    for (int i = R[bel]; i >= L[bel]; --i)
    {
        if (exist[i])
            continue;
        while (top > 1 && judge(st[top - 1], st[top], i))
            --top;
        st[++top] = i;
    }
    while (top > 1 && p[st[top]].a > p[st[top - 1]].a)
        top--;
}
inline void pushdown(int bel)
{
    for (int i = L[bel]; i <= R[bel]; ++i)
        p[i].a += add[bel] + (ll)p[i].b * cnt[bel];
    add[bel] = cnt[bel] = 0;
}
inline void solve()
{
    int where = 0;
    ll minn = 1e18;
    for (int i = 1; i <= num; ++i)
    {
        auto st = buf_st[i];
        auto &top = buf_top[i];
        if (!top)
            continue;
        ll x = p[st[top]].a + (ll)p[st[top]].b * cnt[i] + add[i];
        if (x >= minn)
            continue;
        minn = x;
        where = st[top];
    }
    exist[where] = true;
    int bel = belong[where];
    for (int i = 1; i < bel; ++i)
        add[i] += a[where].b;
    for (int i = bel + 1; i <= num; ++i)
    {
        ++cnt[i];
        auto st = buf_st[i];
        auto &top = buf_top[i];
        while (top > 1 && p[st[top]].a + (ll)p[st[top]].b * cnt[i] + add[i] >
                              p[st[top - 1]].a + (ll)p[st[top - 1]].b * cnt[i] + add[i])
            --top;
    }
    pushdown(bel);
    for (int i = L[bel]; i < where; ++i)
        p[i].a += a[where].b;
    for (int i = where + 1; i <= R[bel]; ++i)
        p[i].a += a[i].b;
    pushup(bel);
}
int pre[N];
ll suf[N];
ll c[N], d[N];
signed main()
{
#ifdef PAPERDOG
    freopen("project.in", "r", stdin);
    freopen("project.out", "w", stdout);
#else
    freopen("marshmallow.in", "r", stdin);
    freopen("marshmallow.out", "w", stdout);
#endif
    read(n, k, mode);
    for (int i = 1; i <= n; ++i)
        read(a[i].a, a[i].b);
    sort(a + 1, a + 1 + n);
    for (int i = 1; i <= n; ++i)
    {
        p[i].a = a[i].a;
        p[i].b = a[i].b;
    }
    block = (int)sqrt(n);
    num = (n - 1) / block + 1;
    for (int i = 1; i <= num; ++i)
    {
        L[i] = R[i - 1] + 1;
        R[i] = R[i - 1] + block;
    }
    R[num] = n;
    for (int i = 1; i <= num; ++i)
    {
        for (int j = L[i]; j <= R[i]; ++j)
            belong[j] = i;
        pushup(i);
    }
    for (int i = 1; i <= k; ++i)
        solve();
    // for (int i = 1; i <= n; ++i)
    //     printf("%d ", exist[i]);
    // putchar('\n');
    ll ans = 0;
    for (int i = 1, j = 0; i <= n; ++i)
        if (exist[i])
            ans += a[i].a + (ll)(j++) * a[i].b;
    if (mode)
    {
        ll delta = 0;
        for (int i = 1; i <= n; ++i)
            if (exist[i])
                ckmax(delta, (ll)a[i].a);
        for (int i = 1; i <= n; i++)
            if (exist[i])
                pre[i] = pre[i - 1] + 1;
            else
                pre[i] = pre[i - 1];
        for (int i = n; i >= 1; i--)
            if (exist[i])
                suf[i] = suf[i + 1] + a[i].b;
            else
                suf[i] = suf[i + 1];
        for (int i = 1; i <= n; i++)
            c[i] = a[i].a + (ll)pre[i - 1] * a[i].b + suf[i + 1];
        d[0] = -1e18;
        for (int i = 1; i <= n; i++)
            d[i] = max(d[i - 1], exist[i] ? c[i] : 0);
        for (int i = 1; i <= n; i++)
            if (!exist[i])
                ckmax(delta, d[i - 1] - c[i] + a[i].b + a[i].a);
        ans -= delta;
    }
    write(ans, '\n');
#ifdef FAST_OUT
    IO::OUTPUT::flush();
#endif
    return 0;
}