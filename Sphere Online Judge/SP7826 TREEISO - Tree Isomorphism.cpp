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
const int N=1e4+5;
int prime[N],tot;
bitset<N>vis;
inline void getprime(int n)
{
	vis.set(1);
	for(int i=2; i<=n; ++i)
	{
		if(!vis[i])
			prime[++tot]=i;
		for(int j=1; j<=tot; ++j)
		{
			if(prime[tot]*i>n)
				break;
			vis.set(i*prime[j]);
			if(i%prime[j]==0)
				break;
		}
	}
}
struct Edge
{
	int next,to;
} edge[N];
int head[N],num_edge;
inline void add_edge(int from,int to)
{
	edge[++num_edge].next=head[from];
	edge[num_edge].to=to;
	head[from]=num_edge;
}
int n,m;
int size[N];
ull dp[N];
inline void dfs(int u,int fa)
{
//	printf("%d ",u);
	dp[u]=size[u]=1;
	for(int i=head[u]; i; i=edge[i].next)
	{
		int &v=edge[i].to;
		if(v==fa)
			continue;
		dfs(v,u);
		size[u]+=size[v];
		dp[u]+=dp[v]*prime[size[v]];
	}
}
unordered_map<ull,int>mp;
signed main()
{
//	freopen("tree.in","r",stdin);
//	freopen("tree.out","w",stdout);
	getprime(1000);
	read(m);
	for(int kase=1; kase<=m; ++kase)
	{
		memset(head,num_edge=0,sizeof(head));
		read(n);
		for(int i=1; i<=n; ++i)
		{
			int u,v;
			read(u,v);
			add_edge(u,v);
			add_edge(v,u);
		}
		int root=1;
		dfs(root,0);
//		putchar('\n');
		if(mp[dp[root]])
		{
			printf("NO\n");
			continue;
		}
		else
			mp[dp[root]]=kase;
		printf("YES\n");
		for(root=2; root<=n; ++root)
		{
			dfs(root,0);
//			putchar('\n');
			mp[dp[root]]=kase;
		}
	}
	return 0;
}


