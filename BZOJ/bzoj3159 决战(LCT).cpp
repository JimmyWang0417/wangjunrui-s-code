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
const int N=5e4+5,INF=0x3f3f3f3f;
struct Tree
{
	int ch[2];
	int fa;
	int size;
	int val,tag;
	int max,min;
	ll sum;
	bool reverse;
} tree[N];
#define lc(x) tree[x].ch[0]
#define rc(x) tree[x].ch[1]
#define fa(x) tree[x].fa
#define tmax(x) tree[x].max
#define tmin(x) tree[x].min
#define sum(x) tree[x].sum
#define val(x) tree[x].val
#define size(x) tree[x].size
#define tag(x) tree[x].tag
#define rev(x) tree[x].reverse
inline void lazy(int x,int val)
{
	sum(x)+=1ll*val*size(x);
	val(x)+=val;
	tag(x)+=val;
	tmin(x)+=val;
	tmax(x)+=val;
	printf("!%d %d\n",x,tmax(x));
}
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
	printf("!!%d %d %d val%d %d %d %d\n",x,lc(x),rc(x),val(x),tmax(lc(x)),tmax(rc(x)),tmax(x));
	tmax(x)=max(max(tmax(lc(x)),tmax(rc(x))),val(x));
	tmin(x)=min(min(tmin(lc(x)),tmin(rc(x))),val(x));
	sum(x)=sum(lc(x))+sum(rc(x))+val(x);
	size(x)=size(lc(x))+size(rc(x))+1;
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
	if(tag(x))
	{
		if(lc(x))
			lazy(lc(x),tag(x));
		if(rc(x))
			lazy(rc(x),tag(x));
		tag(x)=0;
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
	int top;printf("!!!\n"); 
	st[top=1]=x;
	for(re int i=x; nroot(i); i=fa(i))
		st[++top]=fa(i);
	while(top)
		pushdown(st[top--]);
	while(nroot(x))
	{
		if(nroot(fa(x)))
			check(x)==check(fa(x))?rotate(fa(x)):rotate(x);
		rotate(x);
	}
}
inline void access(int x)
{
	for(re int y=0; x; y=x,x=fa(y))
	{
		splay(x);printf("2lc%d rc%d %d\n",lc(2),rc(2),y);
		rc(x)=y;
		if(y)
			fa(y)=x;
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
	printf("------\n");
	splay(y);
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
	lc(y)=fa(x)=0;
	pushup(x);
}
signed main()
{
	tree[0].max=-INF,tree[0].min=INF;
	int n,m,r;
	read(n),read(m),read(r);
	for(re int i=1; i<n; ++i)
	{
		int x,y;
		read(x),read(y);
		link(x,y);
	}
	while(m--)
	{
		char opt[15];
		scanf("%s",opt+1);
		int x,y;
		read(x),read(y);
		if(opt[3]=='c')
		{
			int w;
			read(w);
			split(x,y);
			lazy(y,w);
		}
		else if(opt[3]=='m')
		{
			split(x,y);
			printf("%lld\n",tree[y].sum);
		}
		else if(opt[3]=='j')
		{
			split(x,y);
			printf("%d\n",tree[y].max);
		}
		else if(opt[3]=='n')
		{
			split(x,y);
			printf("%d\n",tree[y].min);
		}
		else if(opt[3]=='v')
		{
			split(x,y);
			rev(y)^=1;
		}
	}
	return 0;
}

