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
int n,m;
int fa[N],size[N];
inline int find(int x)
{
	return !fa[x]?x:fa[x]=find(fa[x]);
}
inline void unionn(int x,int y)
{
	if(find(x)==find(y))
		return;
	fa[find(x)]=find(y);
}
struct node
{
	int w,v;
} a[N];
int cnt,num[N];
inline void solve(int val)
{
	int now=1;
	while(num[val]>=now)
	{
		a[++cnt].w=now;
		a[cnt].v=now*val;
		num[val]-=now;
		now*=2;
	}
	if(num[val]>0)
	{
		a[++cnt].w=num[val];
		a[cnt].v=num[val]*val;
	}
}
int dp[N];
inline bool check(int val)
{
	while(val)
	{
		int c=val%10;
		val/=10;
		if(c==4||c==7)
			continue;
		return false;
	}
	return true;
}
signed main()
{
	read(n,m);
	for(int i=1; i<=m; ++i)
	{
		int x,y;
		read(x,y);
		unionn(x,y);
	}
	for(int i=1; i<=n; ++i)
		++size[find(i)];
	for(int i=1; i<=n; ++i)
		if(find(i)==i)
			++num[size[i]];
	for(int i=1; i<=n; ++i)
		solve(i);
	memset(dp,0x3f,sizeof(dp));
	dp[0]=-1;
	for(int i=1; i<=cnt; ++i)
	{
		for(int j=n; j>=a[i].v; --j)
			dp[j]=min(dp[j],dp[j-a[i].v]+a[i].w);
	}
	int ans=1e9;
	for(int i=1; i<=n; ++i)
		if(check(i))
			ans=min(ans,dp[i]);
	if(ans==1e9)
		printf("-1\n");
	else
		printf("%d\n",ans);
	return 0;
}


