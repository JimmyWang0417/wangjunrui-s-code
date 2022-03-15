#include<cstdio>
#include<vector>
#include<queue>
#include<cstring>
#include<cstring>
#define re register
using namespace std;
const int N=100;
int r,c,len;
int dx[4]= {1,-1,0,0},dy[4] {0,0,1,-1},dis[N][N];
int vis[N][N];
char s[10010],map[N][N];
struct Edge
{
	int x,y;
} edge[N][N][4];
struct node
{
	int dep,find,x,y;
	node(int d,int f,int xx,int yy):dep(d),find(f),x(xx),y(yy) {}
};
inline void pre()
{
	for(re int i=1; i<=r; i++)
		for(re int j=1; j<=c; j++)
			for(re int k=0; k<4; k++)
			{
				int xx=i+dx[k],yy=j+dy[k];
				while(map[i][j]==map[xx][yy])
				{
					xx+=dx[k];
					yy+=dy[k];
				}
				edge[i][j][k].x=xx;
				edge[i][j][k].y=yy;
			}
}
inline int init()
{
	memset(vis,0,sizeof(vis));
	queue<node>q;
	for(re int i=1; i<=r; i++)
		scanf("%s",map[i]+1);
	scanf("%s",s+1);
	len=strlen(s+1);
	s[++len]='*';
	pre();
	int k=1;
	while(map[1][1]==s[k]&&k<=len)
		k++;
	q.push(node(k-1,k,1,1));
	vis[1][1]=k;
	while(!q.empty())
	{
		node u=q.front();
		//printf("%d %d\n",u.x,u.y);
		q.pop();
		if(map[u.x][u.y]==s[u.find])
		{
			if(u.find==len)
			{
				printf("%d\n",u.dep+1);
				return 0;
			}
			vis[u.x][u.y]=u.find+1;
			q.push(node(u.dep+1,u.find+1,u.x,u.y));
			continue;
		}
		for(int i=0; i<=3; i++)
		{
			Edge v=edge[u.x][u.y][i];
			if(v.x<1||v.x>r||v.y<1||v.y>c||vis[v.x][v.y]>=u.find)
				continue;
			vis[v.x][v.y]=u.find;
			q.push(node (u.dep+1,u.find,v.x,v.y));
		}
	}
}
int main()
{
	while(scanf("%d%d",&r,&c)!=EOF)
	{
		init();
	}

}
