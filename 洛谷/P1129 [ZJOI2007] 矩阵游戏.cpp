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
const int N=205;
int n,belong[N];
int g[N][N];
bitset<N>vis;
inline bool find(int u)
{
	for(int v=1; v<=n; ++v)
		if(g[u][v])
		{
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
inline void work()
{
	read(n);
	for(int i=1; i<=n; ++i)
		for(int j=1; j<=n; ++j)
			read(g[i][j]);
	int ans=0;
	memset(belong,0,sizeof(belong));
	for(int i=1; i<=n; ++i)
	{
		ans+=find(i);
		vis.reset();
	}
	puts(ans==n?"Yes":"No");
}
signed main()
{
	int T;
	read(T);
	while(T--)
		work();
	return 0;
}


