#include<cstdio>
#include<vector>
#include<cstring>
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
const int N=1e2+5;
int n,color[N],diff[N],cc;
bool g[N][N],dp[N][N<<1];
vector<int>team[N][2];
inline bool dfs(int u,int c)
{
	color[u]=c;
	team[cc][c-1].push_back(u);
	for(re int v=0; v<n; ++v)
		if(u!=v&&!(g[u][v]&&g[v][u]))
			if((color[v]>0&&color[v]==color[u])||(!color[v]&&!dfs(v,3-c)))
				return false;
	return true;
}
inline bool build_graph()
{
	memset(color,0,sizeof(color));
	cc=0;
	for(re int i=0; i<n; ++i)
		if(!color[i])
		{
			team[cc][0].clear();
			team[cc][1].clear();
			if(!dfs(i,1))
				return false;
			diff[cc]=(int)team[cc][0].size()-(int)team[cc][1].size();
			++cc;
		}
	return true;
}
inline void print(int ans)
{
	vector<int>team1,team2;
	for(re int i=cc-1; i>=0; --i)
	{
		int t;
		if(dp[i][ans-diff[i]+n])
		{
			ans-=diff[i];
			t=0;
		}
		else
		{
			ans+=diff[i];
			t=1;
		}
		for(re int j=0; j<(int)team[i][t].size(); ++j)
			team1.push_back(team[i][t][j]);
		for(re int j=0; j<(int)team[i][1^t].size(); ++j)
			team2.push_back(team[i][1^t][j]);
	}
	printf("%d",(int)team1.size());
	for(re int i=0; i<(int)team1.size(); ++i)
		printf(" %d",(int)team1[i]+1);
	printf("\n%d",(int)team2.size());
	for(re int i=0; i<(int)team2.size(); ++i)
		printf(" %d",(int)team2[i]+1);
	printf("\n");
}
inline void DP()
{
	memset(dp,false,sizeof(dp));
	dp[0][n]=true;
	for(re int i=0; i<cc; ++i)
		for(re int j=-n; j<=n; ++j)
			if(dp[i][j+n])
				dp[i+1][j-diff[i]+n]=dp[i+1][j+diff[i]+n]=true;
	for(re int ans=0; ans<=n; ++ans)
	{
		if(dp[cc][ans+n])
		{
			print(ans);
			return;
		}
		if(dp[cc][-ans+n])
		{
			print(-ans);
			return;
		}
	}
}
int main()
{
	int T;
	read(T);
	while(T--)
	{
		read(n);
		memset(g,0,sizeof(g));
		for(re int u=0; u<n; ++u)
		{
			int v;
			while(read(v),v)
				g[u][v-1]=true;
		}
		if(n==1||!build_graph())
			printf("No solution\n");
		else
			DP();
		if(T)
			printf("\n");
	}
}
