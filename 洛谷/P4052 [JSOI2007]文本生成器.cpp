#include <cstdio>
#include <cstring>
#include <queue>
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
const int N=100*60+5,mod=10007;
int tot,ch[N][26],nxt[N];
bool bo[N];
inline void insert(char *s)
{
	int u=0;
	for(re int i=0; s[i]; ++i)
	{
		int c=s[i]-'A';
		if(!ch[u][c])
			ch[u][c]=++tot;
		u=ch[u][c];
	}
	bo[u]=true;
}
inline void build()
{
	queue<int>q;
	for(re int i=0; i<26; ++i)
		if(ch[0][i])
			q.push(ch[0][i]);
	while(!q.empty())
	{
		int u=q.front();
		q.pop();
		for(re int i=0; i<26; ++i)
			if(!ch[u][i])
				ch[u][i]=ch[nxt[u]][i];
			else
			{
				q.push(ch[u][i]);
				nxt[ch[u][i]]=ch[nxt[u]][i];
				bo[ch[u][i]]|=bo[ch[nxt[u]][i]];
			}
	}
}
int dp[N][105],power[105];
inline int dfs(int u,int len)
{
	if(bo[u])
		return power[len];
	if(len==0)
		return 0;
	int &res=dp[u][len];
	if(res!=-1)
		return res;
	res=0;
	for(re int i=0; i<26; ++i)
		(res+=dfs(ch[u][i],len-1))%=mod;
	return res;
}
int n,m;
char str[105];
int main()
{
	memset(dp,-1,sizeof(dp));
	read(n),read(m);
	for(re int i=1; i<=n; ++i)
	{
		scanf("%s",str);
		insert(str);
	}
	build();
	power[0]=true;
	for(re int i=1; i<=m; ++i)
		power[i]=power[i-1]*26%mod;
//	for(re int i=0; i<=tot; ++i)
//		printf("%d ",bo[i]);
	printf("%d\n",(dfs(0,m)+mod)%mod);
	return 0;
}
