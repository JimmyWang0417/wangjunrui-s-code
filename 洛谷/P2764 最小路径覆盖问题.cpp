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
const int N=6005*2;
int n,m;
int head[N],num_edge;
struct Edge
{
	int next,to;
} edge[N];
inline void add_edge(int from,int to)
{
	edge[++num_edge].next=head[from];
	edge[num_edge].to=to;
	head[from]=num_edge;
}
bitset<N>vis,exist;
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
inline void print(int u)
{
	if(belong[u+n])
		print(belong[u+n]);
	printf("%d ",u);
}
signed main()
{
	read(n,m);
	for(int i=1; i<=m; ++i)
	{
		int u,v;
		read(u,v);
		add_edge(u,v+n);
	}
	int ans=0;
	for(int i=1; i<=n; ++i)
	{
		if(find(i))
			++ans;
		else
			exist.set(i);
		vis.reset();
	}
	for(int i=1; i<=n; ++i)
	{
		if(exist[i])
		{
			print(i);
			putchar('\n');
		}
	}
	printf("%d\n",n-ans);
	return 0;
}


