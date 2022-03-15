#include <cstdio>
#include <cstring>
#include <queue>
#define re register
using namespace std;
const int N=(1<<14)*52;
int ch[N][26],nxt[N];
bool bo[N];
int tot=0;
inline void insert(int x,int len)
{
	int u=0;
	for(re int i=0; i<len; ++i)
	{
		bool c=(x>>i)&1;
		if(!ch[u][c])
			ch[u][c]=++tot;
		u=ch[u][c];
	}
	for(re int i=0; i<len; ++i)
	{
		bool c=(x>>i)&1;
		if(!ch[u][c])
			ch[u][c]=++tot;
		u=ch[u][c];
	}
	for(re int i=0; i<len; ++i)
	{
		bool c=(x>>i)&1;
		if(!ch[u][c])
			ch[u][c]=++tot;
		u=ch[u][c];
	}
	bo[u]=true;
}
inline void bfs()
{
	queue<int>q;
	if(ch[0][0])
		q.push(ch[0][0]);
	if(ch[0][1])
		q.push(ch[0][1]);
	while(!q.empty())
	{
		int u=q.front();
		q.pop();
		for(re int i=0; i<=1; ++i)
		{
			if(!ch[u][i])
				ch[u][i]=ch[nxt[u]][i];
			else
			{
				q.push(ch[u][i]);
				int v=nxt[u];
				while(v>0&&!ch[v][i])
					v=nxt[v];
				nxt[ch[u][i]]=ch[v][i];
				bo[ch[u][i]]|=bo[ch[v][i]];
			}
		}
	}
	return;
}
inline void insert(int len)
{
	for(re int i=0; i<(1<<len); ++i)
		insert(i,len);
}
int dp[N][45];
inline int dfs(int u,int len)
{
	if(bo[u])
		return 0;
	if(len==0)
		return 1;
	if(dp[u][len]!=-1)
		return dp[u][len];
	return dp[u][len]=dfs(ch[u][0],len-1)+dfs(ch[u][1],len-1);
}
int main()
{
	int n;
	scanf("%d",&n);
	for(re int i=1; i*3<=n; ++i)
		insert(i);
	bfs();
	memset(dp,-1,sizeof(dp));
	printf("%d\n",dfs(0,n));
	return 0;
}
