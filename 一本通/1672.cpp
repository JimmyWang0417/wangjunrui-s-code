#include<cstdio>
#include<algorithm>
#define re register
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
const int N=200010;
int n,father[N];
int ans;
inline int find(int x)
{
	return x!=father[x]?father[x]=find(father[x]):x;
}
struct node
{
	int w,t;
} a[N];
inline bool comp(const node a,const node b)
{
	return a.w>b.w||a.w==b.w&&a.t>b.t;
}
int main()
{
	read(n);
	for(re int i=1; i<=n; i++)
	{
		read(a[i].t);
		if(a[i].t>n)
			a[i].t=n;
		read(a[i].w);
		father[i]=i;
	}
	stable_sort(a+1,a+1+n,comp);
	for(re int i=1,x; i<=n; i++)
	{
		x=find(a[i].t);
		if(x==0)
			continue;
		ans+=a[i].w;
		father[x]=x-1;
	}
	printf("%d\n",ans);
	return 0;
}
