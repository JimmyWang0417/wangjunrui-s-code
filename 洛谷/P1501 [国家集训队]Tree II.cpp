#include <cstdio>
#include <algorithm>
#define re register
#define ll long long
using namespace std;
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
const int N=1e5+5,mod=51061;
struct Tree
{
	int ch[2];
	int size;
	int fa;
	int val;
	int sum,add,mul;
	bool reverse;
	inline void update1(int v)
	{
		(val+=v)%=mod;
		(add+=v)%=mod;
		sum=(int)((1ll*size*v%mod+sum)%mod);
	}
	inline void update2(int v)
	{
		val=(int)(1ll*v*val%mod);
		add=(int)(1ll*v*add%mod);
		mul=(int)(1ll*v*mul%mod);
		sum=(int)(1ll*v*sum%mod);
	}
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
	tree[x].size=tree[lc(x)].size+tree[rc(x)].size+1;
	tree[x].sum=(tree[lc(x)].sum+tree[rc(x)].sum+tree[x].val)%mod;
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
	if(tree[x].mul!=1)
	{
		if(lc(x))
			tree[lc(x)].update2(tree[x].mul);
		if(rc(x))
			tree[rc(x)].update2(tree[x].mul);
		tree[x].mul=1;
	}
	if(tree[x].add)
	{
		if(lc(x))
			tree[lc(x)].update1(tree[x].add);
		if(rc(x))
			tree[rc(x)].update1(tree[x].add);
		tree[x].add=0;
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
	makeroot(x);
	fa(x)=y;
}
inline void cut(int x,int y)
{
	split(x,y);
	lc(y)=fa(x)=0;
}
signed main()
{
	int n,q;
	read(n),read(q);
	for(re int i=1; i<=n; ++i)
	{
		tree[i].val=tree[i].mul=1;
		pushup(i);
	}
	for(re int i=1; i^n; ++i)
	{
		int u,v;
		read(u),read(v);
		link(u,v);
	}
	while(q--)
	{
		char opt[5];
		scanf("%s",opt);
		int u,v,c;
		switch(opt[0])
		{
			case '+':
				read(u),read(v),read(c);
				split(u,v);
				tree[v].update1(c);
				break;
			case '-':
				read(u),read(v);
				cut(u,v);
				read(u),read(v);
				link(u,v);
				break;
			case '*':
				read(u),read(v),read(c);
				split(u,v);
				tree[v].update2(c);
				break;
			case '/':
				read(u),read(v);
				split(u,v);
				printf("%d\n",tree[v].sum);
				break;
		}
	}
	return 0;
}
