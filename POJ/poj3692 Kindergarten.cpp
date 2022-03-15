#include <bitset>
#include <cstdio>
#include <cstring>
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
template<typename T>
inline void clear(T*a,int l,int r,int val)
{
	memset(&a[l],val,sizeof(T)*(r-l+1));
}
const int N=405;
int g,b,m;
int G[N][N];
int belong[N];
std::bitset<N>vis;
inline bool find(int u)
{
	for(re int v=1; v<=g+b; ++v)
	{
		if(G[u][v]||u==v)
			continue;
		if(vis[v])
			continue;
		vis[v]=true;
		if(!belong[v]||find(belong[v]))
		{
			belong[v]=u;
			return true;
		}
	}
	return false;
}
signed main()
{
	int kase=0;
	while(read(g),read(b),read(m),g||b||m)
	{
		for(re int i=1; i<=g; ++i)
			for(re int j=1; j<=g; ++j)
				if(i!=j)
					G[i][j]=G[j][i]=true;
		for(re int i=1; i<=b; ++i)
			for(re int j=1; j<=b; ++j)
				if(i!=j)
					G[i+g][j+g]=G[j+g][i+g]=true;
		for(re int i=1; i<=m; ++i)
		{
			int u,v;
			read(u),read(v);
			G[u][v+g]=G[v+g][u]=true;
		}
		int ans=0;
		for(re int i=1; i<=g; ++i)
		{
			vis.reset();
			if(find(i))
				++ans;
		}
		printf("Case %d: %d\n",++kase,g+b-ans);
		memset(belong,0,sizeof(belong));
		memset(G,0,sizeof(G));
	}
	return 0;
}


