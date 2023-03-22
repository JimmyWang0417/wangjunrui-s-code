/**
 *    name:     B. 囙父夕顼弍
 *    author:   whitepaperdog (蒟蒻wjr)
 *    located:  Xuanwu District, Nanjing City, Jiangsu Province, China
 *    created:  2023.03.22 周三 21:58:46 (Asia/Shanghai)
 *    unicode:  UTF-8
 *    standard: c++23
 **/
#include <algorithm>
#include <cstdio>
#include <cstring>
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
constexpr int N = 10005;
constexpr int mod = 1e9 + 9;
typedef MODINT::modint<mod> modint;
constexpr modint inv2 = modint(2).inv();
int n, m;
pair<int, int> p[N];
bool can[N], vis[N];
modint a[N], b[N], sum[N];
modint answer[N];
inline void work()
{
    read(n);
    for (int i = 1; i <= n; ++i)
        read(p[i].first);
    for (int i = 1; i <= n; ++i)
        read(p[i].second);
    sort(p + 1, p + 1 + n);
    if (p[1].first == 0 && p[1].second == 0)
    {
        write("-1\n");
        return;
    }
    n = (int)(unique(p + 1, p + 1 + n) - p - 1);
    memset(can, 1, sizeof(can));
    memset(vis, 0, sizeof(vis));
    for (int i = 1; i < n; ++i)
        if (p[i].first == p[i + 1].first)
        {
            write("-1\n");
            return;
        }
    for (int i = 1; i <= n; ++i)
        if (!vis[i] && p[i].first)
        {
            modint inv = modint(p[i].first).inv();
            int pos = (int)(lower_bound(p + 1, p + 1 + n, make_pair(inv.data(), 0)) - p);
            if (pos <= n && p[pos].first == inv.data())
            {
                vis[i] = vis[pos] = true;
                modint now = p[i].second;
                for (int j = 0; j <= 10000; ++j, now *= p[pos].first)
                    if (p[pos].second != now.data())
                        can[j] = false;
            }
        }
    int d = -1;
    for (int i = 10000; i >= 0; --i)
        if (can[i])
        {
            d = i;
            break;
        }
    if (d == -1)
    {
        write("-1\n");
        return;
    }
    for (int i = 1, _n = n; i <= _n; ++i)
        if (!vis[i] && p[i].first)
        {
            modint inv = modint(p[i].first).inv();
            p[++n] = make_pair(inv.data(), ((inv ^ d) * p[i].second).data());
        }
    sort(p + 1, p + 1 + n);
    memset(static_cast<void *>(a), 0, sizeof(a));
    memset(static_cast<void *>(sum), 0, sizeof(sum));
    a[m = 0] = 1;
    for (int i = 1; i <= n; ++i)
        if (p[i].first)
        {
            for (int j = ++m; j >= 1; --j)
                a[j] = a[j - 1] - a[j] * p[i].first;
            a[0] = -a[0] * p[i].first;
        }
    for (int i = 1; i <= n; ++i)
        if (p[i].first)
        {
            modint times = 1;
            for (int j = 1; j <= n; ++j)
                if (i != j && p[j].first)
                    times *= modint(p[i].first) - p[j].first;
            times = times.inv() * p[i].second;
            modint las = a[m + 1];
            for (int j = m; j >= 0; --j)
            {
                b[j] = las;
                las = a[j] + las * p[i].first;
            }
            for (int j = 0; j <= m; ++j)
                sum[j] += times * b[j];
        }
    int qwq = m;
    while (qwq > 0 && !sum[qwq].data())
        --qwq;
    if (qwq > d)
    {
        write("-1\n");
        return;
    }
    memset(static_cast<void *>(answer), 0, sizeof(answer));
    for (int i = 0; i <= qwq; ++i)
    {
        answer[i] += sum[i] * inv2;
        answer[d - i] += sum[i] * inv2;
    }
    if (answer[0] == 0 || (p[1].first == 0 && answer[0] != p[1].second))
    {
        if (d < m)
        {
            write("-1\n");
            return;
        }
        int to = max(p[1].second, 1);
        auto times = (-answer[0] + to) * a[0].inv();
        for (int i = 0; i <= m; ++i)
            answer[i] += a[i] * times;
        if (d > m)
            for (int i = 0; i <= m; ++i)
                answer[d - i] += a[i] * times;
    }
	write(d, '\n');
	for (int i = 0; i <= d; ++i)
		write(answer[i].data(), ' ');
	write('\n');
}
signed main()
{
    int T = 1;
    read(T);
    while (T--)
        work();
#ifdef FAST_OUT
    IO::OUTPUT::flush();
#endif
    return 0;
}