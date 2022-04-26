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
const int N=2e5+5;
struct Tree
{
	int ch[2];
	int fa;

	int val;
	ll sum;

	int id;
	int size;

	int reverse;
} tree[N];
#define lc(x) tree[x].ch[0]
#define rc(x) tree[x].ch[1]
#define fa(x) tree[x].fa
#define rev(x) tree[x].reverse
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
	tree[x].size=tree[lc(x)].size+tree[rc(x)].size+(bool)(tree[x].id);
}
inline void pushdown(int x)
{
	if(rev(x))
	{
		std::swap(lc(x),rc(x));
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
	tree[y].ch[k]=w;
	tree[x].ch[k^1]=y;
	if(w)
		fa(w)=y;
	fa(x)=z;
	fa(y)=x;
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
inline int k_th(int x,int rk)
{
	while(rk)
	{
		pushdown(x);
		if(tree[x].id&&rk==tree[lc(x)].size+(bool)tree[x].id)
			return tree[x].id;
		if(tree[lc(x)].size>=rk)
			x=lc(x);
		else
		{
			rk-=tree[lc(x)].size+(bool)tree[x].id;
			x=rc(x);
		}
	}
	return 0;
}
inline void link(int x,int y)
{
	if(findroot(x)==findroot(y))
		return;
	makeroot(x);
	fa(x)=y;
}
inline void work()
{
	memset(tree,0,sizeof(tree));
	int n;
	read(n);
	for(re int i=1; i<=n; ++i)
	{
		tree[i].id=i;
		pushup(i);
	}
	for(re int i=1; i<n; ++i)
	{
		int u,v,w;
		read(u,v,w);
		tree[i+n].val=w;
		pushup(i+n);
		link(u,i+n);
		link(i+n,v);
	}
	while(1)
	{
		char opt[10];
		scanf("%s",opt);
		if(opt[0]=='D'&&opt[1]=='O')
			return;
		if(opt[0]=='K')
		{
			int u,v,k;
			read(u,v,k);
			split(u,v);
			printf("%d\n",k_th(v,k));
		}
		else
		{
			int u,v;
			read(u,v);
			split(u,v);
			printf("%lld\n",tree[v].sum);
		}
	}
}
signed main()
{
	int T;
	read(T);
	while(T--)
		work();
	return 0;
}


