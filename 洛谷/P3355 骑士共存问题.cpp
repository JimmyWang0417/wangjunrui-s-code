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
const int N=5e5+5;
const int dx[8]= {1,-1,1,-1,2,-2,2,-2};
const int dy[8]= {2,2,-2,-2,1,1,-1,-1};
bool vis[N];
int belong[N];
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
bool mp[1005][1005];
inline bool check(int x,int y)
{
	return (x>=1&&x<=n&&y>=1&&y<=n&&!mp[x][y]);
}
inline int calc(int x,int y)
{
	return (x-1)*n+y;
}
inline bool find(int u)
{
	for(re int i=head[u]; i; i=edge[i].next)
	{
		int &v=edge[i].to;
		if(vis[v])
			continue;
		vis[v]=true;
		if(!belong[v]||find(belong[v]))
		{
			belong[v]=u;
			return true;
		}
	}
	return false;
}
signed main()
{
	read(n,m);
	for(re int i=1; i<=m; ++i)
	{
		int x,y;
		read(x,y);
		mp[x][y]=true;
	}
	for(re int i=1; i<=n; ++i)
		for(re int j=1; j<=n; ++j)
		{
			if(!check(i,j)||!((i+j)&1))
				continue;
			for(re int d=0; d<8; ++d)
			{
				const int x=i+dx[d],y=j+dy[d];
				if(check(x,y))
					add_edge(calc(i,j),calc(x,y));
			}
		}
	int ans=0;
//	for(re int u=1; u<=n*m; ++u)
//	{
//		printf("%d:",u);
//		for(re int i=head[u]; i; i=edge[i].next)
//			printf(" %d",edge[i].to-n*m);
//		putchar('\n');
//	}
	for(re int i=1; i<=n; ++i)
		for(re int j=1; j<=n; ++j)
		{
			if(!check(i,j)||!((i+j)&1))
				continue;
			clear(vis,1,n*n,0);
			if(find(calc(i,j)))
				++ans;
		}
	printf("%d\n",n*n-ans-m);
	return 0;
}
