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
const int N=1005,M=10005;
vector<int>g[N],revg[N];
bitset<N>vis[N],revvis[N];
int cnt[N];
int n,m;
inline void bfs(int s)
{
	queue<int>q;
	vis[s][s]=true;
	q.push(s);
	while(!q.empty())
	{
		int u=q.front();
		q.pop();
		for(auto v:g[u])
		{
			if(vis[v][s])
				continue;
			vis[v][s]=true;
			q.push(v);
		}
	}
}
inline void revbfs(int s)
{
	queue<int>q;
	revvis[s][s]=true;
	q.push(s);
	while(!q.empty())
	{
		int u=q.front();
		q.pop();
		for(auto v:revg[u])
		{
			if(revvis[v][s])
				continue;
			revvis[v][s]=true;
			q.push(v);
		}
	}
}
signed main()
{
	read(n,m);
	for(int i=1; i<=m; ++i)
	{
		int u,v;
		read(u,v);
		g[u].push_back(v);
		revg[v].push_back(u);
	}
	for(int i=1; i<=n; ++i)
	{
		bfs(i);
		revbfs(i);
	}
	int ans=0;
	for(int i=1; i<=n; ++i)
		ans+=((vis[i]|revvis[i]).count()==n);
	printf("%d\n",ans);
	return 0;
}


