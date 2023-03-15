/**
 *    name:     C. 刷墙
 *    author:   whitepaperdog (蒟蒻wjr)
 *    located:  Xuanwu District, Nanjing City, Jiangsu Province, China
 *    created:  2023.03.14 周二 20:04:10 (Asia/Shanghai)
 *    unicode:  UTF-8
 *    standard: c++23
 **/
#include <algorithm>
#include <cstdio>
#include <cstring>
#include <tuple>
#include <vector>
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
using IO::INPUT::read;
using IO::OUTPUT::write;
using namespace std;
constexpr int N = 1e6 + 5;
int n[2], k, type;
int fa[N];
inline int find(int x)
{
    return !fa[x] ? x : fa[x] = find(fa[x]);
}
tuple<int, int, int, int> que[N];
int a[2][N], c[2][N];
namespace subtask1
{
    int p[2][N];
    int mp[N];
    bool exist[N];
    inline ll main()
    {
        for (int o = 0; o < 2; ++o)
        {
            for (int i = 1; i <= n[o]; ++i)
                p[o][i] = i;
            sort(p[o] + 1, p[o] + 1 + n[o], [o](int x, int y)
                 { return a[o][x] > a[o][y]; });
        }
        ll ans = 0;
        for (int o = 0; o < 2; ++o)
        {
            for (int i = 1, j = 1, cnt = n[o ^ 1] - 1; i <= n[o]; ++i)
            {
                int x = p[o][i];
                while (j <= n[o ^ 1] && a[o ^ 1][p[o ^ 1][j]] > a[o][x])
                {
                    int y = p[o ^ 1][j];
                    if (y > 1)
                    {
                        if (exist[y - 1])
                        {
                            --mp[c[o ^ 1][y - 1]];
                            cnt += c[o ^ 1][y] == c[o ^ 1][y - 1];
                        }
                        else
                        {
                            ++mp[c[o ^ 1][y]];
                            --cnt;
                        }
                    }
                    if (y < n[o ^ 1])
                    {
                        if (exist[y + 1])
                        {
                            --mp[c[o ^ 1][y + 1]];
                            cnt += c[o ^ 1][y] == c[o ^ 1][y + 1];
                        }
                        else
                        {
                            ++mp[c[o ^ 1][y]];
                            --cnt;
                        }
                    }
                    exist[y] = true;
                    ++j;
                }
                ans += cnt + mp[c[o][x]];
            }
            memset(mp, 0, sizeof(mp));
            memset(exist, 0, sizeof(exist));
        }
        return ans;
    }
}
namespace subtask2
{
    struct
    {
        int limit;
        int c[N];
        inline void init(int _n)
        {
            limit = _n;
        }
        inline void add(int pos)
        {
            for (int i = pos; i <= limit; i += lowbit(i))
                ++c[i];
        }
        inline int query(int pos)
        {
            int res = 0;
            for (int i = pos; i; i -= lowbit(i))
                res += c[i];
            return res;
        }
        inline int query(int l, int r)
        {
            return query(r) - query(l - 1);
        }
        inline void clear(int pos)
        {
            for (int i = pos; i <= limit && c[i]; i += lowbit(i))
                c[i] = 0;
        }
    } tree;
    struct node
    {
        int opt, x, l, r;
        node(int _opt = 0, int _x = 0, int _l = 0, int _r = 0) : opt(_opt), x(_x), l(_l), r(_r) {}
        inline bool operator<(const node &rhs) const
        {
            return x < rhs.x;
        }
    };
    inline ll solve(vector<node> &g)
    {
        ll res = 0;
        sort(g.begin(), g.end());
        for (auto [opt, x, l, r] : g)
        {
            if (opt == 0)
                tree.add(l);
            else
                res += tree.query(l, r);
        }
        for (auto [opt, x, l, r] : g)
        {
            if (opt == 0)
                tree.clear(l);
        }
        return res;
    }
    vector<node> qwq[N];
    inline ll main()
    {
        ll res = 0;
        tree.init(k + 2);
        for (int o = 0; o < 2; ++o)
        {
            vector<node> p;
            for (int i = 1; i < n[o]; ++i)
                p.emplace_back(0, a[o][i], a[o][i + 1]);
            for (int i = 1; i < n[o ^ 1]; ++i)
                if (c[o ^ 1][i] == c[o ^ 1][i + 1])
                {
                    p.emplace_back(1, a[o ^ 1][i], 1, a[o ^ 1][i + 1]);
                    p.emplace_back(1, a[o ^ 1][i + 1], 1, a[o ^ 1][i]);
                }
            res += solve(p);
        }
        for (int i = 1; i < n[0]; ++i)
        {
            qwq[c[0][i]].emplace_back(1, a[0][i], a[0][i + 1], tree.limit);
            qwq[c[0][i + 1]].emplace_back(1, a[0][i + 1], a[0][i], tree.limit);
        }
        for (int i = 1; i < n[1]; ++i)
        {
            qwq[c[1][i]].emplace_back(0, a[1][i + 1], a[1][i]);
            qwq[c[1][i + 1]].emplace_back(0, a[1][i], a[1][i + 1]);
        }
        for (int i = 0; i <= k; ++i)
            res += solve(qwq[i]);
        return res;
    }
}
signed main()
{
#ifdef PAPERDOG
    freopen("project.in", "r", stdin);
    freopen("project.out", "w", stdout);
#else
    freopen("painting.in", "r", stdin);
    freopen("painting.out", "w", stdout);
#endif
    read(n[0], n[1], k, type);
    for (int o = 0; o < 2; ++o)
        for (int i = 1; i <= n[o]; ++i)
            a[o][i] = o + 1;
    for (int i = 1; i <= k; ++i)
    {
        auto &[opt, l, r, col] = que[i];
        read(opt, l, r, col);
    }
    for (int i = k; i >= 1; --i)
    {
        auto [opt, l, r, col] = que[i];
        if (opt == 0)
            for (int j = find(l); j <= r; j = find(j))
            {
                a[0][j] = i + 2;
                c[0][j] = col;
                fa[j] = j + 1;
            }
    }
    memset(fa, 0, sizeof(fa));
    for (int i = k; i >= 1; --i)
    {
        auto [opt, l, r, col] = que[i];
        if (opt == 1)
            for (int j = find(l); j <= r; j = find(j))
            {
                a[1][j] = i + 2;
                c[1][j] = col;
                fa[j] = j + 1;
            }
    }
    ll answer = subtask1::main();
    if (type)
        answer += subtask2::main();
    write(answer, '\n');
#ifdef FAST_OUT
    IO::OUTPUT::flush();
#endif
    return 0;
}