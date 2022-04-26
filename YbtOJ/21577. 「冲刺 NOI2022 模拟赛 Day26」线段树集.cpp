#include <bits/stdc++.h>

template <class T>
inline void read(T &x)
{
	static char ch; 
	static bool opt; 
	while (!isdigit(ch = getchar()) && ch != '-'); 
	x = (opt = ch == '-') ? 0 : ch - '0'; 
	while (isdigit(ch = getchar()))
		x = x * 10 + ch - '0'; 
	if (opt)
		x = ~x + 1; 
}

typedef long long s64; 

const int MaxN = 2e3 + 5; 
const int MaxM = 3e6 + 5; 

struct point
{
	int x, y; 
	point(){}
	point(int _x, int _y):
		x(_x), y(_y) {}
	inline point operator + (point rhs) const 
    {
        return point(x + rhs.x, y + rhs.y);
    }
	inline point operator - (point rhs) const 
    {
        return point(x - rhs.x, y - rhs.y);
    }
	inline bool operator < (point rhs) const 
    {
        return x < rhs.x || (x == rhs.x && y < rhs.y);
    }
	inline bool operator != (point rhs) const 
    {
        return x != rhs.x || y != rhs.y;
    }
	inline s64 operator * (point rhs) const 
    {
        return 1LL * x * rhs.y - 1LL * y * rhs.x;
    }
	
	inline void scan() 
    {
        read(x), read(y);
    }
	inline point rotate() const 
    {
        return point(-y, x);
    }
	inline s64 norm() const 
    {
        return 1LL * x * x + 1LL * y * y;
    }
	inline friend s64 dot(point lhs, point rhs) 
    {
        return 1LL * lhs.x * rhs.x + 1LL * lhs.y * rhs.y;
    }

	inline void simplify()
	{
		int d = std::__gcd(abs(x), abs(y)); 
		x /= d, y /= d; 
		if (x < 0 || (!x && y < 0))
			x = -x, y = -y; 
	}
}a[MaxN]; 

inline bool where(point a)
{
	return a.y < 0 || (a.y == 0 && a.x < 0); 
}

inline bool cmp_angle(point a, point b)
{
	if (where(a) != where(b))
		return where(a) < where(b); 
	else
		return a * b > 0; 
}

struct seg
{
	point st, dir; 
	seg(){}
	seg(point _st, point _dir):
		st(_st), dir(_dir) {dir.simplify();}

	inline bool operator < (const seg &rhs) const
	{
		if (dir != rhs.dir)
			return dir < rhs.dir; 
		else if (st * dir != rhs.st * dir)
			return st * dir < rhs.st * dir; 
		else
			return st < rhs.st; 
	}
}s[MaxM]; 

int n, m; 
s64 cur_S; 

inline int find(point a, point b)
{
	if (b < a)
		std::swap(a, b); 

	seg t1(a + a, b - a), t2(b + b, b - a); 
	int l = std::upper_bound(s + 1, s + m + 1, t1) - s; 
	int r = std::lower_bound(s + 1, s + m + 1, t2) - s; 
	return std::max(0, r - l); 
}

int main()
{
#ifdef ONLINE_JUDGE
	freopen("C.in", "r", stdin); 
	freopen("C.out", "w", stdout); 
#endif
	read(n); 
	for (int i = 1; i <= n; ++i)
		a[i].scan(); 
	for (int i = 1; i < n; ++i)
		for (int j = i + 1; j <= n; ++j)
			s[++m] = seg(a[i] + a[j], (a[j] - a[i]).rotate()); 
	std::sort(s + 1, s + m + 1); 
    
	s64 ans = 0; 
	for (int D = 1; D <= n; ++D)
	{
		int cnt = 0; 
		static point b[MaxN]; 
		for (int i = 1; i <= n; ++i)
			if (i != D)
				b[++cnt] = point(a[i] - a[D]); 
		std::sort(b + 1, b + cnt + 1, cmp_angle);  
		for (int i = 1; i <= cnt; ++i)
			b[cnt + i] = b[i]; 

		std::map<s64, int> S; 
		S.clear(); cur_S = 0; 

		int l = 1, r = 1; //[l, r)
		for (int A = 1; A <= cnt; ++A)
		{
			while (b[A] * b[r] > 0 || (b[A] * b[r] == 0 && r <= cnt) || dot(b[A], b[r]) < 0)
				cur_S += S[b[r++].norm()]++; 
			while (l < r && dot(b[l], b[A]) >= 0)
				cur_S -= --S[b[l++].norm()]; 
			
			if (cur_S)
				ans += 1LL * cur_S * find(a[D], a[D] + b[A]);
		}
	}

	std::cout << (ans << 2) << '\n'; 

	return 0; 
}
