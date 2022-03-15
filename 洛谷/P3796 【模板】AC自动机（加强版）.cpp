#include <cstdio>
#include <queue>
#include <cstring>
#define re register
const int N=150*70+5,M=1e6+5;
int ch[N][26],pos[155],tot,nxt[N];
inline void insert(char *s,int id)
{
	int u=0;
	for(re int i=0; s[i]; ++i)
	{
		int c=s[i]-'a';
		if(!ch[u][c])
			ch[u][c]=++tot;
		u=ch[u][c];
	}
	pos[id]=u;
}
inline void build()
{
	std::queue<int>q;
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
int tag[N];
inline void query(char *s)
{
	int u=0;
	for(re int i=0; s[i]; ++i)
	{
		int c=s[i]-'a';
		u=ch[u][c];
		int now=u;
		while(now)
		{
			++tag[now];
			now=nxt[now];
		}
	}
}
char str[M],a[155][75];
int main()
{
	int n;
	while(scanf("%d",&n)!=EOF&&n)
	{
		for(re int i=1; i<=n; ++i)
		{
			scanf("%s",a[i]);
			insert(a[i],i);
		}
		build();
		scanf("%s",str);
		query(str);
		int where=1;
		for(re int i=2; i<=n; ++i)
			if(tag[pos[i]]>tag[pos[where]])
				where=i;
		printf("%d\n%s\n",tag[pos[where]],a[where]);
		for(re int i=where+1;i<=n; ++i)
			if(tag[pos[where]]==tag[pos[i]])
				printf("%s\n",a[i]);
		memset(ch,0,(tot+1)*26*sizeof(int));
		memset(tag,0,(tot+1)*sizeof(int));
		memset(nxt,0,(tot+1)*sizeof(int));
		tot=0;
	}
	return 0;
}
