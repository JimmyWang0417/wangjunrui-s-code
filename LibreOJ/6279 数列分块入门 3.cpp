#include <cmath>
#include <cstdio>
#include <vector>
#include <algorithm>
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
const int N=1e5+5,M=500,INF=0x7fffffff;
int l[M],r[M],tag[M],num,block;
int belong[N];
int n,a[N];
vector<int>p[M];
inline void rebuild(int id)
{
	p[id].clear();
	for(re int i=l[id]; i<=r[id]; ++i)
		p[id].push_back(a[i]);
	sort(p[id].begin(),p[id].end());
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
	for(re int i=1; i<=n; ++i)
		belong[i]=(i-1)/block+1;
	for(re int i=1; i<=num; ++i)
		rebuild(i);
}
inline void update(int x,int y,int val)
{
	if(belong[x]==belong[y])
	{
		for(re int i=x; i<=y; ++i)
			a[i]+=val;
		rebuild(belong[x]);
		return;
	}
	for(re int i=x; i<=r[belong[x]]; ++i)
		a[i]+=val;
	rebuild(belong[x]);
	for(re int i=belong[x]+1; i<belong[y]; ++i)
		tag[i]+=val;
	for(re int i=l[belong[y]]; i<=y; ++i)
		a[i]+=val;
	rebuild(belong[y]);
}
inline int query(int x,int y,int val)
{
	int res=~INF;
	if(belong[x]==belong[y])
	{
		for(re int i=x; i<=y; ++i)
			if(a[i]+tag[belong[i]]<val)
				res=max(res,a[i]+tag[belong[i]]);
		return res==~INF?-1:res;
	}
	for(re int i=x; i<=r[belong[x]]; ++i)
		if(a[i]+tag[belong[i]]<val)
			res=max(res,a[i]+tag[belong[i]]);
	for(re int i=belong[x]+1; i<belong[y]; ++i)
	{
		int id=(int)(lower_bound(p[i].begin(),p[i].end(),val-tag[i])-p[i].begin()-1);
		if(id==-1||id==(int)p[i].size())
			continue;
		res=max(res,p[i][id]+tag[i]);
	}
	for(re int i=l[belong[y]]; i<=y; ++i)
		if(a[i]+tag[belong[i]]<val)
			res=max(res,a[i]+tag[belong[i]]);
	return res==~INF?-1:res;
}
int main()
{
	read(n);
	for(re int i=1; i<=n; ++i)
		read(a[i]);
	build();
	for(re int i=1; i<=n; ++i)
	{
		int opt,x,y,c;
		read(opt),read(x),read(y),read(c);
		if(opt==0)
			update(x,y,c);
		else if(opt==1)
			printf("%d\n",query(x,y,c));
	}
	return 0;
}
