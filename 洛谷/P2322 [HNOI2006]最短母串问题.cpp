#include <cstdio>
#include <queue>
#define re register
using namespace std;
const int N=15,M=55;
char str[M];
int ch[N*M][26],tot,w[N*M],nxt[N*M];
inline void insert(char *s,int id)
{
	int u=0;
	for(re int i=0; s[i]; ++i)
	{
		int c=s[i]-'A';
		if(!ch[u][c])
			ch[u][c]=++tot;
		u=ch[u][c];
	}
	w[u]|=1<<(id-1);
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
				int v=nxt[u];
				while(v&&!ch[v][i])
					v=nxt[v];
				nxt[ch[u][i]]=ch[v][i];
				w[ch[u][i]]|=w[ch[v][i]];
//				size[ch[v][i]]+=size[ch[u][i]];
			}
	}
}
const int CNT=2480500;
bool vis[N*M][1<<13];
struct node
{
	int u,status;
	node(int x=0,int y=0):u(x),status(y) {}
};
int fa[CNT],col[CNT];
int n;
int ans[N*M],cnt;
inline void bfs(const int *w)
{
	queue<node>q;
	q.push(node(0,0));
	int head=0,tail=0;
	while(!q.empty())
	{
		int x=q.front().u,y=q.front().status;
		q.pop();
//		printf("%d %d %d %c\n",x,y,fa[head],col[head]+'A');
		if(y==(1<<n)-1)
		{
			for(re int i=head; i; i=fa[i])
				ans[++cnt]=col[i];
			for(re int i=cnt; i>=1; --i)
				putchar(ans[i]+'A');
			putchar('\n');
			return;
		}
		for(re int i=0; i<26; ++i)
		{
			int v=ch[x][i];
			if(!vis[v][y|w[v]])
			{
				vis[v][y|w[v]]=true;
//			printf("%d %d\n",v,w[v]);
				++tail;
				fa[tail]=head;
				col[tail]=i;
				q.push(node(v,y|w[v]));
			}
		}
		++head;
	}
//	printf("%d\n",-1);
}
int main()
{
	scanf("%d",&n);
	for(re int i=1; i<=n; ++i)
	{
		scanf("%s",str);
		insert(str,i);
	}
	build();
//	for(re int i=0; i<=tot; ++i)
//		printf("%d ",w[i]);
//	for(re int i=0; i<=tot; ++i)
//	{
//		for(re int j=0; j<26; ++j)
//			printf("%d ",ch[i][j]);
//		putchar('\n');
//	}
	bfs(w);
	return 0;
}
