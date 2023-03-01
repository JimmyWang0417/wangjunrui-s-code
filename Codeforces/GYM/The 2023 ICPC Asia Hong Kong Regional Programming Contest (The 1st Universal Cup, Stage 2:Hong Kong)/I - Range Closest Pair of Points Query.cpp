/**
 *    name:     P9062 [Ynoi2002] Adaptive Hsearch&Lsearch
 *    author:   whitepaperdog (蒟蒻wjr)
 *    located:  Xuanwu District, Nanjing City, Jiangsu Province, China
 *    created:  2023.02.27 周一 20:45:03 (Asia/Shanghai)
 *    unicode:  UTF-8
 *    standard: c++23
 **/
#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <vector>
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
constexpr int N = 2.5e5 + 5;
constexpr int d = 3;
constexpr int mod = 19260817;
int n, m;
pair<int, int> a[N];
struct Edge
{
    int next;
    int x, y;
    int l, r;
} edge[N * 100];
int head[mod], num_edge;
int st[N], top;
inline void insert(int x, int y, int l, int r)
{
    int from = (int)(((ll)1e9 * x + y) % mod);
    if (!head[from])
        st[++top] = from;
    edge[++num_edge].next = head[from];
    edge[num_edge].x = x;
    edge[num_edge].y = y;
    edge[num_edge].l = l;
    edge[num_edge].r = r;
    head[from] = num_edge;
}
inline pair<int, int> query(int x, int y)
{
    if (x < 0 || y < 0)
        return make_pair(-1, -1);
    int from = (int)(((ll)1e9 * x + y) % mod);
    for (int i = head[from]; i; i = edge[i].next)
        if (x == edge[i].x && y == edge[i].y)
            return make_pair(edge[i].l, edge[i].r);
    return make_pair(-1, -1);
}
inline void clean()
{
    num_edge = 0;
    while (top)
        head[st[top--]] = 0;
}
vector<int> g[N];
vector<pair<int, int>> q[N];
int p[N];
constexpr int dx[] = {-1, 0, 1, 1};
constexpr int dy[] = {1, 1, 1, 0};
int buf[N];
ll answer[N];
int block, belong[N];
ll minn[N], minblock[N];
inline void update(int pos, ll val)
{
    ckmin(minn[pos], val);
    ckmin(minblock[belong[pos]], val);
}
inline ll query(int pos)
{
    ll res = 1e18;
    for (int i = pos; belong[i] == belong[pos]; ++i)
        ckmin(res, minn[i]);
    for (int i = belong[pos] + 1; i <= belong[n]; ++i)
        ckmin(res, minblock[i]);
    return res;
}
signed main()
{
    read(n, m);
    block = (int)sqrt(n);
    for (int i = 1; i <= n; ++i)
        belong[i] = (i - 1) / block + 1;
    for (int i = 1; i <= n; ++i)
        read(a[i].first, a[i].second);
    for (int i = 1; i <= n; ++i)
        p[i] = i;
    for (int k = 0; k < 27; ++k)
    {
        auto compare = [k](int x, int y)
        {
            int x1 = a[x].first >> k, y1 = a[x].second >> k;
            int x2 = a[y].first >> k, y2 = a[y].second >> k;
            return x1 == x2 ? y1 < y2 : x1 < x2;
        };
        sort(p + 1, p + 1 + n, compare);
        auto equal = [k](int x, int y)
        {
            int x1 = a[x].first >> k, y1 = a[x].second >> k;
            int x2 = a[y].first >> k, y2 = a[y].second >> k;
            return x1 == x2 && y1 == y2;
        };
        for (int l = 1, r; l <= n; l = r)
        {
            r = l + 1;
            while (r <= n && equal(p[l], p[r]))
                ++r;
            sort(p + l, p + r);
            insert(a[p[l]].first >> k, a[p[l]].second >> k, l, r);
            for (int i = l; i < r; ++i)
                for (int j = i + 1; j <= i + d && j < r; ++j)
                    g[p[j]].push_back(p[i]);
        }
        for (int l = 1, r; l <= n; l = r)
        {
            r = l + 1;
            while (r <= n && equal(p[l], p[r]))
                ++r;
            int x = a[p[l]].first >> k, y = a[p[l]].second >> k;
            for (int i = 0; i < 4; ++i)
            {
                auto qwq = query(x + dx[i], y + dy[i]);
                if (qwq.first != -1)
                {
                    int pl = qwq.first, pr = qwq.second;
                    int all = r - l + pr - pl;
                    merge(p + l, p + r, p + pl, p + pr, buf);
                    for (int j = 0; j < all; ++j)
                        for (int kk = j + 1; kk <= j + d && kk < all; ++kk)
                            g[buf[kk]].push_back(buf[j]);
                }
            }
        }
        clean();
    }
    memset(minn, 0x3f, sizeof(minn));
    memset(minblock, 0x3f, sizeof(minblock));
    auto distance = [](int x, int y)
    {
        return (ll)(a[x].first - a[y].first) * (a[x].first - a[y].first) +
               (ll)(a[x].second - a[y].second) * (a[x].second - a[y].second);
    };
    for (int i = 1; i <= m; ++i)
    {
        int l, r;
        read(l, r);
        q[r].emplace_back(l, i);
    }
    for (int i = 1; i <= n; ++i)
    {
        for (int j : g[i])
            update(j, distance(i, j));
        for (auto j : q[i])
            answer[j.second] = query(j.first);
    }
    for (int i = 1; i <= m; ++i)
        write(answer[i], '\n');
#ifdef FAST_OUT
    IO::OUTPUT::flush();
#endif
    return 0;
}