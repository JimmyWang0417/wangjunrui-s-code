#include <cmath>
#include <cstdio>
#define re register
#define ll long long
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
const int N=5e4+5,M=255;
int block,num,l[M],r[M];
int belong[N],n,a[N];
ll tag[M],sum[M];
inline void build()
{
	block=(int)sqrt(n);
	num=n/block;
	if(n%block)
		++num;
	for(re int i=1; i<=num; ++i)
	{
		l[i]=(i-1)*block+1;
		r[i]=i*block;
	}
	for(re int i=1; i<=n; ++i)
	{
		belong[i]=(i-1)/block+1;
		sum[belong[i]]+=a[i];
	}
}
inline void update(int x,int y,int val)
{
	if(belong[x]==belong[y])
	{
		for(re int i=x; i<=y; ++i)
		{
			a[i]+=val;
			sum[belong[i]]+=val;
		}
		return;
	}
	for(re int i=x; i<=r[belong[x]]; ++i)
	{
		a[i]+=val;
		sum[belong[i]]+=val;
	}
	for(re int i=belong[x]+1; i<belong[y]; ++i)
		tag[i]+=val;
	for(re int i=l[belong[y]]; i<=y; ++i)
	{
		a[i]+=val;
		sum[belong[i]]+=val;
	}
}
inline ll query(int x,int y,ll mod)
{
	ll ans=0;
	if(belong[x]==belong[y])
	{
		for(re int i=x; i<=y; ++i)
			(ans+=a[i]+tag[belong[i]])%=mod;
		return ans;
	}
	for(re int i=x; i<=r[belong[x]]; ++i)
		(ans+=a[i]+tag[belong[i]])%=mod;
	for(re int i=belong[x]+1; i<belong[y]; ++i)
		(ans+=tag[i]*(r[i]-l[i]+1)%mod+sum[i]%mod)%=mod;
	for(re int i=l[belong[y]]; i<=y; ++i)
		(ans+=a[i]+tag[belong[i]])%=mod;
	return ans;
}
signed main()
{
	read(n);
	for(re int i=1; i<=n; ++i)
		read(a[i]);
	build();
	for(re int i=1; i<=n; ++i)
	{
		int opt,x,y;
		ll val;
		read(opt),read(x),read(y),read(val);
		if(opt==0)
			update(x,y,val);
		else if(opt==1)
			printf("%lld\n",query(x,y,val+1));
	}
	return 0;
}
