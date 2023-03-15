/**
 *    name:     A. 消除罗结晶
 *    author:   whitepaperdog (蒟蒻wjr)
 *    located:  Xuanwu District, Nanjing City, Jiangsu Province, China
 *    created:  2023.03.15 周三 09:36:49 (Asia/Shanghai)
 *    unicode:  UTF-8
 *    standard: c++23
 **/
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
constexpr int N = 1e5 + 5;
int n, m;
char str[N];
struct node
{
    char opt;
    int x, y;
    node(char _opt = 0, int _x = 0, int _y = 0) : opt(_opt), x(_x), y(_y) {}
} st[N];
int top;
signed main()
{
#ifdef PAPERDOG
    freopen("project.in", "r", stdin);
    freopen("project.out", "w", stdout);
#else
    freopen("iluoblock.in", "r", stdin);
    freopen("iluoblock.out", "w", stdout);
#endif
    read(m, n);
    if (m == 1)
        st[++top] = node('I', 1, 0);
    else if (m == 2)
        st[++top] = node('O', 1, 0);
    else if (m == 3)
    {
        st[++top] = node('T', 1, 2);
        st[++top] = node('T', 2, 1);
        st[++top] = node('J', 1, 2);
    }
    else
    {
        int pos = 0;
        for (int i = 1; i <= n; ++i)
        {
            read(str + 1);
            for (int j = 1; j <= m; ++j)
            {
                if (str[j] == '#')
                {
                    pos = j;
                    break;
                }
            }
            if (pos)
                break;
        }
        if (!pos)
            pos = 1;
        if (m & 1)
        {
            if (pos == m)
                pos -= 2;
            if (pos % 2 == 0)
                --pos;
            st[++top] = node('T', pos, 2);
            for (int i = pos + 2; i + 2 <= m; i += 2)
                st[++top] = node('Z', i, 0);
            for (int i = pos; i - 2 >= 1; i -= 2)
                st[++top] = node('S', i - 2, 0);
            st[++top] = node('T', m - 1, 1);
            st[++top] = node('T', 1, 3);
            for (int i = 2; i + 2 < m - 1; i += 2)
                st[++top] = node('Z', i, 0);
            st[++top] = node('T', m - 3, 0);
        }
        else
        {
            if (pos % 2 == 0)
                --pos;
            if (pos == m - 1)
            {
                st [++top] = node('T', m - 2, 2);
                for (int i = pos; i - 2 >= 3; i -= 2)
                    st[++top] = node('S', i - 3, 0);
                st[++top] = node('T', m - 1, 1);
                st[++top] = node('T', 1, 3);
                for (int i = m - 3; i >= 2; i -= 2)
                    st[++top] = node('S', i, 0);
                st[++top] = node('T', 1, 0);
            }
            else
            {
                st[++top] = node('T', pos, 2);
                for (int i = pos + 2; i + 2 <= m; i += 2)
                    st[++top] = node('Z', i, 0);
                for (int i = pos; i - 2 >= 1; i -= 2)
                    st[++top] = node('S', i - 2, 0);
                st[++top] = node('T', m - 1, 1);
                st[++top] = node('T', 1, 3);
                for (int i = 2; i + 2 < m - 1; i += 2)
                    st[++top] = node('Z', i, 0);
                st[++top] = node('T', m - 2, 0);
            }
        }
    }
    write(top, '\n');
    for (int i = 1; i <= top; ++i)
    {
        auto [opt, x, y] = st[i];
        write(opt, ' ', y, ' ', x, '\n');
    }
#ifdef FAST_OUT
    IO::OUTPUT::flush();
#endif
    return 0;
}