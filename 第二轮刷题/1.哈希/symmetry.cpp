#include <cstdio>
#include <cmath>
using namespace std;
#define re register
#define ull long long
template <typename T>
inline void read(T& x)
{
	x = 0;
	char s = (char)getchar();
	bool f = false;
	while (!(s >= '0' && s <= '9'))
	{
		if (s == '-')
			f = true;
		s = (char)getchar();
	}
	while (s >= '0' && s <= '9')
	{
		x = (x << 1) + (x << 3) + s - '0';
		s = (char)getchar();
	}
	if (f)
		x = (~x) + 1;
}
const int N = 4e5 + 10, mul = 1e4 + 7, mod = 1e9 + 7;
int n, T;
struct node
{
	int x, y;
} point[N];
inline ull angle(int x)
{
	int y = x + 1, z = x + 2;
	if (y > n)
	{
		y -= n;
		z -= n;
	}
	else if (z > n)
		z -= n;
	ull tmp1 = point[y].x - point[x].x, tmp2 = point[y].y - point[x].y, tmp3 = point[z].x - point[y].x,
	    tmp4 = point[z].y - point[y].y;
	return tmp1 * tmp4 - tmp2 * tmp3;
}
inline ull side(int x)
{
	int y = x + 1;
	if (y > n)
		y -= n;
	ull tmp1 = point[x].x - point[y].x, tmp2 = point[x].y - point[y].y;
	return tmp1 * tmp1 + tmp2 * tmp2;
}
ull power[N], hash_right[N], hash_left[N], sum[N];
#define len (n - 1)
inline ull calc_left(int from, int to)
{
	return hash_left[from] - hash_left[to + 1] * power[to - from + 1] % mod;
}
inline ull calc_right(int from, int to)
{
	return hash_right[to] - hash_right[from - 1] * power[to - from + 1] % mod;
}
inline bool check(int x)
{
	ull tmp1 = (calc_right(x + 1, x + len) % mod + mod) % mod,
	    tmp2 = (calc_left(x + n + 1, x + n + len) % mod + mod) % mod;
	// printf("%lld %lld\n",tmp1,tmp2);
	return tmp1 == tmp2;
}
#undef len
int main()
{
	power[0] = 1ull;
	for (re int i = 1; i <= 400000; ++i) power[i] = power[i - 1] * mul % mod;
	//	for(re int i=1; i<=400000; ++i)
	//		printf("%lld ",power[i]);
	//	putchar('\n');
	read(T);
	re int ans = 0;
	while (T--)
	{
		ans = 0;
		read(n);
		for (re int i = 1; i <= n; ++i) read(point[i].x), read(point[i].y);
		for (re int i = 1; i <= n; ++i) sum[i << 1] = angle(i);
		for (re int i = 1; i <= n; ++i) sum[(i << 1) - 1] = side(i);
		for (re int i = 1; i <= (n << 1); ++i) sum[i + (n << 1)] = sum[i];
		hash_right[0] = 0ull;
		hash_left[n << 2] = sum[n << 2];
		for (re int i = 1; i <= (n << 2); ++i)
			hash_right[i] = ((hash_right[i - 1] * mul % mod) + sum[i]) % mod;
		for (re int i = (n << 2) - 1; i >= 1; --i)
			hash_left[i] = ((hash_left[i + 1] * mul % mod) + sum[i]) % mod;
		/*for(re int i=1; i<=(n<<2); --i)
		        printf("%lld %lld\n",hash_left[i],hash_right[i]);*/
		for (re int i = 1; i <= n; ++i)
			if (check(i))
				// printf("%d\n",i);
				++ans;
		printf("%d\n", ans);
	}
	return 0;
}
