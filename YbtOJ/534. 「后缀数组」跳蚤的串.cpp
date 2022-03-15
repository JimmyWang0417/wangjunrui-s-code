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
int n,q;
char str[N];

#define rank Rank
#define ws nihao
int sa[N],height[N],rank[N];
int wa[N],wb[N],ws[N];

inline bool cmp(int *r,int a,int b,int l)
{
	return r[a]==r[b]&&r[a+l]==r[b+l];
}
inline void buildsa(int color)
{
	int *x=wa,*y=wb;

	for(int i=1; i<=color; ++i)
		ws[i]=0;
	for(int i=1; i<=n; ++i)
		++ws[x[i]=str[i]-'0'+1];
	for(int i=2; i<=color; ++i)
		ws[i]+=ws[i-1];
	for(int i=n; i>=1; --i)
		sa[ws[x[i]]--]=i;

	for(int j=1,p=1; j<n; j*=2,color=p)
	{
		p=0;
		for(int i=n-j+1; i<=n; ++i)
			y[++p]=i;
		for(int i=1; i<=n; ++i)
			if(sa[i]>j)
				y[++p]=sa[i]-j;

		for(int i=1; i<=color; ++i)
			ws[i]=0;
		for(int i=1; i<=n; ++i)
			++ws[x[i]];
		for(int i=2; i<=color; ++i)
			ws[i]+=ws[i-1];
		for(int i=n; i>=1; --i)
			sa[ws[x[y[i]]]--]=y[i];

		swap(x,y);
		p=0;
		for(int i=1; i<=n; ++i)
			x[sa[i]]=cmp(y,sa[i],sa[i-1],j)?p:++p;
	}
	for(int i=1; i<=n; ++i)
		Rank[sa[i]]=i;
	for(int i=1,h=0; i<=n; ++i)
	{
		if(h)
			--h;
		while(str[i+h]==str[sa[rank[i]-1]+h])
			++h;
		height[rank[i]]=h;
	}
}
struct node
{
	int height,pos;
	inline bool operator <(const node &rhs)const
	{
		return height>rhs.height;
	}
} a[N];
struct Query
{
	int l,r;
} zqq[N];
const int BLOCK=25005;
bitset<BLOCK>cyx[N],czk[N],haveans,pre,nxt,need;
bitset<N>vis;
int ans[N];
int fa[N];
inline int find(int x)
{
	return !fa[x]?x:fa[x]=find(fa[x]);
}
inline void unionn(int x,int y)
{
	x=find(x),y=find(y);
	if(x==y)
		return;
	fa[y]=x;
	cyx[x]|=cyx[y];
}
inline void solve(int l,int r)
{
	haveans.set();
	vis.reset();
	fill(fa+1,fa+1+n,0);
	memset(czk,0,sizeof(czk));
	for(int i=l; i<=r; ++i)
	{
		czk[zqq[i].l].set(i-l+1);
		if(zqq[i].r<n)
			czk[zqq[i].r+1].set(i-l+1);
	}
	for(int i=2; i<=n; ++i)
		czk[i]^=czk[i-1];
//	for(int i=1; i<=n; ++i)
//		cout<<czk[i]<<' ';
//	putchar('\n');
	for(int i=1; i<n; ++i)
	{
		int u=a[i].pos;
//		printf(" %d %d\n",a[i].pos,a[i].height);
		vis.set(u);
		cyx[u]=czk[sa[u]]|czk[sa[u-1]];
		if(vis[u-1])
		{
			pre=cyx[find(u-1)];
			unionn(u-1,u);
		}
		else
			pre=czk[sa[u-1]];
		if(vis[u+1])
		{
			nxt=cyx[find(u+1)];
			unionn(u,u+1);
		}
		else
			nxt=czk[sa[u]];
		need=pre&nxt&haveans;
		for(int j=need._Find_first(); j<BLOCK; j=need._Find_next(j))
		{
//			printf("%d ",j);
			haveans.reset(j);
			ans[j+l-1]=a[i].height;
		}
//		putchar('\n');
//		for(int j=1; j<=q; ++j)
//			printf("%d ",ans[j]);
//		putchar('\n');
	}
}
signed main()
{
	freopen("history.in", "r", stdin);
	freopen("history.out", "w", stdout);
	read(n,q);
	scanf("%s",str+1);
	reverse(str+1,str+1+n);
	buildsa(2);
//	printf("%s\n",str+1);
//	for(int i=1; i<=n; ++i)
//		printf("%d ",rank[i]);
//	putchar('\n');
	for(int i=1; i<=q; ++i)
	{
		int x,y;
		read(x,y);
		zqq[i].r=n-x+1;
		zqq[i].l=n-y+1;
	}
//	printf("sa\n");
	// for(int i=1; i<=n; ++i)
	// printf("%d ",sa[i]);
//	putchar('\n');
//	printf("zqq\n");
//	for(int i=1; i<=q; ++i)
//		printf("%d %d\n",zqq[i].l,zqq[i].r);
//	printf("height\n");
	// for(int i=1; i<=n; ++i)
	// printf("%d ",height[i]);
//	putchar('\n');
	for(int i=2; i<=n; ++i)
	{
		a[i-1].height=height[i];
		a[i-1].pos=i;
	}
	sort(a+1,a+n);
	for(int i=1; i<=q; i+=25000)
		solve(i,min(i+24999,q));
	for(int i=1; i<=q; ++i)
		printf("%d\n",ans[i]);
	return 0;
}

