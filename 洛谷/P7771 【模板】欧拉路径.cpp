#include <bits/stdc++.h>
#include <bits/extc++.h>
#define ll long long
#define ull unsigned ll
#define lowbit(x) (x & (-x))
template <typename T>
inline void read(T &x)
{
    x = 0;
    char s = (char)getchar();
    bool f = false;
    while (!(s >= '0' && s <= '9'))
    {
        if (s == '-')
            f = true;
        s = (char)getchar();
    }
    while (s >= '0' && s <= '9')
    {
        x = (x << 1) + (x << 3) + s - '0';
        s = (char)getchar();
    }
    if (f)
        x = (~x) + 1;
}
template <typename T, typename... T1>
inline void read(T &x, T1 &...x1)
{
    read(x);
    read(x1...);
}
template <typename T>
inline void ckmin(T &x, T y)
{
    if (x > y)
        x = y;
}
template <typename T>
inline void ckmax(T &x, T y)
{
    if (x < y)
        x = y;
}
using namespace std;
constexpr int N = 2e5 + 5;
int n, m;
int head[N];
vector<int> g[N];
int st[N], top;
inline void dfs(int u)
{
    for (int i = head[u]; i < (int)g[u].size(); i = head[u])
    {
        head[u] = i + 1;
        dfs(g[u][i]);
    }
    st[++top] = u;
}
int deg[N][2];
signed main()
{
    read(n, m);
    for (int i = 1; i <= m; ++i)
    {
        int u, v;
        read(u, v);
        g[u].push_back(v);
        ++deg[u][0], ++deg[v][1];
    }
    for (int i = 1; i <= n; ++i)
        sort(g[i].begin(), g[i].end());
    int S = 1, cnt0 = 0, cnt1 = 0;
    for (int u = 1; u <= n; ++u)
    {
        if (deg[u][0] - deg[u][1] == 1)
        {
            S = u;
            ++cnt0;
        }
        else if (deg[u][1] - deg[u][0] == 1)
            ++cnt1;
    }
    if (!(cnt0 == cnt1 && cnt0 <= 1))
    {
        printf("No\n");
        return 0;
    }
    dfs(S);
    while (top)
        printf("%d ", st[top--]);
    putchar('\n');
    return 0;
}