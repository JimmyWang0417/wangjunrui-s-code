#include<cstdio>
#include<algorithm>
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
int tot,n,m,ans,sum,father[200];
struct Edge
{
	int x,y,z;
} edge[10000];
inline int find(int x)
{
	return x==father[x]?x:father[x]=find(father[x]);
}
inline bool comp(Edge a,Edge b)
{
	return a.z>b.z;
}
inline int min(const int a,const int b)
{
	return a<b?a:b;
}
int main()
{
	//freopen("span.in","r",stdin);
	//freopen("span.out","w",stdout);
	while(read(n),read(m),n||m)
	{
		sum=0x7fffffff;
		for(register int i=1; i<=m; i++)
		{
			read(edge[i].x);
			read(edge[i].y);
			read(edge[i].z);
		}
		sort(edge+1,edge+1+m,comp);
		for(register int e=1; e<=m; e++)
		{
			for(register int i=1; i<=n; i++)
				father[i]=i;
			ans=0;
			for(register int i=e; i<=m; i++)
			{
				int fx=find(edge[i].x),fy=find(edge[i].y);
				if(fx!=fy)
				{
					father[fx]=fy;
					ans++;
					if(ans==n-1)
					{
						sum=min(sum,edge[e].z-edge[i].z);
						break;
					}
				}
			}
		}
		if(sum==0x7fffffff)
			printf("-1\n");
		else
			printf("%d\n",sum);
	}
	return 0;
}
