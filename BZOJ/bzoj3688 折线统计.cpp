#include<cstdio>
#include<algorithm>
#define re register
#define lowbit(x) (x&(-x))
using namespace std;
template<typename T>
inline void read(T&x)
{
	x=0;
	char s=getchar();
	bool f=false;
	while(!(s>='0'&&s<='9'))
	{
		if(s=='-')
			f=true;
		s=getchar();
	}
	while(s>='0'&&s<='9')
	{
		x=(x<<1)+(x<<3)+s-'0';
		s=getchar();
	}
	if(f)
		x=(~x)+1;
}
const int M=15,N=1e5+5,mod=100007;
int c[2][M][N],maxx,n,m;
inline void update(bool flag,int id,int x,int y)
{
	for(; x<=maxx; x+=lowbit(x))
		(c[flag][id][x]+=y)%=mod;
}
inline int query(bool flag,int id,int x)
{
	int res=0;
	for(; x; x-=lowbit(x))
		(res+=c[flag][id][x])%=mod;
	return res;
}
struct node
{
	int x,y;
	inline bool operator < (const node &rhs)const
	{
		return x<rhs.x;
	}
} point[N];
int dp[N][M][2];
signed main()
{
	read(n);
	read(m);
	for(re int i=1; i<=n; ++i)
	{
		read(point[i].x);
		read(point[i].y);
		maxx=max(maxx,point[i].y+1);
	}
	stable_sort(point+1,point+1+n);
	for(re int i=1; i<=n; ++i)
	{
		dp[i][0][1]=dp[i][0][0]=1;
		for(re int j=1; j<=m; ++j)
		{
			dp[i][j][0]=(query(0,j,point[i].y-1)+query(1,j-1,point[i].y-1))%mod;
			dp[i][j][1]=(query(1,j,maxx)-query(1,j,point[i].y)+query(0,j-1,maxx)-query(0,j-1,point[i].y))%mod;
		}
		for(re int j=0; j<=m; ++j)
		{
			update(0,j,point[i].y,dp[i][j][0]);
			update(1,j,point[i].y,dp[i][j][1]);
		}
	}
	printf("%d\n",((query(0,m,maxx)+query(1,m,maxx))%mod+mod)%mod);
	return 0;
}
