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
struct node
{
	int u,v,w;
} e[100010];
int father[100010];
inline bool cmp(node a,node b)
{
	return a.w<b.w;
}
inline int find(const int &x)
{
	return father[x]==0?x:father[x]=find(father[x]);
}
int n,point[100010];
long long ans;
int main()
{
	read(n);
	for(re int i=1; i<n; i++)
	{
		point[i]=1;
		read(e[i].u);
		read(e[i].v);
		read(e[i].w);
		ans+=e[i].w;
	}
	point[n]=1;
	sort(e+1,e+n,cmp);
	for(re int i=1,fa,fb; i<n; i++)
	{
		fa=find(e[i].u);
		fb=find(e[i].v);
		if(fa!=fb)
		{
			ans+=(((long long)point[fa])*point[fb]-1)*(e[i].w+1);
			father[fa]=fb;
			point[fb]+=point[fa];
		}
	}
	printf("%lld\n",ans);
	return 0;
}

