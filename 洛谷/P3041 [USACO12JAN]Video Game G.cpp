#include <bits/stdc++.h>
#define ll long long
#define ull unsigned ll
#define lowbit(x) (x & (-x))
using namespace std;
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
const int N = 1005;
int n, m;
char str[N];
int ch[N][26], nxt[N], tot;
int cnt[N];
inline void insert(char *s)
{
    int u = 0;
    for (int i = 0; s[i]; ++i)
    {
        int c = s[i] - 'A';
        if (!ch[u][c])
            ch[u][c] = ++tot;
        u = ch[u][c];
    }
    ++cnt[u];
}
inline void build()
{
    queue<int, list<int>> q;
    for (int i = 0; i < 26; ++i)
        if (ch[0][i])
            q.push(ch[0][i]);
    while (!q.empty())
    {
        int u = q.front();
        q.pop();
        for (int i = 0; i < 26; ++i)
            if (ch[u][i])
            {
                nxt[ch[u][i]] = ch[nxt[u]][i];
                cnt[ch[u][i]] += cnt[nxt[ch[u][i]]];
                q.push(ch[u][i]);
            }
            else
                ch[u][i] = ch[nxt[u]][i];
    }
}
bool vis[N][N];
ll dp[N][N];
inline ll dfs(int u, int len)
{
    if (len == m)
        return cnt[u];
    if (vis[u][len])
        return dp[u][len];
    vis[u][len] = true;
    ll &res = dp[u][len];
    for (int i = 0; i < 26; ++i)
        ckmax(res, dfs(ch[u][i], len + 1));
    res += cnt[u];
    return res;
}
signed main()
{
    read(n, m);
    for (int i = 1; i <= n; ++i)
    {
        scanf("%s", str);
        insert(str);
    }
    build();
    printf("%lld\n", dfs(0, 0));
    return 0;
}