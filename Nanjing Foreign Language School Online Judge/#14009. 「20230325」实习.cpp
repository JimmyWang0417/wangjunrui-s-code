/**
 *    name:     A. 实习
 *    author:   whitepaperdog (蒟蒻wjr)
 *    located:  Xuanwu District, Nanjing City, Jiangsu Province, China
 *    created:  2023.03.25 周六 08:22:23 (Asia/Shanghai)
 *    unicode:  UTF-8
 *    standard: c++23
 **/
#include <algorithm>
#include <cstdio>
typedef long long ll;
typedef unsigned long long ull;
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
namespace MODINT
{
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
        constexpr inline bool operator==(const modint &rhs) const
        {
            return x == rhs.x;
        }
        constexpr inline bool operator!=(const modint &rhs) const
        {
            return x != rhs.x;
        }
        constexpr inline int &data()
        {
            return x;
        }
    };
}
using IO::INPUT::read;
using IO::OUTPUT::write;
using namespace std;
constexpr int N = 1e5 + 5;
constexpr int INF = 0x7fffffff;
constexpr int dx[4] = {-1, 1, -1, 1};
constexpr int dy[4] = {-1, -1, 1, 1};
int n, m;
int S, T;
struct Edge
{
    int next, to, flow, cap;
} edge[N];
int head[N], num_edge = 1;
inline void add_edge(int from, int to, int cap, bool flag = true)
{
    edge[++num_edge].next = head[from];
    edge[num_edge].to = to;
    edge[num_edge].flow = 0;
    edge[num_edge].cap = cap;
    head[from] = num_edge;
    if (flag)
        add_edge(to, from, 0, false);
}
struct
{
    int q[N], head, tail;
    inline void init()
    {
        head = 1;
        tail = 0;
    }
    inline void push(int x)
    {
        q[++tail] = x;
    }
    inline void pop()
    {
        ++head;
    }
    inline int front()
    {
        return q[head];
    }
    inline bool empty()
    {
        return head > tail;
    }
} que;
int cur[N], dis[N];
bool exist[N];
inline bool bfs()
{
    for (int i = S; i <= T; ++i)
    {
        dis[i] = 0;
        exist[i] = false;
        cur[i] = head[i];
    }
    que.init();
    que.push(S);
    dis[S] = 1;
    while (!que.empty())
    {
        int u = que.front();
        que.pop();
        for (int i = head[u]; i; i = edge[i].next)
        {
            int v = edge[i].to;
            if (!dis[v] && edge[i].cap > edge[i].flow)
            {
                dis[v] = dis[u] + 1;
                que.push(v);
            }
        }
    }
    return dis[T];
}
inline int dinic(int u, int flow)
{
    if (u == T)
        return flow;
    int res = 0;
    exist[u] = true;
    for (int &i = cur[u]; i; i = edge[i].next)
    {
        int v = edge[i].to;
        if (!exist[v] && edge[i].cap > edge[i].flow && dis[v] == dis[u] + 1)
        {
            int f = dinic(v, min(flow, edge[i].cap - edge[i].flow));
            if (f)
            {
                res += f;
                flow -= f;
                edge[i].flow += f;
                edge[i ^ 1].flow -= f;
                if (!flow)
                {
                    exist[u] = false;
                    break;
                }
            }
        }
    }
    return res;
}
char str[105][105];
inline int maxflow()
{
    int res = 0;
    while (bfs())
        res += dinic(S, 0x7fffffff);
    return res;
}
int where1[105][105], where2[105][105];
inline void _main()
{
    read(n, m);
    for (int i = 1; i <= n; ++i)
        read(str[i] + 1);
    int tot = 0;
    S = 0, T = n + m + 1;
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= m; ++j)
            if (str[i][j] >= '1' && str[i][j] <= '4')
            {
                int d = str[i][j] - '1';
                int x = i + dx[d], y = j;
                if (x < 1 || x > n)
                {
                    write("-1\n");
                    return;
                }
                if (str[x][y] >= '1' && str[x][y] <= '4' && x + dx[str[x][y] - '1'] != i)
                {
                    write("-1\n");
                    return;
                }
                x = i, y = j + dy[d];
                if (y < 1 || y > m)
                {
                    write("-1\n");
                    return;
                }
                if (str[x][y] >= '1' && str[x][y] <= '4' && y + dy[str[x][y] - '1'] != j)
                {
                    write("-1\n");
                    return;
                }
            }
    for (int i = 1; i <= n; ++i)
    {
        for (int l = 1, r = l + 1; l <= m; l = r++)
            if (str[i][l] == 'o' || str[i][l] == '.')
            {
                while (r <= m && (str[i][r] == 'o' || str[i][r] == '.'))
                    ++r;
                int len = r - l;
                if (str[i][l - 1] == 'x' || str[i][r] == 'x')
                    continue;
                if (str[i][r] == '1' || str[i][r] == '2')
                    --len;
                if (str[i][l - 1] == '3' || str[i][l - 1] == '4')
                    --len;
                if (len & 1)
                {
                    bool flag = true;
                    for (int j = l; j < r; ++j)
                        if (str[i][j] == '.')
                        {
                            flag = false;
                            break;
                        }
                    if (flag)
                    {
                        write("-1\n");
                        return;
                    }
                    ++tot;
                    for (int j = l; j < r; ++j)
                        where1[i][j] = tot;
                    add_edge(S, tot, 1);
                }
            }
    }
    int las = tot;
    for (int i = 1; i <= m; ++i)
    {
        for (int l = 1, r = l + 1; l <= n; l = r++)
        {
            if (str[l][i] == 'o' || str[l][i] == '.')
            {
                while (r <= n && (str[r][i] == 'o' || str[r][i] == '.'))
                    ++r;
                int len = r - l;
                if (str[l - 1][i] == 'x' || str[r][i] == 'x')
                    continue;
                if (str[r][i] == '1' || str[r][i] == '3')
                    --len;
                if (str[l - 1][i] == '2' || str[l - 1][i] == '4')
                    --len;
                if (len & 1)
                {
                    bool flag = true;
                    for (int j = l; j < r; ++j)
                        if (str[j][i] == '.')
                        {
                            flag = false;
                            break;
                        }
                    if (flag)
                    {
                        write("-1\n");
                        return;
                    }
                    ++tot;
                    for (int j = l; j < r; ++j)
                        where2[j][i] = tot;
                }
            }
        }
    }
    int sum = -tot;
    T = ++tot;
    for (int i = las + 1; i < T; ++i)
        add_edge(i, T, 1);
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= m; ++j)
        {
            if (str[i][j] == 'x')
                continue;
            ++sum;
            if (str[i][j] == '.' && where1[i][j] && where2[i][j])
                add_edge(where1[i][j], where2[i][j], 1);
        }
    write(sum + maxflow(), '\n');
}
signed main()
{
#ifdef PAPERDOG
    freopen("project.in", "r", stdin);
    freopen("project.out", "w", stdout);
#else
    freopen("practice.in", "r", stdin);
    freopen("practice.out", "w", stdout);
#endif
    _main();
#ifdef FAST_OUT
    IO::OUTPUT::flush();
#endif
    return 0;
}