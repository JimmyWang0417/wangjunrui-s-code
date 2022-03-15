#include<cstdio>
#include<queue>
#include<iostream>
#define re register
using namespace std;
int n,m,w;
char s[1010][1010];
int f[1010][1010],qix,qiy,zhongx,zhongy;
int fx[4]= {0,0,1,-1},
           fy[4]= {1,-1,0,0};
bool exist[1010][1010];
struct node
{
	int x,y;
} u,v;
queue<node>q;
int main()
{
	cin>>n>>m;
	for(re int i=1; i<=n; i++)
		for(re int j=1; j<=m; j++)
			f[i][j]=3;
	for(re int i=1; i<=n; i++)
		for(re int j=1; j<=m; j++)
		{
			cin>>s[i][j];
			if(s[i][j]=='s')
			{
				qix=i;
				qiy=j;
			}
			else if(s[i][j]=='g')
			{
				zhongx=i;
				zhongy=j;
			}
		}
	u.x=qix;
	u.y=qiy;
	q.push(u);
	f[u.x][u.y]=0;
	while(!q.empty())
	{
		u=q.front();
		q.pop();
		exist[u.x][u.y]=false;
		for(re int i=0; i<4; i++)
		{
			v.x=u.x+fx[i];
			v.y=u.y+fy[i];
			w=f[u.x][u.y];
			if(s[v.x][v.y]=='#')
				w++;
			if(w<f[v.x][v.y])
			{
				f[v.x][v.y]=w;
				if(v.x==zhongx&&v.y==zhongy)
				{
					printf("YES\n");
					return 0;
				}
				if(!exist[v.x][v.y])
				{
					q.push(v);
					exist[v.x][v.y]=true;
				}
			}
		}
	}
	printf("NO\n");
	return 0;
}
