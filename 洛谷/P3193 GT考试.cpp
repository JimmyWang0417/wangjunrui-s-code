#include <cstdio>
#include <cassert>
#include <cstring>
#define re register
using namespace std;
template <typename T>
inline void read(T &x)
{
	x = 0;
	char s = getchar();
	bool f = false;
	while (!(s >= '0' && s <= '9'))
	{
		if (s == '-')
			f = true;
		s = getchar();
	}
	while (s >= '0' && s <= '9')
	{
		x = (x << 1) + (x << 3) + s - '0';
		s = getchar();
	}
	if (f)
		x = (~x) + 1;
}
int n, m, mod, p[25];
struct node
{
	int g[25][25];
	inline void print()
	{
		for (re int i = 0; i < m; ++i)
		{
			for (re int j = 0; j < m; ++j) printf("%d ", g[i][j]);
			printf("\n");
		}
	}
} a, f;
inline node operator*(const node &aa, const node &b)
{
	node ans;
	memset(ans.g, 0, sizeof(ans.g));
	for (re int i = 0; i < m; ++i)
		for (re int j = 0; j < m; ++j)
			for (re int k = 0; k < m; ++k) ans.g[i][j] = (ans.g[i][j] + aa.g[i][k] * b.g[k][j] % mod) % mod;
	return ans;
}
char str[25];
inline void pre()
{
	p[1] = 0;
	for (re int i = 1, j = 0; i < m; ++i)
	{
		while (j && str[i + 1] != str[j + 1]) j = p[j];
		if (str[i + 1] == str[j + 1])
			++j;
		p[i + 1] = j;
	}
}
inline void init()
{
	for (re int i = 0; i < m; ++i)
		for (re char j = '0'; j <= '9'; ++j)
		{
			re int t = i;
			while (t && str[t + 1] != j) t = p[t];
			if (str[t + 1] == j)
				++t;
			if (t != m)
				a.g[t][i] = (a.g[t][i] + 1) % mod;
		}
}
int main()
{
	int ans = 0;
	read(n), read(m), read(mod);
	scanf("%s", str + 1);
	pre();
	init();
	for (re int i = 0; i < m; ++i) f.g[i][i] = 1;
	while (n)
	{
		if (n & 1)
			f = f * a;
		a = a * a;
		n >>= 1;
	}
	for (re int i = 0; i < m; ++i) ans = (ans + f.g[i][0]) % mod;
	printf("%d\n", ans);
}
