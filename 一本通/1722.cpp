#include<cstdio>
#include<queue>
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
const int N=2e5+10,M=1e6+10;
vector<int>father[N];
int head[N],n,num_edge,r[N];
long long s[N],k[N],dis[N];
bool exist[N];
struct Edge
{
	int next,to;
} edge[M<<2];
inline void add_edge(const int &from,const int &to)
{
	edge[++num_edge].next=head[from];
	head[from]=num_edge;
	edge[num_edge].to=to;
}
queue<int>q;
int main()
{
	read(n);
	for(re int i=1; i<=n; i++)
	{
		read(s[i]);
		read(k[i]);
		dis[i]=k[i];
		q.push(i);
		exist[i]=true;
		read(r[i]);
		for(re int j=1,x; j<=r[i]; j++)
		{
			read(x);
			add_edge(i,x);
			father[x].push_back(i);
		}
	}
	int u;
	long long sum;
	while(!q.empty())
	{
		u=q.front();
		q.pop();
		exist[u]=false;
		sum=s[u];
		for(re int i=head[u]; i; i=edge[i].next)
		{
			int &v=edge[i].to;
			sum+=dis[v];
			if(sum>=dis[u])
				break;
		}
		if(dis[u]>sum)
		{
			dis[u]=sum;
			for(re int i=0; i<father[u].size(); i++)
				if(!exist[father[u][i]])
				{
					exist[father[u][i]]=true;
					q.push(father[u][i]);
				}
		}
	}
	printf("%lld\n",dis[1]);
	return 0;
}
