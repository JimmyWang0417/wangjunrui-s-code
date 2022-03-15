#include <cstdio>
#include <cstring>
#define re register
#define size sze
using namespace std;
const int N=1e6+5;
int tot,ch[N][26],pos[N],nxt[N],size[N];
inline void insert(char *s,int id)
{
	int u=0;
	for(re int i=0; s[i]; ++i)
	{
		int c=s[i]-'a';
		if(!ch[u][c])
			ch[u][c]=++tot;
		u=ch[u][c];
		++size[u];
	}
	pos[id]=u;
}
inline void build()
{
	static int q[N];
	int head=1,tail=0;
	for(re int i=0; i<26; ++i)
		if(ch[0][i])
			q[++tail]=ch[0][i];
	while(head<=tail)
	{
		int u=q[head];
		for(re int i=0; i<26; ++i)
			if(!ch[u][i])
				ch[u][i]=ch[nxt[u]][i];
			else
			{
				q[++tail]=ch[u][i];
				int v=nxt[u];
				while(v&&!ch[v][i])
					v=nxt[v];
				nxt[ch[u][i]]=ch[v][i];
//				size[ch[v][i]]+=size[ch[u][i]];
			}
		++head;
	}
	for(re int i=tail; i>=0; --i)
		size[nxt[q[i]]]+=size[q[i]];
}
int n;
char str[N];
int main()
{
	scanf("%d",&n);
	for(re int i=1; i<=n; ++i)
	{
		scanf("%s",str);
		insert(str,i);
	}
	build();
	for(re int i=1; i<=n; ++i)
		printf("%d\n",size[pos[i]]);
	return 0;
}
