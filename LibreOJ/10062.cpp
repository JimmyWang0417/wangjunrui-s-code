#include<cstdio>
#include<queue>
#include<cstring>
#include<cstdlib>
#define re register
using namespace std;
queue<int>q;
const int N=(100000+5)<<1;
int ch[N][2],tot,nxt[N],n;
bool bo[N],vis[N],ins[N];
char s[30001];
inline void make(const char *s)
{
	int len=strlen(s),u=0;
	char c;
	for(re int i=0; i<len; i++)
	{
		c=s[i]-'0';
		if(!ch[u][c])
			ch[u][c]=++tot;
		u=ch[u][c];
	}
	bo[u]=true;
	return;
}
inline void bfs()
{
	for(re int i=0; i<=1; i++)
		if(ch[0][i])
			q.push(ch[0][i]);
	do
	{
		int u=q.front();
		q.pop();
		for(re int i=0; i<=1; i++)
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
	while(!q.empty());
}
inline void find(int x)
{
	if(ins[x])
	{
		printf("TAK\n");
		exit(0);
	}
	if(vis[x]||bo[x])
		return;
	ins[x]=vis[x]=true;
	if(ch[x][0])
		find(ch[x][0]);
	if(ch[x][1])
		find(ch[x][1]);
	ins[x]=false;
	return;
}
int main()
{
	scanf("%d",&n);
	for(re int i=1; i<=n; i++)
	{
		scanf("%s",s);
		make(s);
	}
	bfs();
	find(0);
	printf("NIE\n");
	return 0;
}
