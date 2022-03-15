#include <cstdio>
#include <cstring>
#define re register
#define ll long long
using namespace std;
template <typename T>
inline void read(T&x)
{
	x=0;
	char s=(char)getchar();
	bool flag=false;
	while(s<'0'||s>'9')
	{
		if(s=='-')
			flag=true;
		s=(char)getchar();
	}
	while(s>='0'&&s<='9')
	{
		x=(x<<1)+(x<<3)+(s^'0');
		s=(char)getchar();
	}
	if(flag)
		x=~x+1;
}
ll d[65];
inline void add(ll x)
{
	for(re int i=60; i>=0; --i)
		if((x>>i)&1)
		{
			if(!d[i])
			{
				d[i]=x;
				break;
			}
			else
				x=x^d[i];
		}
}
int tot;
inline void work()
{
	for(re int i=0; i<=60; ++i)
		if(d[i])
			++tot;
	for(re int i=1; i<=60; ++i)
		for(re int j=0; j<i; ++j)
			if(d[i]&(1ll<<j))
				d[i]^=d[j];
}
int T,n,q,kase;
inline ll kth_number(ll k)
{
	if(tot<n)
		--k;
	ll ans=0ll;
	for(re int i=0; i<=60; ++i)
		if(d[i])
		{
			if(k&1)
				ans^=d[i];
			k>>=1;
		}
	return k?-1:ans;
}
int main()
{
	read(T);
	while(T--)
	{
		printf("Case #%d:\n",++kase);
		ll val;
		memset(d,0ll,sizeof(d));
		tot=0;
		read(n);
		for(re int i=0; i<n; ++i)
		{
			read(val);
			add(val);
		}
		work();
		read(q);
		while(q--)
		{
			read(val);
			printf("%lld\n",kth_number(val));
		}
	}
	return 0;
}
