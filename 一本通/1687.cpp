#include<cstdio>
#include<queue>
#include<cstring>
using namespace std;
#define re register
template<typename T>
inline void read(T&x)
{
	x=0;
	char s=getchar();
	bool flag=false;
	while(!(s>='0'&&s<='9'))
	{
		if(s=='-')
			flag=true;
		s=getchar();
	}
	while(s>='0'&&s<='9')
	{
		x=(x<<1)+(x<<3)+s-'0';
		s=getchar();
	}
	if(flag)
		x=(~x)+1;
}
struct node
{
	int x,y;
	node(int&xx,int&yy):x(xx),y(yy) {}
};
const int N=310;
int n,m,a[N][N],dis[N][N];
short dx[4]= {1,-1,0,0},dy[4]= {0,0,1,-1};
queue<node>q;
int main()
{
	read(n);
	read(m);
	memset(dis,0x3f3f3f3f,sizeof(dis));
	//printf("%d\n",dis[1][1]);
	for(re int i=1; i<=n; i++)
		for(re int j=1; j<=m; j++)
			read(a[i][j]);
	for(re int i=1,j,w; i<=n; i++)
	{
		j=1;
		w=max(0,a[i][j]);
		if(w<dis[i][j])
		{
			dis[i][j]=w;
			q.push(node(i,j));
		}
		j=m;
		w=max(0,a[i][j]);
		if(w<dis[i][j])
		{
			dis[i][j]=w;
			q.push(node(i,j));
		}
	}
	for(re int j=1,i,w; j<=m; j++)
	{
		i=1;
		w=max(0,a[i][j]);
		if(w<dis[i][j])
		{
			dis[i][j]=w;
			q.push(node(i,j));
		}
		i=n;
		w=max(0,a[i][j]);
		if(w<dis[i][j])
		{
			dis[i][j]=w;
			q.push(node(i,j));
		}
	}
	while(!q.empty())
	{
		node u=q.front();
		q.pop();
		for(re int i=0,x,y,w; i<4; i++)
		{
			x=u.x+dx[i];
			y=u.y+dy[i];
			if(x<1||x>n||y<1||y>m)
				continue;
			w=max(a[x][y],dis[u.x][u.y]);
			if(w<dis[x][y])
			{
				dis[x][y]=w;
				q.push(node(x,y));
			}
		}
	}
	for(re int i=1; i<=n; i++)
	{
		for(re int j=1; j<=m; j++)
			printf("%d ",dis[i][j]-a[i][j]);
		putchar('\n');
	}
	return 0;
}
