#include <bits/stdc++.h>
#define lowbit(x) ((x)&(-(x)))
#define re register
#define ll long long
#define ull unsigned long long
#define rep(i,a,b) for(re int i=a;i<=b;++i)
#define per(i,a,b) for(re int i=a;i>=b;--i)
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
template<typename T,typename ...T1>
inline void read(T&x,T1&...x1)
{
	read(x);
	read(x1...);
}
template<typename T>
inline void clear(T*array,int l,int r,int val)
{
	memset(&array[l],val,sizeof(T)*(r-l+1));
}
using namespace std;
const int N=1005;
int mod;
int n,m,k;
int cnt[N],mul[N];
int power[N];
signed main()
{
	read(n,m,k);
	if((n&1)!=(m&1))
	{
		printf("0\n");
		return 0;
	}
	bool flag=false;
	if(n<m)
	{
		swap(n,m);
		flag=true;
	}
	power[0]=1;
	for(int i=1; i<=n; ++i)
		mul[i]=1;
	for(int i=1; i<=k; ++i)
	{
		int x,y,v;
		read(x,y,v);
		if(flag)
			swap(x,y);
		++cnt[x],mul[x]*=v;
	}
	read(mod);
	for(int i=1; i<=n; ++i)
		power[i]=power[i-1]*2%mod;
	for(int i=1; i<n; ++i)
		if(!cnt[i])
		{
			swap(cnt[i],cnt[n]);
			swap(mul[i],mul[n]);
			break;
		}
	ll ans=1;
	for(int i=1; i<n; ++i)
	{
		if(cnt[i]==m)
		{
			if(mul[i]==1)
				ans=0;
		}
		else
			ans=ans*power[m-cnt[i]-1]%mod;
	}
	printf("%lld\n",ans);
	return 0;
}


