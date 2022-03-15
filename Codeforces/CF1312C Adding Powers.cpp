#include<cstdio>
#include<vector>
#include<iostream>
#include<algorithm>
#define re register
#define int long long
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
const int N=105;
int n,k,a[N],prime[N],cnt[N],tot;
inline void work()
{
	read(n),read(k);
	for(re int i=1; i<=n; ++i)
		read(a[i]);
	prime[tot=0]=1;
	for(; prime[tot]<=1e16; ++tot)
		prime[tot+1]=prime[tot]*k;
	for(re int i=tot; i>=0; --i)
	{
		cnt[i]=0;
		for(re int j=1; j<=n; ++j)
		{
			cnt[i]+=a[j]/prime[i];
			a[j]%=prime[i];
		}
	}
	for(re int i=tot; i>=0; --i)
		if(cnt[i]>1)
		{
			printf("NO\n");
			return;
		}
	printf("YES\n");
}
signed main()
{
	int T;
	read(T);
	while(T--)
		work();
	return 0;
}
