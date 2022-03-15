#include<cstdio>
#include<map>
#include<cmath>
#define re register
#define ll long long
using namespace std;
template<typename T>
inline void read(T&x)
{
	x=0;
	char s=getchar();
	bool f=false;
	while(!(s>='0'&&s<='9'))
	{
		if(s=='-')
			f=true;
		s=getchar();
	}
	while(s>='0'&&s<='9')
	{
		x=(x<<1)+(x<<3)+s-'0';
		s=getchar();
	}
	if(f)
		x=(~x)+1;
}
inline ll quickpow(ll&a,ll&b,ll&p)
{
	ll res=1;
	while(b)
	{
		if(b&1)
			res=res*a%p;
		a=a*a%p;
		b>>=1;
	}
	return res%p;
}
inline void Exgcd(ll a,ll b,ll&d,ll&x,ll&y)
{
	if(b==0)
	{
		d=a;
		x=1;
		y=0;
	}
	else
	{
		Exgcd(b,a%b,d,x,y);
		ll t=x;
		x=y;
		y=t-a/b*y;
	}
	return;
}
inline void solve1(int&T)
{
	ll a,b,p;
	while(T--)
	{
		read(a);
		read(b);
		read(p);
		printf("%lld\n",quickpow(a,b,p));
	}
	return;
}
inline void solve2(int&T)
{
	ll a,b,p,d,x,y;
	while(T--)
	{
		read(a);
		read(b);
		read(p);
		Exgcd(a,p,d,x,y);
		if(b%d)
		{
			printf("Orz, I cannot find x!\n");
			continue;
		}
		printf("%lld\n",((x*b/d%p)+p)%p);
	}
	return;
}
map<ll,ll>mp;
inline void BSGS(ll&a,ll&b,ll&p)
{
	if(a%p==0&&b)
	{
		puts("Orz, I cannot find x!");
		return;
	}
	a%=p;
	mp.clear();
	ll m=ceil(sqrt(p)),tmp=1ll;
	mp[1]=m+1;
	for(re ll j=1; j<m; j++)
	{
		tmp=tmp*a%p;
		if(!mp[tmp])
			mp[tmp]=j;
	}
	tmp=tmp*a%p;
	ll d=1,gcd,x,y,j;
	for(re int i=0; i<m; i++)
	{
		Exgcd(d,p,gcd,x,y);
		x=(b/gcd*x%p+p)%(p/gcd);
		j=mp[x];
		if(j)
		{
			if(j==m+1)
				j=0;
			printf("%lld\n",i*m+j);
			return;
		}
		d=d*tmp%p;
	}
	printf("Orz, I cannot find x!\n");
	return;
}
inline void solve3(int&T)
{
	ll a,b,c;
	while(T--)
	{
		read(a);
		read(b);
		read(c);
		BSGS(a,b,c);
	}
	return;
}
int main()
{
	int t,k;
	read(t);
	read(k);
	if(k==1)
		solve1(t);
	else if(k==2)
		solve2(t);
	else
		solve3(t);
	return 0;
}

