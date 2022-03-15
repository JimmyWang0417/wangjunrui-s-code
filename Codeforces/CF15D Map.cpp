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
int n,m,a,b,h[N][N];
int minn[N][N];
ll sum[N][N];
struct dandiao
{
	int q[N],valq[N],head,tail,limit;
	inline void init(int _limit)
	{
		head=1,tail=0;
		limit=_limit;
	}
	inline void insert(int pos,int val)
	{
		while(head<=tail&&q[head]<pos-limit+1)
			++head;
		while(head<=tail&&valq[tail]>val)
			--tail;
		++tail;
		q[tail]=pos,valq[tail]=val;
	}
	inline int calc()
	{
		return valq[head];
	}
} q1[N],q2;
#define query(x1,y1,x2,y2) (sum[x2][y2]-sum[(x1)-1][y2]-sum[x2][(y1)-1]+sum[(x1)-1][(y1)-1])
bool vis[N][N];
signed main()
{
	read(n,m,a,b);
	for(int i=1; i<=n; ++i)
		for(int j=1; j<=m; ++j)
		{
			read(h[i][j]);
			sum[i][j]=h[i][j]+sum[i-1][j]+sum[i][j-1]-sum[i-1][j-1];
		}
	priority_queue<pair<ll,pair<int,int> > >q;
	for(int i=1; i<=m; ++i)
	{
		q1[i].init(a);
		for(int j=1; j<a; ++j)
			q1[i].insert(j,h[j][i]);
	}
	for(int i=1; i+a-1<=n; ++i)
	{
		q2.init(b);
		for(int j=1; j<=m; ++j)
			q1[j].insert(i+a-1,h[i+a-1][j]);
		for(int j=1; j<=b; ++j)
			q2.insert(j,q1[j].calc());
		minn[i][1]=q2.calc();
		for(int j=b+1; j<=m; ++j)
		{
			q2.insert(j,q1[j].calc());
			minn[i][j-b+1]=q2.calc();
		}
	}
	for(int i=1; i+a-1<=n; ++i)
		for(int j=1; j+b-1<=m; ++j)
			q.push(make_pair(-(query(i,j,i+a-1,j+b-1)-(ll)minn[i][j]*a*b),make_pair(-i,-j)));
	int cnt=0;
	while(!q.empty())
	{
		int x=-q.top().second.first,y=-q.top().second.second;
		q.pop();
		if(vis[x][y])
			continue;
		++cnt;
		for(int i=max(x-a+1,1); i<=x+a-1; ++i)
			for(int j=max(y-b+1,1); j<=y+b-1; ++j)
				vis[i][j]=true;
	}
	memset(vis,0,sizeof(vis));
	for(int i=1; i+a-1<=n; ++i)
		for(int j=1; j+b-1<=m; ++j)
			q.push(make_pair(-(query(i,j,i+a-1,j+b-1)-(ll)minn[i][j]*a*b),make_pair(-i,-j)));
	printf("%d\n",cnt);
	while(!q.empty())
	{
		ll now=-q.top().first;
		int x=-q.top().second.first,y=-q.top().second.second;
		q.pop();
		if(vis[x][y])
			continue;
		printf("%d %d %lld\n",x,y,now);
		for(int i=max(x-a+1,1); i<=x+a-1; ++i)
			for(int j=max(y-b+1,1); j<=y+b-1; ++j)
				vis[i][j]=true;
	}
	return 0;
}
