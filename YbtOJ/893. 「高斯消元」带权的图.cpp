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
const int N=105;
struct node
{
	int u,v;
	ll a,b;
} e[N*N];
int n,m;
ll mod;
inline void add(ll &a,ll b)
{
	a+=b;
	if(a>=mod)
		a-=mod;
}
inline void mul(ll &a,ll b)
{
	a-=b;
	if(a<0)
		a+=mod;
}
inline ll times(ll a,ll b)
{
	ll res=0;
	while(b)
	{
		if(b&1)
			add(res,a);
		add(a,a);
		b>>=1;
	}
	return res;
}
inline ll quickpow(ll a,ll b)
{
	ll res=1;
	while(b)
	{
		if(b&1)
			res=times(res,a);
		a=times(a,a);
		b>>=1;
	}
	return res;
}
ll g[N][N];
#define inv(x) quickpow(x,mod-2)
inline void add_edge(int u,int v,ll a,ll b)
{
	ll invb=inv(b);
//	cout<<' '<<u<<' '<<v<<' '<<a<<' '<<b<<' '<<invb<<endl;
	mul(g[u][v],invb);
	add(g[u][u],invb);
	add(g[u][n+1],times(a,invb));
}
ll ans[N];
inline void gaosi()
{
	for(int i=1; i<=n; ++i)
	{
		int id=i;
		for(int j=i+1; j<=n; ++j)
			if(fabs(g[id][i])>fabs(g[j][i]))
				id=i;
		if(id!=i)
			swap(g[i],g[id]);
		ll div=inv(g[i][i]);
		for(int j=1; j<=n+1; ++j)
			g[i][j]=times(g[i][j],div); 
		for(int j=i+1; j<=n; ++j)
		{
			ll cnt=g[j][i];
			if(!cnt)
				continue;
			for(int k=i; k<=n+1; ++k)
				mul(g[j][k],times(cnt,g[i][k]));
		}
	}
	for(int i=n; i>=1; --i)
	{
		ans[i]=g[i][n+1];
		for(int j=i+1; j<=n; ++j)
			mul(ans[i],times(g[i][j],ans[j]));
	}
}
signed main()
{
	freopen("graph.in","r",stdin);
	freopen("graph.out","w",stdout);
	read(n,m,mod);
	for(int i=1; i<=m; ++i)
	{
		read(e[i].u,e[i].v,e[i].a,e[i].b);
		if(e[i].u!=1)
			add_edge(e[i].u,e[i].v,e[i].a,e[i].b);
		if(e[i].v!=1)
			add_edge(e[i].v,e[i].u,(mod-e[i].a)%mod,e[i].b);
	}
	g[1][1]=1;
//	for(int i=1; i<=n; ++i)
//	{
//		for(int j=1; j<=n+1; ++j)
//			cout<<g[i][j]<<' ';
//		cout<<endl;
//	}
	gaosi();
//	for(int i=1; i<=n; ++i)
//		printf("%d ",ans[i]);
//	putchar('\n');
	for(int i=1; i<=m; ++i)
	{
		ll now=ans[e[i].v];
		mul(now,ans[e[i].u]);
		add(now,e[i].a);
//		printf(" %lld %lld\n",now,inv(e[i].b));
		now=times(now,inv(e[i].b));
		printf("%lld\n",now);
	}
	return 0;
}


