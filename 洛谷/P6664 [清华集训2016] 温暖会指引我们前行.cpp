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
int fa[N];
inline int find(int x)
{
	return !fa[x]?x:fa[x]=find(fa[x]);
}
inline void unionn(int x,int y)
{
	if(find(x)==find(y))
		return;
	fa[find(x)]=y;
}
struct Edge
{
	int u,v,w;
} e[N];
struct Tree
{
	int ch[2],fa;
	int id,minid;
	int val,sum;
	bool rev;
} tree[N];
#define lc(x) tree[x].ch[0]
#define rc(x) tree[x].ch[1]
#define fa(x) tree[x].fa
inline bool check(int x)
{
	return rc(fa(x))==x;
}
inline bool nroot(int x)
{
	return lc(fa(x))==x||rc(fa(x))==x;
}
inline void pushup(int x)
{
	tree[x].sum=tree[x].val+tree[lc(x)].sum+tree[rc(x)].sum;

	tree[x].minid=tree[x].id;

	if(e[tree[lc(x)].minid].w<e[tree[x].minid].w)
		tree[x].minid=tree[lc(x)].minid;

	if(e[tree[rc(x)].minid].w<e[tree[x].minid].w)
		tree[x].minid=tree[rc(x)].minid;
}
inline void pushdown(int x)
{
	if(tree[x].rev)
	{
		swap(lc(x),rc(x));
		if(lc(x))
			tree[lc(x)].rev^=1;
		if(rc(x))
			tree[rc(x)].rev^=1;
		tree[x].rev=false;
	}
}
inline void rotate(int x)
{
	int y=fa(x),z=fa(y),k=check(x),w=tree[x].ch[k^1];

	if(nroot(y))
		tree[z].ch[check(y)]=x;
	fa(x)=z;

	tree[x].ch[k^1]=y;
	fa(y)=x;

	tree[y].ch[k]=w;
	if(w)
		fa(w)=y;

	pushup(y),pushup(x);
}
int st[N];
inline void splay(int x)
{
	int top;
	st[top=1]=x;
	for(int y=x; nroot(y); y=fa(y))
		st[++top]=fa(y);
	while(top)
		pushdown(st[top--]);
	while(nroot(x))
	{
		if(nroot(fa(x)))
			rotate(check(x)==check(fa(x))?fa(x):x);
		rotate(x);
	}
}
inline void access(int x)
{
	for(int y=0; x; x=fa(y=x))
	{
		splay(x);
		rc(x)=y;
		pushup(x);
	}
}
inline int findroot(int x)
{
	access(x);
	splay(x);
	while(pushdown(x),lc(x))
		x=lc(x);
	splay(x);
	return x;
}
inline void makeroot(int x)
{
	access(x);
	splay(x);
	tree[x].rev^=1;
}
inline void split(int x,int y)
{
	makeroot(x);
	access(y);
	splay(y);
}
inline void link(int x,int y)
{
	makeroot(x);
	fa(x)=y;
}
inline void cut(int x,int y)
{
	split(x,y);
	lc(y)=fa(x)=0;
}
int n,m;
inline void work()
{
	char opt[10];
	scanf("%s",opt);
	if(opt[0]=='f')
	{
		int id;
		read(id);
		++id;
		int &u=e[id].u,&v=e[id].v,&w=e[id].w;
		read(u,v,w,tree[id+n].val);
		tree[id+n].id=id;
		++u,++v;
		pushup(id+n);
//		printf("%d %d %d %d\n",id,u,v,w);
		if(find(u)==find(v))
		{
			split(u,v);
			int ans=tree[v].minid;
//			printf("%d\n",ans);
			if(e[ans].w>=w)
				return;
			cut(e[ans].u,ans+n),cut(ans+n,e[ans].v);
			link(u,id+n),link(id+n,v);
		}
		else
		{
			link(u,id+n),link(id+n,v);
			unionn(u,v);
		}
	}
	else if(opt[0]=='c')
	{
		int pos;
		read(pos);
		++pos;
		splay(pos+n);
		read(tree[pos+n].val);
		pushup(pos+n);
	}
	else
	{
		int u,v;
		read(u,v);
		++u,++v;
		if(find(u)==find(v))
		{
			split(u,v);
			printf("%d\n",tree[v].sum);
		}
		else
			printf("-1\n");
	}
}
signed main()
{
	e[0].w=0x7fffffff;
	read(n,m);
	for(int i=1; i<=n; ++i)
		pushup(i);
	for(int i=1; i<=m; ++i)
		work();
	return 0;
}


