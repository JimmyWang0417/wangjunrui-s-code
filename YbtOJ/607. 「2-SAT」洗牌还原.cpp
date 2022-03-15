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
const int N=4005;
int n;
int mp[N],cnt;
int l1[N],l2[N],r1[N],r2[N];
inline bool check(int x1,int x2,int y1,int y2)
{
	return (x1<y1&&y2<x2)||(y1<x1&&x2<y2);
}
inline bool calc(int a,int b)
{
	return check(l1[a],r1[a],l1[b],r1[b])||check(l2[a],r2[a],l1[b],r1[b])||
	       check(l2[a],r2[a],l1[b],r1[b])||check(l2[a],r2[a],l2[b],r2[b]);
}
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
int dfn[N],low[N],dfstime;
int st[N],top;
int belong[N],col;
inline void tarjan(int u)
{
	low[u]=dfn[u]=++dfstime;
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
	if(low[u]==dfn[u])
	{
		belong[u]=++col;
		while(st[top]!=u)
			belong[st[top--]]=col;
		--top;
	}
}
int ans[N];
#define opp(x) (x>cnt?x-cnt:x+cnt)
signed main()
{
	freopen("wash.in","r",stdin),freopen("wash.out","w",stdout);
	read(n);
	vector<int>a[N];
	for(int i=1; i<=n; ++i)
	{
		int val;
		read(val);
		if(!mp[val])
			mp[val]=++cnt;
		a[mp[val]].push_back(i);
	}
	for(int i=1; i<=cnt; ++i)
		if(a[i].size()==2)
		{
			l1[i]=l1[i+cnt]=l2[i]=l2[i+cnt]=a[i][0];
			r1[i]=r1[i+cnt]=r2[i]=r2[i+cnt]=a[i][1];
		}
		else
		{
			l1[i]=l1[i+cnt]=a[i][0];
			r1[i]=l2[i+cnt]=a[i][1];
			l2[i]=r1[i+cnt]=a[i][2];
			r2[i]=r2[i+cnt]=a[i][3];
		}
	for(int i=1; i<=2*cnt; ++i)
		for(int j=i+1; j<=2*cnt; ++j)
			if(opp(i)!=j&&calc(i,j))
			{
				add_edge(i,opp(j));
				add_edge(j,opp(i));
			}
	for(int i=1; i<=2*cnt; ++i)
		if(!dfn[i])
			tarjan(i);
	for(int i=1; i<=cnt; ++i)
		ans[r1[belong[i]<belong[i+cnt]?i:i+cnt]]=ans[r2[i]]=1;
	for(int i=1; i<=n; ++i)
		printf("%d",ans[i]);
	putchar('\n');
	return 0;
}

