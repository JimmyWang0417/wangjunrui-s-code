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
inline void clear(T*a,int l,int r,int val)
{
	memset(&a[l],val,sizeof(T)*(r-l+1));
}
const int N=1e5+5;
struct Tree
{
	int ch[2],fa;
	int id,leftid,rightid;
	bool exist;
	bool reverse;
} tree[N];
#define lc(x) tree[x].ch[0]
#define rc(x) tree[x].ch[1]
#define fa(x) tree[x].fa
#define rev(x) tree[x].reverse
using std::swap;
inline bool check(int x)
{
	return rc(fa(x))==x;
}
inline bool nroot(int x)
{
	return lc(fa(x))==x||rc(fa(x))==x;
}
inline void reverse(int x)
{
	rev(x)^=1;
	swap(tree[x].leftid,tree[x].rightid);
}
inline void pushup(int x)
{
	if(tree[lc(x)].leftid)
		tree[x].leftid=tree[lc(x)].leftid;
	else if(tree[x].exist)
		tree[x].leftid=tree[x].id;
	else
		tree[x].leftid=tree[rc(x)].leftid;
	if(tree[rc(x)].rightid)
		tree[x].rightid=tree[rc(x)].rightid;
	else if(tree[x].exist)
		tree[x].rightid=tree[x].id;
	else
		tree[x].rightid=tree[lc(x)].rightid;
}
inline void pushdown(int x)
{
	if(rev(x))
	{
		swap(lc(x),rc(x));
		if(lc(x))
			reverse(lc(x));
		if(rc(x))
			reverse(rc(x));
		rev(x)=false;
	}
}
inline void rotate(int x)
{
	int y=fa(x),z=fa(y),k=check(x),w=tree[x].ch[k^1];
	if(nroot(y))
		tree[z].ch[check(y)]=x;
	tree[y].ch[k]=w;
	tree[x].ch[k^1]=y;
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
			rotate(check(fa(x))==check(x)?fa(x):x);
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
	makeroot(x);
	fa(x)=y;
}
inline void work()
{
	int opt,u;
	read(opt,u);
	if(opt==0)
	{
		splay(u);
		tree[u].exist^=1;
		pushup(u);
	}
	else if(opt==1)
	{
		split(1,u);
		printf("%d\n",tree[u].leftid?tree[u].leftid:-1);
	}
}
signed main()
{
	int n,q;
	read(n,q);
	for(re int i=1; i<=n; ++i)
		tree[i].id=i;
	for(re int i=1; i<n; ++i)
	{
		int u,v;
		read(u,v);
		link(u,v);
	}
	while(q--)
		work();
	return 0;
}


