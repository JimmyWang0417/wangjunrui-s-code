#include<cstdio>
#include<cstring>
#define re register
#define ll long long
#define min(x,y) ((x)>(y)?y:x)
#define max(x,y) ((x)>(y)?x:y)
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
const int N=1e4+5;
struct Edge
{
	int next,to;
} edge[N<<1];
int num_edge,head[N];
inline void add_edge(int from,int to)
{
	edge[++num_edge].next=head[from];
	edge[num_edge].to=to;
	head[from]=num_edge;
}
int n,dp[N][3];
inline void DP(int u,int fa)
{
	dp[u][0]=1,dp[u][1]=0,dp[u][2]=N;
	for(re int i=head[u]; i; i=edge[i].next)
	{
		int &v=edge[i].to;
		if(v==fa)
			continue;
		DP(v,u);
		dp[u][0]+=min(dp[v][0],dp[v][1]);
		dp[u][1]+=dp[v][2];
	}
	for(re int i=head[u]; i; i=edge[i].next)
	{
		int &v=edge[i].to;
		if(v==fa)
			continue;
		dp[u][2]=min(dp[u][2],dp[u][1]-dp[v][2]+dp[v][0]);
	}
}
int main()
{
	//freopen("ans.in","r",stdin);
	//freopen("ans.out","w",stdout);
	re int opt;
	while(true)
	{
		read(n);
		for(re int i=1,a,b; i<n; ++i)
		{
			read(a),read(b);
			add_edge(a,b);
			add_edge(b,a);
		}
		DP(1,1);
		printf("%d\n",min(dp[1][0],dp[1][2]));
		/*for(int i=1; i<=n; ++i)
			printf("%d %d %d\n",dp[i][0],dp[i][1],dp[i][2]);*/
		num_edge=0;
		memset(head,0,sizeof(head));
		read(opt);
		if(opt==-1)
			return 0;
	}
	return 0;
}
