/**
 *    unicode: UTF-8
 *    name:    #1410. 【五一省选集训day5】超简单题
 *    author:  whitepaperdog (蒟蒻wjr)
 *    located: Changle District, Fuzhou City, Fujian Province, China
 *    created: 2023.01.15 周日 12:32:49 (Asia/Shanghai)
 **/
#include <algorithm>
#include <cstdio>
#include <cstring>
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
template <typename _T, const _T _mod>
struct modint
{
    _T x;
    modint(_T _x = 0) : x(_x) {}
    inline modint operator+() const
    {
        return *this;
    }
    inline modint operator-() const
    {
        return !x ? 0 : _mod - x;
    }
    inline modint &operator++()
    {
        ++x;
        if (x >= _mod)
            x -= _mod;
        return *this;
    }
    inline modint &operator--()
    {
        --x;
        if (x < 0)
            x += _mod;
        return *this;
    }
    inline modint operator++(_T)
    {
        int res = x;
        if (x >= _mod)
            x -= _mod;
        return res;
    }
    inline modint operator--(_T)
    {
        int res = x;
        if (x < 0)
            x += _mod;
        return res;
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
constexpr int N = 3e5 + 5;
constexpr ll limit = 1e18 + 114514;
int n, m;
char str[N];
int a[N][26];
int Log[N];
int b[N][20];
ll c[N][20];
ll f[N], g[26];
int p[N], q[N], tot;
int top, cnt;
char st[N], e[N];
signed main()
{
#ifdef PAPERDOG
    freopen("project.in", "r", stdin);
    freopen("project.out", "w", stdout);
#endif
    n = read(str + 1);
    for (int i = 0; i < 26; ++i)
        a[n][i] = n + 1;
    for (int i = n - 1; i >= 0; --i)
    {
        memcpy(a[i], a[i + 1], sizeof(a[i]));
        a[i][str[i + 1] - 'a'] = i + 1;
    }
    ll sum = 1;
    auto check = [](auto &x)
    {
        if (x > limit)
            x = limit;
    };
    for (int i = n; i >= 1; --i)
    {
        f[i] = sum;
        check(sum += f[i] - g[str[i] - 'a']);
        g[str[i] - 'a'] = f[i];
    }
    f[0] = sum - 1;
    Log[0] = -1;
    for (int i = 1; i <= n; ++i)
        Log[i] = Log[i >> 1] + 1;
    for (int i = 0; i < 20; ++i)
    {
        b[n][i] = b[n + 1][i] = n + 1;
        c[n][i] = c[n + 1][i] = limit;
    }
    for (int i = n - 1; i >= 0; --i)
    {
        int maxx = a[i][0];
        ll qwq = 0;
        sum = f[a[i][0]];
        for (int j = 1; j < 26; ++j)
        {
            if (f[a[i][j]] > f[maxx])
            {
                maxx = a[i][j];
                qwq = sum;
            }
            check(sum += f[a[i][j]]);
        }
        b[i][0] = maxx, c[i][0] = qwq + 1;
        for (int j = 0; j < Log[n]; ++j)
        {
            b[i][j + 1] = b[b[i][j]][j];
            check(c[i][j + 1] = c[i][j] + c[b[i][j]][j]);
        }
    }
    read(m);
    while (m--)
    {
        ll k;
        int pwp;
        read(k, pwp);
        if (k > f[0])
            write("-1\n");
        else
        {
            ++k;
            int u = 0;
            tot = 0;
            while (k)
            {
                ++tot;
                p[tot] = u;
                int len = 1;
                for (int i = Log[n - u]; i >= 0; --i)
                {
                    if (k > c[u][i] && k <= c[u][i] + f[b[u][i]])
                    {
                        k -= c[u][i];
                        u = b[u][i];
                        len += (1 << i);
                    }
                }
                q[tot] = len;
                --k;
                if (!k)
                    break;
                for (int i = 0; i < 26; ++i)
                {
                    if (k > f[a[u][i]])
                        k -= f[a[u][i]];
                    else
                    {
                        u = a[u][i];
                        break;
                    }
                }
            }
            p[1] = b[p[1]][0];
            --q[1];
            for (int i = tot; i >= 1 && pwp; --i)
            {
                if (pwp > q[i])
                {
                    pwp -= q[i];
                    u = p[i];
                    while (q[i]--)
                    {
                        e[++cnt] = str[u];
                        u = b[u][0];
                    }
                    while (cnt)
                        st[++top] = e[cnt--];
                }
                else
                {
                    int other = q[i] - pwp;
                    u = p[i];
                    while (other)
                        u = b[u][Log[other]], other ^= 1 << Log[other];
                    while (pwp--)
                    {
                        e[++cnt] = str[u];
                        u = b[u][0];
                    }
                    while (cnt)
                        st[++top] = e[cnt--];
                    break;
                }
            }
            while (top)
                write(st[top--]);
            write('\n');
        }
    }
#ifdef FAST_OUT
    IO::OUTPUT::flush();
#endif
    return 0;
}