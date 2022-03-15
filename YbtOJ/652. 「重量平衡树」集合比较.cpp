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
const int N=1e5+5;
struct node
{
	int l,r;
	node(int _l=0,int _r=0):l(_l),r(_r) {}
};
int n;
struct Tree
{
	int ch[2];
	int fa;
	int size;
	node val;
	int cnt;
} tree[N];
#define lc(x) tree[x].ch[0]
#define rc(x) tree[x].ch[1]
#define fa(x) tree[x].fa
int rt[N],root,cnt;
inline bool check(int x)
{
	return rc(fa(x))==x;
}
inline void pushup(int now)
{
	if(!now)
		return;
	tree[now].size=tree[lc(now)].size+tree[rc(now)].size+tree[now].cnt;
}
inline void rorate(int x)
{
	int y=fa(x),z=fa(y),k=check(x),w=tree[x].ch[k^1];
	tree[y].ch[k]=w,fa(w)=y;
	tree[z].ch[check(y)]=x,fa(x)=z;
	tree[x].ch[k^1]=y,fa(y)=x;
	pushup(z),pushup(y),pushup(x);
}
inline void splay(int x,int tar=0)
{
	while(fa(x)!=tar)
	{
		int y=fa(x),z=fa(y);
		if(z!=tar)
		{
			if(check(x)==check(y))
				rorate(y);
			else
				rorate(x);
		}
		rorate(x);
	}
	if(!tar)
		root=x;
}
inline int getrank(int now)
{
	if(now==1)
		return tree[now].cnt;
	if(now==2)
		return tree[root].size;
	int size=tree[lc(now)].size+tree[now].cnt;
	while(fa(now))
	{
		pushup(fa(now));
		if(rc(fa(now))==now)
			size+=tree[fa(now)].size-tree[now].size;
		now=fa(now);
	}
	return size;
}
inline int cmp(node x,node y)
{
	if(rt[x.l]!=rt[y.l])
	{
//		printf("%d %d %d %d\n",x.l,y.l,rt[x.l],rt[y.l]);
		int l=getrank(rt[x.l]),r=getrank(rt[y.l]);
		return l<r?-1:1;
	}

	else if(rt[x.r]!=rt[y.r])
	{
		int l=getrank(rt[x.r]),r=getrank(rt[y.r]);
		return l<r?-1:1;
	}
	else
		return 0;
}
inline int insert(node val)
{
	int now=root;
	int las=0;
	while(now)
	{
//		printf("now=%d\n",now);
		las=now;
		int k=cmp(val,tree[now].val);
		if(k==0)
		{
			++tree[now].cnt;
			++tree[now].size;
			splay(now);
			return now;
		}
		else if(k==-1)
			now=lc(now);
		else
			now=rc(now);
	}
	now=++cnt;
//	printf("las=%d now=%d\n",las,now);
	tree[now].size=tree[now].cnt=1;
	tree[now].val=val;
	pushup(now);
	if(!las)
	{
		root=now;
		return now;
	}
	else
	{
		int k=cmp(val,tree[las].val);
//		printf("%d\n",k);
		if(k==-1)
			lc(las)=now;
		else
			rc(las)=now;
		fa(now)=las;
		pushup(las);
		splay(now);
		return now;
	}
}
inline void print(int now)
{
	if(lc(now))
		print(lc(now));
	printf(" %d %d %d %d size=%d cnt=%d\n",now,lc(now),rc(now),fa(now),tree[now].size,tree[now].cnt);
	if(rc(now))
		print(rc(now));
}
inline void dfs()
{
	printf("%d\n",tree[0].size);
	print(root);
	putchar('\n');
}
signed main()
{
	freopen("comparison.in","r",stdin),freopen("comparison.out","w",stdout);
	read(n);
	rt[0]=1;
	rt[n+1]=2;
	tree[1].cnt=tree[1].size=1;
	tree[2].cnt=tree[2].size=1;
	tree[1].val=node(0,0);
	tree[2].val=node(n+1,n+1);
	fa(1)=2;
	lc(2)=1;
	cnt=root=2;
	pushup(1);
	pushup(2);
//	dfs();
	for(int i=1; i<=n; ++i)
	{
		int x,y;
		read(x,y);
		rt[i]=insert(node(x,y));
//		printf(" %d\n",cmp(tree[rt[i]].val,tree[rt[n+1]].val));
		printf("%d\n",getrank(rt[i]));
//		printf("rt[%d]=%d\n",i,rt[i]);
//		dfs();
	}
	return 0;
}

