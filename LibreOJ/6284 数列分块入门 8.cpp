#include <cmath>
#include <cstdio>
#include <vector>
#include <algorithm>
#define re register
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
int num,block,l[M],r[M];
int belong[N];
int n,a[N];
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
int tag[M];
bool lazy[M];
inline void pushdown(int id)
{
	if(!lazy[id])
		return;
	for(re int i=l[id]; i<=r[id]; ++i)
		a[i]=tag[id];
	lazy[id]=false;
}
inline void update(int x,int y,int val)
{
	if(belong[x]==belong[y])
	{
		for(re int i=x; i<=y; ++i)
			a[i]=val;
		return;
	}
	for(re int i=x; i<=r[belong[x]]; ++i)
		a[i]=val;
	for(re int i=belong[x]+1; i<belong[y]; ++i)
	{
		lazy[i]=true;
		tag[i]=val;
	}
	for(re int i=l[belong[y]]; i<=y; ++i)
		a[i]=val;
}
inline int query(int x,int y,int val)
{
	int ans=0;
	if(belong[x]==belong[y])
	{
		pushdown(belong[x]);
		for(re int i=x; i<=y; ++i)
			if(a[i]==val)
				++ans;
		return ans;
	}
	pushdown(belong[x]);
	for(re int i=x; i<=r[belong[x]]; ++i)
		if(a[i]==val)
			++ans;
	for(re int i=belong[x]+1; i<belong[y]; ++i)
	{
		if(lazy[i])
			ans+=(tag[i]==val)*(r[i]-l[i]+1);
		else
			for(re int j=l[i]; j<=r[i]; ++j)
				if(a[j]==val)
					++ans;
	}
	pushdown(belong[y]);
	for(re int i=l[belong[y]]; i<=y; ++i)
		if(a[i]==val)
			++ans;
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
		int x,y,c;
		read(x),read(y),read(c);
		printf("%d\n",query(x,y,c));
		update(x,y,c);
	}
	return 0;
}
