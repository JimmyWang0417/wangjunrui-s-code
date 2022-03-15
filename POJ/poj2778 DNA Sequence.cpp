#include <queue>
#include <cstdio>
#include <cstring>
#define re register
using namespace std;
const int mod=1e5;
int n,m;
char str[15];
int ch[105][4],tot,bo[105],nxt[105];
#define calc(ch) ((ch)=='A'?0:((ch)=='C'?1:((ch)=='T'?2:3)))
inline void insert(char *s)
{
	int u=0;
	for(; *s; ++s)
	{
		int c=calc(*s);
		if(!ch[u][c])
			ch[u][c]=++tot;
		u=ch[u][c];
	}
	bo[u]=true;
}
inline void build()
{
	queue<int>q;
	for(re int i=0; i<4; ++i)
		if(ch[0][i])
			q.push(ch[0][i]);
	while(!q.empty())
	{
		int u=q.front();
		q.pop();
		for(re int i=0; i<4; ++i)
			if(!ch[u][i])
				ch[u][i]=ch[nxt[u]][i];
			else
			{
				q.push(ch[u][i]);
				nxt[ch[u][i]]=ch[nxt[u]][i];
				bo[ch[u][i]]|=bo[nxt[ch[u][i]]];
			}
	}
}
struct Matrix
{
	int g[105][105];
	Matrix()
	{
		memset(g,0,sizeof(g));
	}
	inline Matrix operator *(const Matrix &rhs)const
	{
		Matrix ans=Matrix();
		for(re int i=0; i<=tot; ++i)
			for(re int j=0; j<=tot; ++j)
				for(re int k=0; k<=tot; ++k)
					(ans.g[i][j]=(int)((ans.g[i][j]+1ll*g[i][k]*rhs.g[k][j])%mod));
		return ans;
	}
	inline Matrix operator ^(int power)
	{
		Matrix res=Matrix(),a=*this;
		for(re int i=0; i<=tot; ++i)
			res.g[i][i]=1;
		while(power)
		{
			if(power&1)
				res=res*a;
			a=a*a;
			power>>=1;
		}
		return res;
	}
	inline void print()
	{
		for(re int i=0; i<=tot; ++i)
		{
			for(re int j=0; j<=tot; ++j)
				printf(" %d",g[i][j]);
			putchar('\n');
		}
	}
} a,ans;
inline void init()
{
	for(re int u=0; u<=tot; ++u)
	{
		if(bo[u])
			continue;
		for(re int i=0; i<4; ++i)
		{
			if(bo[ch[u][i]])
				continue;
			++a.g[u][ch[u][i]];
		}
	}
}
int main()
{
	scanf("%d%d",&n,&m);
	for(re int i=0; i^n; ++i)
	{
		scanf("%s",str);
		insert(str);
	}
	build();
	init();
	ans=a^m;
	int sum=0;
	for(re int i=0; i<=tot; ++i)
		(sum+=ans.g[0][i])%=mod;
	printf("%d\n",sum);
	return 0;
}
