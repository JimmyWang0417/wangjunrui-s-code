/**
 *    unicode: UTF-8
 *    name:    P3760 [TJOI2017] 异或和
 *    author:  wangjunrui (蒟蒻wjr)
 *    located: Changle District, Fuzhou City, Fujian Province, China
 *    created: 2022.08.31 周三 14:34:45 (Asia/Shanghai)
 **/
#include <algorithm>
#include <cstdio>
#include <cstring>
#define ll long long
#define lll __int128
#define ull unsigned ll
#define lowbit(_x) (_x & (-_x))

// #define FAST_IO

#ifndef WIN32
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
#ifdef getchar
#undef getchar
#endif
#define getchar() (_now == _end && (_end = (_now = _buf) + fread(_buf, 1, FAST_OUT_BUFFER_SIZE, stdin), _now == _end) ? EOF : *_now++)
#else
#ifndef WIN32
#define getchar getchar_unlocked
#endif
#endif
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
#ifdef putchar
#undef putchar
#endif
#define putchar(c) (_now - _buf == FAST_OUT_BUFFER_SIZE ? flush(), *_now++ = c : *_now++ = c)
#else
#ifndef WIN32
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
constexpr int N = 1e5 + 5;
constexpr int M = (1 << (__lg((int)1e6 - 1) + 1)) + 5;
int n, m, a[N];
struct tree_array
{
    bool c[M];
    inline void update(int pos)
    {
        for (int i = pos + 1; i <= m; i += lowbit(i))
            c[i] ^= 1;
    }
    inline bool query(int pos)
    {
        bool res = 0;
        for (int i = pos + 1; i; i -= lowbit(i))
            res ^= c[i];
        return res;
    }
    inline void clear()
    {
        // memset(c + 1, 0, sizeof(int) * m);
        memset(c, 0, sizeof(c));
    }
} tree0, tree1;
signed main()
{
    read(n);
    for (int i = 1; i <= n; ++i)
    {
        read(a[i]);
        a[i] += a[i - 1];
    }
    int ans = 0;
    for (int kase = 0; kase < 20; ++kase)
    {
        m = 1 << kase;
        tree0.update(a[0]);
        bool res = 0;
        for (int i = 1; i <= n; ++i)
        {
            int S = a[i] & (m - 1);
            if (!((a[i] >> kase) & 1))
            {
                res ^= tree0.query(m - 1) ^ tree0.query(S) ^ tree1.query(S); 
                tree0.update(S);
            }
            else
            {
                res ^= tree0.query(S) ^ tree1.query(m - 1) ^ tree1.query(S);
                tree1.update(S);
            }
        }
        ans |= res << kase;
        tree0.clear(), tree1.clear();
    }
    printf("%d\n", ans);
#ifdef FAST_OUT
    flush();
#endif
    return 0;
}