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
int n,m;
struct Tree
{
	int l,r;
	int val;
	int dist;
} tree[N];
#define lc(x) tree[x].l
#define rc(x) tree[x].r
int root[N];
inline void pushup(int x)
{
	tree[x].dist=tree[rc(x)].dist+1;
}
inline int merge(int x,int y)
{
	if(!x||!y)
		return x|y;
	if(tree[x].val<tree[y].val)
		swap(x,y);
	rc(x)=merge(rc(x),y);
	if(tree[lc(x)].dist<tree[rc(x)].dist)
		swap(lc(x),rc(x));
	pushup(x);
	return x;
}
int fa[N];
inline int find(int x)
{
	return !fa[x]?x:fa[x]=find(fa[x]);
}
signed main()
{
	while(scanf("%d",&n)!=EOF)
	{
		tree[0].dist=-1;
		for(int i=1; i<=n; ++i)
		{
			read(tree[root[i]=i].val);
			lc(i)=rc(i)=0;
			pushup(i);
		}
		fill(fa+1,fa+1+n,0);
		read(m);
		for(int i=1; i<=m; ++i)
		{
			int x,y;
			read(x,y);
			x=find(x),y=find(y);
			if(x==y)
			{
				printf("-1\n");
				continue;
			}
			int rootx=merge(lc(root[x]),rc(root[x])),rooty=merge(lc(root[y]),rc(root[y]));
			lc(root[x])=rc(root[x])=0,lc(root[y])=rc(root[y])=0;
			tree[root[x]].val/=2,tree[root[y]].val/=2;
			root[fa[x]=y]=merge(merge(root[x],rootx),merge(root[y],rooty));
			printf("%d\n",tree[root[y]].val);
		}
	}
	return 0;
}


