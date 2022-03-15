
// Problem : P1280 尼克的任务
// Contest : Luogu
// URL : https://www.luogu.com.cn/problem/P1280
// Memory Limit : 125 MB
// Time Limit : 1000 ms
// Powered by CP Editor (https://github.com/cpeditor/cpeditor)

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
inline void clear(T*a,int l,int r,int val)
{
	memset(&a[l],val,sizeof(T)*(r-l+1));
}
const int N=2e4+5;
int n,k,dp[N];
struct Edge{
	int next,to,dis;
}edge[N];
int num_edge,head[N];
inline void add_edge(int from,int to,int dis)
{
	edge[++num_edge].next=head[from];
	edge[num_edge].to=to;
	edge[num_edge].dis=dis;
	head[from]=num_edge;
}
using std::min;
signed main()
{
	memset(dp,0x3f,sizeof(dp));
	read(n,k);
	for(re int i=1;i<=k;++i)
	{
		int p,t;
		read(p,t);
		add_edge(p,p+t,t);
	}
	dp[1]=0;
	for(re int i=1;i<=n;++i)
		if(!head[i])
			add_edge(i,i+1,0);
	for(re int i=1;i<=n;++i)
	{
		for(re int e=head[i];e;e=edge[e].next)
			dp[edge[e].to]=min(dp[edge[e].to],dp[i]+edge[e].dis);
	}
	// for(re int i=1;i<=n+1;++i)
		// printf("%d ",dp[i]);
	// putchar('\n');
	printf("%d\n",n-dp[n+1]);
	return 0;
}

