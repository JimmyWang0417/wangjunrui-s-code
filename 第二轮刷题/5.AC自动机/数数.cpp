#include <queue>
#include <cstdio>
#include <cstring>
#define re register
using namespace std;
const int N=1200+5,M=1500*10,mod=1e9+7;
int ch[N][10],tot=1,bo[N],nxt[N];
inline void insert(char *s)
{
	int u=1;
	for(re int i=0; s[i]; ++i)
	{
		int c=s[i]-'0';
		if(!ch[u][c])
			ch[u][c]=++tot;
		u=ch[u][c];
	}
	bo[u]=true;
}
inline void build()
{
	queue<int>q;
	for(re int i=0; i<10; ++i)
		ch[0][i]=1;
	q.push(1);
	while(!q.empty())
	{
		int u=q.front();
		q.pop();
		for(re int i=0; i<10; ++i)
			if(!ch[u][i])
				ch[u][i]=ch[nxt[u]][i];
			else
			{
				q.push(ch[u][i]);
				int v=nxt[u];
				while(v>0&&!ch[v][i])
					v=nxt[u];
				nxt[ch[u][i]]=ch[v][i];
				bo[ch[u][i]]|=bo[ch[v][i]];
			}
	}
}
int digit[N],len;
char str[N];
int dp[N][M];
int n;
inline void add(int &x,int y)
{
	x+=y;
	if(x>=mod)
		x-=mod;
}
inline int dfs(int pos,int now,bool lead,bool limit)
{
	if(bo[now])
		return 0;
	if(pos==0)
		return !lead;
	if(!lead&&!limit&&dp[pos][now]!=-1)
		return dp[pos][now];
	int maxx=limit?digit[pos]:9;
	int res=0;
//	printf("%d\n",maxx);
	for(re int i=0; i<=maxx; ++i)
	{
		if(i==0&&lead)
			add(res,dfs(pos-1,now,lead&&i==0,limit&&i==maxx));
		else
			add(res,dfs(pos-1,ch[now][i],lead&&i==0,limit&&i==maxx));
	}
//	printf("dp[%d][%d]=%d\n",pos,now,dp[pos][now]);
	if(!lead&&!limit)
		dp[pos][now]=res;
	return res;
}
int main()
{
	scanf("%s",str);
	len=strlen(str);
	for(re int i=1; i<=len; ++i)
		digit[i]=str[len-i]-'0';
//	for(re int i=1; i<=len; ++i)
//		printf("%d ",digit[i]);
	scanf("%d",&n);
	for(re int i=0; i<n; ++i)
	{
		scanf("%s",str);
		insert(str);
	}
	build();
	memset(dp,-1,sizeof(dp));
	printf("%d\n",dfs(len,1,true,true));
	return 0;
}
