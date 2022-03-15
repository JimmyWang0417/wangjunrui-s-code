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
int w,h;
char s[N][N];
pair<int,int>q[N];
int top;
bitset<N>vis[N];
inline void dfs(int x,int y)
{
	if(x<1||x>h||y<1||y>w)
		return;
	if(vis[x][y])
		return;
	if(s[x][y]=='0')
		return;
	vis[x].set(y);
	q[++top]=make_pair(x,y);
	for(int a=x-1; a<=x+1; ++a)
		for(int b=y-1; b<=y+1; ++b)
		{
			if(a==x&&b==y)
				continue;
			dfs(a,b);
		}
}
inline double getdist(pair<int,int>x,pair<int,int>y)
{
	double dx=x.first-y.first;
	double dy=x.second-y.second;
	return sqrt(dx*dx+dy*dy);
}
int cnt;
double p[N];

inline void solve(int x,int y)
{
	top=0;
	dfs(x,y);
	double sum=0;
	for(int i=1; i<=top; ++i)
		for(int j=i+1; j<=top; ++j)
			sum+=getdist(q[i],q[j]);
	int id=-1;
	for(int i=1; i<=cnt; ++i)
		if(fabs(sum-p[i])<1e-8)
		{
			id=i;
			break;
		}
	if(id==-1)
		p[id=++cnt]=sum;
	for(int i=1; i<=top; ++i)
		s[q[i].first][q[i].second]=(char)(id+'a'-1);
}
signed main()
{
	read(w,h);
	for(int i=1; i<=h; ++i)
		scanf("%s",s[i]+1);
	for(int i=1; i<=h; ++i)
	{
		for(int j=1; j<=w; ++j)
		{
			if(s[i][j]=='0'||vis[i][j])
				continue;
			solve(i,j);
		}
	}
	for(int i=1; i<=h; ++i)
		puts(s[i]+1);
	return 0;
}


