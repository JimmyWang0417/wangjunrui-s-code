/**
 *    unicode: UTF-8
 *    name:    after
 *    author:  wangjunrui (蒟蒻wjr)
 *    located: Changle District, Fuzhou City, Fujian Province, China
 *    created: 2022.09.11 周日 10:26:02 (Asia/Shanghai)
 **/
#include <algorithm>
#include <cstdio>
#include <cstring>
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
using namespace IO::INPUT;
using namespace IO::OUTPUT;
using namespace std;
constexpr int N = 5005;
constexpr int mod = 998244353;
template <typename T>
inline void add(T &x, T y)
{
    x += y;
    if (x >= mod)
        x -= mod;
}
int n, a[N], b[N];
int buf[2][N];
int st[N], top;
int L[N], R[N];
signed main()
{
#ifdef ONLINE_JUDGE
    freopen("after.in", "r", stdin);
    freopen("after.out", "w", stdout);
#endif
    read(n);
    for (int i = 1; i <= n; ++i)
    {
        read(a[i]);
        b[a[i]] = i;
    }
    for (int i = 1; i <= n; ++i)
    {
        while (top && a[st[top]] < a[i])
            --top;
        L[i] = st[top] + 1;
        st[++top] = i;
    }
    a[st[top = 0] = n + 1] = 0x7fffffff;
    for (int i = n; i >= 1; --i)
    {
        while (top && a[st[top]] < a[i])
            --top;
        R[i] = st[top] - 1;
        st[++top] = i;
    }
    auto f = buf[0], g = buf[1];
    for (int i = 1; i <= n; ++i)
        if (L[b[i]] == 1)
            f[i] = 1;
    for (int i = 2; i <= n; ++i)
    {
        swap(f, g);
        // memset(f, 0, sizeof(buf[0]));
        // for (int j = 1; j <= n; ++j)
        //     if (g[j])
        //         for (int k = 1; k <= n; ++k)
        //             if (L[b[k]] <= i && i <= R[b[k]])
        //             {
        //                 if (j < k && b[k] < i)
        //                     continue;
        //                 if (j > k && b[j] > i)
        //                     continue;
        //                 add(f[k], g[j]);
        //             }
        for (int j = 1; j <= n; ++j)
            f[j] = (L[b[j]] <= i && i <= R[b[j]] ? g[j] : 0);
        for (int j = 1, now = 0; j <= n; add(now, g[j++]))
            if (L[b[j]] <= i && i <= R[b[j]] && b[j] >= i)
                add(f[j], now);
        for (int j = n, now = 0; j >= 1; j--)
        {
            if (L[b[j]] <= i && i <= R[b[j]])
                add(f[j], now);
            if (b[j] <= i)
                add(now, g[j]);
        }
    }
    int res = 0;
    for (int i = 1; i <= n; ++i)
        if (f[i])
            add(res, f[i]);
    printf("%d\n", res);
#ifdef FAST_OUT
    flush();
#endif
    return 0;
}
