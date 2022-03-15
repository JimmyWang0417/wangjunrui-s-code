#include <queue>
#include <cstdio>
#include <cstring>
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
const int N=15,M=6000;
int tot,ch[M][4],w[M],nxt[M];
inline int change(char &s)
{
	if(s=='A')
		return 0;
	if(s=='G')
		return 1;
	if(s=='C')
		return 2;
	return 3;
}
inline void insert(char *s,int id)
{
	int u=0;
	for(re int i=0; s[i]; ++i)
	{
		int c=change(s[i]);
		if(!ch[u][c])
			ch[u][c]=++tot;
		u=ch[u][c];
	}
	w[u]|=1<<id;
	return;
}
inline void build()
{
	queue<int>que;
	for(re int i=0; i<4; ++i)
		if(ch[0][i])
			que.push(ch[0][i]);
	while(!que.empty())
	{
		int u=que.front();
		que.pop();
		for(re int i=0; i<4; ++i)
			if(!ch[u][i])
				ch[u][i]=ch[nxt[u]][i];
			else
			{
				que.push(ch[u][i]);
				nxt[ch[u][i]]=ch[nxt[u]][i];
				w[ch[u][i]]|=w[ch[nxt[u]][i]];
			}
	}
	return;
}
struct node
{
	int u,status,len;
	node(int uu=0,int s=0,int l=0):u(uu),status(s),len(l) {}
} ;
bool vis[M][(1<<12)+5];
int n;
inline void bfs()
{
	queue<node>q;
	q.push(node());
	while(!q.empty())
	{
		int x=q.front().u,y=q.front().status,len=q.front().len;
		q.pop();
//		printf("%d %d %d\n",x,y,q[head].len);
		if(y==(1<<n)-1)
		{
			printf("%d\n",len);
			return;
		}
		for(re int i=0; i<4; ++i)
		{
			const int v=ch[x][i];
			if(!vis[v][y|w[v]])
			{
				vis[v][y|w[v]]=true;
				q.push(node(v,y|w[v],len+1));
			}
		}
	}
//	printf("%d\n",-1);
	return;
}
char str[M+5];
inline void work()
{
	read(n);
	for(re int i=0; i<n; ++i)
	{
		scanf("%s",str);
		insert(str,i);
	}
	build();
//	for(re int i=1; i<=tot; ++i)
//		printf("%d ",w[i]);
	bfs();
	memset(ch,0,sizeof(ch));
	memset(w,0,sizeof(w));
	memset(nxt,0,sizeof(nxt));
	memset(vis,0,sizeof(vis));
	return;
}
int main()
{
	int T;
	read(T);
	while(T--)
		work();
	return 0;
}
