#include<cstdio>
#include<queue>
#include<iostream>
#define rep(i,a,n) for (int i=a;i<=n;i++)
#define per(i,n,a) for (int i=n;i>=a;i--)
#define re register
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
#define int long long
const int N = 3e5 + 10;
struct Edge
{
	int v, nxt;
} edge[N << 1];
int cnt = 0, last[N];
void add_edge(int u, int v)
{
	edge[++cnt].v = v;
	edge[cnt].nxt = last[u], last[u] = cnt;
}
int dis[N], path[N], ord[N];
queue<int> q;
void bfs(int s)
{
	dis[s] = 1;
	path[s] = 1;
	q.push(s);
	while (!q.empty())
	{
		int u = q.front();
		q.pop();
		for (int i = last[u]; i; i = edge[i].nxt)
		{
			int v = edge[i].v;
			if (!dis[v])
			{
				dis[v] = dis[u] + 1;
				q.push(v);
			}
			if (dis[v] == dis[u] + 1)
				++ path[v];
		}
	}
}
int a[N];
signed main()
{
	int n, m;
	cin >> n >> m;
	for(re int i=1; i^(m+1); ++i)
	{
		int u , v;
		read(u),read(v);
		add_edge(v, u);
	}
	int minv = 0, maxv = 0 , p;
	cin >> p;
	for(re int i=1; i^(p+1); ++i) cin >> a[i];
	bfs(a[p]);
	for(re int i=2; i^(p+1); ++i)
	{
		if (dis[a[i]] + 1 != dis[a[i - 1]])
			++ minv, ++ maxv;
		else if (path[a[i - 1]] > 1)
			++ maxv;
	}
	printf("%lld %lld\n",minv,maxv);
	return 0;
}

