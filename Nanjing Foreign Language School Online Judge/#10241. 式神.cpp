/**
 *    name:     ran
 *    author:   whitepaperdog (蒟蒻wjr)
 *    located:  Xuanwu District, Nanjing City, Jiangsu Province, China
 *    created:  2023.03.03 周五 08:19:26 (Asia/Shanghai)
 *    unicode:  UTF-8
 *    standard: c++23
 **/
#include <algorithm>
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
using IO::INPUT::read;
using IO::OUTPUT::write;
using namespace std;
constexpr int N = 5e5 + 5;
int n, q, opt;
struct Tree
{
    int size, leaf;
    ll sumx, sumxx;
    ll sumy, sumyy;
    ll sumxy;
    ll leafx, leafxx;
} tree[N * 4];
#define lc (rt << 1)
#define rc (rt << 1 | 1)
inline void build(int rt, int l, int r)
{
    if (l == r)
    {
        tree[rt].leaf = 1;
        tree[rt].leafx = l;
        tree[rt].leafxx = (ll)l * r;
        return;
    }
    int mid = (l + r) >> 1;
    build(lc, l, mid);
    build(rc, mid + 1, r);
    tree[rt].size = tree[lc].size + tree[rc].size + 1;

    tree[rt].sumx = tree[lc].sumx + tree[rc].sumx + l;
    tree[rt].sumxx = tree[lc].sumxx + tree[rc].sumxx + (ll)l * l;

    tree[rt].sumy = tree[lc].sumy + tree[rc].sumy + r;
    tree[rt].sumyy = tree[lc].sumyy + tree[rc].sumyy + (ll)r * r;

    tree[rt].sumxy = tree[lc].sumxy + tree[rc].sumxy + (ll)l * r;

    tree[rt].leaf = tree[lc].leaf + tree[rc].leaf;
    tree[rt].leafx = tree[lc].leafx + tree[rc].leafx;
    tree[rt].leafxx = tree[lc].leafxx + tree[rc].leafxx;
}
inline ll query(int rt, int l, int r, int x, int y)
{
    if (r < x || l > y)
        return 0;
    if (x <= l && r <= y)
    {
        ll res = 0;
        res += (ll)(y - x + 2) * (y - x + 1) / 2 * tree[rt].size;
        res -= (tree[rt].sumxx - (ll)(2 * x - 1) * tree[rt].sumx + (ll)x * (x - 1) * tree[rt].size) / 2;
        res -= (tree[rt].sumyy - (ll)(2 * y + 1) * tree[rt].sumy + (ll)y * (y + 1) * tree[rt].size) / 2;
        res -= 2 * (-tree[rt].sumxy + tree[rt].sumx * (y + 1) + tree[rt].sumy * (x - 1) - (ll)(x - 1) * (y + 1) * tree[rt].size);
        res += -tree[rt].leafxx + tree[rt].leafx * (x + y) - (ll)(x - 1) * (y + 1) * tree[rt].leaf;
        return res;
    }
    int mid = (l + r) >> 1;
    ll res = query(lc, l, mid, x, y) + query(rc, mid + 1, r, x, y);
    res += (ll)(y - x + 2) * (y - x + 1) / 2;
    if (x < l)
        res -= (ll)(l - x) * (l - x + 1) / 2;
    if (r < y)
        res -= (ll)(y - r) * (y - r + 1) / 2;
    return res;
}
signed main()
{
#ifdef PAPERDOG
    freopen("project.in", "r", stdin);
    freopen("project.out", "w", stdout);
#else
    freopen("ran.in", "r", stdin);
    freopen("ran.out", "w", stdout);
#endif
    read(n, q, opt);
    build(1, 1, n);
    ll lastans = 0;
    for (int i = 1; i <= q; ++i)
    {
        int l, r;
        read(l, r);
        l = (int)((l ^ (lastans * opt)) % n + 1);
        r = (int)((r ^ (lastans * opt)) % n + 1);
        if (l > r)
            swap(l, r);
        write(lastans = query(1, 1, n, l, r), '\n');
    }
#ifdef FAST_OUT
    IO::OUTPUT::flush();
#endif
    return 0;
}