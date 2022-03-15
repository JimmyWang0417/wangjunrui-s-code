#include <cstdio>
#include <cmath>
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
const int N=5e4+5,Sqrt=230;
int n;
int block,num,l[Sqrt],r[Sqrt],belong[N];
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
	for(re int i=1; i<=n; ++i)
		belong[i]=(i-1)/block+1;
}
int tag[Sqrt],a[N];
inline void update(int x,int y,int val)
{
	if(belong[y]-belong[x]<=1)
	{
		for(re int i=x; i<=y; ++i)
			a[i]+=val;
		return;
	}
	for(re int i=x; i<=r[belong[x]]; ++i)
		a[i]+=val;
	for(re int i=belong[x]+1; i<belong[y]; ++i)
		tag[i]+=val;
	for(re int i=l[belong[y]]; i<=y; ++i)
		a[i]+=val;
}
inline int query(int x)
{
	return a[x]+tag[belong[x]];
}
int main()
{
	read(n);
	for(re int i=1; i<=n; ++i)
		read(a[i]);
	build();
	for(re int i=1; i<=n; ++i)
	{
		int opt,ll,rr,c;
		read(opt),read(ll),read(rr),read(c);
		if(opt==0)
			update(ll,rr,c);
		else if(opt==1)
			printf("%d\n",query(rr));
	}
	return 0;
}
