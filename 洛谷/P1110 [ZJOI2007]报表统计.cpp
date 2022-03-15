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
const int N=1e6+5;
const int INF=0x7fffffff;
struct Tree
{
	int l,r;
	int fa;
	int size;
	int key,val;
	int abs,min;
} tree[N];
#define lc(x) tree[x].l
#define rc(x) tree[x].r
#define fa(x) tree[x].fa
int root,cnt;
mt19937 rnd(114514u*1919810u*258u);
inline int newnode(int val,int abss)
{
	int now=++cnt;
	tree[now].key=rnd();
	tree[now].val=val;
	tree[now].min=tree[now].abs=abss;
	tree[now].size=1;
	return now;
}
inline void pushup(int x)
{
	tree[x].min=min(tree[x].abs,min(tree[lc(x)].min,tree[rc(x)].min));
	tree[x].size=tree[lc(x)].size+tree[rc(x)].size+1;
	tree[lc(x)].fa=tree[rc(x)].fa=x;
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
			pushup(x);
		}
		else
		{
			y=now;
			split(lc(now),size,x,lc(y));
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
inline int getrank(int x)
{
	int sum=tree[lc(x)].size+1;
	while(fa(x))
	{
		if(x==rc(fa(x)))
			sum+=tree[lc(fa(x))].size+1;
		x=fa(x);
	}
	return sum;
}
int n,m;
set<int>mp;
signed main()
{
	tree[0].val=tree[0].abs=tree[0].min=INF;
	read(n,m);
	int minn=INF;
	mp.insert(-INF/2);
	mp.insert(INF);
	for(int i=1,las=INF; i<=n; ++i)
	{
		int val;
		read(val);
		root=merge(root,newnode(val,abs(val-las)));
		minn=min(minn,min(val-*(--mp.upper_bound(val)),*(mp.lower_bound(val))-val));
		mp.insert(val);
		las=val;
	}
	for(int i=1; i<=m; ++i)
	{
		char opt[10];
		scanf("%s",opt);
		if(opt[4]=='R')
		{
			int pos,val;
			read(pos,val);
			pos=(pos==n)?tree[root].size:getrank(pos+1)-1;
			minn=min(minn,min(val-*(--mp.upper_bound(val)),*(mp.lower_bound(val))-val));
			mp.insert(val);
			int x,y,z,cnm;
			split(root,pos-1,x,y);
			split(y,1,y,z);
			split(z,1,z,cnm);
			int now=newnode(val,abs(tree[y].val-val));
			tree[z].abs=tree[z].min=abs(tree[z].val-val);
			root=merge(x,merge(merge(y,now),merge(z,cnm)));
		}
		else if(opt[4]=='S')
			printf("%d\n",minn);
		else
			printf("%d\n",tree[root].min);
	}
	return 0;
}


