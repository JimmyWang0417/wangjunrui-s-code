/**
 *    unicode: UTF-8
 *    name:    magic
 *    author:  wangjunrui (蒟蒻wjr)
 *    located: Changle District, Fuzhou City, Fujian Province, China
 *    created: 2022.09.10 周六 20:23:35 (Asia/Shanghai)
 **/
#include <bits/stl_pair.h>
#include <cstdio>
#include <ext/pb_ds/assoc_container.hpp>
#include <list>
#include <queue>
#include <tuple>
#include <unordered_map>
#define ll long long
#define lll __int128
#define ull unsigned ll
#define lowbit(_x) (_x & (-_x))

//#define FAST_IO

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
#undef getchar
#define getchar() (_now == _end && (_end = (_now = _buf) + fread(_buf, 1, FAST_OUT_BUFFER_SIZE, stdin), _now == _end) ? EOF : *_now++)
#else
#ifndef WIN32
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
#ifndef WIN32
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
#ifdef FAST_OUT
#undef putchar
#ifndef WIN32
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
constexpr int N = 1e3 + 5;
int n;
namespace move
{
    typedef pair<int, int> node;
    typedef tuple<node, node, node> point;
    inline int calc(node x)
    {
        return x.first * n + x.second;
    }
    inline void print(node x)
    {
        write(x.first, ' ', x.second, '\n');
    }
    inline int calc(point x)
    {
        return calc(get<0>(x)) * n * n * n * n + calc(get<1>(x)) * n * n + calc(get<2>(x));
    }
    inline node down(node x)
    {
        return node((x.first + 1) % n, x.second);
    }
    inline node right(node x)
    {
        return node(x.first, (x.second + 1) % n);
    }
    inline node swap(node x)
    {
        return node(x.second, x.first);
    }
    inline node rotate90(node x)
    {
        return node(x.second, n - x.first - 1);
    }
    inline node rotate180(node x)
    {
        return node(n - x.first - 1, n - x.second - 1);
    }
    inline node rotate270(node x)
    {
        return node(n - x.second - 1, x.first);
    }
    inline node linereverse(node x)
    {
        return node(x.first, n - x.second - 1);
    }
    inline node columnreverse(node x)
    {
        return node(n - x.first - 1, x.second);
    }
}
using namespace move;
signed main()
{
#ifdef ONLINE_JUDGE
    freopen("magic.in", "r", stdin);
    freopen("magic.out", "w", stdout);
#endif
    queue<point, list<point>> q;
    __gnu_pbds::cc_hash_table<ll, int> dis;
    int T = 1;
    read(T);
    while (T--)
    {
        read(n);
        node T1, T2, T3;
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < n; ++j)
            {
                int x;
                read(x);
                if (x == 1)
                    T1 = node(i, j);
                else if (x == 2)
                    T2 = node(i, j);
                else if (x == n + 1)
                    T3 = node(i, j);
            }
        q.emplace(T1, T2, T3);
        dis[calc(point(T1, T2, T3))] = 1;
        while (!q.empty())
        {
            if (q.front() == point(node(0, 0), node(0, 1), node(1, 0)))
            {
            	write(dis[calc(q.front())] - 1, '\n');
                break;
            }
            auto [x, y, z] = q.front();
            auto u = calc(point(x, y, z));
            auto disu = dis[u];

            q.pop();

            auto dx = down(x), dy = down(y), dz = down(z);
            auto v = calc(point(dx, dy, dz));
            if (!dis[v])
            {
                dis[v] = disu + 1;
                q.emplace(dx, dy, dz);
            }

            dx = right(x), dy = right(y), dz = right(z);
            v = calc(point(dx, dy, dz));
            if (!dis[v])
            {
                dis[v] = disu + 1;
                q.emplace(dx, dy, dz);
            }

            dx = swap(x), dy = swap(y), dz = swap(z);
            v = calc(point(dx, dy, dz));
            if (!dis[v])
            {
                dis[v] = disu + 1;
                q.emplace(dx, dy, dz);
            }

            dx = rotate90(x), dy = rotate90(y), dz = rotate90(z);
            v = calc(point(dx, dy, dz));
            if (!dis[v])
            {
                dis[v] = disu + 1;
                q.emplace(dx, dy, dz);
            }

            dx = linereverse(x), dy = linereverse(y), dz = linereverse(z);
            v = calc(point(dx, dy, dz));
            if (!dis[v])
            {
                dis[v] = disu + 1;
                q.emplace(dx, dy, dz);
            }

            dx = columnreverse(x), dy = columnreverse(y), dz = columnreverse(z);
            v = calc(point(dx, dy, dz));
            if (!dis[v])
            {
                dis[v] = disu + 1;
                q.emplace(dx, dy, dz);
            }
        }
        while (!q.empty())
            q.pop();
        dis.clear();
    }
#ifdef FAST_OUT
    flush();
#endif
    return 0;
}
