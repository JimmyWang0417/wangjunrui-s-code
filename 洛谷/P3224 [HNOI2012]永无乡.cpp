#include <cstdio>
#define ll long long
#define re register
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
const int N=1e5+5;
int root[N];
struct Tree
{
	int id;
	int l,r;
	int size;
} tree[N*40];
#define lc(x) tree[x].l
#define rc(x) tree[x].r
int cnt;
inline void pushup(int &rt)
{
	tree[rt].size=tree[lc(rt)].size+tree[rc(rt)].size;
}
inline void update(int &rt,int l,int r,int pos,int val,int id)
{
	if(!rt)
		rt=++cnt;
	if(l==r)
	{
		tree[rt].id=id;
		tree[rt].size+=val;
		return;
	}
	int mid=(l+r)>>1;
	if(pos<=mid)
		update(lc(rt),l,mid,pos,val,id);
	else
		update(rc(rt),mid+1,r,pos,val,id);
	pushup(rt);
}
inline int merge(int x,int y,int l=1,int r=1e5)
{
	if(!x||!y)
		return x|y;
	if(l==r)
	{
		tree[x].size+=tree[y].size;
		return x;
	}
	int mid=(l+r)>>1;
	lc(x)=merge(lc(x),lc(y),l,mid);
	rc(x)=merge(rc(x),rc(y),mid+1,r);
	pushup(x);
	return x;
}
inline int query(int &rt,int l,int r,int rk)
{
	if(l==r)
		return tree[rt].id;
	int mid=(l+r)>>1;
	if(rk<=tree[lc(rt)].size)
		return query(lc(rt),l,mid,rk);
	else
		return query(rc(rt),mid+1,r,rk-tree[lc(rt)].size);
}
int fa[N];
inline int find(int x)
{
	if(!fa[x])
		return x;
	return fa[x]=find(fa[x]);
}
int main()
{
	int n,m,q;
	read(n),read(m);
	for(re int i=1; i<=n; ++i)
	{
		int val;
		read(val);
		update(root[i],1,1e5,val,1,i);
//		printf("%d\n",tree[root[i]].size);
	}
	while(m--)
	{
		int x,y;
		read(x),read(y);
		int fx=find(x),fy=find(y);
		fa[fy]=fx;
		root[fx]=merge(root[fx],root[fy]);
	}
	read(q);
	while(q--)
	{
		char opt[4];
		scanf("%s",opt);
		if(opt[0]=='B')
		{
			int x,y;
			read(x),read(y);
			int fx=find(x),fy=find(y);
			fa[fy]=fx;
			root[fx]=merge(root[fx],root[fy]);
		}
		else if(opt[0]=='Q')
		{
			int x,rk;
			read(x),read(rk);
			int fx=find(x);
			if(tree[root[fx]].size<rk)
				printf("-1\n");
			else
				printf("%d\n",query(root[fx],1,1e5,rk));
		}
	}

	return 0;
}
