#include <ctime>
#include <cstdio>
#include <random>
#define re register
#define int unsigned int
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

const int N=2e5+5,K=15;
struct node
{
	int l,r,size;
	int val,key;
	int ans[K];
} tree[N];
int cnt,root;
#define lc(x) tree[x].l
#define rc(x) tree[x].r
mt19937 rnd((int)time(0));
inline int newnode(int val)
{
	++cnt;
	tree[cnt].val=val;
	tree[cnt].key=rnd();
	tree[cnt].size=1;
	for(re int i=0; i<=10; ++i)
		tree[cnt].ans[i]=val;
	return cnt;
}
int c[K][K];
int power[15];
inline void update(int now)
{
	tree[now].size=tree[lc(now)].size+tree[rc(now)].size+1;
	for(re int i=power[0]=1; i<=10; ++i)
		power[i]=power[i-1]*(tree[lc(now)].size+1);
	for(re int k=0; k<=10; ++k)
	{
		tree[now].ans[k]=tree[lc(now)].ans[k]+tree[now].val*power[k];
		for(re int i=0; i<=k; ++i)
			tree[now].ans[k]+=c[k][i]*power[k-i]*tree[rc(now)].ans[i];
	}
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
			split(rc(now),size-tree[lc(now)].size-1,rc(now),y);
		}
		else
		{
			y=now;
			split(lc(now),size,x,lc(now));
		}
		update(now);
	}
}
inline int merge(int x,int y)
{
	if(!x||!y)
		return x|y;
	if(tree[x].key>tree[y].key)
	{
		rc(x)=merge(rc(x),y);
		update(x);
		return x;
	}
	else
	{
		lc(y)=merge(x,lc(y));
		update(y);
		return y;
	}
}
inline void dfs(int now)
{
	if(!now)
		return;
	dfs(lc(now));
	printf("%d ",tree[now].val);
	dfs(rc(now));
}
inline void print(int now)
{
	dfs(now);
	putchar('\n');
}
char str[5];
int n,q;
signed main()
{
	for(re int i=c[0][0]=1; i<=10; ++i)
		for(re int j=c[i][0]=1; j<=i; ++j)
			c[i][j]=c[i-1][j-1]+c[i-1][j];
	read(n);
	for(re int i=0; i<n; ++i)
	{
		int val;
		read(val);
		root=merge(root,newnode(val));
	}
	read(q);
	while(q--)
	{
//		print(root);
		scanf("%s",str);
		if(str[0]=='I')
		{
			int pos,val;
			read(pos),read(val);
			++pos;
			int x,y;
			split(root,pos-1,x,y);
			root=merge(merge(x,newnode(val)),y);
		}
		else if(str[0]=='D')
		{
			int pos;
			read(pos);
			++pos;
			int x,y,z;
			split(root,pos,x,z);
			split(x,pos-1,x,y);
			root=merge(x,z);
		}
		else if(str[0]=='R')
		{
			int pos,val;
			read(pos),read(val);
			++pos;
			int x,y,z;
			split(root,pos,x,z);
			split(x,pos-1,x,y);
			tree[y].val=val;
			for(re int i=0; i<=10; ++i)
				tree[y].ans[i]=val;
			root=merge(merge(x,y),z);
		}
		else if(str[0]=='Q')
		{
			int l,r,k;
			read(l),read(r),read(k);
			++l,++r;
			int x,y,z;
			split(root,r,x,z);
			split(x,l-1,x,y);
			printf("%u\n",tree[y].ans[k]);
			root=merge(merge(x,y),z);
		}
	}
	return 0;
}
