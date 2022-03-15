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
const int N=605,mod=123456789;

const int dx[]= {1,-1,1,-1,2,-2,2,-2};
const int dy[]= {2,-2,-2,2,1,-1,-1,1};
bitset<N*3>g[N][N],f[N*3];
inline void add(int &x,int y)
{
	x+=y;
	if(x>=mod)
		x-=mod;
}
int cnt;
int sum;
inline void gaosi()
{
//	for(int i=1; i<=cnt; ++i)
//	{
//		for(int j=1; j<=cnt+1; ++j)
//			printf("%d ",(int)f[i][j]);
//		putchar('\n');
//	}
	int ans=1;
	for(int i=1; i<=cnt; ++i)
	{
		int id=0;
		for(int j=i; j<=cnt; ++j)
			if(f[j][i])
			{
				id=j;
				break;
			}
		if(!id)
		{
			add(ans,ans);
			continue;
		}
		if(id!=i)
			swap(f[id],f[i]);
		for(int j=i+1; j<=cnt; ++j)
		{
			if(f[j][i])
				f[j]^=f[i];
		}
	}
	printf("%d\n",ans);
}
int n,m;
signed main()
{
	freopen("present.in","r",stdin);
	freopen("present.out","w",stdout);
	read(n,m);
	for(int i=1; i<=min(n,2); ++i)
		for(int j=1; j<=m; ++j)
			g[i][j].set(++cnt);
	for(int i=3; i<=n; ++i)
		g[i][1].set(++cnt);
	for(int i=3; i<=n; ++i)
		for(int j=2; j<=m; ++j)
		{
			int x=i-2,y=j-1;
			g[i][j]=g[x][y];
			for(int k=0; k<8; ++k)
				if(k!=4)
				{
					int a=x+dx[k],b=y+dy[k];
					if(a<1||a>n||b<1||b>m)
						continue;
					g[i][j]^=g[a][b];
				}
		}
	for(int i=max(n-1,1); i<=n; ++i)
		for(int j=1; j<=m; ++j)
		{
			f[++sum]=g[i][j];
			f[sum][cnt+1]=!f[sum][cnt+1];
			for(int k=0; k<8; ++k)
			{
				int a=i+dx[k],b=j+dy[k];
				if(a<1||a>n||b<1||b>m)
					continue;
				f[sum]^=g[a][b];
			}
		}
//	printf("nmsl\n");
	for(int i=n-2; i>=1; --i)
	{
		f[++sum]=g[i][m];
		f[sum][cnt+1]=!g[i][m][cnt+1];
		for(int k=0; k<8; ++k)
		{
			int a=i+dx[k],b=m+dy[k];
			if(a<1||a>n||b<1||b>m)
				continue;
//			printf("%d %d\n",a,b);
			f[sum]^=g[a][b];
		}
	}
	gaosi();
	return 0;
}


