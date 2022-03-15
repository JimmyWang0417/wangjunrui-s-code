#include<cstdio>
#include<queue>
#include<cstring>
using namespace std;
#define r register
const int N=5e6+5,Z=26;
queue<int>q;
int tot=1,nxt[N],ch[N][Z],shu[N],cnt,n,father[N];
char cha[N],a[N],b[N];
bool bo[N];
inline void make(char*s)
{
	int len=strlen(s+1),u=1;
	for(r int i=1,c; i<=len; i++)
	{
		c=s[i]-'a';
		if(!ch[u][c])
			ch[u][c]=++tot;
		u=ch[u][c];
	}
	bo[u]=true;
	shu[u]=len;
}
inline void bfs()
{
	for(r int i=0; i<26; i++)
		ch[0][i]=1;
	q.push(1);
	do
	{
		int u=q.front();
		q.pop();
		for(r int i=0; i<26; i++)
		{
			if(!ch[u][i])ch[u][i]=ch[nxt[u]][i];
			else
			{
				q.push(ch[u][i]);
				int v=nxt[u];
				while(v>0&&!ch[v][i])
					v=nxt[v];
				nxt[ch[u][i]]=ch[v][i];
			}
		}
	}
	while(!q.empty());
}
inline void find(char*s)
{
	int u=1,len=strlen(s+1);
	for(r int i=1; i<=len; i++)
	{
		cha[++cnt]=a[i];
		u=ch[u][a[i]-'a'];
		father[cnt]=u;
		if(bo[u])
		{
			cnt-=shu[u];
			u=father[cnt];
		}
	}
}
int main()
{
	scanf("%s%d",a+1,&n);
	while(n--)
	{
		scanf("%s",b+1);
		make(b);
	}
	bfs();
	find(a);
	for(r int i=1; i<=cnt; i++)
		putchar(cha[i]);
	putchar('\n');
}
