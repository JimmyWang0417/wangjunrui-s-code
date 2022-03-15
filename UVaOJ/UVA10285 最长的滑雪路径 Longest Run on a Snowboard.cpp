#include<cstdio>
#include<algorithm>
#define re register
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
const int N=105,INF=0x3f3f3f3f;
const int movex[4]= {1,-1,0,0},movey[4]= {0,0,1,-1};
char s[N];
int r,c,a[N][N],dp[N][N],vis[N][N],kase;
inline int DP(int x,int y)
{
	if(vis[x][y]==kase)
		return dp[x][y];
	vis[x][y]=kase;
	int &ans=dp[x][y];
	ans=1;
	for(re int i=0; i<4; ++i)
	{
		int nextx=x+movex[i],nexty=y+movey[i];
		if(a[x][y]>a[nextx][nexty]&&nextx>0&&nexty>0&&nextx<=r&&nexty<=c)
			ans=max(ans,DP(nextx,nexty)+1);
	}
	return ans;
}
inline void solve()
{
	++kase;
	scanf("%s",s);
	read(r);
	read(c);
	int ans=0;
	for(re int i=1; i<=r; ++i)
		for(re int j=1; j<=c; ++j)
			read(a[i][j]);
	for(re int i=1; i<=r; ++i)
		for(re int j=1; j<=c; ++j)
			ans=max(ans,DP(i,j));
	printf("%s: %d\n",s,ans);
}
//#define agree
int main()
{
#ifdef agree
	freopen("ans.in","r",stdin),freopen("ans.out","w",stdout);
#endif
	int T;
	read(T);
	while(T--)
		solve();
}
