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
const int N=155,M=3e5+5,Q=3e5+5;
int n,m,q;
struct Edge
{
	int u,v;
} e[M];
int belong[M],block;
struct Query
{
	int l,r,id;
	inline bool operator < (const Query &rhs) const
	{
		return belong[l]==belong[rhs.l]?r<rhs.r:l<rhs.l;
	}
} a[M];
bitset<N>vis,g[N],revg[N];
int cnt[N][N];
inline void add(int pos)
{
//	printf(" %d %d\n",e[pos].u,e[pos].v);
	g[e[pos].u][e[pos].v]=true;
	revg[e[pos].v][e[pos].u]=true;
	++cnt[e[pos].u][e[pos].v];
}
inline void del(int pos)
{
	if(!--cnt[e[pos].u][e[pos].v])
	{
		g[e[pos].u][e[pos].v]=false;
		revg[e[pos].v][e[pos].u]=false;
	}

}
int st[M],top;
inline void dfs1(int u)
{
	vis.reset(u);
	int v=0;
	while(1)
	{
		v=(vis&g[u])._Find_next(v);
		if(v>n)
			break;
		dfs1(v);
	}
	st[++top]=u;
}
int size=0;
inline void dfs2(int u)
{
	vis.reset(u);
//	printf("%d ",u);
	++size;
	int v=0;
	while(1)
	{
		v=(vis&revg[u])._Find_next(v);
		if(v>n)
			break;
		dfs2(v);
	}
}
inline ll kosaraju()
{
	vis.set();
	for(int i=1; i<=n; ++i)
		if(vis[i])
			dfs1(i);
//	for(int i=1; i<=top; ++i)
//		printf("%d ",st[i]);
//	putchar('\n');
	vis.set();
	ll ans=0;
	while(top)
	{
		int u=st[top--];
		if(vis[u])
		{
			size=0;
			dfs2(u);
//			putchar('\n');
			ans+=(ll)size*(size-1)/2;
		}
	}
//	putchar('\n');
	return ans;
}
ll answer[M];
signed main()
{
	freopen("friend.in","r",stdin);
	freopen("friend.out","w",stdout);
	read(n,m,q);
	block=(int)(m/sqrt(q));
	for(int i=1; i<=m; ++i)
		belong[i]=(i-1)/block+1;
	for(int i=1; i<=m; ++i)
		read(e[i].u,e[i].v);
	for(int i=1; i<=q; ++i)
	{
		read(a[i].l,a[i].r);
		a[i].id=i;
	}
	sort(a+1,a+1+q);
	int l=1,r=0;
	for(int i=1; i<=q; ++i)
	{
		const int &ql=a[i].l,&qr=a[i].r;
		while(ql<l)
			add(--l);
		while(qr>r)
			add(++r);
		while(ql>l)
			del(l++);
		while(qr<r)
			del(r--);
//		for(int j=1; j<=n; ++j)
//			cout<<g[j]<<endl;
//		for(int j=1; j<=n; ++j)
//			cout<<revg[j]<<endl;
//		printf("%d %d\n",l,r);
//		printf("%d\n",kosaraju());
		answer[a[i].id]=kosaraju();
	}
	for(int i=1; i<=q; ++i)
		printf("%lld\n",answer[i]);
	return 0;
}


