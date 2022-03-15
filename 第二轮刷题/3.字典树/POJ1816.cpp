#include<cstdio>
#include<vector>
#include<cstring>
#define re register
#define calc(s) ((s)=='?'?26:((s)=='*'?27:(s)-'a'))
using namespace std;
const int N=1e5+5,SIZE=30;
int tree[N*SIZE][SIZE],pos[N];
bool vis[N*SIZE],flag[N*SIZE];
int tot;
inline int insert(char *s)
{
	re int u=0;
	int len=strlen(s);
	for(re int i=0; i<len; ++i)
	{
		int c=calc(s[i]);
		if(!tree[u][c])
			tree[u][c]=++tot;
		u=tree[u][c];
	}
	flag[u]=true;
	return u;
}
inline void find(char *s,int root,int pos2)
{
	int len=strlen(s);
	if(pos2==len&&flag[root])
		vis[root]=true;
	int c=s[pos2]-'a';
	if(tree[root][c])
		find(s,tree[root][c],pos2+1);
	if(tree[root][26])
		find(s,tree[root][26],pos2+1);
	if(tree[root][27])
		for(re int i=pos2; i<=len; ++i)
			find(s,tree[root][27],i);
}
int n,m;
char str[21];
int main()
{
//	freopen("ans.in","r",stdin);
//	freopen("ans.out","w",stdout);
	scanf("%d%d",&n,&m);
	for(re int i=0; i<n; ++i)
	{
		scanf("%s",str);
		pos[i]=insert(str);
		//printf("%d ",pos[i]);
	}
	/*for(re int i=1; i<=tot; ++i)
	{
		printf("%d:",i);
		for(re int j=0; j<ans[i].size(); ++j)
			printf("%d ",ans[i][j]);
		printf("\n");
	}*/
	while(m--)
	{
		scanf("%s",str);
		memset(vis,false,sizeof(vis));
		find(str,0,0);
		bool flag=true;
		for(re int i=0; i<n; ++i)
			if(vis[pos[i]])
			{
				printf("%d ",i);
				flag=false;
			}
		if(flag)
			printf("Not match");
		putchar('\n');
	}
}
