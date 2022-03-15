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
const int N=2e5+5;
const int INF=0x3f3f3f3f;
struct Tree
{
	int l,r;
	int size;
	int key,val;
	int abs,minabs;
	int min,max;
} tree[N];
int root,cnt;
#define lc(x) tree[x].l
#define rc(x) tree[x].r
mt19937 rnd((unsigned int)time(0));
inline int newnode(int val)
{
	int now=++cnt;
	lc(now)=rc(now)=0;
	tree[now].size=1;
	tree[now].key=rnd();
	tree[now].max=tree[now].min=tree[now].val=val;
	return now;
}
inline void pushup(int now)
{
	tree[now].minabs=min(tree[now].abs,min(tree[lc(now)].minabs,tree[rc(now)].minabs));
	tree[now].size=tree[lc(now)].size+tree[rc(now)].size+1;
	tree[now].min=min(tree[now].val,min(tree[lc(now)].min,tree[rc(now)].min));
	tree[now].max=max(tree[now].val,max(tree[lc(now)].max,tree[rc(now)].max));
}
inline void split(int now,int size,int &x,int &y)
{
	if(!now)
		x=y=0;
	else
	{
		if(tree[lc(now)].size<size)
		{
			x=now;
			split(rc(now),size-tree[lc(now)].size-1,rc(x),y);
		}
		else
		{
			y=now;
			split(lc(now),size,x,lc(y));
		}
		pushup(now);
	}
}
inline int merge(int x,int y)
{
	if(!x||!y)
		return x|y;
	if(tree[x].key>tree[y].key)
	{
		rc(x)=merge(rc(x),y);
		pushup(x);
		return x;
	}
	else
	{
		lc(y)=merge(x,lc(y));
		pushup(y);
		return y;
	}
}
inline int getval(int &rt,int pos)
{
	int x,y,z;
	split(rt,pos-1,x,y);
	split(y,1,y,z);
	int ans=tree[y].val;
	rt=merge(x,merge(y,z));
	return ans;
}
inline void getmerge(int pos,int val)
{
	int a,b,c,d,e,f;
	split(root,pos-2,a,b);
	split(b,1,b,c);
	split(c,1,c,d);
	split(d,1,d,e);
	split(e,1,e,f);
	int x=newnode(val);
	tree[b].minabs=tree[b].abs=abs(tree[b].val-tree[x].val);
	tree[x].minabs=tree[x].abs=abs(tree[x].val-tree[e].val);
	root=merge(merge(a,b),merge(x,merge(e,f)));
}
inline void insert(int pos,int val)
{
	int a,b,c,d;
	split(root,pos-1,a,b);
	split(b,1,b,c);
	split(c,1,c,d);
	int x=newnode(val);
	tree[b].minabs=tree[b].abs=abs(tree[b].val-tree[x].val);
	tree[x].minabs=tree[x].abs=abs(tree[x].val-tree[c].val);
	root=merge(merge(a,b),merge(x,merge(c,d)));
}
inline int getmax(int l,int r)
{
	int x,y,z;
	split(root,l-1,x,y);
	split(y,r-l+1,y,z);
	int ans=tree[y].max-tree[y].min;
//	printf("max=%d min=%d\n",tree[y].max,tree[y].min);
	root=merge(x,merge(y,z));
	return ans;
}
inline int getmin(int l,int r)
{
	int x,y,z;
	split(root,l-1,x,y);
	split(y,r-l,y,z);
	int ans=tree[y].minabs;
	root=merge(x,merge(y,z));
	return ans;
}
int n,m;
int a[N];
signed main()
{
	freopen("atom.in","r",stdin),freopen("atom.out","w",stdout);
	tree[0].abs=tree[0].minabs=INF;
	tree[0].min=INF,tree[0].max=-INF;
	tree[0].val=INF;
	read(n,m);
	for(int i=1; i<=n; ++i)
		read(a[i]);
	a[n+1]=INF;
	for(int i=1; i<=n; ++i)
	{
		int x=newnode(a[i]);
		tree[x].minabs=tree[x].abs=abs(a[i+1]-a[i]);
		root=merge(root,x);
	}
	for(int i=1; i<=m; ++i)
	{
		char opt[8];
		scanf("%s",opt);
		int x,y;
		read(x,y);
		if(opt[1]=='a')
			printf("%d\n",getmax(x,y));
		else if(opt[1]=='i')
			printf("%d\n",getmin(x,y));
		else if(opt[1]=='n')
			insert(x,y);
		else
			getmerge(x,y);
//		for(int j=1; j<=n; ++j)
//			printf("%d ",getval(root,j));
//		putchar('\n');
	}
	return 0;
}


