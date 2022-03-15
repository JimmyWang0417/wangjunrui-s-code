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
using std::max;
using std::min;
using std::swap;
const int N=4e5+5;
struct Tree
{
	int ch[2];
	int fa;
	int val,sum,max,min;
	bool exist;
	bool opp;
	bool reverse;
	inline void oppsite()
	{
		opp^=1;
		swap(max,min);
		sum=-sum;
		max=-max;
		min=-min;
		val=-val;
	}
} tree[N];
#define lc(x) tree[x].ch[0]
#define rc(x) tree[x].ch[1]
#define fa(x) tree[x].fa
#define rev(x) tree[x].reverse
#define opp(x) tree[x].opp
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
	tree[x].sum=tree[lc(x)].sum+tree[rc(x)].sum+tree[x].val;
	tree[x].max=max(tree[lc(x)].max,tree[rc(x)].max);
	tree[x].min=min(tree[lc(x)].min,tree[rc(x)].min);
	if(tree[x].exist)
	{
		tree[x].max=max(tree[x].max,tree[x].val);
		tree[x].min=min(tree[x].min,tree[x].val);
	}
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
	if(opp(x))
	{
		if(lc(x))
			tree[lc(x)].oppsite();
		if(rc(x))
			tree[rc(x)].oppsite();
		opp(x)=false;
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
	rev(x)^=1;
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
int n,m;
inline void work()
{
	char opt[10];
	scanf("%s",opt);
	if(opt[0]=='C')
	{
		int i,w;
		++i;
		read(i,w);
		splay(i+n);
		tree[i+n].val=w;
		pushup(i+n);
	}
	else
	{
		int u,v;
		read(u,v);
		++u,++v;
		split(u,v);
		if(opt[0]=='N')
			tree[v].oppsite();
		else if(opt[2]=='M')
			printf("%d\n",tree[v].sum);
		else if(opt[2]=='X')
			printf("%d\n",tree[v].max);
		else
			printf("%d\n",tree[v].min);
	}
}
signed main()
{
	tree[0].min=0x3f3f3f3f,tree[0].max=~0x3f3f3f3f;
	read(n);
	for(re int i=1; i<n; ++i)
	{
		int u,v,w;
		read(u,v,w);
		++u,++v;
		tree[i+n].val=w;
		tree[i+n].exist=true;
		pushup(i+n);
		link(u,i+n),link(i+n,v);
	}
	read(m);
	while(m--)
		work();
	return 0;
}


