/**
 *    unicode: UTF-8
 *    name:    #1409. 【五一省选集训day4】Grid Game
 *    author:  whitepaperdog (蒟蒻wjr)
 *    located: Changle District, Fuzhou City, Fujian Province, China
 *    created: 2023.01.14 周六 15:01:25 (Asia/Shanghai)
 **/
#include <cstdio>
#include <random>
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
constexpr int N = 2005;
int n, m, k;
bool a[N][N];
ull b[N], c[N][N], d[N][N];
int e[N][N];
struct node
{
    int x, y;
    node(int _x = 0, int _y = 0) : x(_x), y(_y) {}
    inline int calc() const
    {
        return max(x, y);
    }
    inline node operator-(const node &rhs) const
    {
        return node(x - rhs.x, y - rhs.y);
    }
    inline bool operator<(const node &rhs) const
    {
        return calc() < rhs.calc();
    }
} f[N][N];
inline int calc(int x1, int y1, int x2, int y2)
{
    return e[x2][y2] - e[x1 - 1][y2] - e[x2][y1 - 1] + e[x1 - 1][y1 - 1];
}
signed main()
{
    read(n, m, k);
    mt19937_64 rnd((random_device())());
    uniform_int_distribution<ull> ranges(0);
    for (int i = 1; i <= n; ++i)
    {
        static char str[N];
        scanf("%s", str + 1);
        for (int j = 1; j <= m; ++j)
            a[i][j] = (str[j] == '1');
    }
    for (int i = 1; i <= n || i <= m; ++i)
        b[i] = ranges(rnd);
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= m; ++j)
        {
            c[i][j] = c[i - 1][j];
            d[i][j] = d[i][j - 1];
            e[i][j] = e[i - 1][j] + e[i][j - 1] - e[i - 1][j - 1];
            if (a[i][j])
            {
                c[i][j] ^= b[i];
                d[i][j] ^= b[j];
                ++e[i][j];
            }
        }
    for (int i = 1; i <= n; ++i)
        f[i][m + 1] = node(i, m + 1);
    for (int i = 1; i <= m; ++i)
        f[n + 1][i] = node(n + 1, i);
    for (int i = n; i >= 1; --i)
        for (int j = m; j >= 1; --j)
            if (a[i][j])
                f[i][j] = (f[i][j + 1] - node(i, j) < f[i + 1][j] - node(i, j)) ? f[i][j + 1] : f[i + 1][j];
            else
                f[i][j] = node(i, j);
    auto check = [](int x, int y, int l)
    {
        if (l == 1)
            return true;
        if (calc(x + 1, y + 1, x + l - 1, y + l - 1) == (l - 1) * (l - 1))
            return calc(x, y + 1, x, y + l - 1) == l - 1 || calc(x + 1, y, x + l - 1, y) == l - 1;
        else
        {
            int px = f[x + 1][y + 1].x, py = f[x + 1][y + 1].y;
            auto solvec = [l](int x1, int y1, int x2, int y2)
            {
                return (c[x1 - 1][y1] ^ c[x2][y1]) == (c[x1 - 1][y2] ^ c[x2][y2]) || calc(x1, y1, x2, y1) == l;
            };
            auto solved = [l](int x1, int y1, int x2, int y2)
            {
                return (d[x1][y1 - 1] ^ d[x1][y2]) == (d[x2][y1 - 1] ^ d[x2][y2]) || calc(x1, y1, x1, y2) == l;
            };
            return solvec(x, y, x + l - 1, py) && solved(x, y, px, y + l - 1);
        }
    };
    auto solvemin = [](int x, int y, int l)
    {
        if (calc(x, y, x + l - 1, y + l - 1) == l * l)
            return l;
        int px = f[x][y].x, py = f[x][y].y;
        return min(calc(px, y, px, y + l - 1), calc(x, py, x + l - 1, py));
    };
    auto solvemax = [](int x, int y, int l)
    {
        if (calc(x, y, x + l - 1, y + l - 1) == l * l)
            return l;
        int px = f[x][y].x, py = f[x][y].y;
        return max(calc(px, y, px, y + l - 1), calc(x, py, x + l - 1, py));
    };
    int res = 0;
    for (int stx = 1, sty = m; sty; stx == n ? --sty : ++stx)
    {
        int x = stx, y = sty, l = 1, L = 1, R = 1;
        while (x > 1 && y > 1)
        {
            --x, --y, ++l, ++L, ++R;
            while (!check(x, y, l))
                --l;
            ckmin(L, l), ckmin(R, l);
            while (L > 1 && calc(x, y, x + L - 1, y + L - 1) != L * L && solvemin(x, y, L) >= k)
                --L;
            while (R > 1 && calc(x, y, x + R - 1, y + R - 1) != R * R && solvemax(x, y, R) > k)
                --R;
            if (calc(x, y, x + R - 1, y + R - 1) != R * R && L < R)
                res += R - L;
        }
    }
    for (int i = n - k + 1; i >= 1; --i)
        for (int j = m - k + 1; j >= 1; --j)
            res += (calc(i, j, i + k - 1, j + k - 1) == k * k);
    write(res, '\n');
#ifdef FAST_OUT
    IO::OUTPUT::flush();
#endif
    return 0;
}