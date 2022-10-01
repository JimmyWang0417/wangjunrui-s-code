/**
 *    unicode: UTF-8
 *    name:
 *    author:  wangjunrui (蒟蒻wjr)
 *    located: Changle District, Fuzhou City, Fujian Province, China
 *    created: 2022.09.26 周一 12:15:29 (Asia/Shanghai)
 **/
#include <cstdio>
#include <set>
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
using IO::INPUT::read;
using IO::OUTPUT::write;
using namespace std;
constexpr int N = 2e5 + 5;
int n, m;
vector<int> g[N];
struct node
{
    int l, r;
    int x, y;
    node(int _l = 0, int _r = 0, int _x = 0, int _y = 0) : l(_l), r(_r), x(_x), y(_y) {}
    inline bool operator<(const node &rhs) const
    {
        return l < rhs.l;
    }
};
set<node> se;
int answer;
inline void update0(int x)
{
    auto pos = se.lower_bound(node(x, x));
    if (pos == se.end() || pos->l > x)
        --pos;
    auto val = *pos;
    se.erase(pos);
    answer -= (val.r - val.l + 1) / 2;
    if (val.l < x)
    {
        answer += (x - val.l) / 2;
        se.emplace(val.l, x - 1, val.x, -1);
    }
    if (val.r > x)
    {
        answer += (val.r - x) / 2;
        se.emplace(x + 1, val.r, -1, val.y);
    }
    se.emplace(x, x);
}
inline void update1(int x)
{
    auto pos = se.lower_bound(node(x, x));
    if (pos == se.end() || pos->l > x)
        --pos;
    auto val = *pos;
    se.erase(pos);
    answer -= (val.r - val.l + 1) / 2;
    val.x = val.y = -1;
    if (val.l == x && val.l > 1)
    {
        auto pre = se.lower_bound(node(x, x));
        --pre;
        if (pre->y == 1)
        {
            val.l = pre->l;
            val.x = pre->x;
            answer -= (pre->r - pre->l + 1) / 2;
            se.erase(pre);
        }
    }

    if (val.r == x && val.r < n)
    {
        auto suf = se.lower_bound(node(x, x));
        if (suf->x == 1)
        {
            val.r = suf->r;
            val.y = suf->y;
            answer -= (suf->r - suf->l + 1) / 2;
            se.erase(suf);
        }
    }
    answer += (val.r - val.l + 1) / 2;
    se.insert(val);
}
signed main()
{
    freopen("trans.in", "r", stdin);
    freopen("trans.out", "w", stdout);
    read(n, m);
    for (int i = 1; i <= n; ++i)
    {
        int x;
        read(x);
        g[x].push_back(i);
    }
    for (int i = 1; i <= n; ++i)
        se.emplace(i, i, 1, 1);
    for (int i = 1; i <= m; ++i)
    {
        for (auto j : g[i - 1])
            update1(j);
        for (auto j : g[i])
            update0(j);
        auto l = se.begin(), r = prev(se.end());
        int res = answer;
        if (l != r && ((l -> x == -1 && r -> y == 1) || (l -> x == 1 && r -> y == -1)))
        {
            res -= (l -> r - l -> l + 1) / 2;
            res -= (r -> r - r -> l + 1) / 2;
            res += (l -> r - l -> l + 1 + r -> r - r -> l + 1) / 2;
        }
        if (g[i].empty())
            write("-1 ");
        else
            write(n - (int)g[i].size() + res, ' ');
    }
    write('\n');
#ifdef FAST_OUT
    flush();
#endif
    return 0;
}
