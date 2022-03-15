#include <bits/stdc++.h>
#define int unsigned int 
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
const int N=5005,M=N*N*2;
struct Edge
{
	int next,to;
} edge[M];
int head[M],num_edge;
inline void add_edge(int from,int to)
{
	edge[++num_edge].next=head[from];
	edge[num_edge].to=to;
	head[from]=num_edge;
}
int dfn[N*2],low[N*2],dfstime;
int st[N*2],top;
int belong[N*2],col;
inline void tarjan(int u)
{
	dfn[u]=low[u]=++dfstime;
	st[++top]=u;
	for(int i=head[u]; i; i=edge[i].next)
	{
		int &v=edge[i].to;
		if(!dfn[v])
		{
			tarjan(v);
			low[u]=min(low[u],low[v]);
		}
		else if(!belong[v])
			low[u]=min(low[u],dfn[v]);
	}
	if(dfn[u]==low[u])
	{
		belong[u]=++col;
		while(st[top]!=u)
			belong[st[top--]]=col;
		--top;
	}
}
int n;
int out[N];
bool g[N][N];
int outa[N],outb[N];
signed main()
{
	freopen("conspiracy.in", "r", stdin);
	freopen("conspiracy.out", "w", stdout);
	read(n);
	for(int i=1; i<=n; ++i)
	{
		read(out[i]);
		for(int j=1; j<=out[i]; ++j)
		{
			int val;
			read(val);
			g[i][val]=true;
		}
	}
	for(int i=1; i<=n; ++i)
		for(int j=i+1; j<=n; ++j)
		{
			if(g[i][j])
			{
				add_edge(i,j+n);
				add_edge(j,i+n);
			}
			else
			{
				add_edge(i+n,j);
				add_edge(j+n,i);
			}
		}
	for(int i=1; i<=2*n; ++i)
		if(!dfn[i])
			tarjan(i);
	vector<int>A,B;
	for(int i=1; i<=n; ++i)
	{
		if(belong[i]==belong[i+n])
		{
			printf("0\n");
//			printf("%d\n",i);
			return 0;
		}
		else if(belong[i]<belong[i+n])
			A.push_back(i);
		else B.push_back(i);
	}
	int ans=(A.size()&&B.size());
//	for(auto v:A)
//		printf("%d ",v);
//	putchar('\n');
//	for(auto v:B)
//		printf("%d ",v);
//	putchar('\n');
	for(auto a:A)
		for(auto b:B)
			if(g[a][b])
				++outb[a];
	for(auto a:A)
		for(auto b:B)
			if(!g[a][b])
				++outa[b];
//	putchar('\n');
//	for(auto i:A)
//		printf("%d %d\n",i,outb[i]);
//	putchar('\n');
//	for(auto i:B)
//		printf("%d %d\n",i,outb[i]);
//	putchar('\n');

	for(auto u:A)
		if(outb[u]==B.size()&&A.size()>1)
			++ans;
	for(auto u:B)
		if(outa[u]==A.size()&&B.size()>1)
			++ans;
	for(auto a:A)
		for(auto b:B)
			if(outb[a]==B.size()||(outb[a]==B.size()-1&&!g[a][b]))
				if(outa[b]==A.size()||(outa[b]==A.size()-1&&g[a][b]))
					++ans;
	printf("%d\n",ans);
	return 0;
}

