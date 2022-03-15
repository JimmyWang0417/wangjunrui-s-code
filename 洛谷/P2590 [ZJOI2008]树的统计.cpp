#include<cstdio>
#include<algorithm>
using namespace std;
template<typename T>
inline void read(T&x)
{
	x=0;
	char s=getchar();
	bool f=false;
	while(!(s>='0'&&s<='9'))
	{
		if(s=='-')
			f=true;
		s=getchar();
	}
	while(s>='0'&&s<='9')
	{
		x=(x<<1)+(x<<3)+s-'0';
		s=getchar();
	}
	if(f)
		x=(~x)+1;
	return;
}
const int N=30010;
#define re register
#define M N<<1
#define T N<<2
int n,m,summ,maxx,tot;
int seg[N],rev[T],size[N],son[N],top[N],dep[N];
int num[N],father[N];
int head[N];
struct Edge
{
	int next,to;
} edge[M];
struct Tree
{
	int sum,max;
} tree[T];
inline void add_edge(int from,int to)
{
	edge[++tot].next=head[from];
	edge[tot].to=to;
	head[from]=tot;
}
inline void build(int k,int l,int r)
{
	int mid=l+r>>1;
	if(l==r)
	{
		tree[k].sum=tree[k].max=num[rev[l]];
		return;
	}
	build(k<<1,l,mid);
	build(k<<1|1,mid+1,r);
	tree[k].sum=tree[k<<1].sum+tree[k<<1|1].sum;
	tree[k].max=max(tree[k<<1].max,tree[k<<1|1].max);
	return;
}
inline void change(int k,int l,int r,int val,int pos)
{
	if(pos<l||pos>r)
		return;
	if(l==r)
	{
		tree[k].sum=tree[k].max=val;
		return;
	}
	int mid=l+r>>1;
	change(k<<1,l,mid,val,pos);
	change(k<<1|1,mid+1,r,val,pos);
	tree[k].sum=tree[k<<1].sum+tree[k<<1|1].sum;
	tree[k].max=max(tree[k<<1].max,tree[k<<1|1].max);
	return;
}
inline void query(int k,int l,int r,int x,int y)
{
	if(x>r||y<l)
		return;
	if(l>=x&&r<=y)
	{
		summ+=tree[k].sum;
		maxx=max(maxx,tree[k].max);
		return;
	}
	int mid=l+r>>1,res=0;
	query(k<<1,l,mid,x,y);
	query(k<<1|1,mid+1,r,x,y);
	return;
}
inline void dfs1(int u,int f)
{
	size[u]=1;
	father[u]=f;
	dep[u]=dep[f]+1;
	for(re int i=head[u]; i; i=edge[i].next)
	{
		int &v=edge[i].to;
		if(v==f)
			continue;
		dfs1(v,u);
		size[u]+=size[v];
		if(size[v]>size[son[u]])
			son[u]=v;
	}
	return;
}
inline void dfs2(int u)
{
	if(son[u])
	{
		seg[son[u]]=++seg[0];
		top[son[u]]=top[u];
		rev[seg[0]]=son[u];
		dfs2(son[u]);
	}
	for(re int i=head[u]; i; i=edge[i].next)
	{
		int &v=edge[i].to;
		if(top[v])
			continue;
		seg[v]=++seg[0];
		rev[seg[0]]=v;
		top[v]=v;
		dfs2(v);
	}
	return;
}
inline void ask(int x,int y)
{
	int fx=top[x],fy=top[y];
	while(fx!=fy)
	{
		if(dep[fx]<dep[fy])
		{
			swap(x,y);
			swap(fx,fy);
		}
		query(1,1,seg[0],seg[fx],seg[x]);
		x=father[fx];
		fx=top[x];
	}
	if(dep[x]>dep[y])
		swap(x,y);
	query(1,1,seg[0],seg[x],seg[y]);
}
char s[110];
int main()
{
	read(n);
	for(re int i=1,x,y; i<n; ++i)
	{
		read(x),read(y);
		add_edge(x,y);
		add_edge(y,x);
	}
	for(re int i=1; i<=n; ++i)
		read(num[i]);
	dfs1(1,0);
	seg[0]=seg[1]=top[1]=rev[1]=1;
	dfs2(1);
	build(1,1,seg[0]);
	read(m);
	for(re int i=1,x,y; i<=m; ++i)
	{
		scanf("%s",s+1);
		read(x),read(y);
		if(s[1]=='C')
			change(1,1,seg[0],y,seg[x]);
		else if(s[1]=='Q')
		{
			summ=0;
			maxx=~0x7fffffff;
			ask(x,y);
			if(s[2]=='M')
				printf("%d\n",maxx);
			else if(s[2]=='S')
				printf("%d\n",summ);
		}
	}
	return 0;
}
