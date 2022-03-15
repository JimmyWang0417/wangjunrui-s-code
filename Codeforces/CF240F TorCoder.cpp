#include <cstdio>
#include <cstring>
#define re register
#define ll long long
#define rep(i,a,b) for(re int i=a;i<=b;++i)
#define per(i,a,b) for(re int i=a;i>=b;--i)
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
const int N=1e5+5;
struct Tree
{
	int size;
	int cnt[26];
	int tag;
	Tree():tag(-1)
	{
		memset(cnt,0,sizeof(cnt));
	}
	inline void update(int val)
	{
		tag=val;
		memset(cnt,0,sizeof(cnt));
		cnt[val]=size;
	}
	inline Tree operator +(const Tree&rhs)const
	{
		Tree ans;
		for(re int i=0; i<26; ++i)
			ans.cnt[i]=cnt[i]+rhs.cnt[i];
		return ans;
	}
} tree[N*4];
#define lc (rt<<1)
#define rc (rt<<1|1)
inline void pushup(int rt)
{
	for(re int i=0; i<26; ++i)
		tree[rt].cnt[i]=tree[lc].cnt[i]+tree[rc].cnt[i];
}
inline void pushdown(int rt)
{
	int &tag=tree[rt].tag;
	if(~tag)
	{
		tree[lc].update(tag);
		tree[rc].update(tag);
		tag=-1;
	}
}
char str[N];
#define calc(x) (x-'a')
inline void build(int rt,int l,int r)
{
	tree[rt].size=r-l+1;
	if(l==r)
	{
		tree[rt].update(calc(str[l]));
		return;
	}
	int mid=(l+r)>>1;
	build(lc,l,mid);
	build(rc,mid+1,r);
	pushup(rt);
}
inline void update(int rt,int l,int r,int x,int y,int val)
{
	if(r<x||l>y)
		return;
	if(x<=l&&r<=y)
	{
		tree[rt].update(val);
		return;
	}
	pushdown(rt);
	int mid=(l+r)>>1;
	update(lc,l,mid,x,y,val);
	update(rc,mid+1,r,x,y,val);
	pushup(rt);
}
inline Tree query(int rt,int l,int r,int x,int y)
{
	if(r<x||l>y)
		return Tree();
	if(x<=l&&r<=y)
		return tree[rt];
	pushdown(rt);
	int mid=(l+r)>>1;
	return query(lc,l,mid,x,y)+query(rc,mid+1,r,x,y);
}
int n,m;
inline void solve1(int l,int r)
{
	Tree now=query(1,1,n,l,r);
	int cnt=0;
	for(re int i=0; i<26; ++i)
		cnt+=now.cnt[i]&1;
	if(cnt!=1)
		return;
	for(re int i=0; i<26; ++i)
	{
		int ans=now.cnt[i]>>1;
		update(1,1,n,l,l+ans-1,i);
		l+=ans;
//		printf("%d ",sum);
	}
	for(re int i=0; i<26; ++i)
		if(now.cnt[i]&1)
		{
			update(1,1,n,l,l,i);
			++l;
			break;
		}
	for(re int i=25; i>=0; --i)
	{
		int ans=now.cnt[i]>>1;
		update(1,1,n,l,l+ans-1,i);
		l+=ans;
//		printf("%d ",sum);
	}
//	putchar('\n');
}
inline void solve2(int l,int r)
{
	Tree now=query(1,1,n,l,r);
	int cnt=0;
	for(re int i=0; i<26; ++i)
		cnt+=now.cnt[i]&1;
	if(cnt!=0)
		return;
	for(re int i=0; i<26; ++i)
	{
		int ans=now.cnt[i]>>1;
		update(1,1,n,l,l+ans-1,i);
		l+=ans;
//		printf("%d ",sum);
	}
	for(re int i=25; i>=0; --i)
	{
		int ans=now.cnt[i]>>1;
		update(1,1,n,l,l+ans-1,i);
		l+=ans;
//		printf("%d ",sum);
	}
}
inline void dfs(int rt,int l,int r)
{
	if(l==r)
	{
		int id=-1;
		for(re int i=0; i<26; ++i)
			if(tree[rt].cnt[i])
				id=i;
		putchar(id+'a');
		return;
	}
	pushdown(rt);
	int mid=(l+r)>>1;
	dfs(lc,l,mid);
	dfs(rc,mid+1,r);
}
inline void print()
{
	dfs(1,1,n);
	putchar('\n');
}
inline void work()
{
	int l,r;
	read(l,r);
	int len=r-l+1;
	if(len&1)
		solve1(l,r);
	else solve2(l,r);
//	print();
}
signed main()
{
	freopen("input.txt","r",stdin),freopen("output.txt","w",stdout);
	read(n,m);
	scanf("%s",str+1);
	build(1,1,n);
	while(m--)
		work();
	print();
	return 0;
}


