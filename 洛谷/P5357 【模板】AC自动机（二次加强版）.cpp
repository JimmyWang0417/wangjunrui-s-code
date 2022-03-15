#include <queue>
#include <cstdio>
#include <vector>
#define re register
using namespace std;
const int N=2e5+5,M=2e6+5;
int ch[N][26],pos[N];
int nxt[N],appear[N];
int tot;
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
int q[N],qs;
inline void build()
{
	int head=1;
	qs=0;
	for(re int i=0; i<26; ++i)
		if(ch[0][i])
			q[++qs]=ch[0][i];
	while(head<=qs)
	{
		int u=q[head];
		for(re int i=0; i<26; ++i)
			if(!ch[u][i])
				ch[u][i]=ch[nxt[u]][i];
			else
			{
				q[++qs]=ch[u][i];
				nxt[ch[u][i]]=ch[nxt[u]][i];
			}
		++head;
	}
}
inline void query(char *s)
{
	int u=0;
	for(re int i=0; s[i]; ++i)
	{
		int c=s[i]-'a';
		u=ch[u][c];
		++appear[u];
	}
	for(re int i=qs; i>=1; --i)
		appear[nxt[q[i]]]+=appear[q[i]];
}
int n;
char str[M];
int main()
{
	scanf("%d",&n);
	for(re int i=1; i<=n; ++i)
	{
		scanf("%s",str);
		insert(str,i);
	}
	build();
	scanf("%s",str);
	query(str);
	for(re int i=1; i<=n; ++i)
		printf("%d\n",appear[pos[i]]);
	return 0;
}
