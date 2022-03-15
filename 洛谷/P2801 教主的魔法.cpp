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
const int N=1000005,M=1e3+5;
int block,num,l[M],r[M];
int belong[N];
int n,a[N];
int p[M][M],cnt[M];
inline void rebuild(int id)
{
	cnt[id]=0;
	for(re int i=l[id]; i<=r[id]; ++i)
		p[id][++cnt[id]]=a[i];
	sort(p[id]+1,p[id]+1+cnt[id]);
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
int tag[M];
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
	if(belong[x]==belong[y])
	{
		int ans=0;
		for(re int i=x; i<=y; ++i)
			if(a[i]+tag[belong[i]]<val)
				++ans;
		return ans;
	}
	int ans=0;
	for(re int i=x; i<=r[belong[x]]; ++i)
		if(a[i]+tag[belong[i]]<val)
			++ans;
//	printf("%d\n",r[belong[x]]);
//	printf(" %d",ans);
	for(re int i=belong[x]+1; i<belong[y]; ++i)
		ans+=(int)(lower_bound(p[i]+1,p[i]+1+cnt[i],val-tag[i])-p[i]-1);

//	printf(" %d ",ans);
	for(re int i=l[belong[y]]; i<=y; ++i)
		if(a[i]+tag[belong[i]]<val)
			++ans;
	return ans;
}
int m;
char str[6];
int main()
{
	read(n),read(m);
	for(re int i=1; i<=n; ++i)
		read(a[i]);
	build();
	while(m--)
	{
		scanf("%s",str);
		int x,y,c;
		read(x),read(y),read(c);
		if(str[0]=='M')
			update(x,y,c);
		else if(str[0]=='A')
			printf("%d\n",y-x+1-query(x,y,c));
	}
	return 0;
}
