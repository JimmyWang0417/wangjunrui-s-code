#include<cstdio>
#include<algorithm>
#define re register
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
	return;
}
#define lc(x) tree[x].l
#define rc(x) tree[x].r
const int N=1e6+5;
struct Tree
{
	int l,r;
	int dist,val;
	int fa;
} tree[N];
inline int merge(int x,int y)
{
	if(!x||!y)
		return x+y;
	if(tree[x].val>tree[y].val)
		swap(x,y);
	rc(x)=merge(rc(x),y);
	tree[rc(x)].fa=x;
	if(tree[lc(x)].dist<tree[rc(x)].dist)
		swap(lc(x),rc(x));
	tree[x].dist=tree[rc(x)].dist+1;
	return x;
}
inline void deletemin(int x)
{
	tree[x].val=-1;
	tree[lc(x)].fa=lc(x);
	tree[rc(x)].fa=rc(x);
	tree[x].fa=merge(lc(x),rc(x));
}
inline int find(int x)
{
	return tree[x].fa==x?x:tree[x].fa=find(tree[x].fa);
}
int n,m;
int main()
{
	read(n);
	tree[0].dist=-1;
	for(re int i=1; i<=n; ++i)
	{
		read(tree[i].val);
		tree[i].fa=i;
	}
	char str[5];
	read(m);
	while(m--)
	{
		scanf("%s",str);
		if(str[0]=='M')
		{
			int x,y;
			read(x),read(y);
			if(tree[x].val==-1||tree[y].val==-1)
				continue;
			int fx=find(x),fy=find(y);
			if(fx==fy)
				continue;
			tree[fx].fa=tree[fy].fa=merge(fx,fy);
		}
		else if(str[0]=='K')
		{
			int x;
			read(x);
			if(tree[x].val==-1)
			{
				printf("0\n");
				continue;
			}
			int fa=find(x);
			printf("%d\n",tree[fa].val);
			deletemin(fa);
		}
	}
	return 0;
}
