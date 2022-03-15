#include <cstdio>
#include <algorithm>
#define re register
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
const int N=1e4+5;
struct Tree
{
	int ch[2];
	int fa;
	bool reverse;
} tree[N];
#define lc(x) tree[x].ch[0]
#define rc(x) tree[x].ch[1]
#define fa(x) tree[x].fa
#define rev(x) tree[x].reverse
inline bool nroot(int x)
{
	return lc(fa(x))==x||rc(fa(x))==x;
}
inline void pushdown(int x)
{
	if(!rev(x))
		return;
	swap(lc(x),rc(x));
	if(lc(x))
		rev(lc(x))^=1;
	if(rc(x))
		rev(rc(x))^=1;
	rev(x)=false;
}
inline bool check(int x)
{
	return rc(fa(x))==x;
}
inline void rorate(int x)
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
		{
			if(check(x)==check(fa(x)))rorate(fa(x));
			else rorate(x);
		}
		rorate(x);
	}
}
inline void access(int x)
{
	for(re int y=0; x; y=x,x=fa(y))
	{
		splay(x);
		rc(x)=y;
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
inline void link(int x,int y)
{
	makeroot(x);
	fa(x)=y;
}
inline void cut(int x,int y)
{
	makeroot(x);
	access(y);
	splay(y);
	lc(y)=0,fa(x)=0;
}
signed main()
{
	int n,m;
	read(n),read(m);
	while(m--)
	{
		char opt[15];
		scanf("%s",opt);
		int x,y;
		read(x),read(y);
		if(opt[0]=='C')
			link(x,y);
		else if(opt[0]=='D')
			cut(x,y);
		else if(opt[0]=='Q')
		{
			if(findroot(x)==findroot(y))
				printf("Yes\n");
			else
				printf("No\n");
		}
	}
	return 0;
}
