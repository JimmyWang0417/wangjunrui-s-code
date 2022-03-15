#include<cstdio>
#include<cstring>
#include<iostream>
#define re register
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
const int S=13,N=130,INF=20;
int m,n,cnt[1<<S][1<<S],dp[1<<S][1<<S],features[N];
bool vis[1<<S][1<<S];
char str[S];
inline int DP(int s,int a)
{
	if(vis[s][a])
		return dp[s][a];
	vis[s][a]=true;
	int &ans=dp[s][a];
	if(cnt[s][a]<=1)
		return ans=0;
	ans=INF;
	for(re int i=0; i<m; ++i)
		if(!(s&(1<<i)))
			ans=min(ans,max(DP(s|(1<<i),a),DP(s|(1<<i),a|(1<<i)))+1);
	return ans;
}
int main()
{
	while(read(m),read(n),m&&n)
	{
		for(re int i=0; i<n; ++i)
		{
			scanf("%s",str);
			features[i]=0;
			for(re int j=0; j<m; ++j)
				features[i]|=(str[j]=='1')<<j;
		}
		for(re int i=0; i<(1<<m); ++i)
			for(re int j=0; j<n; ++j)
				++cnt[i][i&features[j]];
		printf("%d\n",DP(0,0));
		memset(vis,false,sizeof(vis));
		memset(cnt,0,sizeof(cnt));
	}
}
