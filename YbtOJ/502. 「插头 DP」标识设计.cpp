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
const int N=35,M=4800;
int n,m;
char str[N][N];
ll dp[N][N][4][M][2];
bool vis[N][N][4][M][2];
int p[M];
map<int,int>mp;
int cnt;
inline ll dfs(int x,int y,int k,int pos,bool flag)
{
	ll &ans=dp[x][y][k][pos][flag];
	if(vis[x][y][k][pos][flag])
		return ans;
	vis[x][y][k][pos][flag]=true;
	int S=p[pos];
	ans=0;
	if(x>n)
	{
		if((!S)&&(!k))
			return ans=1;
		return ans=0;
	}
	if(y>m)
	{
		if(flag)
			return ans=0;
		return ans=dfs(x+1,1,k,pos,0);
	}
	if((S>>(y-1))&1)
	{
		if(str[x][y]=='#'||flag)
			return ans=0;
		return ans=dfs(x,y+1,k,pos,0)+dfs(x,y+1,k,mp[S^(1<<(y-1))],1);
	}
	if(flag)
	{
		if(str[x][y]=='#')
			return ans=0;
		return ans=dfs(x,y+1,k,pos,1)+dfs(x,y+1,k,pos,0);
	}
	ans=dfs(x,y+1,k,pos,flag);
	if(k>0&&str[x][y]=='.'&&y<m)
	{
		ans+=dfs(x,y+1,k-1,mp[S|(1<<(y-1))],flag);
	}
//	printf("%d %d %d %d %d = %d\n",x,y,k,pos,flag,ans);
	return ans;
}
signed main()
{
	read(n,m);
	for(int i=1; i<=n; ++i)
		scanf("%s",str[i]+1);

	mp[0]=++cnt;
	p[cnt]=0;//ÀëÉ¢»¯×´Ì¬
	for(int i=1; i<=m; i++)
	{
		int t=1<<(i-1);
		mp[t]=++cnt;
		p[cnt]=t;
		for(int j=i+1; j<=m; j++)
		{
			int tt=t|(1<<(j-1));
			mp[tt]=++cnt;
			p[cnt]=tt;
			for(int k=j+1; k<=m; k++)
			{
				int ttt=tt|(1<<(k-1));
				mp[ttt]=++cnt;
				p[cnt]=ttt;
			}
		}
	}
	printf("%lld\n",dfs(1,1,3,0,0));
	return 0;
}


