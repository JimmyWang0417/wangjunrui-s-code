#include <queue>
#include <cstdio>
#include <cassert>
#include <cstring>
#define re register
#define LD long double
using namespace std;
const int N=5*15+5;
int ch[N][26],nxt[N],tot;
bool bo[N];
inline void insert(char *s)
{
	int u=0;
	for(re int i=0; s[i]; ++i)
	{
		int c=s[i]-'a';
		if(!ch[u][c])
			ch[u][c]=++tot;
		u=ch[u][c];
	}
	bo[u]=true;
}
int n,len,alphabet;
inline void build()
{
	queue<int>q;
	for(re int i=0; i<alphabet; ++i)
		if(ch[0][i])
			q.push(ch[0][i]);
	while(!q.empty())
	{
		int u=q.front();
		q.pop();
		for(re int i=0; i<alphabet; ++i)
		{
			if(!ch[u][i])
				ch[u][i]=ch[nxt[u]][i];
			else
			{
				q.push(ch[u][i]);
				nxt[ch[u][i]]=ch[nxt[u]][i];
			}
			bo[u]|=bo[nxt[u]];
		}
	}
}
bool vis[N];
struct Matrix
{
	LD g[N][N];
	Matrix()
	{
		memset(g,0,sizeof(g));
	}
	inline void operator *= (const Matrix&rhs)
	{
		Matrix ans=Matrix();
		for(re int i=0; i<=tot+1; ++i)
			for(re int j=0; j<=tot+1; ++j)
				for(re int k=0; k<=tot+1; ++k)
					ans.g[i][j]+=g[i][k]*rhs.g[k][j];
		*this=ans;
	}
	inline Matrix operator ^(int power)const
	{
		Matrix res=Matrix(),a=(*this);
		for(re int i=0; i<=tot+1; ++i)
			res.g[i][i]=1.0;
		while(power)
		{
			if(power&1)
				res*=a;
			a*=a;
			power>>=1;
		}
		return res;
	}
	inline void print()
	{
		for(re int i=0; i<=tot+1; ++i)
		{
			for(re int j=0; j<=tot+1; ++j)
				printf(" %LF",g[i][j]);
			putchar('\n');
		}

	}
} f;
inline void buildmatrix()
{
	queue<int>q;
	LD tmp=(LD)1.0/alphabet;
	q.push(0);
	vis[0]=true;
	while(!q.empty())
	{
		int u=q.front();
		q.pop();
		for(re int i=0; i<alphabet; ++i)
		{
			int &v=ch[u][i];
			if(!vis[v])
			{
				vis[v]=true;
				q.push(v);
			}
			if(bo[v])
			{
				f.g[u][0]+=tmp;
				f.g[u][tot+1]+=tmp;
			}
			else
				f.g[u][v]+=tmp;
		}
	}
	f.g[tot+1][tot+1]=1;
}
char str[20];
int main()
{
	scanf("%d%d%d",&n,&len,&alphabet);
	for(re int i=1; i<=n; ++i)
	{
		scanf("%s",str);
		insert(str);
	}
	build();
	buildmatrix();
	printf("%.10LF\n",(f^len).g[0][tot+1]);
	return 0;
}
