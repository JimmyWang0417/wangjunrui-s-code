#include <cstdio>
#include <vector>
#define ll long long
using namespace std;
template <typename T>
inline void ckmax(T &x, T y)
{
	if (x < y)
		x = y;
}
template <typename T>
inline void ckmin(T &x, T y)
{
	if (x > y)
		x = y;
}
constexpr int N = 1e6 + 5;
constexpr int mod = 1e9 + 7;
template <typename T>
inline void add(T &x, T y)
{
	x += y;
	if (x >= mod)
		x -= mod;
}
inline ll quickpow(ll a, int b)
{
	ll res = 1;
	while (b)
	{
		if (b & 1)
			(res *= a) %= mod;
		(a *= a) %= mod;
		b >>= 1;
	}
	return res;
}
int n, m;
struct Edge
{
	int next, to;
} edge[N * 2];
int head[N], num_edge = 1;
inline void add_edge(int from, int to)
{
	edge[++num_edge].next = head[from];
	edge[num_edge].to = to;
	head[from] = num_edge;
}
int st[N], top;
int dfn[N], low[N], dfstime;
int belong[N], color;
vector<int> G[N];
inline void tarjan(int u, int las)
{
	st[++top] = u;
	dfn[u] = low[u] = ++dfstime;
	for (int i = head[u]; i; i = edge[i].next)
	{
		int v = edge[i].to;
		if (i == (las ^ 1))
			continue;
		if (!dfn[v])
		{
			tarjan(v, i);
			ckmin(low[u], low[v]);
		}
		else 
			ckmin(low[u], dfn[v]);
	}
	if (dfn[u] == low[u])
	{
		belong[u] = ++color;
		while (st[top] != u)
			belong[st[top--]] = color;
		--top;
	}
}
int power[N];
int cnt[N];
int size[N];
ll f[N], g[N];
inline void dfs(int u, int _fa)
{
	size[u] = 1;
	f[u] = power[cnt[u]] - 1;
	ll times = 1;
	for (int v : G[u])
	{
		if (v == _fa)
			continue;
		dfs(v, u);
		size[u] += size[v];
		f[u] = (f[u] * power[size[v]] + f[u] * f[v] + f[v] * times) % mod;
		(times *= power[size[v]]) %= mod;
	}
}
ll answer = 0;
signed main()
{
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= m; ++i)
	{
		int u, v;
		scanf("%d%d", &u, &v);
		add_edge(u, v);
		add_edge(v, u);
	}
	for (int i = 1; i <= n; ++i)
		if (!dfn[i])
			tarjan(i, 0);
	power[0] = 1;
	for (int i = 1; i <= n || i <= m; ++i)
	{
		power[i] = power[i - 1];
		add(power[i], power[i - 1]);
	}
	int qwq = 0;
	for (int u = 1; u <= n; ++u)
		for (int i = head[u]; i; i = edge[i].next)
		{
			int v = edge[i].to;
			if (belong[u] == belong[v])
				continue;
			G[belong[u]].push_back(belong[v]);
			++qwq;
		}
	for (int u = 1; u <= n; ++u)
		++cnt[belong[u]];
	dfs(1, 0);
	ll res = f[1] * power[m - size[1] + 1];
	for (int i = 2; i <= color; ++i)
		(res += f[i] * power[m - size[i]]) %= mod;
	printf("%lld\n", res);
	return 0;
}