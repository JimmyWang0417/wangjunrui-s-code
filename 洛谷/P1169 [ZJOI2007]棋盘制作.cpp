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
const int N=2005;
struct node
{
	int left,right,up;
} g[N][N];
int n,m;
int a[N][N];
signed main()
{
	int ans1=0,ans2=0;
	read(n,m);
	for(int i=1; i<=n; ++i)
		for(int j=1; j<=m; ++j)
		{
			read(a[i][j]);
			g[i][j].left=g[i][j].right=j;
			g[i][j].up=i;
		}
	for(int i=1; i<=n; ++i)
		for(int j=2; j<=m; ++j)
			if(a[i][j]!=a[i][j-1])
				g[i][j].left=g[i][j-1].left;
	for(int i=1; i<=n; ++i)
		for(int j=m-1; j>=1; --j)
			if(a[i][j]!=a[i][j+1])
				g[i][j].right=g[i][j+1].right;
	for(int i=1; i<=n; ++i)
		for(int j=1; j<=m; ++j)
		{
			if(i>1&&a[i][j]!=a[i-1][j])
			{
				if(g[i-1][j].left>g[i][j].left)
					g[i][j].left=g[i-1][j].left;
				if(g[i-1][j].right<g[i][j].right)
					g[i][j].right=g[i-1][j].right;
				g[i][j].up=g[i-1][j].up;
			}
			int x=min(g[i][j].right-g[i][j].left+1,i-g[i][j].up+1);
			ans1=max(ans1,x*x);
			ans2=max(ans2,(g[i][j].right-g[i][j].left+1)*(i-g[i][j].up+1));
		}
	printf("%d\n%d\n",ans1,ans2);
	return 0;
}


