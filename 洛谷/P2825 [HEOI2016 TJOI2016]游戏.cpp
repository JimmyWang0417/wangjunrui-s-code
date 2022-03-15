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
const int N=1000+5;
int n,m;
char str[N][N];
struct node
{
	int x,y;
} a[N][N];
int cntx,cnty;
struct Edge
{
	int next,to;
} edge[N*N];
int head[N],num_edge;
inline void add_edge(int from,int to)
{
	edge[++num_edge].next=head[from];
	edge[num_edge].to=to;
	head[from]=num_edge;
}
inline void init()
{
	for(int i=1; i<=n; ++i)
	{
		++cntx;
		for(int j=1; j<=m; ++j)
		{
			if(str[i][j]=='#')
				++cntx;
			else
				a[i][j].x=cntx;
		}
	}
	for(int j=1; j<=m; ++j)
	{
		++cnty;
		for(int i=1; i<=n; ++i)
		{
			if(str[i][j]=='#')
				++cnty;
			else
				a[i][j].y=cnty;
		}
	}
}
bitset<N>vis;
int belong[N];
inline bool find(int u)
{
	for(int i=head[u]; i; i=edge[i].next)
	{
		int &v=edge[i].to;
		if(vis[v])
			continue;
		vis.set(v);
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
//	freopen("bomb.in","r",stdin),freopen("bomb.out","w",stdout);
	read(n,m);
	for(int i=1; i<=n; ++i)
		scanf("%s",str[i]+1);
	init();
	for(int i=1; i<=n; ++i)
		for(int j=1; j<=m; ++j)
			if(str[i][j]=='*')
				add_edge(a[i][j].x,a[i][j].y);
//	printf("%d\n",num_edge);
	int ans=0;
	for(int i=1; i<=cntx; ++i)
	{
		if(find(i))
			++ans;
		vis.reset();
	}
	printf("%d\n",ans);
	return 0;
}


