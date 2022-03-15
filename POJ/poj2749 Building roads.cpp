#include <cstdio>
#include <cstring>
#include <iostream>
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
//s1 :0
//s2 :1
template<typename T>
inline void clear(T*array,int l,int r,int val)
{
	memset(&array[l],val,sizeof(T)*(r-l+1));
}
const int N=1e6+5;
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
using std::min;
int dfn[N],low[N],dfstime;
int st[N],top;
int belong[N],color;
inline void tarjan(int u)
{
	dfn[u]=low[u]=++dfstime;
	st[++top]=u;
	for(re int i=head[u]; i; i=edge[i].next)
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
		belong[u]=++color;
		while(st[top]!=u)
			belong[st[top--]]=color;
		--top;
	}
}
int n,na,nb,sx1,sy1,sx2,sy2;
int a[N],b[N],len;
int ax[N],ay[N];
int bx[N],by[N];
inline bool check(int val)
{
	clear(dfn,1,2*n,0);
	clear(belong,1,2*n,0);
	clear(head,1,2*n,0);
	num_edge=color=top=dfstime=0;
	for(re int i=1; i<=n; ++i)
		for(re int j=i+1; j<=n; ++j)
		{
			if(a[i]+a[j]>val)
			{
				add_edge(i,i+n);
				add_edge(j,j+n);
			}
			if(b[i]+b[j]>val)
			{
				add_edge(i+n,i);
				add_edge(j+n,j);
			}
			if(a[i]+b[j]+len>val)
			{
				add_edge(i,j);
				add_edge(j+n,i+n);
			}
			if(b[i]+a[j]+len>val)
			{
				add_edge(j,i);
				add_edge(i+n,j+n);
			}
		}
	for(re int i=1; i<=na; ++i)
	{
		int &x=ax[i],&y=ay[i];
		add_edge(x,y+n);
		add_edge(y,x+n);
		add_edge(x+n,y);
		add_edge(y+n,x);
	}
	for(re int i=1; i<=nb; ++i)
	{
		int &x=bx[i],&y=by[i];
		add_edge(x,y);
		add_edge(y,x);
		add_edge(x+n,y+n);
		add_edge(y+n,x+n);
	}
	for(re int i=1; i<=2*n; ++i)
		if(!dfn[i])
			tarjan(i);
	for(re int i=1; i<=n; ++i)
		if(belong[i]==belong[i+n])
			return false;
	return true;
}
signed main()
{
	while(scanf("%d",&n)!=EOF)
	{
		read(na),read(nb),read(sx1),read(sy1),read(sx2),read(sy2);
		len=abs(sx1-sx2)+abs(sy1-sy2);
		for(re int i=1; i<=n; ++i)
		{
			int x,y;
			read(x),read(y);
			a[i]=abs(x-sx1)+abs(y-sy1);
			b[i]=abs(x-sx2)+abs(y-sy2);
		}
		for(re int i=1; i<=na; ++i)
			read(ax[i]),read(ay[i]);
		for(re int i=1; i<=nb; ++i)
			read(bx[i]),read(by[i]);
//	printf("%d\n",check(1));
		int l=0,r=1e7,ans=-1;
		while(l<=r)
		{
			int mid=(l+r)>>1;
			if(check(mid))
			{
				ans=mid;
				r=mid-1;
			}
			else l=mid+1;
		}
		printf("%d\n",ans);
	}

	return 0;
}
