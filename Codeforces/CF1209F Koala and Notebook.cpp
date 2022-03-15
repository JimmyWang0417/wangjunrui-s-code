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
const int N=2e6+5;
const int mod=1e9+7;
vector<int>g[N][10];
int tot;
int n,m;
inline void add_edge(int from,int to,int dis)
{
	while(dis>=10)
	{
		++tot;
		g[tot][dis%10].push_back(to);
		to=tot;
		dis/=10;
	}
	g[from][dis].push_back(to);
}
bool vis[N];
int power[10]= {1,10,100,1000,10000,100000};
ll answer[N];
inline void dijkstra()
{
	queue<vector<int> >q;
	vector<int>tmp;
	tmp.push_back(1);
	q.push(tmp);
	vis[1]=true;
	while(!q.empty())
	{
		for(int i=0; i<10; ++i)
		{
			tmp.clear();
			for(auto u:q.front())
				for(auto v:g[u][i])
					if(!vis[v])
					{
						answer[v]=(answer[u]*10+i)%mod;
						tmp.push_back(v);
						vis[v]=true;
					}
			if(!tmp.empty())
				q.push(tmp);
		}
		q.pop();
	}
	for(int i=2; i<=n; ++i)
		printf("%lld\n",answer[i]);
}
signed main()
{
	read(n,m);
	tot=n;
	for(int i=1; i<=m; ++i)
	{
		int u,v;
		read(u,v);
		add_edge(u,v,i);
		add_edge(v,u,i);
	}
	dijkstra();
	return 0;
}


