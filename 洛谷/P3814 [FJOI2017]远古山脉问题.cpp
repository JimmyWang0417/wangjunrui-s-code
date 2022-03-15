#include <bits/stdc++.h>
#define int ll
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
const int N=50005;
const int mod=1e9+7;
const int INF=0x3f3f3f3f;
struct Tree
{
	int lc,rc;
	int size;

	int key;

	int val;
	int max,cnt;

	int lcnt,rcnt;

	int lans,rans;

	int l,r;

	bool rev;
} tree[N*80];
#define lc(now) tree[now].lc
#define rc(now) tree[now].rc
int cnt;
mt19937 rnd((unsigned)time(0));
inline int newnode(int val)
{
	int now=++cnt;
	tree[now].size=1;
	lc(now)=rc(now)=0;

	tree[now].l=tree[now].r=tree[now].max=tree[now].val=val;
	tree[now].cnt=1;

	tree[now].key=rnd();

	tree[now].lcnt=tree[now].rcnt=tree[now].lans=tree[now].rans;

	tree[now].rev=false;
	return now;
}
inline int copynode(int prex)
{
	tree[++cnt]=tree[prex];
	return cnt;
}
inline void rev(int now)
{
	swap(tree[now].lcnt,tree[now].rcnt);
	swap(tree[now].lans,tree[now].rans);
	swap(tree[now].l,tree[now].r);
	tree[now].rev^=1;
}
inline void pushup(int now)
{
	tree[now].size=tree[lc(now)].size+tree[rc(now)].size+1;
	tree[now].max=tree[now].val;
	tree[now].cnt=1;

	tree[now].l=tree[now].r=tree[now].val;

	tree[now].lcnt=tree[now].rcnt=tree[now].lans=tree[now].rans=0;

	if(lc(now))
	{
		tree[now].l=tree[lc(now)].l;
		if(tree[now].max<tree[lc(now)].max)
		{
			tree[now].max=tree[lc(now)].max;
			tree[now].cnt=tree[lc(now)].cnt;
		}
		else if(tree[now].max==tree[lc(now)].max)tree[now].cnt+=tree[lc(now)].cnt;

		tree[now].lans+=tree[lc(now)].lans+(tree[rc(now)].size+1)*tree[lc(now)].lcnt;
		tree[now].rans+=tree[lc(now)].rans;
		tree[now].lcnt+=tree[lc(now)].lcnt;
		tree[now].rcnt+=tree[lc(now)].rcnt;

		if(tree[lc(now)].r>tree[now].val)
		{
			tree[now].lans+=tree[rc(now)].size+1;
			++tree[now].lcnt;
		}
		else if(tree[lc(now)].r<tree[now].val)
		{
			tree[now].rans+=tree[lc(now)].size;
			++tree[now].rcnt;
		}
	}
	if(rc(now))
	{
		tree[now].r=tree[rc(now)].r;
		if(tree[now].max<tree[rc(now)].max)
		{
			tree[now].max=tree[rc(now)].max;
			tree[now].cnt=tree[rc(now)].cnt;
		}
		else if(tree[now].max==tree[rc(now)].max)tree[now].cnt+=tree[rc(now)].cnt;

		tree[now].lans+=tree[rc(now)].lans;
		tree[now].rans+=tree[rc(now)].rans+(tree[lc(now)].size+1)*tree[rc(now)].rcnt;
		tree[now].lcnt+=tree[rc(now)].lcnt;
		tree[now].rcnt+=tree[rc(now)].rcnt;
		if(tree[now].val>tree[rc(now)].l)
		{
			tree[now].lans+=tree[rc(now)].size;
			++tree[now].lcnt;
		}
		else if(tree[now].val<tree[rc(now)].l)
		{
			tree[now].rans+=tree[lc(now)].size+1;
			++tree[now].rcnt;
		}
	}
}
inline void pushdown(int now)
{
	if(tree[now].rev)
	{
		swap(lc(now),rc(now));
		if(lc(now))
		{
			lc(now)=copynode(lc(now));
			rev(lc(now));
		}
		if(rc(now))
		{
			rc(now)=copynode(rc(now));
			rev(rc(now));
		}
		tree[now].rev=false;
		pushup(now);
	}
}
inline void split(int now,int size,int &x,int &y)
{
//	printf("%d\n",now);
	if(!now)
		x=y=0;
	else
	{
		pushdown(now);
		if(tree[lc(now)].size<size)
		{
			x=copynode(now);
			split(rc(x),size-tree[lc(now)].size-1,rc(x),y);
			pushup(x);
		}
		else
		{
			y=copynode(now);
			split(lc(y),size,x,lc(y));
			pushup(y);
		}
	}
}
inline int merge(int x,int y)
{
	if(!x||!y)
		return x|y;
	if(tree[x].key>tree[y].key)
	{
		pushdown(x);
		rc(x)=merge(rc(x),y);
		pushup(x);
		return x;
	}
	else
	{
		pushdown(y);
		lc(y)=merge(x,lc(y));
		pushup(y);
		return y;
	}
}
inline int find(int rt)
{
	int val=tree[rt].max,nowcnt=(tree[rt].cnt+1)/2,pos=0;
	int now=rt;
	while(now)
	{
		now=copynode(now);
		pushdown(now);
		int sum=0;
		if(val==tree[lc(now)].max)
			sum+=tree[lc(now)].cnt;
		if(tree[now].val==val)
		{
			if(nowcnt==sum+1)
				return pos+tree[lc(now)].size+1;
			else
				++sum;
		}

		if(nowcnt>sum)
		{
			nowcnt-=sum;
			pos+=tree[lc(now)].size+1;
			now=rc(now);
		}
		else
			now=lc(now);
	}
	return pos+1;
}
int root[N];
inline void dfs(int now)
{
	pushdown(now);
	if(lc(now))
		dfs(lc(now));
	printf("rt=%lld lc=%lld rc=%lld val=%lld lans=%lld rans=%lld lcnt=%lld rcnt=%lld\n",now,lc(now),rc(now),tree[now].val,tree[now].lans,tree[now].rans,tree[now].lcnt,tree[now].rcnt);
//	printf("%lld ",tree[now].val);
	if(rc(now))
		dfs(rc(now));
	pushup(now);
}
inline void print(int rt)
{
	dfs(rt);
	putchar('\n');
}
inline void work(int id)
{
	root[id]=root[id-1];
#define root root[id]
	char opt[4];
	scanf("%s",opt);
	if(opt[0]=='I')
	{
		int h,pos;
		read(h,pos);
		int x,y;
		split(root,pos,x,y);
		root=merge(x,merge(newnode(h),y));
	}
	else if(opt[0]=='R')
	{
		int l,r;
		read(l,r);
		int x,y,z;
		split(root,l-1,x,y);
		split(y,r-l+1,y,z);
		rev(y);
		root=merge(x,merge(y,z));
	}
	else if(opt[0]=='Q')
	{
		int l,r;
		read(l,r);
		int x,y,z;
		split(root,l-1,x,y);
		split(y,r-l+1,y,z);
//		dfs(y);
		int pos=find(y);
		printf("%d\n",pos);
		int a,b,c;
		split(y,pos-1,a,b);
		dfs(b);
		split(b,1,b,c);
		dfs(c);
		int ans=(tree[a].lans+tree[a].lcnt)+(tree[c].rans+tree[c].rcnt);
//		dfs(c);
		y=merge(a,merge(b,c));
		root=merge(x,merge(y,z));
		printf("%lld\n",ans%mod);
	}
#undef root
	else if(opt[0]=='M')
	{
		int pos,t;
		read(pos,t);
		int x,y;
		split(root[id],pos,x,y);
		root[id]=merge(x,merge(root[t],y));
	}
//	print(root[id]);
//	printf("root:\n");
//	print(root);
}
signed main()
{
	tree[0].val=INF;
	tree[0].max=-INF;
	int n;
	read(n);
	for(int i=1; i<=n; ++i)
		work(i);
	return 0;
}


