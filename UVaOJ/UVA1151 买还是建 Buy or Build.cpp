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
int n,q,sum,cnt,t,father[1010],x[1010],y[1010],num_edge,minn;
inline int find(int&x)
{
	return father[x]==x?x:father[x]=find(father[x]);
}
struct node
{
	int size,point[1010],cost;
} a[1010];
struct Edge
{
	int from,to,dis;
} e[1000010];
inline bool comp(Edge a,Edge b)
{
	return a.dis<b.dis;
}
int main()
{
	re int fx,fy;
	read(t);
	while(t--)
	{
		read(n);
		read(q);
		num_edge=0;
		minn=0x7fffffff;
		for(re int i=1; i<=q; i++)
		{
			read(a[i].size);
			read(a[i].cost);
			for(re int j=1; j<=a[i].size; j++)
				read(a[i].point[j]);
		}
		for(re int i=1; i<=n; i++)
		{
			read(x[i]);
			read(y[i]);
		}
		for(re int i=1; i<=n; i++)
			for(re int j=i+1; j<=n; j++)
			{
				e[++num_edge].from=i;
				e[num_edge].to=j;
				e[num_edge].dis=(x[i]-x[j])*(x[i]-x[j])+(y[i]-y[j])*(y[i]-y[j]);
			}
		stable_sort(e+1,e+1+num_edge,comp);
		for(re int ans=0; ans<=(1<<q)-1; ans++)
		{
			sum=cnt=0;
			for(re int i=1; i<=n; i++)
				father[i]=i;
			for(re int i=1; i<=q; i++)
				if(ans&(1<<i-1))
				{
					sum+=a[i].cost;
					for(re int j=2; j<=a[i].size; j++)
					{
						fx=find(a[i].point[1]);
						fy=find(a[i].point[j]);
						if(fx==fy)
							continue;
						cnt++;
						father[fx]=fy;
					}
				}
			for(re int i=1; cnt<n-1; i++)
			{
				fx=find(e[i].from);
				fy=find(e[i].to);
				if(fx==fy)
					continue;
				cnt++;
				sum+=e[i].dis;
				father[fx]=fy;
			}
			if(sum<minn)
				minn=sum;
		}
		printf("%d\n",minn);
		if(t)
			puts("");
	}
	return 0;
}
