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
const int N=1.5e5+5;
int n;
int fa[N];
queue<int>g[N];
inline int find(int x)
{
	return !fa[x]?x:fa[x]=find(fa[x]);
}
inline void unionn(int x,int y)
{
	x=find(x),y=find(y);
	if(g[x].size()<g[y].size())
		swap(x,y);
	fa[y]=x;
	while(!g[y].empty())
	{
		g[x].push(g[y].front());
		g[y].pop();
	}
}
signed main()
{
	read(n);
	for(int i=1; i<=n; ++i)
		g[i].push(i);
	for(int i=1; i<n; ++i)
	{
		int x,y;
		read(x,y);
		unionn(x,y);
	}
	int root=find(1);
	while(!g[root].empty())
	{
		printf("%d ",g[root].front());
		g[root].pop();
	}
	putchar('\n');
	return 0;
}


