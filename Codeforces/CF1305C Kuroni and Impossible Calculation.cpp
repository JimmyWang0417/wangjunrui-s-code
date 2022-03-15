#include <cstdio>
#include <cstring>
#include <string>
#include <iostream>
#include <algorithm>
#include <cmath>
#define ll long long
#define re register
#define int ll
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
const int N = 3e5 + 10;
int a[N], b[N] , c[N],ans=1ll;
char s[N];
signed main()
{
	int n , mod;
	read(n),read(mod);
	int flag = 0;
	for(re int i=1 ; i<=n; ++i)
	{
		cin >> a[i];
		++ c[a[i] % mod];
		if (c[a[i] % mod] > 1)
			flag = 1;
	}
	if (flag)
		return cout << 0 << endl,0;
	int ans = 1;
	for(re int i=1; i<=n; ++i)
		for(re int j=i+1; j<=n; ++j)
			ans = ans * (abs(a[i] - a[j])) % mod;
	cout << ans << endl;
	return 0;
}
