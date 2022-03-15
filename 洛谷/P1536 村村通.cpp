#include <set>
#include <map>
#include <cmath>
#include <queue>
#include <vector>
#include <cstdio>
#include <bitset>
#include <cstring>
#include <iostream>
#include <algorithm>
#define lowbit(x) (x&(-x))
#define re register
#define ll long long
#define ull unsigned long long
#define rep(i,a,b) for(re int i=a;i<=b;++i)
#define per(i,a,b) for(re int i=a;i>=b;--i)
using namespace std;
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
const int N=1005,M=N*N;
int n,m,fa[N];
bool vis[N];
template<typename T>
inline void clear(T*a,int l,int r,T val)
{
	memset(&a[l],val,sizeof(T)*(r-l+1));
}
inline int find(int x)
{
	return fa[x]==x?x:fa[x]=find(fa[x]);
}
signed main()
{
	while(read(n),n)
	{
		read(m);
		for(re int i=1; i<=n; ++i)
			fa[i]=i;
		clear(vis,1,n,false);
		for(re int i=1; i<=m; ++i)
		{
			int x,y;
			read(x,y);
			fa[find(x)]=find(y);
		}
		int ans=-1;
		for(re int i=1; i<=n; ++i)
			ans+=(i==find(i));
		printf("%d\n",ans);
	}
	return 0;
}


