#include <cstdio>
#include <cmath>
#define re register
#define mod 10007
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
const int N=1e5+5,M=350;
int block,num,l[M],r[M];
int belong[N];
int n,a[N];
int add[M],mul[N];
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
		mul[i]=1;
	}
	r[num]=n;
	for(re int i=1; i<=n; ++i)
		belong[i]=(i-1)/block+1;
}
inline void pushdown(int id)
{
	for(re int i=l[id]; i<=r[id]; ++i)
		a[i]=(a[i]*mul[id]+add[id])%mod;
	mul[id]=1;
	add[id]=0;
}
inline void update1(int x,int y,int val)
{
	if(belong[x]==belong[y])
	{
		pushdown(belong[x]);
		for(re int i=x; i<=y; ++i)
			(a[i]+=val)%=mod;
		return;
	}
	pushdown(belong[x]);
	for(re int i=x; i<=r[belong[x]]; ++i)
		(a[i]+=val)%=mod;
	for(re int i=belong[x]+1; i<belong[y]; ++i)
		(add[i]+=val)%=mod;
	pushdown(belong[y]);
	for(re int i=l[belong[y]]; i<=y; ++i)
		(a[i]+=val)%=mod;
}
inline void update2(int x,int y,int val)
{
	if(belong[x]==belong[y])
	{
		pushdown(belong[x]);
		for(re int i=x; i<=y; ++i)
			(a[i]*=val)%=mod;
		return;
	}
	pushdown(belong[x]);
	for(re int i=x; i<=r[belong[x]]; ++i)
		(a[i]*=val)%=mod;
	for(re int i=belong[x]+1; i<belong[y]; ++i)
	{
		(mul[i]*=val)%=mod;
		(add[i]*=val)%=mod;
	}
	pushdown(belong[y]);
	for(re int i=l[belong[y]]; i<=y; ++i)
		(a[i]*=val)%=mod;
}
inline int query(int pos)
{
	return (a[pos]*mul[belong[pos]]+add[belong[pos]])%mod;
}
int main()
{
	read(n);
	for(re int i=1; i<=n; ++i)
	{
		read(a[i]);
		a[i]%=mod;
	}
	build();
	for(re int i=1; i<=n; ++i)
	{
		int opt,x,y,c;
		read(opt),read(x),read(y),read(c);
		c%=mod;
		if(opt==0)
			update1(x,y,c);
		else if(opt==1)
			update2(x,y,c);
		else if(opt==2)
			printf("%d\n",query(y));
	}
	return 0;
}
