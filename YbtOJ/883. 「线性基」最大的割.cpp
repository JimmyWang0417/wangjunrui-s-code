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
#define bit bitset<N>
const int L=1000;
const int N=1005;
struct node
{
	bit d[L+5];
	inline void clear()
	{
		memset(d,0,sizeof(d));
	}
	inline void insert(bit val)
	{
		for(int i=L; i>=0; --i)
			if(val[i])
			{
				if(!d[i][i])
				{
					d[i]=val;
					return;
				}
				else
					val^=d[i];
			}
	}
	inline void operator +=(const node &rhs)
	{
		for(int i=L; i>=0; --i)
			if(rhs.d[i][i])
				insert(rhs.d[i]);
	}
	inline bit calc()
	{
		bit ans;
		for(int i=L; i>=0; --i)
			if(!ans[i]&&d[i][i])
				ans^=d[i];
		return ans;
	}
	inline void print()
	{
		for(int i=L; i>=0; --i)
			cout<<d[i].to_ulong()<<" ";
		cout<<endl;
	}
};
inline void print(bit val)
{
	int cnt=(int)val.count();
	if(!cnt)
	{
		printf("0\n");
		return;
	}
	int pos=0;
	while(1)
	{
		if(val[pos])
			--cnt;
		if(!cnt)
			break;
		++pos;
	}
	for(int i=pos; i>=0; --i)
		putchar(val[i]+'0');
	putchar('\n');
}
node tree[N*4];
#define lc (rt<<1)
#define rc (rt<<1|1)
inline void update(int rt,int l,int r,int x,int y,bit val)
{
	if(r<x||l>y)
		return;
//	printf("%d %d %d\n",rt,l,r);
	if(x<=l&&r<=y)
	{
//		printf("%d %d %d %d\n",x,y,l,r);
		tree[rt].insert(val);
//		tree[rt].print();
		return;
	}
	int mid=(l+r)>>1;
	update(lc,l,mid,x,y,val);
	update(rc,mid+1,r,x,y,val);
}
node ans;
inline void query(int rt,int l,int r,int pos)
{
	ans+=tree[rt];
//	printf("%d %d %d\n",rt,l,r);
//	printf("%d\n",rt);
//	putchar(' '),tree[rt].print();
//	ans.print();
//	printf("%d %d %u\n",l,r,tree[rt].calc().to_ulong());
	if(l==r)
		return;
	int mid=(l+r)>>1;
	if(pos<=mid)
		query(lc,l,mid,pos);
	else
		query(rc,mid+1,r,pos);
	return;
}
int n,m;
int las[N];
bit val[N];
int cnt;
struct query
{
	int l,r;
	bit val;
} a[N*4];
char str[N];
signed main()
{
	freopen("cut.in","r",stdin);
	freopen("cut.out","w",stdout);
	read(n,m);
	bit add;
	for(int i=1; i<=m; ++i)
	{
		int x,y;
		read(x,y);
		scanf("%s",str);
		if(x==y)
			continue;
		add.reset();
		int len=(int)strlen(str);
		for(int j=0; j<len; ++j)
			add[len-j-1]=str[j]-'0';
//		cout<<add<<endl;
//		print(add);
		a[las[x]].r=i-1;
		las[x]=++cnt;
		a[cnt].l=i;
		a[cnt].val=(val[x]^=add);


		a[las[y]].r=i-1;
		las[y]=++cnt;
		a[cnt].l=i;
		a[cnt].val=(val[y]^=add);
	}
	for(int i=1; i<=cnt; ++i)
		if(!a[i].r)
			a[i].r=m+1;
//	for(int i=1; i<=cnt; ++i)
//		printf("%d %d\n",a[i].l,a[i].r);
	for(int i=1; i<=cnt; ++i)
		update(1,1,m,a[i].l,a[i].r,a[i].val);
	for(int i=1; i<=m; ++i)
	{
		query(1,1,m,i);
		print(ans.calc());
		ans.clear();
	}
	return 0;
}


