#include <cmath>
#include <cstdio>
#include <cassert>
#include <vector>
#include <algorithm>
#define ll long long
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
const int N=5e4+5;
int a[N],n;
int l[N],r[N],belong[N],block,num,tag[N];
vector<int>v[N];
inline void rebuild(int id)
{
	v[id].clear();
	for(re int i=l[id]; i<=r[id]; ++i)
		v[id].push_back(a[i]);
	sort(v[id].begin(),v[id].end());
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
	assert(belong[x]!=belong[y]);
	for(re int i=x; i<=r[belong[x]]; ++i)
		a[i]+=val;
	rebuild(belong[x]);
	for(re int i=belong[x]+1; i<belong[y]; ++i)
		tag[i]+=val;
	for(re int i=l[belong[y]]; i<=y; ++i)
		a[i]+=val;;
	rebuild(belong[y]);
}
inline int query(int x,int y,int val)
{
	if(belong[x]==belong[y])
	{
		int ans=0;
		for(re int i=x; i<=y; ++i)
			if(a[i]+tag[belong[i]]<val)
				++ans;
		return ans;
	}
	assert(belong[x]!=belong[y]);
	int ans=0;
	for(re int i=x; i<=r[belong[x]]; ++i)
		if(a[i]+tag[belong[i]]<val)
			++ans;
	for(re int i=belong[x]+1; i<belong[y]; ++i)
		ans+=lower_bound(v[i].begin(),v[i].end(),val-tag[i])-v[i].begin();
	for(re int i=l[belong[y]]; i<=y; ++i)
		if(a[i]+tag[belong[i]]<val)
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
		int opt,x,y,val;
		read(opt),read(x),read(y),read(val);
		if(opt==0)
			update(x,y,val);
		else
			printf("%d\n",query(x,y,val*val));
	}
	return 0;
}
