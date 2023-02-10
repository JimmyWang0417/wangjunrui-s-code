#include <bits/stdc++.h>
#define lowbit(x) ((x) & (-(x)))
#define re register
#define ll long long
#define ull unsigned long long
#define rep(i, a, b) for (re int i = a; i <= b; ++i)
#define per(i, a, b) for (re int i = a; i >= b; --i)
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
inline void clear(T *array, int l, int r, int val)
{
    memset(&array[l], val, sizeof(T) * (r - l + 1));
}
using namespace std;
const int N = 4e6 + 5;
int n;
int ch[N][2];
int tot = 1;
vector<int> g[N];
inline int rev(int x)
{
    if (x <= n)
        return x + n;
    else
        return x - n;
}
int cnt;
int cur[N], ruc[N];
inline void insert(char *s, int id)
{
    int u = 1;
    for (int i = 0; s[i]; ++i)
    {
        int c = s[i] - '0';
        if (!ch[u][c])
            ch[u][c] = ++tot;
        u = ch[u][c];
    }
    if (!cur[u])
    {
        cur[u] = ++cnt;
        ruc[u] = ++cnt;
        g[id].push_back(cur[u]);
        g[ruc[u]].push_back(rev(id));
    }
    else
    {
        g[id].push_back(ruc[u]);
        g[cur[u]].push_back(rev(id));

        ++cnt;
        g[id].push_back(cnt);
        g[cur[u]].push_back(cnt);
        cur[u] = cnt;

        ++cnt;
        g[cnt].push_back(rev(id));
        g[cnt].push_back(ruc[u]);
        ruc[u] = cnt;
    }
    //	putchar('\n');
}
inline void dfs(int u, int pre1, int pre2)
{
    if (cur[u])
    {
        if (!pre1)
            pre1 = cur[u], pre2 = ruc[u];
        else
        {
            g[cur[u]].push_back(pre2);
            g[pre1].push_back(ruc[u]);
            ++cnt;
            g[pre1].push_back(cnt);
            g[cur[u]].push_back(cnt);
            pre1 = cnt;

            ++cnt;
            g[cnt].push_back(pre2);
            g[cnt].push_back(ruc[u]);
            pre2 = cnt;
        }
    }
    if (ch[u][0])
        dfs(ch[u][0], pre1, pre2);
    if (ch[u][1])
        dfs(ch[u][1], pre1, pre2);
}
char str[N];
int dfn[N], low[N], dfstime;
int st[N], top;
int belong[N], col;
inline void tarjan(int u)
{
    dfn[u] = low[u] = ++dfstime;
    st[++top] = u;
    for (auto v : g[u])
    {
        if (!dfn[v])
        {
            tarjan(v);
            low[u] = min(low[u], low[v]);
        }
        else if (!belong[v])
            low[u] = min(low[u], dfn[v]);
    }
    if (dfn[u] == low[u])
    {
        belong[u] = ++col;
        while (st[top] != u)
            belong[st[top--]] = col;
        --top;
    }
}
signed main()
{
    freopen("code.in", "r", stdin);
    freopen("code.out", "w", stdout);
    read(n);
    cnt = n * 2 + 2;
    for (int i = 1; i <= n; ++i)
    {
        scanf("%s", str);
        int j;
        for (j = 0; str[j]; ++j)
            if (str[j] == '?')
                break;
        if (str[j])
        {
            str[j] = '0';
            insert(str, i);
            str[j] = '1';
            insert(str, rev(i));
        }
        else
        {
            insert(str, i);
            g[rev(i)].push_back(i);
            //			printf("%d %d\n",rev(i),i);
        }
        //		printf("%d %d\n",a[i].first,a[i].second);
    }
    dfs(1, 0, 0);
    for (int i = 1; i <= 2 * n; ++i)
        if (!dfn[i])
            tarjan(i);
    for (int i = 1; i <= n; ++i)
    {
        if (belong[i] == belong[i + n])
        {
            printf("NO\n");
            return 0;
        }
    }
    printf("YES\n");
    return 0;
}
