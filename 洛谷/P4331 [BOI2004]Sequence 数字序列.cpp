#include <cstdio>
#include <cctype>
#include <algorithm>
#define re register
#define ll long long
template <typename T>
inline void read(T&x)
{
	x=0;
	char s=(char)getchar();
	bool flag=false;
	while(s<'0'||s>'9')
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
		x=~x+1;
	return;
}
const int N=1e6+5;
struct node
{
	int l,r;
	int size,val;
	int dist;
} tree[N];
#define lc(x) tree[x].l
#define rc(x) tree[x].r
inline int merge(int x,int y)
{
	if(!x||!y)
		return x+y;
	if(tree[x].val<tree[y].val)
		std::swap(x,y);
	rc(x)=merge(rc(x),y);
	if(tree[lc(x)].dist<tree[rc(x)].dist)
		std::swap(lc(x),rc(x));
	tree[x].size=tree[lc(x)].size+tree[rc(x)].size+1;
	tree[x].dist=tree[rc(x)].dist+1;
	return x;
}
int l[N],r[N],root[N],tot[N],n;
int main()
{
	int now=0;
	tree[0].dist=-1;
	read(n);
	for(re int i=1; i<=n; ++i)
	{
		read(tree[i].val);
		tree[i].val-=i;
		++now;
		l[now]=r[now]=root[now]=i;
		tot[now]=tree[i].size=1;
		while(now>1&&tree[root[now-1]].val>tree[root[now]].val)
		{
			--now;
			tot[now]+=tot[now+1];
			r[now]=r[now+1];
			root[now]=merge(root[now],root[now+1]);
			while(tree[root[now]].size*2>tot[now]+1)
				root[now]=merge(lc(root[now]),rc(root[now]));
		}
	}
	ll ans=0ll;
	for(re int i=1; i<=now; ++i)
		for(re int j=l[i]; j<=r[i]; ++j)
			ans+=abs(tree[root[i]].val-tree[j].val);
	printf("%lld\n",ans);
	for(re int i=1; i<=now; ++i)
		for(re int j=l[i]; j<=r[i]; ++j)
			printf("%d ",tree[root[i]].val+j);
	putchar('\n');
	return 0;
}
