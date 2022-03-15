#include<cstdio>
#include<cstring>
#define re register
#define calc(x) (x-'a'+1)
#define lc(x) (x<<1)
#define rc(x) (x<<1|1)
using namespace std;
template<typename T>
inline void read(T&x)
{
	x=0;
	char s=getchar();
	bool f=false;
	while(!(s>='0'&&s<='9'))
	{
		if(s=='-')
			f=true;
		s=getchar();
	}
	while(s>='0'&&s<='9')
	{
		x=(x<<1)+(x<<3)+s-'0';
		s=getchar();
	}
	if(f)
		x=(~x)+1;
	return;
}
const int N=1e6+10,SIZE=30;
int t[SIZE],n,m;
struct Tree
{
	int cnt[SIZE],add;
	inline void clear()
	{
		memset(cnt,0,sizeof(cnt));
	}
} tree[N<<2];
char s[N];
inline void build(int root,int l,int r)
{
	if(l==r)
	{
		tree[root].cnt[calc(s[l])]=1;
		return;
	}
	int mid=l+r>>1;
	build(lc(root),l,mid);
	build(rc(root),mid+1,r);
	for(re int i=1; i<=26; i++)
		tree[root].cnt[i]=tree[lc(root)].cnt[i]+tree[rc(root)].cnt[i];
	return;
}
inline void add(int root,int l,int r,int v)
{
	tree[root].add=v;
	tree[root].clear();
	tree[root].cnt[v]=r-l+1;
}
inline void pushdown(int root,int l,int r,int mid)
{
	if(tree[root].add)
	{
		//int mid=l+r>>1;
		add(lc(root),l,mid,tree[root].add);
		add(rc(root),mid+1,r,tree[root].add);
		tree[root].add=0;
	}
	return;
}
inline void update(int root,int l,int r,int x,int y,int v)
{
	if(r<x||l>y)
		return;
	if(l>=x&&r<=y)
		return add(root,l,r,v);
	int mid=l+r>>1;
	pushdown(root,l,r,mid);
	update(lc(root),l,mid,x,y,v);
	update(rc(root),mid+1,r,x,y,v);
	for(re int i=1; i<=26; i++)
		tree[root].cnt[i]=tree[lc(root)].cnt[i]+tree[rc(root)].cnt[i];
	return;
}
inline void query(int root,int l,int r,int x,int y)
{
	if(r<x||l>y)
		return;
	if(l>=x&&r<=y)
	{
		for(re int i=1; i<=26; i++)
			t[i]+=tree[root].cnt[i];
		return;
	}
	int mid=l+r>>1;
	pushdown(root,l,r,mid);
	query(lc(root),l,mid,x,y);
	query(rc(root),mid+1,r,x,y);
	return;
}

inline void print(int root,int l,int r)
{
	if(l==r)
	{
		for(re int i=1; i<=26; i++)
			if(tree[root].cnt[i])
			{
				s[l]=i+'a'-1;
				break;
			}
		return;
	}
	int mid=l+r>>1;
	pushdown(root,l,r,mid);
	print(lc(root),l,mid);
	print(rc(root),mid+1,r);
}
int main()
{
	read(n);
	read(m);
	scanf("%s",s+1);
	build(1,1,n);
	int l,r,x;
	while(m--)
	{
		read(l);
		read(r);
		read(x);
		memset(t,0,sizeof(t));
		query(1,1,n,l,r);
		int tmp=l;
		/*for(re int i=1; i<=26; i++)
			printf("%d ",t[i]);
		putchar('\n');*/
		if(x==1)
		{
			for(re int i=1; i<=26; i++)
				if(t[i])
				{
					update(1,1,n,tmp,tmp+t[i]-1,i);
					tmp+=t[i];
				}
		}
		else if(x==0)
		{
			for(re int i=26; i>=1; i--)
				if(t[i])
				{
					update(1,1,n,tmp,tmp+t[i]-1,i);
					tmp+=t[i];
				}
		}
	}
	print(1,1,n);
	printf("%s\n",s+1);
	return 0;
}
