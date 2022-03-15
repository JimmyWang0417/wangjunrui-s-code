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
const int N=55,M=4005;
int n,m;
int p[M],tot;
struct node
{
	int l,r,v;
} a[M];
int g[N][M];
int mx[N][N][M];
int f[N][N][M],pre[N][N][M];
inline void dfs(int l,int r,int k)
{
	int pos=f[l][r][k=pre[l][r][k]];
//	printf("%d %d %d %d\n",l,r,pos,k);
	if(pos>l)
		dfs(l,pos-1,k);
	printf("%d ",p[k]);
	if(pos<r)
		dfs(pos+1,r,k);
}
signed main()
{
	read(n,m);
	for(int i=1; i<=m; ++i)
	{
		read(a[i].l,a[i].r,a[i].v);
		p[++tot]=a[i].v;
	}
	sort(p+1,p+1+tot);
	tot=(int)(unique(p+1,p+1+tot)-p-1);
	for(int i=1; i<=m; ++i)
		a[i].v=(int)(lower_bound(p+1,p+1+tot,a[i].v)-p);
//	for(int i=1; i<=n; ++i)
//		printf("%d ",p[i]);
//	putchar('\n');
	for(int len=1; len<=n; ++len)
	{
		for(int l=1; l+len-1<=n; ++l)
		{
			int r=l+len-1;
			memset(g,0,sizeof(g));
			for(int i=1; i<=m; ++i)
				if(l<=a[i].l&&a[i].r<=r)
					for(int j=a[i].l; j<=a[i].r; ++j)
						++g[j][a[i].v];
			for(int i=l; i<=r; ++i)
				for(int j=tot; j>=1; --j)
					g[i][j-1]+=g[i][j];
			for(int k=tot; k>=0; --k)
			{
				int maxx=-1;
				for(int i=l; i<=r; ++i)
				{
					int w=mx[l][i-1][k]+mx[i+1][r][k]+p[k]*g[i][k];
					if(w>maxx)
					{
						maxx=w;
						f[l][r][k]=i;
					}
				}
				if(maxx<mx[l][r][k+1])
				{
					mx[l][r][k]=mx[l][r][k+1];
					pre[l][r][k]=pre[l][r][k+1];
				}
				else
				{
					mx[l][r][k]=maxx;
					pre[l][r][k]=k;
				}
			}
		}
	}
	printf("%d\n",mx[1][n][1]);
	dfs(1,n,1);
	putchar('\n');
	return 0;
}


