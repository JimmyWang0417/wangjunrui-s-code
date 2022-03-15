#include <bits/stdc++.h>
#define lowbit(x) ((x)&(-(x)))
#define re register
#define ll long long
#define ull unsigned long long
#define rep(i,a,b) for(re int i=a;i<=b;++i)
#define per(i,a,b) for(re int i=a;i>=b;--i)
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
template<typename T>
inline void clear(T*array,int l,int r,int val)
{
	memset(&array[l],val,sizeof(T)*(r-l+1));
}
using namespace std;
const int N=1005;
const int dx[]= {1,-1,0,0};
const int dy[]= {0,0,1,-1};
bool vis[N][N],have[N][N];
int need[N][N];
int dis[N][N];
int n,m,k,d;
inline void bfs()
{
	queue<pair<int,int> >q;
	for(int i=1; i<=n; ++i)
		for(int j=1; j<=n; ++j)
			if(have[i][j])
			{
				vis[i][j]=true;
				q.push(make_pair(i,j));
			}
	ll ans=0;
	while(!q.empty())
	{
		int x=q.front().first,y=q.front().second;
		q.pop();
		if(need[x][y])
			ans+=need[x][y]*dis[x][y];
		for(int i=0; i<4; ++i)
		{
			int vx=x+dx[i],vy=y+dy[i];
			if(vx<1||vx>n||vy<1||vy>n||vis[vx][vy])
				continue;
			dis[vx][vy]=dis[x][y]+1;
			vis[vx][vy]=true;
			q.push(make_pair(vx,vy));
		}
	}
	printf("%lld\n",ans);
}
signed main()
{
	read(n,m,k,d);
	for(int i=1; i<=m; ++i)
	{
		int x,y;
		read(x,y);
		have[x][y]=true;
	}
	for(int i=1; i<=k; ++i)
	{
		int x,y,c;
		read(x,y,c);
		need[x][y]+=c;
	}
	for(int i=1; i<=d; ++i)
	{
		int x,y;
		read(x,y);
		vis[x][y]=true;
	}
	bfs();
	return 0;
}


