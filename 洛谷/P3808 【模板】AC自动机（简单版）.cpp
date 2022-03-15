#include <cstdio>
#include <queue>
#define re register
using namespace std;
const int N=1e6+5;
int tot,ch[N][26],bo[N],nxt[N];
bool vis[N];
inline void insert(char *s)
{
	int u=0;
	for(re int i=0; s[i]; ++i)
	{
		int c=s[i]-'a';
		if(!ch[u][c])
			ch[u][c]=++tot;
		u=ch[u][c];
	}
	++bo[u];
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
			}
	}
}
inline int query(char *s)
{
	int u=0,ans=0;
	for(re int i=0; s[i]; ++i)
	{
		int c=s[i]-'a';
		u=ch[u][c];
		int now=u;
		while(now&&!vis[now])
		{
			ans+=bo[now];
			vis[now]=true;
			now=nxt[now];
		}
	}
	return ans;
}
int n;
char str[N];
int main()
{
	scanf("%d",&n);
	for(re int i=1; i<=n; ++i)
	{
		scanf("%s",str);
		insert(str);
	}
	build();
	scanf("%s",str);
	printf("%d\n",query(str));
	return 0;
}
