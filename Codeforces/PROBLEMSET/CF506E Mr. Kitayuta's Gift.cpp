/**
 *    name:     CF506E Mr. Kitayuta's Gift
 *    author:   whitepaperdog (蒟蒻wjr)
 *    located:  Xuanwu District, Nanjing City, Jiangsu Province, China
 *    created:  2023.02.28 周二 22:17:24 (Asia/Shanghai)
 *    unicode:  UTF-8
 *    standard: c++23
 **/
#include <cstdio>
#include <cstring>
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
using IO::INPUT::read;
using IO::OUTPUT::write;
using namespace std;
constexpr int N = 205;
constexpr int M = 305;
constexpr int mod = 10007;
inline void add(int &x, int y)
{
    x += y;
    if (x >= mod)
        x -= mod;
}
inline void del(int &x, int y)
{
    x -= y;
    if (x < 0)
        x += mod;
}
int n, m, limit;
char str[N];
inline int calc(int x) { return (x + 1) / 2; }
int dp[N][N][N];
bool vis[N][N][N];
inline int dfs(int i, int j, int k)
{
    if (i < 0)
        return 0;
    if (j == 1 && k == m)
        return !i;
    if (vis[i][j][k])
        return dp[i][j][k];
    vis[i][j][k] = true;
    int &res = dp[i][j][k];
    if (j > 1 && k < m && str[j - 1] == str[k + 1])
        add(res, dfs(i, j - 1, k + 1));
    if (j > 1 && str[j - 1] != str[k])
        add(res, dfs(i - 1, j - 1, k));
    if (k < m && str[j] != str[k + 1])
        add(res, dfs(i - 1, j, k + 1));
    return res;
}
int f[M], g[M][M];
int _f[M], _g[M][M];
int a[M], b[M][M];
inline void quickpow(int power)
{
    while (power)
    {
        if (power & 1)
        {
            for (int i = 1; i <= limit; ++i)
                for (int j = 1; j <= limit; ++j)
                    a[i] = (a[i] + f[j] * g[j][i]) % mod;
            memcpy(f, a, sizeof(f));
            memset(a, 0, sizeof(a));
        }
        for (int i = 1; i <= limit; ++i)
            for (int k = 1; k <= limit; ++k)
                for (int j = 1; j <= limit; ++j)
                    b[i][j] = (b[i][j] + g[i][k] * g[k][j]) % mod;
        memcpy(g, b, sizeof(g));
        memset(b, 0, sizeof(b));
        power >>= 1;
    }
}
signed main()
{
#ifdef PAPERDOG
    freopen("project.in", "r", stdin);
    freopen("project.out", "w", stdout);
#endif
    m = read(str + 1);
    read(n);
    limit = m + calc(m);
    for (int i = 0; i < m; ++i)
    {
        int res = 0;
        for (int j = 1; j <= m; ++j)
            add(res, dfs(i, j, j));
        for (int j = 1; j < m; ++j)
            if (str[j] == str[j + 1])
                add(res, dfs(i, j, j + 1));
        if (!i)
        {
            f[m] = res;
            g[limit][limit] = 26;
            for (int j = m; j < limit; ++j)
                g[j][j + 1] = 1, g[j][j] = 25;
        }
        else
        {
            g[i][limit - calc(m - i)] = res;
            g[i][i] = 24;
            if (i > 1)
                g[i - 1][i] = 1;
            else
                f[i] = 1;
        }
    }
    memcpy(_f, f, sizeof(f));
    memcpy(_g, g, sizeof(g));
    quickpow(calc(n + m));
    int ans = f[limit];
    if ((n + m) % 2 == 0)
        write(ans, '\n');
    else
    {
        memcpy(f, _f, sizeof(f));
        memcpy(g, _g, sizeof(g));
        for (int i = 0; i < m; ++i)
        {
            int res = 0;
            for (int j = 1; j < m; ++j)
                if (str[j] == str[j + 1])
                    add(res, dfs(i, j, j + 1));
            if (i)
                g[i][limit - calc(m - i)] = res;
            else
            {
                f[m] = res;
                g[limit][limit] = 0;
            }
        }
        quickpow(calc(n + m));
        del(ans, f[limit]);
        write(ans, '\n');
    }
#ifdef FAST_OUT
    IO::OUTPUT::flush();
#endif
    return 0;
}