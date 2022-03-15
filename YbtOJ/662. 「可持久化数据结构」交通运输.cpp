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
const int N=1e5+5;
int n;
struct Tree
{
	int l,r;
	int size;
} tree[N*100];
int cnt,root[N];
#define lc(rt) tree[rt].l
#define rc(rt) tree[rt].r
inline void update(int &rt,int pre,int l,int r,int pos,int val)
{
	rt=++cnt;
	tree[rt]=tree[pre];
	tree[rt].size+=val;
	if(l==r)
		return;
	int mid=(l+r)>>1;
	if(pos<=mid)
		update(lc(rt),lc(pre),l,mid,pos,val);
	else
		update(rc(rt),rc(pre),mid+1,r,pos,val);
}
inline int query(int rtl,int rtr,int l,int r,int x,int y)
{
	if(r<x||l>y)
		return 0;
	if(x<=l&&r<=y)
		return tree[rtr].size-tree[rtl].size;
	int mid=(l+r)>>1;
	return query(lc(rtl),lc(rtr),l,mid,x,y)+query(rc(rtl),rc(rtr),mid+1,r,x,y);
}
int C[N];
inline void add(int pos,int val)
{
	for(int i=pos; i<=n; i+=lowbit(i))
		C[i]+=val;
}
inline int query(int pos)
{
	int res=0;
	for(int i=pos; i; i-=lowbit(i))
		res+=C[i];
	return res;
}
inline int query(int l,int r)
{
	return query(r)-query(l-1);
}
int sum[N];
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
int dfn[N],size[N],id[N],dfstime;
inline void dfs1(int u)
{
	dfn[u]=++dfstime;
	id[dfstime]=u;
	size[u]=1;
	for(int i=head[u]; i; i=edge[i].next)
	{
		int &v=edge[i].to;
		dfs1(v);
		size[u]+=size[v];
	}
}
int dp[N];
inline void dfs2(int u)
{
	if(u!=1)
		add(size[u],1);



	int max1=0,max2=0;
	int minn=0x3f3f3f3f;
	for(int i=head[u]; i; i=edge[i].next)
	{
		int &v=edge[i].to;
		dfs2(v);
		if(size[v]>max1)
		{
			max2=max1;
			max1=size[v];
		}
		else if(size[v]>max2)
			max2=size[v];
		if(size[v]<minn)
			minn=size[v];
	}
	if(u!=1)
	{
		if(n-size[u]>max1)
		{
			max2=max1;
			max1=n-size[u];
		}
		else if(n-size[u]>max2)
			max2=n-size[u];
		if(n-size[u]<minn)
			minn=n-size[u];
		add(size[u],-1);
	}
//	printf("%d %d %d %d\n",u,minn,max1,max2);



	int L=max2,R=max1,&ans=dp[u]=max1;
//	printf("%d %d\n",L,R);
	while(L<=R)
	{
		int mid=(L+R)>>1;
		int l=max(1,max1-mid),r=min(n,mid-minn);
//		printf("%d %d\n",l,r);
		if(l>r)
		{
			L=mid+1;
			continue;
		}
		bool flag=0;
		for(int i=head[u]; i; i=edge[i].next)
		{
			int &v=edge[i].to;
//			printf("%d %d\n",v,size[v]);
			if(size[v]==max1)
			{
				int now=query(root[dfn[v]-1],root[dfn[v]+size[v]-1],1,n,l,r);
//				printf(" %d %d %d %d\n",dfn[v],dfn[v]+size[v]-1,l,r);
//				printf("%d\n",now);
				now-=(l<=size[v]&&size[v]<=r);
				if(now)
				{
					ans=mid;
					R=mid-1;
					flag=true;
					break;
				}
			}
		}
		if(flag)
			continue;
		if(n-size[u]==max1)
		{
			int now=sum[r]-sum[l-1]-query(root[dfn[u]-1],root[dfn[u]+size[u]-1],1,n,l,r)-query(l,r);
			if(now)
			{
				ans=mid;
				R=mid-1;
				continue;
			}
			int a=l+size[u],b=min(r+size[u],n);
			if(a<=n&&query(a,b))
			{
				ans=mid;
				R=mid-1;
				continue;
			}
		}
		L=mid+1;
	}
}
//inline void print(int &rt,int l,int r)
//{
//	if(!rt)
//		return;
//	if(l==r)
//	{
//		printf("%d ",l);
//		return;
//	}
//	int mid=(l+r)>>1;
//	print(lc(rt),l,mid);
//	print(rc(rt),mid+1,r);
//}
signed main()
{
	freopen("traffic.in","r",stdin);
	freopen("traffic.out","w",stdout);
	read(n);
	for(int i=2; i<=n; ++i)
	{
		int fa;
		read(fa);
		add_edge(fa,i);
	}
	dfs1(1);
//	putchar('\n');
	for(int i=2; i<=n; ++i)
		++sum[size[i]];
	for(int i=1; i<=n; ++i)
	{
		int u=id[i];
		update(root[i],root[i-1],1,n,size[u],1);
	}
//	for(int i=1; i<=n; ++i)
//		printf("%d ",size[i]);
//	putchar('\n');
	for(int i=2; i<=n; ++i)
		sum[i]+=sum[i-1];
//	for(int i=1; i<=n; ++i)
//	{
//		print(root[i],1,n);
//		putchar('\n');
//	}
	dfs2(1);
	for(int i=1; i<=n; ++i)
		printf("%d\n",dp[i]);
	return 0;
}


