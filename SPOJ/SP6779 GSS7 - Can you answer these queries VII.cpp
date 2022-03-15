#include<cstdio>
#include<algorithm>
using namespace std;

#define ll long long
#define re register
#define lc (rt<<1)
#define rc (rt<<1|1)

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
	return;
}

const int N=1e6+10;
struct Edge
{
	int next,to;
	Edge() {}
	Edge(int x,int y):next(x),to(y) {}
} edge[N<<1];
int num_edge,head[N];
inline void add_edge(int from,int to)
{
	edge[++num_edge]=Edge(head[from],to);
	head[from]=num_edge;
}

#define size sze
int rk[N],dep[N],top[N],father[N],size[N],son[N],idx[N];
int dfstime;
inline void dfs1(int u,int f)
{
	dep[u]=dep[f]+1;
	father[u]=f;
	size[u]=1;
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
inline void dfs2(int u,int tp)
{
	idx[u]=++dfstime;
	rk[dfstime]=u;
	top[u]=tp;
	if(!son[u])
		return;
	dfs2(son[u],tp);
	for(re int i=head[u]; i; i=edge[i].next)
	{
		int &v=edge[i].to;
		if(idx[v])
			continue;
		dfs2(v,v);
	}
	return;
}

struct Tree
{
	int suf,pre,sum,ans,tag;
	bool flag;
	Tree()
	{
		suf=pre=sum=ans=0;
	}
} tree[N<<2];
inline void upd(int rt,int l,int r,int val)
{
	tree[rt].sum=(r-l+1)*val;
	tree[rt].suf=tree[rt].pre=tree[rt].ans=max(0,tree[rt].sum);
	tree[rt].tag=val;
	tree[rt].flag=true;
}
inline void pushdown(int rt,int l,int r)
{
	if(!tree[rt].flag)
		return;
	int mid=(l+r)>>1;
	upd(lc,l,mid,tree[rt].tag);
	upd(rc,mid+1,r,tree[rt].tag);
	tree[rt].tag=0;
	tree[rt].flag=false;
}
inline Tree calc(Tree L,Tree R)
{
	Tree ans;
	ans.suf=max(R.suf,L.suf+R.sum);
	ans.pre=max(L.pre,L.sum+R.pre);
	ans.sum=L.sum+R.sum;
	ans.ans=max(max(L.ans,R.ans),L.suf+R.pre);
	ans.tag=0;
	ans.flag=false;
	return ans;
}
int n,m,a[N];
inline void build(int rt,int l,int r)
{
	if(l==r)
	{
		tree[rt].sum=a[rk[l]];
		tree[rt].suf=tree[rt].pre=tree[rt].ans=max(a[rk[l]],0);
		tree[rt].flag=false;
		return;
	}
	int mid=(l+r)>>1;
	build(lc,l,mid);
	build(rc,mid+1,r);
	tree[rt]=calc(tree[lc],tree[rc]);
}
inline void change(int rt,int l,int r,int x,int y,int val)
{
	if(x<=l&&r<=y)
	{
		upd(rt,l,r,val);
		return;
	}
	pushdown(rt,l,r);
	int mid=(l+r)>>1;
	if(x<=mid)
		change(lc,l,mid,x,y,val);
	if(mid<y)
		change(rc,mid+1,r,x,y,val);
	tree[rt]=calc(tree[lc],tree[rc]);
}
inline Tree query(int rt,int l,int r,int x,int y)
{
	if(x<=l&&r<=y)
		return tree[rt];
	int mid=(l+r)>>1;
	pushdown(rt,l,r);
	if(y<=mid)
		return query(lc,l,mid,x,y);
	if(mid<x)
		return query(rc,mid+1,r,x,y);
	return calc(query(lc,l,mid,x,y),query(rc,mid+1,r,x,y));
}
inline void update(int x,int y,int val)
{
	while(top[x]!=top[y])
	{
		if(dep[top[x]]<dep[top[y]])
			swap(x,y);
		change(1,1,n,idx[top[x]],idx[x],val);
		x=father[top[x]];
	}
	if(dep[x]>dep[y])
		swap(x,y);
	change(1,1,n,idx[x],idx[y],val);
}
inline Tree ask(int x,int y)
{
	Tree L,R;
	while(top[x]!=top[y])
	{
		if(dep[top[x]]>dep[top[y]])
		{
			L=calc(query(1,1,n,idx[top[x]],idx[x]),L);
			x=father[top[x]];

		}
		else
		{
			R=calc(query(1,1,n,idx[top[y]],idx[y]),R);
			y=father[top[y]];
		}
	}
	if(dep[x]<dep[y])
		R=calc(query(1,1,n,idx[x],idx[y]),R);
	else
		L=calc(query(1,1,n,idx[y],idx[x]),L);
	swap(L.suf,L.pre);
	return calc(L,R);
}
int main()
{
	read(n);
	for(re int i=1; i<=n; ++i)
		read(a[i]);
	for(re int i=1; i<n; ++i)
	{
		int u,v;
		read(u),read(v);
		add_edge(u,v);
		add_edge(v,u);
	}
	dfs1(1,0);
	dfs2(1,1);
	build(1,1,n);
//	for(re int i=1; i<=n; ++i)
//		printf("%d %d %d %d %d %d %d\n",size[i],rk[i],top[i],idx[i],son[i],dep[i],father[i]);
	read(m);
	while(m--)
	{
		int opt,l,r,val;
		read(opt);
		if(opt==1)
		{
			read(l),read(r);
			printf("%d\n",ask(l,r).ans);
		}
		else if(opt==2)
		{
			read(l),read(r),read(val);
			update(l,r,val);
		}
//		for(re int i=1;i<=(n<<2);++i)
//		printf("%d %d %d %d %d\n",tree[i].suf,tree[i].pre,tree[i].sum,tree[i].ans.)
	}
}
