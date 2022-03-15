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
const int N=5e4+5;
#define lc(x) tree[x].ch[0]
#define rc(x) tree[x].ch[1]
#define fa(x) tree[x].fa
class Splay
{
	public:
		struct Tree
		{
			int ch[2],fa;
			int val,max,min,tag;
			ll sum;
			int size;
			bool rev;
			inline void update(int add)
			{
				val+=add,max+=add,min+=add,tag+=add;
				sum+=(ll)size*add;
			}
		} tree[N];
		inline void init()
		{
			tree[0].max=-0x3f3f3f3f;
			tree[0].min=0x3f3f3f3f;
		}
		inline bool check(int x)
		{
			return rc(fa(x))==x;
		}
		inline bool nroot(int x)
		{
			return fa(x);
		}
		inline void pushup(int x)
		{
			if(!x)
				return;
			tree[x].size=tree[lc(x)].size+tree[rc(x)].size+1;
			tree[x].sum=tree[lc(x)].sum+tree[rc(x)].sum+tree[x].val;
			tree[x].max=max(tree[x].val,max(tree[lc(x)].max,tree[rc(x)].max));
			tree[x].min=min(tree[x].min,min(tree[lc(x)].min,tree[rc(x)].min));
		}
		inline void reverse(int x)
		{
			tree[x].rev^=1;
			swap(lc(x),rc(x));
		}
		inline void pushdown(int x)
		{
			if(tree[x].rev)
			{
				if(lc(x))
					reverse(lc(x));
				if(rc(x))
					reverse(rc(x));
				tree[x].rev=false;
			}
			if(tree[x].tag)
			{
				if(lc(x))
					tree[lc(x)].update(tree[x].tag);
				if(rc(x))
					tree[rc(x)].update(tree[x].tag);
				tree[x].tag=0;
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
			pushup(y),pushup(x),pushup(z);
		}
		int st[N];
		inline void splay(int x)
		{
			int top=0;
			st[++top]=x;
			for(int y=x; nroot(y); y=fa(y))
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
		inline int findroot(int x)
		{
			if(!x)
				return 0;
			while(fa(x))
				x=fa(x);
			return x;
		}
		inline int find(int x,int rank)
		{
			while(x)
			{
//				printf("%d ",x);
//				printf("12312381203123\n");
				pushdown(x);
				if(tree[lc(x)].size+1==rank)
					break;
				if(tree[lc(x)].size>=rank)
					x=lc(x);
				else
				{
					rank-=tree[lc(x)].size+1;
					x=rc(x);
				}
			}
//			putchar('\n');
			return x;
		}
		inline void dfs(int x)
		{
			if(!x)
				return;
			pushdown(x);
			if(lc(x))
				dfs(lc(x));
			printf(" %d",x);
			if(rc(x))
				dfs(rc(x));
		}
		inline void print(int x)
		{
			printf("%d:",x);
			dfs(x);
			putchar('\n');
		}
} val;
int root[N];
struct Tree
{
	int ch[2],fa;
	int size;
	bool rev;
} tree[N];
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
	if(!x)
		return;
	tree[x].size=tree[lc(x)].size+tree[rc(x)].size+1;
}
inline void reverse(int x)
{
	tree[x].rev^=1;
	swap(lc(x),rc(x));
}
inline void pushdown(int x)
{
	if(tree[x].rev)
	{
		if(lc(x))
			reverse(lc(x));
		if(rc(x))
			reverse(rc(x));
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
	pushup(y),pushup(x),pushup(z);
}
int st[N];
inline void splay(int x)
{
	int top=0;
	st[++top]=x;
	for(int y=x; nroot(y); y=fa(y))
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
	for(int y=0; x; x=fa(y=x))
	{
		splay(x);
//		printf(" %d %d %d %d\n",x,y,root[x],root[y]);
//		printf(" %d %d %d\n",x,y,fa(x));
		int rt=val.findroot(root[x]);
		int lasrt=y?val.findroot(root[y]):0;
		rt=val.find(rt,tree[lc(x)].size+1);
		lasrt=val.find(lasrt,tree[lc(y)].size+1);
//		val.print(rt);
		val.splay(rt),root[x]=rt;
		root[rc(x)]=val.rc(rt);
		val.fa(val.rc(rt))=0;


		val.rc(rt)=lasrt;
		if(lasrt)
			val.fa(lasrt)=rt;
		val.pushup(rt);

		rc(x)=y;
		pushup(x);
	}
//	putchar('\n');
}
inline void makeroot(int x)
{
	access(x);

	splay(x);
	int rt=val.findroot(root[x]);
	root[x]=val.find(rt,tree[lc(x)].size+1);
	val.splay(root[x]);

	reverse(x);
	val.reverse(root[x]);
}
inline void split(int x,int y)
{
	makeroot(x);
	access(y);
	splay(y);
}
int n,m,r;
struct Edge
{
	int next,to;
} edge[N*2];
int head[N],num_edge;
inline void add_edge(int from,int to)
{
	edge[++num_edge].next=head[from];
	edge[num_edge].to=to;
	head[from]=num_edge;
}
inline void dfs(int u,int _fa)
{
	fa(u)=_fa;
	root[u]=u;
//	printf("%d %d\n",u,_fa);
	pushup(u);
	val.pushup(u);
	for(int i=head[u]; i; i=edge[i].next)
	{
		int &v=edge[i].to;
		if(v==_fa)
			continue;
		dfs(v,u);
	}
}
signed main()
{
	read(n,m,r);
	for(int i=1; i<n; ++i)
	{
		int u,v;
		read(u,v);
		add_edge(u,v);
		add_edge(v,u);
	}
	dfs(r,0);
	val.init();
	while(m--)
	{
		char opt[10];
		scanf("%s",opt+1);
		int x,y;
		read(x,y);
//		printf("114514\n");
		split(x,y);
		int rt=val.findroot(root[y]);
		if(opt[3]=='c')
		{
			int w;
			read(w);
			val.tree[rt].update(w);
		}
		else if(opt[3]=='m')
			printf("%lld\n",val.tree[rt].sum);
		else if(opt[3]=='j')
			printf("%d\n",val.tree[rt].max);
		else if(opt[3]=='n')
			printf("%d\n",val.tree[rt].min);
		else if(opt[3]=='v')
			val.reverse(rt);
	}
	return 0;
}

