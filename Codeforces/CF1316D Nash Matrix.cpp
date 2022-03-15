#include<cstdio>
#include<queue>
#define re register
#define ll long long
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
const ll MAXN=1e3+51,MOD=998244353,inf=0x3f3f3f3f;
struct Tuple
{
	ll x,y,u,v;
};
ll n,flg;
Tuple top,nxt;
ll x[MAXN][MAXN],y[MAXN][MAXN],vis[MAXN][MAXN];
ll vx[4]= {0,-1,0,1},vy[4]= {-1,0,1,0};
char ch[4]= {'L','U','R','D'};
queue<Tuple>q;
char res[MAXN][MAXN];
inline ll dfs(ll xu,ll yu,ll dir)
{
	vis[xu][yu]=1,res[xu][yu]=ch[(dir+2)%4];
	ll sz=1;
	for(re int i=0; i<4; i++)
	{
		if(x[xu+vx[i]][yu+vy[i]]==-1&&!vis[xu+vx[i]][yu+vy[i]])
		{
			sz+=dfs(xu+vx[i],yu+vy[i],i);
		}
	}
	return sz;
}
inline void dfs2(ll xu,ll yu,ll xx,ll yy,ll dir)
{
	vis[xu][yu]=1;
	if(xx!=xu||yy!=yu)
	{
		res[xu][yu]=ch[(dir+2)%4];
	}
	for(re int i=0; i<4; i++)
	{
		if(x[xu+vx[i]][yu+vy[i]]==xx&&y[xu+vx[i]][yu+vy[i]]==yy&&!vis[xu+vx[i]][yu+vy[i]])
		{
			dfs2(xu+vx[i],yu+vy[i],xx,yy,i);
		}
	}
}
int main()
{
	read(n);
	for(re int i=1; i<=n; i++)
		for(re int j=1; j<=n; j++)
		{
			read(x[i][j]);
			read(y[i][j]);
		}
	for(re int i=1; i<=n; i++)
	{
		for(re int j=1; j<=n; j++)
		{
			if(x[i][j]==-1&&!vis[i][j])
			{
				if(dfs(i,j,0)<2)
				{
					printf("INVALID\n");
					return 0;
				}
			}
			for(re int k=0; k<4; k++)
			{
				if(x[i+vx[k]][j+vy[k]]==-1)
				{
					res[i][j]=ch[k];
					break;
				}
			}
		}
	}
	for(re int i=1; i<=n; i++)
	{
		for(re int j=1; j<=n; j++)
		{
			if(x[i][j]==i&&y[i][j]==j)
			{
				res[i][j]='X';
				dfs2(i,j,i,j,0);
			}
		}
	}
	for(re int i=1; i<=n; i++)
	{
		for(re int j=1; j<=n; j++)
		{
			if(!vis[i][j])
			{
				printf("INVALID\n");
				return 0;
			}
		}
	}
	printf("VALID\n");
	for(re int i=1; i<=n; i++)
	{
		for(re int j=1; j<=n; j++)
			putchar(res[i][j]);
		putchar('\n');
	}
}
