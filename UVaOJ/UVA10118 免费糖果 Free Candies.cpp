#include<cstdio>
#include<cstring>
#include<algorithm>
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
const int N=45;
int n,kase;
int mark[N][4],dp[N][N][N][N],vis[N][N][N][N];
int top[4];
inline int dfs(int sum,int mask)
{
	int &ans=dp[top[0]][top[1]][top[2]][top[3]];
	if(vis[top[0]][top[1]][top[2]][top[3]]==kase)
		return ans;
	vis[top[0]][top[1]][top[2]][top[3]]=kase;
	if(top[0]==n&&top[1]==n&&top[2]==n&&top[3]==n||sum==5)
		return ans=0;
	ans=-1;
	for(re int i=0; i<4; ++i)
		if(top[i]<n)
		{
			int s=1<<mark[top[i]][i];
			++top[i];
			if(mask&s)
				ans=max(ans,dfs(sum-1,mask^s)+1);
			else if(sum<5)
				ans=max(ans,dfs(sum+1,mask|s));
			--top[i];
		}
	return ans;
}
int main()
{
	while(read(n),n)
	{
		++kase;
		for(re int i=0; i<n; ++i)
			for(re int j=0; j<4; ++j)
				read(mark[i][j]);
		memset(top,0,sizeof(top));
		printf("%d\n",dfs(0,0));
	}

	return 0;
}
