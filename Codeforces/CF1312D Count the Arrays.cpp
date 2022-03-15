#include <cstdio>
#define re register
using namespace std;
template<typename T>
inline void read(T&x)
{
	x=0;
	char s=(char)getchar();
	bool f=false;
	while(!(s>='0'&&s<='9'))
	{
		if(s=='-')
			f=true;
		s=(char)getchar();
	}
	while(s>='0'&&s<='9')
	{
		x=(x<<1)+(x<<3)+s-'0';
		s=(char)getchar();
	}
	if(f)
		x=(~x)+1;
}
#define int long long
#define rep(i , a , b) for(int i = a ; i <= b ; i ++)
const int N = 4e5 + 5;
const int Mod = 998244353;
int fac[N], ifac[N];
int ans;
int n, m;
inline void Add(int &x, int y)
{
	x+=y;
	if(x>=Mod)
		x-=Mod;
}
inline int quickpow(int x, int y)
{
	int ret = 1;
	for (; y; y >>= 1, x = x * x % Mod) if (y & 1) ret = ret * x % Mod;
	return ret;
}
inline int C(int x, int y)
{
	return x < y ? 0 : fac[x] * ifac[y] % Mod * ifac[x - y] % Mod;
}

signed main()
{
	read(n),read(m);
	if (n == 2) return printf("0\n"), 0;
	fac[0] = 1;
	for (int i = 1; i <= n+m; i++) fac[i] = fac[i - 1] * (int)i % Mod;
	ifac[n+m] = quickpow(fac[n+m], Mod - 2);
	for (int i = n+m - 1; ~i; i--) ifac[i] = ifac[i + 1] * (int)(i + 1) % Mod;
	int sm = 0;
	for(re int j=2; j<n; ++j) Add(sm, C(n - 3, j - 2));
	for(re int i=1; i<=m; ++i)
	{
		int now = C(i - 1, n - 2) * (int)(n - 2) % Mod;
		Add(ans, sm * now % Mod);
	}
	printf("%lld\n",ans);
	return 0;
}
