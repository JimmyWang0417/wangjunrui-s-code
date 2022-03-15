#include <cstdio>
#include <algorithm>
#define re register
#define calc(cnt,id) ((cnt)*n+(id))
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
template<typename T,typename ...T1>
inline void read(T&x,T1&...x1)
{
	read(x);
	read(x1...);
}
const int N=1e4*10+5;
int n,m,C,q;
struct Tree
{
	int ch[2];
	int fa;
	int size;
	int val,max;
	bool reverse;
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
	tree[x].max=max(tree[x].val,max(tree[lc(x)].max,tree[rc(x)].max));
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
	fa(x)=lc(y)=0;
}
int cnt[15][N];
inline void work()
{
	int opt;
	read(opt);
	if(opt==0)
	{
		int pos,val;
		read(pos,val);
		for(re int i=0; i<C; ++i)
		{
			splay(calc(i,pos));
			tree[calc(i,pos)].val=val;
			pushup(calc(i,pos));
		}
	}
	else if(opt==1)
	{
		int u,v,w;
		read(u,v,w);
		int id=-1;
		for(re int i=0; i<C; ++i)
		{
			int x=calc(i,u),y=calc(i,v);
			makeroot(x);
			if(findroot(y)!=x||fa(y)!=x||lc(y))
				continue;
			id=i;
			break;
		}
//		printf("------%d\n",id);
		if(id==w)
		{
			printf("Success.\n");
			return;
		}
		if(id==-1)
		{
			printf("No such edge.\n");
			return;
		}
		if(cnt[w][u]==2||cnt[w][v]==2)
		{
			printf("Error 1.\n");
			return;
		}
		if(findroot(calc(w,u))==findroot(calc(w,v)))
		{
			printf("Error 2.\n");
			return;
		}
		printf("Success.\n");
		cut(calc(id,u),calc(id,v)),link(calc(w,u),calc(w,v));
		--cnt[id][u],--cnt[id][v];
		++cnt[w][u],++cnt[w][v];
	}
	else if(opt==2)
	{
		int c,u,v;
		read(c,u,v);
		int x=calc(c,u),y=calc(c,v);
		if(findroot(x)!=findroot(y))
		{
			printf("-1\n");
			return;
		}
		split(x,y);
		printf("%d\n",tree[y].max);
	}
//	for(re int i=0; i<C; ++i)
//	{
//		for(re int j=1; j<=n; ++j)
//			printf(" %d",cnt[calc(i,j)]);
//		putchar('\n');
//	}
}
signed main()
{
	read(n,m,C,q);
	for(re int i=1; i<=n; ++i)
	{
		int val;
		read(val);
		for(re int j=0; j<C; ++j)
		{
			tree[calc(j,i)].val=val;
			pushup(calc(j,i));
		}
	}
//	for(re int i=1; i<=n*C; ++i)
//		printf(" %d",tree[i].val);
//	putchar('\n');
	for(re int i=1; i<=m; ++i)
	{
		int u,v,w;
		read(u,v,w);
		++cnt[w][u],++cnt[w][v];
		link(calc(w,u),calc(w,v));
	}
//	for(re int i=0; i<C; ++i)
//	{
//		for(re int j=1; j<=n; ++j)
//			printf(" %d",cnt[calc(i,j)]);
//		putchar('\n');
//	}
	while(q--)
		work();
	return 0;
}
