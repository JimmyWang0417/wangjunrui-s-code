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
struct Tree
{
	int l,r;
	int dist;
	int val;
} tree[N];
int cnt,root[N];
#define lc(x) tree[x].l
#define rc(x) tree[x].r
inline void pushup(int x)
{
	tree[x].dist=tree[rc(x)].dist+1;
}
inline int newnode(int val)
{
	int x=++cnt;
	lc(x)=rc(x)=0;
	tree[x].val=val;
	pushup(x);
	return x;
}
inline int merge(int x,int y)
{
	if(!x||!y)
		return x|y;
	if(tree[x].val>tree[y].val)
		swap(x,y);
	rc(x)=merge(rc(x),y);
	if(tree[lc(x)].dist<tree[rc(x)].dist)
		swap(lc(x),rc(x));
	pushup(x);
	return x;
}
int pos[N],id[N];
int n;
inline void work()
{
	cnt=0;
	read(n);
	clear(root,1,n+1,0);
	for(int i=1; i<=n; ++i)
	{
		int x,y;
		read(x,y);
		root[x]=merge(root[x],newnode(y));
		pos[i]=id[i]=i;
	}
	bool flag=true;
	for(int i=1; i<=n; ++i)
	{
		if(!root[i]||tree[root[i]].val<i)
		{
			printf("D\n");
			return;
		}
		int r=tree[root[i]].val,pre=pos[i];
		if(pos[i]!=root[i])
		{
			swap(pos[i],pos[id[root[i]]]);
			swap(id[pre],id[root[i]]);
			flag^=1;
		}
		root[r+1]=merge(root[r+1],merge(lc(root[i]),rc(root[i])));
	}
	printf(flag?"Y\n":"F\n");
}
signed main()
{
	freopen("fiend.in","r",stdin),freopen("fiend.out","w",stdout);
	int T;
	read(T);
	while(T--)
		work();
	return 0;
}


