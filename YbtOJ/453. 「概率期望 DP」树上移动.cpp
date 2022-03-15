#include <bits/stdc++.h>
//#define int ll
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
inline void clear(T*array,int l,int r,int dp)
{
	memset(&array[l],dp,sizeof(T)*(r-l+1));
}
using namespace std;
const int N=1e5+5,mod=1e9+7;
inline int times(int x,int y)
{
	return (int)((ll)x*y%mod);
}
inline void add(int &x,int y)
{
	x+=y;
	if(x>=mod)
		x-=mod;
}
inline void dec(int &x,int y)
{
	x-=y;
	if(x<0)
		x+=mod;
}
inline int quickpow(int a,int b)
{
	int res=1;
	for(; b; a=times(a,a),b>>=1)
		if(b&1)
			res=times(res,a);
	return res;
}
inline int inv(int a)
{
	return quickpow(a,mod-2);
}
struct node
{
	int a,b,c;
	node(int _a=0,int _b=0,int _c=0):a(_a),b(_b),c(_c) {}
	inline void operator +=(const node &rhs)
	{
		add(a,rhs.a);
		add(b,rhs.b);
		add(c,rhs.c);
	}
	inline void operator -=(const node &rhs)
	{
		dec(a,rhs.a);
		dec(b,rhs.b);
		dec(c,rhs.c);
	}
	inline node operator *(const int &rhs)const
	{
		return node(times(a,rhs),times(b,rhs),times(c,rhs));
	}
} dp[N][2];
vector<int>G[N];
int f[N],g[N],size[N];
int n;
inline void dfs1(int u)
{
	size[u]=1;
	for(auto v:G[u])
	{
		dfs1(v);
		size[u]+=size[v];
		add(f[u],f[v]+size[v]);
	}
}
inline void dfs2(int u)
{
	for(auto v:G[u])
	{
		g[v]=f[u];
		dec(g[v],(f[v]+size[v])%mod);
		add(g[v],(g[u]+n-size[v])%mod);
		dfs2(v);
	}
	add(f[u],g[u]);
}
char str[N];
signed main()
{
	freopen("c.in","r",stdin),freopen("c.out","w",stdout);
	read(n);
	scanf("%s",str+1);
	int cnt=0;
	for(int i=1; i<=n; ++i)
		if(str[i]=='1')
			++cnt;
	for(int i=2; i<=n; ++i)
	{
		int fa;
		read(fa);
		G[fa].push_back(i);
	}
	dfs1(1),dfs2(1);
	dp[0][0]=dp[0][1]=node(0,0,0);
	dp[1][0]=node(1,0,0);
	dp[1][1]=node(0,1,0);
	dp[n-1][1]=node(0,1,0);
	for(int i=1; i<n; ++i)
	{
		node &a=dp[i+1][1];
		a=dp[i][1];
		a-=dp[i-1][1]*times(i-1,inv(n));
		a-=dp[i-1][0]*inv(n);
		if(i>1)
			dec(a.c,inv(n));
		a=a*times(n,inv(n-i));
		node &b=dp[i+1][0];
		b=dp[i][0];
		b-=dp[i-1][0]*times(i,inv(n));
		b-=dp[i+1][1]*inv(n);
		if(i<n-1)
		{
			dec(b.c,inv(n));
			b=b*times(n,inv(n-i-1));
		}
	}
//	for(int i=1; i<=n; ++i)
//	{
//		for(int j=0; j<2; ++j)
//			printf("%d %d %d\n",dp[i][j].a,dp[i][j].b,dp[i][j].c);
//		putchar('\n');
//	}
	node a=dp[n][0],b=dp[n][1];
	a.c=times(a.c,mod-1);
	b.c=times(b.c,mod-1);
	a=a*times(b.a,inv(a.a));
//	printf("%d\n",times(b.a,inv(a.a)));
//	printf(" %d %d %d\n",a.a,a.b,a.c);
//	printf(" %d %d %d\n",b.a,b.b,b.c);
	int y=times((b.c-a.c+mod)%mod,inv((b.b-a.b+mod)%mod)),
	    x=times((b.c-times(b.b,y)+mod)%mod,inv(b.a));
//	printf("%d %d\n",x,y);
	a=dp[cnt][0],b=dp[cnt][1];
	int v0 = (1ll * a.a * x + 1ll * a.b * y + a.c) % mod,
	    v1 = (1ll * b.a * x + 1ll * b.b * y + b.c) % mod;
	add(v0,inv(n));
	add(v1,inv(n));
//	printf("%d %d\n",v0,v1);
//	for(int i=1; i<=n; ++i)
//		printf("%d ",f[i]-g[i]);
//	putchar('\n');
//	for(int i=1; i<=n; ++i)
//		printf("%d ",g[i]);
//	putchar('\n');
	int ans=0;
	for(int i=1; i<=n; ++i)
	{
		add(ans,times(f[i],times(inv(n),str[i]=='1'?v1:v0)));
	}
	cout<<ans<<endl;
	return 0;
}


