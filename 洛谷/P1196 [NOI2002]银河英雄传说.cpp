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
const int n=30000,N=n+5;
int fa[N],size[N],dis[N];
inline int find(int x)
{
	if(fa[x]==x)
		return x;
	int f=find(fa[x]);
	dis[x]+=dis[fa[x]];
	return fa[x]=f;
}
inline void unionn(int x,int y)
{
	int fx=find(x),fy=find(y);
	fa[fx]=fy;
	dis[fx]=size[fy];
	size[fy]+=size[fx];
}
inline void query(int x,int y)
{
	if(find(x)==find(y))
		printf("%d\n",abs(dis[x]-dis[y])-1);
	else
		printf("-1\n");
}
signed main()
{
	for(re int i=1; i<=n; ++i)
	{
		fa[i]=i;
		size[i]=1;
	}
	int T;
	read(T);
	while(T--)
	{
		char opt[2];
		scanf("%s",opt);
		if(opt[0]=='M')
		{
			int x,y;
			read(x,y);
			unionn(x,y);
//			for(re int i=1; i<=4; ++i)
//				printf("%d %d\n",find(i),dis[i]);
		}
		else if(opt[0]=='C')
		{
			int x,y;
			read(x,y);
			query(x,y);
		}
	}
	return 0;
}


