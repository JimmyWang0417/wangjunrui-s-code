#include<cstdio>
#include<cstring>
#include<queue>
using namespace std;
#define r register
const int N=1e7+5,M=1e5+5;
int ans,cnt=1,nxt[N],ch[N][4],m,n;
bool bo[N];
char s[N],a[M][110];
queue<int>q;
inline int change(char x)
{
	if(x=='E')return 0;
	else if(x=='S')return 1;
	else if(x=='W')return 2;
	else if(x=='N')return 3;
}
inline void make(char *s)
{
	int len=strlen(s+1),u=1;
	for(r int i=1,c; i<=len; i++)
	{
		c=change(s[i]);
		if(!ch[u][c])
			ch[u][c]=++cnt;
		u=ch[u][c];
	}
}
inline void bfs()
{
	for(r int i=0; i<=3; i++)
		ch[0][i]=1;
	q.push(1);
	nxt[1]=0;
	while(!q.empty())
	{
		int u=q.front();
		q.pop();
		for(r int i=0,v; i<=3; i++)
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
	int u=1,c,k;
	for(r int i=1; i<=n; i++)
	{
		c=change(s[i]);
		k=ch[u][c];
		while(k>1)
		{
			bo[k]=1;
			k=nxt[k];
		}
		u=ch[u][c];
	}
}
inline int sum(char *s)
{
	int u=1,len=strlen(s+1),c,ans=0;
	for(r int i=1; i<=len; i++)
	{
		c=change(s[i]);
		u=ch[u][c];
		if(bo[u])
			ans=i;
	}
	return ans;
}
int main()
{
	scanf("%d%d",&n,&m);
	scanf("%s",s+1);
	for(r int i=1;i<=m;i++)
	{
		scanf("%s",a[i]+1);
		make(a[i]);
	}
	bfs();
	find(s);
	for(r int i=1;i<=m;i++)
	printf("%d\n",sum(a[i]));
	
}
