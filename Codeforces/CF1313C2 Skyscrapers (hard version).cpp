#include<bits/stdc++.h>
#define re register
#define int long long
using namespace std;
template <typename T> inline void read(T &x)
{
	x = 0;
	T fl = 1;
	char ch = 0;
	for (; ch < '0' || ch > '9'; ch = getchar()) if (ch == '-') fl = -1;
	for (; ch >= '0' && ch <= '9'; ch = getchar()) x = (x << 1) + (x << 3) + (ch ^ 48);
	x *= fl;
}
const int N = 1e6 + 10;
int sta[N] , cnt[N] ,a[N] ,b[N] , dp[N][2];
vector<int>ans;
void dfs(int u,int v)
{
	if(!u) return;
	a[u] = v;
	dfs(dp[u][0] , v);
	dfs(dp[u][1] , v);
}
void dfs1(int u,int tot)
{
	if(!u) return;
	dfs1(dp[u][0] , a[u]);
	dfs1(dp[u][1] , a[u]);
	cnt[u] = cnt[dp[u][0]] + cnt[dp[u][1]] + 1;
	b[u] = cnt[u] * (a[u] - tot);
	if(b[dp[u][0]] > b[dp[u][1]])
	{
		dfs(dp[u][1] , a[u]);
		b[u] += b[dp[u][0]];
	}
	else
	{
		dfs(dp[u][0] , a[u]);
		b[u] += b[dp[u][1]];
	}
}
signed main()
{
	int n , top = 0;
	read(n);
	for(re int i=1; i<=n; ++i)
	{
		read(a[i]);
		int j = top;
		while(j && a[sta[j]] > a[i]) j --;
		if(j) dp[sta[j]][1] = i;
		if(j < top) dp[i][0] = sta[j + 1];
		top = j;
		sta[++ top] = i;
	}
	dfs1(sta[1] , 0);
	for(re int i=1; i<=n; ++i)
		printf("%lld ",a[i]);
	putchar('\n');
	return 0;
}
