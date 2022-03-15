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
const int INF=0x3f3f3f3f;
int n,m,q;
struct Edge
{
	int u,v;
} e[N];
struct Tree
{
	int ch[2];
	int fa;
	int id,minid;
	bool rev;
} tree[N];
#define lc(x) tree[x].ch[0]
#define rc(x) tree[x].ch[1]
#define fa(x) tree[x].fa
#define rev(x) tree[x].rev
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
	tree[x].minid=min(tree[x].id,min(tree[lc(x)].minid,tree[rc(x)].minid));
}
inline void pushdown(int x)
{
	if(rev(x))
	{
		swap(lc(x),rc(x));
		if(lc(x))
			rev(lc(x))^=1;
		if(rc(x))
			rev(rc(x))^=1;
		rev(x)=false;
	}
}
inline void rotate(int x)
{
	int y=fa(x),z=fa(y),k=check(x),w=tree[x].ch[k^1];
	if(nroot(y))
		tree[z].ch[check(y)]=x;
	tree[x].ch[k^1]=y;
	tree[y].ch[k]=w;
	if(w)
		fa(w)=y;
	fa(y)=x;
	fa(x)=z;
	pushup(y),pushup(x);
}
int st[N];
inline void splay(int x)
{
	int top;
	st[top=1]=x;
	for(re int y=x; nroot(y); y=fa(y))
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
	for(re int y=0; x; x=fa(y=x))
	{
		splay(x);
		rc(x)=y;
		pushup(x);
	}
}
inline void makeroot(int x)
{
	access(x);
	splay(x);
	rev(x)^=1;
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
inline void split(int x,int y)
{
	makeroot(x);
	access(y);
	splay(y);
}
inline void link(int x,int y)
{
//	printf("link:%d %d\n",x,y);
	makeroot(x);
	fa(x)=y;
}
inline void cut(int id)
{
	int &x=e[id].u,&y=e[id].v,now=id+n;
	split(x,y);
	splay(now);
	lc(now)=rc(now)=fa(x)=fa(y)=0;
	pushup(now);
}
int C[N];
inline void update(int pos,int val)
{
	for(int i=pos; i<=m; i+=lowbit(i))
		C[i]+=val;
}
inline int query(int pos)
{
	int res=0;
	for(int i=pos; i; i-=lowbit(i))
		res+=C[i];
	return res;
}
struct node
{
	int l,r,id;
	inline bool operator <(const node &rhs)const
	{
		return r<rhs.r;
	}
} a[N];
int answer[N];
signed main()
{
	freopen("graph.in","r",stdin);
	freopen("graph.out","w",stdout);
	read(n,m,q);
	tree[0].minid=tree[0].id=INF;
	for(int i=1; i<=n; ++i)
		tree[i].minid=tree[i].id=INF;
	for(int i=1; i<=m; ++i)
	{
		read(e[i].u,e[i].v);
		tree[i+n].minid=tree[i+n].id=i;
	}
//	for(int i=1; i<=n+m; ++i)
//		printf("%d %d\n",tree[i].minid,tree[i].id);
//	putchar('\n');
	for(int i=1; i<=q; ++i)
	{
		read(a[i].l,a[i].r);
		a[i].id=i;
	}
	sort(a+1,a+1+q);
	int r=0;
	for(int now=1; now<=q; ++now)
	{
//		printf("[%d,%d]\n",a[now].l,a[now].r);
		while(r<a[now].r)
		{
//			printf("nmsl\n");
			++r;
			int u=e[r].u,v=e[r].v;
			if(u==v)
				continue;
//			printf("%d %d %d %d\n",u,v,findroot(u),findroot(v));
			if(findroot(u)==findroot(v))
			{
//				printf("wdnmd\n");
				split(u,v);
				int id=tree[v].minid;
//				printf("%d\n",id);
				cut(id);
				update(id,-1);
			}
			link(u,r+n),link(r+n,v);
			update(r,1);
//			for(int i=0; i<=n+m; ++i)
//				printf("%d %d %d lc=%d rc=%d\n",i,tree[i].minid,tree[i].id,lc(i),rc(i));
//			putchar('\n');
		}
		answer[a[now].id]=n-(query(m)-query(a[now].l-1));
	}
	for(int i=1; i<=q; ++i)
		printf("%d\n",answer[i]);
	return 0;
}

