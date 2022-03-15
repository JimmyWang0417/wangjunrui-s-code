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
using namespace std;
const int N = 2e5 + 5;
struct SAM
{
    int ch[26], len, fa;
} point[N];
int las = 1, tot = 1;
inline void insert(int c)
{
    int p = las, np = las = ++tot;
    point[np].len = point[p].len + 1;
    for (; p && !point[p].ch[c]; p = point[p].fa)
        point[p].ch[c] = np;
    if (!p)
        point[np].fa = 1;
    else
    {
        int q = point[p].ch[c];
        if (point[q].len == point[p].len + 1)
            point[np].fa = q;
        else
        {
            int nq = ++tot;
            point[nq] = point[q];
            point[nq].len = point[p].len + 1;
            point[np].fa = point[q].fa = nq;
            for (; p && point[p].ch[c] == q; p = point[p].fa)
                point[p].ch[c] = nq;
        }
    }
}
struct Edge
{
    int next, to;
} edge[N];
int head[N], num_edge;
inline void add_edge(int from, int to)
{
    edge[++num_edge].next = head[from];
    edge[num_edge].to = to;
    head[from] = num_edge;
}
ll size[N];
inline void dfs(int u)
{
    if (size[u])
        return;
    size[u] = 1;
    for (int c = 0; c < 26; ++c)
    {
        int &v = point[u].ch[c];
        if (!v)
            continue;
        dfs(v);
        size[u] += size[v];
    }
}
inline void solve(int u, int k)
{
    if (!k)
        return;
    for (int c = 0; c < 26; ++c)
    {
        int &v = point[u].ch[c];
        if (!v)
            continue;
        if (k > size[v])
            k -= size[v];
        else
        {
            putchar(c + 'a');
            solve(v, k - 1);
            break;
        }
    }
}
char str[N];
signed main()
{
    scanf("%s", str);
    for (int i = 0; str[i]; ++i)
        insert(str[i] - 'a');
    for (int i = 2; i <= tot; ++i)
        add_edge(point[i].fa, i);
    dfs(1);
    int T;
    read(T);
    while (T--)
    {
        int x;
        read(x);
        solve(1, x);
        putchar('\n');
    }
    return 0;
}