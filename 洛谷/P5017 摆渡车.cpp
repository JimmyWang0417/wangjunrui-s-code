#include<cstdio>
#include<algorithm>
#define re register
#define min(x,y) ((x)>(y)?(y):(x))
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
const int N=510,M=510;
bool vis[N][N];
int dp[N][N],t[N],n,m;
inline int dfs(int late,int st)
{
	if(late==n+1)
		return 0;
	if(st<t[late])
		return dfs(late,t[late]);
	if(vis[late][st-t[late]])
		return dp[late][st-t[late]];
	vis[late][st-t[late]]=true;
	int now=late;
	int sum=0;
	while(t[now]<=st&&now<=n)
		sum+=t[now++];
	int &ans=dp[late][st-t[late]];
	ans=st*(now-late)-sum+dfs(now,st+m);
	for(; now<=n; ++now)
	{
		sum+=t[now];
		ans=min(ans,t[now]*(now-late+1)-sum+dfs(now+1,t[now]+m));
	}
	return ans;
}
int main()
{
	read(n),read(m);
	for(re int i=1; i<=n; ++i)
		read(t[i]);
	stable_sort(t+1,t+1+n);
	printf("%d\n",dfs(1,0));
	return 0;
}
