/**
 *    unicode: UTF-8
 *    name:    #1353. 【20省选集训day4】dict
 *    author:  whitepaperdog (蒟蒻wjr)
 *    located: Changle District, Fuzhou City, Fujian Province, China
 *    created: 2022.12.21 周三 10:24:39 (Asia/Shanghai)
 **/
#include <algorithm>
#include <cstdio>
#include <set>
#define ll long long
#define lll __int128
#define ull unsigned ll
#define lowbit(_x) (_x & (-_x))

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
template <typename _T, const _T _mod>
struct modint
{
	_T x;
	modint(_T _x = 0) : x(_x) {}
	inline modint operator+(const modint &rhs) const
	{
		_T res = x;
		res += rhs.x;
		if (res >= _mod)
			res -= _mod;
		return res;
	}
	inline modint operator-(const modint &rhs) const
	{
		_T res = x;
		res -= rhs.x;
		if (res < 0)
			res += _mod;
		return res;
	}
	inline modint operator*(const modint rhs) const
	{
		return (_T)((ll)x * rhs.x % _mod);
	}
	inline modint &operator+=(const modint rhs)
	{
		x += rhs.x;
		if (x >= _mod)
			x -= _mod;
		return *this;
	}
	inline modint &operator-=(const modint &rhs)
	{
		x -= rhs.x;
		if (x < 0)
			x += _mod;
		return *this;
	}
	inline modint &operator*=(const modint &rhs)
	{
		x = (_T)((ll)x * rhs.x % _mod);
		return *this;
	}
	template <typename _G>
	inline modint operator^(_G rhs) const
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
	inline modint inv() const
	{
		return *this ^ (_mod - 2);
	}
	inline modint operator/(const modint &rhs) const
	{
		return (*this) * rhs.inv();
	}
	inline modint &operator/=(const modint &rhs)
	{
		return (*this) *= rhs.inv();
	}
	inline modint &operator==(const modint &rhs)
	{
		return x == rhs.x;
	}
	inline _T &data()
	{
		return x;
	}
};
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
constexpr int mod = 998244353;
typedef modint<int, mod> node;
int n, m;
int a[N];
int p[N];
node fac[N], ifac[N];
signed main()
{
	read(n, m);
	for (int i = 1; i <= n; ++i)
		read(a[i]);
	for (int i = 1; i <= n; ++i)
		read(p[i]);
	sort(a + 1, a + 1 + n);
	fac[0] = 1;
	for (int i = 1; i <= m; ++i)
		fac[i] = fac[i - 1] * i;
	ifac[m] = fac[m].inv();
	for (int i = m; i >= 1; --i)
		ifac[i - 1] = ifac[i] * i;
	auto C = [](int _n, int _m)
	{
		return fac[_n] * ifac[_m] * ifac[_n - _m];
	};
	a[n + 1] = m + 1;
	node res = C(m, n), ans = 0;
	set<int> se;
	se.insert(0);
	se.insert(n + 1);
	for (int i = 1; i <= n; ++i)
	{
		int l = *prev(se.lower_bound(p[i])), r = *se.upper_bound(p[i]);
		res /= C(a[r] - a[l] - 1, r - l - 1);
		if ((a[p[i]] - a[l]) - (p[i] - l) <= (a[r] - a[p[i]]) - (r - p[i]))
		{
			node now = 0;
			for (int j = a[l] + (p[i] - l); j < a[p[i]]; j++)
				now += C(j - a[l] - 1, p[i] - l - 1) * C(a[r] - j - 1, r - p[i] - 1);
			ans += res * now;
		}
		else
		{
			node now = C(a[r] - a[l] - 1, r - l - 1);
			for (int j = a[r] - (r - p[i]); j >= a[p[i]]; j--)
				now -= C(j - a[l] - 1, p[i] - l - 1) * C(a[r] - j - 1, r - p[i] - 1);
			ans += res * now;
		}
		res *= C(a[p[i]] - a[l] - 1, p[i] - l - 1) * C(a[r] - a[p[i]] - 1, r - p[i] - 1);
		se.insert(p[i]);
	}
	write(ans.data(), '\n');
#ifdef FAST_OUT
	IO::OUTPUT::flush();
#endif
	return 0;
}