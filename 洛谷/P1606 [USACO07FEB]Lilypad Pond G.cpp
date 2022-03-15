#include <bits/stdc++.h>
#define lowbit(x) (x&(-x))
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
const int N=35;
int mp[N][N];
#define pr pair<int,int>
int dx[8]= {1,1,2,2,-1,-1,-2,-2};
int dy[8]= {2,-2,1,-1,2,-2,1,-1};
int dis[N][N],len[N][N];
ull cnt[N][N];
pr pre[N][N];
pr bg,ed;
bool exist[N][N];
inline void dfs(pr now)
{
	if(now==bg)
	{
		printf("%d %d\n",now.first,now.second);
		return;
	}
	dfs(pre[now.first][now.second]);
	printf("%d %d\n",now.first,now.second);
}
signed main()
{
	int n,m;
	read(n,m);
	for(re int i=1; i<=n; ++i)
		for(re int j=1; j<=m; ++j)
		{
			int &x=mp[i][j];
			read(x);
			if(x==3)
				bg=make_pair(i,j);
			if(x==4)
				ed=make_pair(i,j);
		}
	queue<pr>q;
	memset(dis,0x3f,sizeof(dis));
	cnt[bg.first][bg.second]=1;
	dis[bg.first][bg.second]=0;
	q.push(bg);
	while(!q.empty())
	{
		int x=q.front().first,y=q.front().second;
		q.pop();
		exist[x][y]=false;
		for(re int i=0; i<8; ++i)
		{
			int fx=x+dx[i],fy=y+dy[i],val=(mp[fx][fy]==0)+1;
			if(fx<1||fx>n||fy<1||fy>m||mp[fx][fy]==2)
				continue;
			if(dis[fx][fy]>dis[x][y]+val)
			{
				dis[fx][fy]=dis[x][y]+val;
				len[fx][fy]=len[x][y]+1;
				cnt[fx][fy]=cnt[x][y];
				pre[fx][fy]=make_pair(x,y);
				if(!exist[fx][fy])
				{
					exist[fx][fy]=true;
					q.push(make_pair(fx,fy));
				}
			}
			else if(dis[fx][fy]==dis[x][y]+val)
				cnt[fx][fy]+=cnt[x][y];
		}
	}
//	dfs(ed);
	printf("%d\n%llu\n",dis[ed.first][ed.second]-len[ed.first][ed.second],cnt[ed.first][ed.second]);
	return 0;
}

