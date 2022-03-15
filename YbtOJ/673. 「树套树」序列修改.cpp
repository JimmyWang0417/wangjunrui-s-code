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
const int N=4e5+5;
int n,m,a[N];
bool softflag;
struct Query
{
	int l,r,x;
} q[N];
int cntc,cntq;
int p[N],tot;
struct Tree
{
	int l,r;
	int size;
} tree[N*400];
int cnt,root[N];
#define lc(rt) tree[rt].l
#define rc(rt) tree[rt].r
inline void update(int &rt,int l,int r,int pos,int val)
{
	if(!rt)
		rt=++cnt;
	tree[rt].size+=val;
	if(l==r)
		return;
	int mid=(l+r)>>1;
	if(pos<=mid)
		update(lc(rt),l,mid,pos,val);
	else
		update(rc(rt),mid+1,r,pos,val);
}
inline void update(int rt,int pos,int val)
{
	if(pos==n+1)
		return;
	for(int i=rt; i<=n; i+=lowbit(i))
		update(root[i],0,n,pos,val);
}
inline int query(int rt,int l,int r,int pos)
{
	if(l==r)
		return tree[rt].size;
	int mid=(l+r)>>1;
	if(pos<=mid)
		return query(lc(rt),l,mid,pos);
	else
		return tree[lc(rt)].size+query(rc(rt),mid+1,r,pos);
}
inline int query(int rt,int pos)
{
	int ans=0;
	for(int i=rt; i; i-=lowbit(i))
		ans+=query(root[i],0,n,pos);
	return ans;
}
struct node
{
	int l,r,v;
	node(int _l=0,int _r=0,int _v=0):l(_l),r(_r),v(_v) {}
	inline bool operator <(const node &rhs)const
	{
		return l<rhs.l;
	}
};
set<node>all;
set<int>color[N];
#define iter set<node>::iterator
int las[N];
inline iter split(int x)
{
	if(x>n)
		return all.end();
	iter it=all.upper_bound(node(x,0,0));
	--it;
	if(it->l==x)
		return it;
	int l=it->l,r=it->r,v=it->v;
	set<int>::iterator where=color[v].find(l);
	int ne=0;
	++where;
	if(where!=color[v].end())
		ne=*where;
	--where;
	update(x,las[x]=l,1);
	if(ne)
	{
		update(ne,las[ne],-1);
		update(ne,las[ne]=x,1);
	}
	color[v].erase(where);
	color[v].insert(l);
	color[v].insert(x);
	all.erase(it);
	all.insert(node(l,x-1,v));
	return all.insert(node(x,r,v)).first;
}
signed main()
{
	freopen("sequence.in","r",stdin);
	freopen("sequence.out","w",stdout);
	read(n,m);
	for(int i=1; i<=n; ++i)
	{
		read(a[i]);
		p[++tot]=a[i];
	}
	for(int i=1; i<=m; ++i)
	{
		int opt;
		read(opt);
		if(opt==1)
		{
			read(q[i].l,q[i].r,q[i].x);
			p[++tot]=q[i].x;
		}
		else
			read(q[i].l,q[i].r);
	}
	sort(p+1,p+1+tot);
	tot=(int)(unique(p+1,p+1+tot)-p-1);
	for(int i=1; i<=n; ++i)
		a[i]=(int)(lower_bound(p+1,p+1+tot,a[i])-p);
	for(int i=1; i<=m; ++i)
		if(q[i].x)
			q[i].x=(int)(lower_bound(p+1,p+1+tot,q[i].x)-p);
	for(int i=1; i<=n; ++i)
	{
		all.insert(node(i,i,a[i]));
		if(color[a[i]].size()>0)
		{
			set<int>::iterator it=--color[a[i]].end();
			las[i]=*it;
		}
		else
			las[i]=0;
		update(i,las[i],1);
		color[a[i]].insert(i);
	}
	for(int i=1; i<=m; ++i)
	{
		if(q[i].x)
		{
			int &l=q[i].l,&r=q[i].r;
			iter itr=split(r+1),itl=split(l);
			for(iter it=itl; it!=itr; ++it)
			{
				set<int>::iterator where=color[it->v].find(it->l);
				int ne=0,la=0;
				if(where!=color[it->v].begin())
				{
					--where;
					la=*where;
					++where;
				}
				++where;
				if(where!=color[it->v].end())
					ne=*where;
				--where;
				update(*where,las[*where],-1);
				las[*where]=n+1;
				color[it->v].erase(where);
				if(ne)
				{
					update(ne,las[ne],-1);
					update(ne,las[ne]=la,1);
				}
			}
			int &v=q[i].x;
			all.erase(itl,itr);
			all.insert(node(l,r,v));
			set<int>::iterator where=color[v].upper_bound(l);
			int ne=0,la=0;
			if(where!=color[v].end())
				ne=*where;
			if(where!=color[v].begin())
				la=*(--where);
			update(l,las[l]=la,1);
			if(ne)
			{
				update(ne,las[ne],-1);
				update(ne,las[ne]=l,1);
			}
			color[v].insert(l);
		}
		else
		{
			int &l=q[i].l,&r=q[i].r;
			split(l);
			printf("%d\n",query(r,l-1)-query(l-1,l-1));
		}
//		for(auto v:all)
//			printf(" %d %d %d\n",v.l,v.r,v.v);
//		putchar('\n');
	}
	return 0;
}

