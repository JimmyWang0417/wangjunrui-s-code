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
int belong[N];
int a[N],n;
ll sum[M];
bool tag[M];
inline void check(int id)
{
	if(tag[id])
		return;
	sum[id]=0;
	for(re int i=l[id]; i<=r[id]; ++i)
		sum[id]+=a[i];
	for(re int i=l[id]; i<=r[id]; ++i)
		if(a[i]>1)
			return;
	tag[id]=true;
}
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
	r[num]=n;
	for(re int i=1; i<=num; ++i)
		check(i);
	for(re int i=1; i<=n; ++i)
		belong[i]=(i-1)/block+1;
}
inline void update(int x,int y)
{
	if(belong[x]==belong[y])
	{
		if(tag[belong[x]])
			return;
		for(re int i=x; i<=y; ++i)
			a[i]=(int)sqrt(a[i]);
		check(belong[x]);
		return;
	}
	if(!tag[belong[x]])
	{
		for(re int i=x; i<=r[belong[x]]; ++i)
			a[i]=(int)sqrt(a[i]);
		check(belong[x]);
	}
	for(re int i=belong[x]+1; i<belong[y]; ++i)
	{
		if(tag[i])
			continue;
		for(re int j=l[i]; j<=r[i]; ++j)
			a[j]=(int)sqrt(a[j]);
		check(i);
	}
	if(!tag[belong[y]])
	{
		for(re int i=l[belong[y]]; i<=y; ++i)
			a[i]=(int)sqrt(a[i]);
		check(belong[y]);
	}
}
inline ll query(int x,int y)
{
	ll ans=0;
	if(belong[x]==belong[y])
	{
		for(re int i=x; i<=y; ++i)
			ans+=a[i];
		return ans;
	}
	for(re int i=x; i<=r[belong[x]]; ++i)
		ans+=a[i];
	for(re int i=belong[x]+1; i<belong[y]; ++i)
		ans+=sum[i];
	for(re int i=l[belong[y]]; i<=y; ++i)
		ans+=a[i];
	return ans;
}
int main()
{
	read(n);
	for(re int i=1; i<=n; ++i)
		read(a[i]);
	build();
	for(re int i=1; i<=n; ++i)
	{
		int opt,l,r,c;
		read(opt),read(l),read(r),read(c);
		if(opt==0)
			update(l,r);
		else if(opt==1)
			printf("%lld\n",query(l,r));
	}
	return 0;
}
