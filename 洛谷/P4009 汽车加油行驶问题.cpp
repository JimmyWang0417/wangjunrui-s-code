#include <cstdio>
#include <algorithm>
#include <cstring>
#include <cmath>
#include <vector>
#include <queue>
#define re register
#define ll long long
#define ull unsigned long long
#define rep(i,a,b) for(re int i=a;i<=b;++i)
#define per(i,a,b) for(re int i=a;i>=b;--i)
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
template<typename T,typename ...T1>
inline void read(T&x,T1&...x1)
{
	read(x);
	read(x1...);
}
const int N=105;
struct node
{
	int x,y,k,dis;
	node(int _x=0,int _y=0,int _k=0,int _dis=0):x(_x),y(_y),k(_k),dis(_dis) {}
	inline bool operator <(const node &rhs)const
	{
		return dis>rhs.dis;
	}
};
int n,val,a,b,c;
int mp[N][N];
int dis[N][N][15];
int dx[4]= {1,-1,0,0};
int dy[4]= {0,0,1,-1};
bool vis[N][N][15];
signed main()
{
	read(n,val,a,b,c);
	for(re int i=1; i<=n; ++i)
		for(re int j=1; j<=n; ++j)
			read(mp[i][j]);
	priority_queue<node>q;
	memset(dis,0x3f,sizeof(dis));
	dis[1][1][val]=0;
	q.push(node(1,1,val,dis[1][1][val]));
	while(!q.empty())
	{
		int x=q.top().x,y=q.top().y,k=q.top().k;
		q.pop();
		if(vis[x][y][k])
			continue;
		vis[x][y][k]=true;
//		printf("%d %d %d %d\n",x,y,k,dis[x][y][k]);
		if(mp[x][y]&&val!=k)
		{
			if(dis[x][y][val]>dis[x][y][k]+a)
				q.push(node(x,y,val,dis[x][y][val]=dis[x][y][k]+a));
			continue;
		}
		else
		{
			if(dis[x][y][val]>dis[x][y][k]+a+c)
				q.push(node(x,y,val,dis[x][y][val]=dis[x][y][k]+a+c));
		}
		if(k>0)
			for(re int i=0; i<4; ++i)
			{
				int fx=x+dx[i],fy=y+dy[i];
				if(fx<1||fx>n||fy<1||fy>n)
					continue;
				int v=(fx<x||fy<y)?b:0;
				if(dis[fx][fy][k-1]>dis[x][y][k]+v)
					q.push(node(fx,fy,k-1,dis[fx][fy][k-1]=dis[x][y][k]+v));
			}
	}
	int ans=0x3f3f3f3f;
	for(re int i=0; i<=val; ++i)
		ans=min(ans,dis[n][n][i]);
	printf("%d\n",ans);
	return 0;
}

