#include <bits/stdc++.h>
#define lowbit(x) ((x)&(-(x)))
#define re register
#define ll long long
#define ull unsigned long long
#define ld long double
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
inline ld quickpow(ld a,int b)
{
	ld res=1.0;
	while(b)
	{
		if(b&1)
			res=res*a;
		a=a*a;
		b>>=1;
	}
	return res;
}
const int N=5e5+5;
vector<int>g[N];
int n,m;
ld p;
struct Tree_array
{
	ld c[N];
	inline void update(int pos,ld val)
	{
		for(int i=pos; i<=n; i+=lowbit(i))
			c[i]+=val;
	}
	inline ld query(int pos)
	{
		ld res=0;
		for(int i=pos; i; i-=lowbit(i))
			res+=c[i];
		return res;
	}
	inline ld query(int l,int r)
	{
		return query(r)-query(l-1);
	}
} tree;
signed main()
{
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	cin>>n>>m>>p;
	for(int i=1; i<=m; ++i)
	{
		int u,v;
		cin>>u>>v;
		g[u].push_back(v);
	}
	ld ans=0;
	for(int u=1; u<=n; ++u)
	{
		if(g[u].empty())
			continue;
		sort(g[u].begin(),g[u].end());
		ld now=p/(1-quickpow(1-p,g[u].size()));
		for(auto v:g[u])
		{
			ans+=now*tree.query(v+1,n);
			tree.update(v,now);
			now*=(1-p);
		}
		now=p/(1-quickpow(1-p,g[u].size()));
	}
	printf("%.2Lf\n",ans);
	return 0;
}


