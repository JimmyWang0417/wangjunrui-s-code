#include <ctime>
#include <cstdio>
#include <cstdlib>
#define re register
using namespace std;
template<typename T>
inline void read(T&x)
{
	x=0;
	char s=(char)getchar();
	bool flag=false;
	while(!(s>='0'&&s<='9'))
	{
		if(s=='-')
			flag=true;
		s=(char)getchar();
	}
	while(s>='0'&&s<='9')
	{
		x=(x<<1)+(x<<3)+s-'0';
		s=(char)getchar();
	}
	if(flag)
		x=(~x)+1;
}
const int N=8e4+5;
int pos[N];
struct Tree
{
	int val,key;
	int l,r,size;
	int fa;
} tree[N];
int root,cnt;
#define lc(x) tree[x].l
#define rc(x) tree[x].r
#define fa(x) tree[x].fa
inline int newnode(int val)
{
	tree[++cnt].val=val;
	tree[cnt].key=rand();
	pos[val]=cnt;
	lc(cnt)=rc(cnt)=0;
	tree[cnt].size=1;
	return cnt;
}
inline void update(int now)
{
	if(lc(now))
		fa(lc(now))=now;
	if(rc(now))
		fa(rc(now))=now;
	tree[now].size=tree[lc(now)].size+tree[rc(now)].size+1;
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
inline int query(int s)
{
	int now=pos[s],ans=tree[lc(now)].size;
	while(now!=root)
	{
		if(rc(fa(now))==now)
			ans+=tree[lc(fa(now))].size+1;
		now=fa(now);
	}
	return ans;
}
int n,m;
char str[10];
int main()
{
	srand(123456),srand(rand()),srand(rand());
	read(n),read(m);
	for(re int i=1; i<=n; ++i)
	{
		int val;
		read(val);
		root=merge(root,newnode(val));
	}
	while(m--)
	{
		scanf("%s",str);
		if(str[0]=='T')
		{
			int x,y,z,s;
			read(s);
			int Count=query(s);
			split(root,Count,x,y);
			split(y,1,y,z);
			root=merge(y,merge(x,z));
		}
		else if(str[0]=='B')
		{
			int x,y,z,s;
			read(s);
			split(root,query(s),x,y);
			split(y,1,y,z);
			root=merge(merge(x,z),y);
		}
		else if(str[0]=='I')
		{
			int x,y,z,s,t;
			read(s),read(t);
			int Count=query(s);
			split(root,Count,x,y);
			split(y,1,y,z);
			root=merge(x,z);
			split(root,Count+t,x,z);
			root=merge(x,merge(y,z));
		}
		else if(str[0]=='A')
		{
			int s;
			read(s);
			printf("%d\n",query(s));
		}
		else if(str[0]=='Q')
		{
			int x,y,z,s;
			read(s);
			split(root,s-1,x,y);
			split(y,1,y,z);
			printf("%d\n",tree[y].val);
			root=merge(x,merge(y,z));
		}
	}
	return 0;
}
