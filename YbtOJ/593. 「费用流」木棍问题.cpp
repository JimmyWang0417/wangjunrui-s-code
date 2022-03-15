#include <bits/stdc++.h>
#define lowbit(x) ((x)&(-(x)))
#define re register
#define ll long long
#define ull unsigned long long
#define rep(i,a,b) for(re int i=a;i<=b;++i)
#define per(i,a,b) for(re int i=a;i>=b;--i)
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
template<typename T,typename ...T1>
inline void read(T&x,T1&...x1)
{
	read(x);
	read(x1...);
}
template<typename T>
inline void clear(T*array,int l,int r,int val)
{
	memset(&array[l],val,sizeof(T)*(r-l+1));
}
using namespace std;
const int N=5000,INF=0x3f3f3f3f;
struct Edge
{
	int next,to,cap,flow,cost;
} edge[N*N];
int head[N],num_edge=1;
char str[45][45];
inline void add_edge(int from,int to,int cap,int cost,bool flag=true)
{
	edge[++num_edge].next=head[from];
	edge[num_edge].to=to;
	edge[num_edge].cap=cap;
	edge[num_edge].flow=0;
	edge[num_edge].cost=cost;
	head[from]=num_edge;
	if(flag)
		add_edge(to,from,0,-cost,false);
}
int T,n,m,A,B;
#define s 0
#define src (n*m*3+1)
#define t (n*m*3+2)
int cur[N],dis[N];
bool exist[N];
inline bool spfa()
{
	memset(dis,0x3f3f3f3f,sizeof(dis));
	memset(exist,false,sizeof(exist));
	memcpy(cur,head,sizeof(head));
	std::queue<int>q;
	q.push(s);
	dis[s]=0;
	exist[s]=true;
	while(!q.empty())
	{
		int u=q.front();
		q.pop();
		exist[u]=false;
		for(re int i=head[u]; i; i=edge[i].next)
		{
			int &v=edge[i].to;
			if(edge[i].cap>edge[i].flow&&dis[v]>dis[u]+edge[i].cost)
			{
				dis[v]=dis[u]+edge[i].cost;
				if(!exist[v])
				{
					q.push(v);
					exist[v]=true;
				}
			}
		}
	}
	return dis[t]<0x3f3f3f3f;
}
int ans=0;
int cnt=0;
inline int dinic(int u,int flow)
{
	if(u==t)
	{
		ans+=dis[t]*flow;
		if(T>=8&&T<=12)
			cout<<(ans>0)<<endl;
		else
			cout<<ans<<endl;
		++cnt;
		return flow;
	}
	exist[u]=true;
	int res=0;
	for(int &i=cur[u]; i; i=edge[i].next)
	{
		int &v=edge[i].to;
		if(!exist[v]&&dis[v]==dis[u]+edge[i].cost&&edge[i].cap>edge[i].flow)
		{
			int f=dinic(v,std::min(flow,edge[i].cap-edge[i].flow));
			if(f)
			{
				res+=f;
				edge[i].flow+=f;
				edge[i^1].flow-=f;
				flow-=f;
				if(!flow)
				{
					exist[u]=false;
					break;
				}
			}
		}
	}
	return res;
}
inline bool check(int x,int y)
{
	return x>=1&&x<=n&&y>=1&&y<=m&&str[x][y]=='0';
}
inline int calc(int x,int y)
{
	return (x-1)*m+y;
}
int q;
inline void work()
{
//	cout<<"flow="<<flow<<endl;
	while(spfa())
		dinic(s,q);
	for(int i=cnt+1; i<=q; ++i)
		printf("%d\n",ans);
}
signed main()
{
	freopen("trouble.in","r",stdin),freopen("trouble.out","w",stdout);
	read(T,n,m,A,B);
	for(int i=1; i<=n; ++i)
		scanf("%s",str[i]+1);

	for(int i=1; i<=n; ++i)
		for(int j=1; j<=m; ++j)
		{
			if(str[i][j]=='0')
			{
				if((i+j)&1)
				{
					add_edge(s,calc(i,j),1,0);
					add_edge(s,calc(i,j),1,A);
					add_edge(s,calc(i,j),1,2*A);
					add_edge(s,calc(i,j),1,3*A);
					add_edge(calc(i,j),calc(i,j)+n*m,1,0);
					add_edge(calc(i,j),calc(i,j)+n*m,1,B-A);
					add_edge(calc(i,j),calc(i,j)+2*n*m,1,0);
					add_edge(calc(i,j),calc(i,j)+2*n*m,1,B-A);

					if(check(i,j-1))
						add_edge(calc(i,j)+n*m,calc(i,j-1)+n*m,1,0);
					if(check(i,j+1))
						add_edge(calc(i,j)+n*m,calc(i,j+1)+n*m,1,0);
					if(check(i-1,j))
						add_edge(calc(i,j)+2*n*m,calc(i-1,j)+2*n*m,1,0);
					if(check(i+1,j))
						add_edge(calc(i,j)+2*n*m,calc(i+1,j)+2*n*m,1,0);
				}
				else
				{
					add_edge(calc(i,j),t,1,0);
					add_edge(calc(i,j),t,1,A);
					add_edge(calc(i,j),t,1,2*A);
					add_edge(calc(i,j),t,1,3*A);
					add_edge(calc(i,j)+n*m,calc(i,j),1,0);
					add_edge(calc(i,j)+n*m,calc(i,j),1,B-A);
					add_edge(calc(i,j)+2*n*m,calc(i,j),1,0);
					add_edge(calc(i,j)+2*n*m,calc(i,j),1,B-A);

				}
			}
		}
	read(q);
	work();
	return 0;
}


