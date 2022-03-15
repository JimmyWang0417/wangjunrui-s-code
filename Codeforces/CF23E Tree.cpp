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
const int N=705;
const int limit=1e9;
struct Bignumber
{
	ll g[50];
	Bignumber(int _x=0)
	{
		memset(g,0,sizeof(g));
		g[g[0]=1]=_x;
		if(g[1]>=limit)
		{
			g[g[0]=2]=1;
			g[1]-=limit;
		}
	}
	inline void operator = (const int _x)
	{
		memset(g,0,sizeof(g));
		g[g[0]=1]=_x;
		if(g[1]>=limit)
		{
			g[g[0]=2]=1;
			g[1]-=limit;
		}
	}
	inline Bignumber friend operator + (const Bignumber &a,const Bignumber &b)
	{
		Bignumber ans;
		for(int i=1; i<=a.g[0]||i<=b.g[0]; ++i)
		{
			ans.g[i]+=a.g[i]+b.g[i];
			if(ans.g[i]>=limit)
			{
				++ans.g[i+1];
				ans.g[i]-=limit;
			}
		}
		ans.g[0]=max(a.g[0],b.g[0]);
		while(ans.g[ans.g[0]+1])
		{
			++ans.g[0];
			ans.g[ans.g[0]+1]+=ans.g[ans.g[0]]/limit;
			ans.g[ans.g[0]]%=limit;
		}
		return ans;
	}
	inline Bignumber friend operator * (const Bignumber &a,const Bignumber &b)
	{
		Bignumber ans;
		for(int i=1; i<=a.g[0]; ++i)
		{
			ll x=0;
			for(int j=1; j<=b.g[0]; ++j)
			{
				ans.g[i+j-1]+=a.g[i]*b.g[j]+x;
				x=ans.g[i+j-1]/limit;
				ans.g[i+j-1]%=limit;
			}
			ans.g[i+b.g[0]]=x;
		}
		ans.g[0]=a.g[0]+b.g[0]-1;
		while(ans.g[ans.g[0]+1])
		{
			++ans.g[0];
			ans.g[ans.g[0]+1]+=ans.g[ans.g[0]]/limit;
			ans.g[ans.g[0]]%=limit;
		}
		return ans;
	}
	inline Bignumber friend max(const Bignumber &a,const Bignumber &b)
	{
		if(a.g[0]>b.g[0])
			return a;
		if(a.g[0]<b.g[0])
			return b;
		for(int i=(int)a.g[0]; i>=1; --i)
		{
			if(a.g[i]>b.g[i])
				return a;
			if(a.g[i]<b.g[i])
				return b;
		}
		return a;
	}
	inline void print()
	{
//		printf("%d\n",g[0]);
		printf("%lld",g[g[0]]);
		for(int i=(int)g[0]-1; i>=1; --i)
			printf("%09lld",g[i]);
		putchar('\n');
	}
};
struct Edge
{
	int next,to;
} edge[N*2];
int head[N],num_edge;
inline void add_edge(int from,int to)
{
	edge[++num_edge].next=head[from];
	edge[num_edge].to=to;
	head[from]=num_edge;
}
int n,size[N];
Bignumber dp[N][N];
inline void dfs(int u,int _fa)
{
	size[u]=1;
	dp[u][1]=1;
	for(int e=head[u]; e; e=edge[e].next)
	{
		int &v=edge[e].to;
		if(v==_fa)
			continue;
		dfs(v,u);
		for(int i=size[u]; i>=1; --i)
			for(int j=size[v]; j>=0; --j)
				dp[u][i+j]=max(dp[u][i+j],dp[u][i]*dp[v][j]);
		size[u]+=size[v];
	}
	for(int i=1; i<=size[u]; ++i)
		dp[u][0]=max(dp[u][0],dp[u][i]*(Bignumber)i);
}
signed main()
{
//	printf("%lldMB\n",sizeof(dp)/(1<<20));
	read(n);
	for(int i=1; i<n; ++i)
	{
		int u,v;
		read(u,v);
		add_edge(u,v);
		add_edge(v,u);
	}
	dfs(1,0);
	dp[1][0].print();
	return 0;
}


