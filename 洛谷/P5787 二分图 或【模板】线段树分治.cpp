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
const int N=5e5+5;
struct node
{
	int u,v;
} e[N];
int n,m,k;
vector<int>tree[N];
#define lc (rt<<1)
#define rc (rt<<1|1)
inline void update(int rt,int l,int r,int x,int y,int pos)
{
	if(r<x||l>y)
		return;
	if(x<=l&&r<=y)
	{
		tree[rt].push_back(pos);
		return;
	}
	int mid=(l+r)>>1;
	update(lc,l,mid,x,y,pos);
	update(rc,mid+1,r,x,y,pos);
}
int dis[N],dist[N];
int fa[N];
inline int find(int x)
{
	return fa[x]==x?x:find(fa[x]);
}
struct LASTSIZE
{
	int x,y;
	int distx,disty;
	LASTSIZE(int _u=0,int _v=0,int _distx=0,int _disty=0):x(_u),y(_v),distx(_distx),disty(_disty) {}
} st[N];
int top;
bool ans[N];
inline void solve(int rt,int l,int r,bool cur)
{
	if(!cur)
	{
		if(l==r)
			ans[l]=cur;
		else
		{
			int mid=(l+r)>>1;
			solve(lc,l,mid,cur);
			solve(rc,mid+1,r,cur);
		}
		return;
	}
	int lastsize=top;
	for(auto i:tree[rt])
	{
		int u=find(e[i].u),v=find(e[i].v),x=find(e[i].v+n),y=find(e[i].u+n);
		if(u==v||x==y)
		{
			cur=false;
			break;
		}
		if(dist[u]<dist[x])
			swap(u,x);
		fa[x]=u;

		if(dist[v]<dist[y])
			swap(v,y);
		fa[y]=v;

		st[++top]=LASTSIZE(x,y,dist[u],dist[v]);

		if(dist[u]==dist[x])
			++dist[u];

		if(dist[v]==dist[y])
			++dist[v];
	}
	if(l==r)
		ans[l]=cur;
	else
	{
		int mid=(l+r)>>1;
		solve(lc,l,mid,cur);
		solve(rc,mid+1,r,cur);
	}
	while(top>lastsize)
	{
		const LASTSIZE &u=st[top--];

		dist[fa[u.x]]=u.distx;
		dist[fa[u.y]]=u.disty;
		fa[u.x]=u.x;
		fa[u.y]=u.y;
	}
}
signed main()
{
	read(n,m,k);
	for(int i=1; i<=m; ++i)
	{
		int &u=e[i].u,&v=e[i].v,l,r;
		read(u,v,l,r);
		update(1,1,n,l+1,r,i);
	}
	for(int i=1; i<=n*2; ++i)
		fa[i]=i;
	solve(1,1,n,1);
	for(int i=1; i<=n; ++i)
		puts(ans[i]?"Yes":"No");
	return 0;
}


