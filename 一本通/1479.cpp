#include<cstdio>
#include<cstring>
#include<queue>
using namespace std;
#define r register
const int N=5e5+5;
int ans,cnt,nxt[N],ch[N][30],bo[N],t,n;
char s[N<<1];
queue<int>q;
inline void make(char *s)
{
	int len=strlen(s),u=1;
	for(r int i=0,c; i<len; i++)
	{
		c=s[i]-'a';
		if(!ch[u][c])
		{
			ch[u][c]=++cnt;
			memset(ch[cnt],0,sizeof(ch[cnt]));
		}
		u=ch[u][c];
	}
	bo[u]++;
}
inline void bfs()
{
	for(r int i=0; i<=25; i++)
		ch[0][i]=1;
	q.push(1);
	nxt[1]=0;
	while(!q.empty())
	{
		int u=q.front();
		q.pop();
		for(r int i=0,v; i<=25; i++)
		{
			if(!ch[u][i])ch[u][i]=ch[nxt[u]][i];
			else
			{
				q.push(ch[u][i]);
				v=nxt[u];
				while(v>0&&!ch[v][i])v=nxt[v];
				nxt[ch[u][i]]=ch[v][i];
			}
		}
	}
}
inline void find(char *s)
{
	int u=1,len=strlen(s),c,k;
	for(r int i=0; i<len; i++)
	{
		c=s[i]-'a';
		k=ch[u][c];
		while(k>1)
		{
			ans+=bo[k];
			bo[k]=0;
			k=nxt[k];
		}
		u=ch[u][c];
	}
}
int main()
{
	scanf("%d",&t);
	while(t--)
	{
		ans=0;
		cnt=1;
		memset(bo,0,sizeof(bo));
		for(r int i=0; i<26; i++)
		{
			ch[0][i]=1;
			ch[1][i]=0;
		}
		scanf("%d",&n);
		for(r int i=1; i<=n; i++)
		{
			scanf("%s",s);
			make(s);
		}
		bfs();
		scanf("%s",s);
		find(s);
		printf("%d\n",ans);
	}
}

