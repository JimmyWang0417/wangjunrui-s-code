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
inline void ckmin(int &x, int y)
{
    if (x > y)
        x = y;
}
const int N = 305;
struct Edge
{
    int next, to;
} edge[N * N];
int head[N], num_edge = 1;
inline void add_edge(int from, int to)
{
    edge[++num_edge].next = head[from];
    edge[num_edge].to = to;
    head[from] = num_edge;
}
long double edgeanswer[N * N], pointanswer[N];
int n, m;
int a[N][N];
int q[N], tot;
int S;
int dis[N];
ll cnt[N];
signed main()
{
    read(n, m);
    for (int i = 1; i <= m; ++i)
    {
        int u, v;
        read(u, v);
        add_edge(u, v);
        add_edge(v, u);
    }
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= n; ++j)
            read(a[i][j]);
    for (S = 1; S <= n; ++S)
    {
        memset(dis, 0x3f, sizeof(dis));
        dis[S] = 0, cnt[S] = 1;
        q[tot = 1] = S;
        for (int i = 1; i <= tot; ++i)
        {
            int u = q[i];
            for (int e = head[u]; e; e = edge[e].next)
            {
                int &v = edge[e].to;
                if (dis[v] > dis[u] + 1)
                {
                    dis[v] = dis[u] + 1;
                    cnt[v] = cnt[u];
                    q[++tot] = v;
                }
                else if (dis[v] == dis[u] + 1)
                    cnt[v] += cnt[u];
            }
        }
        for (int i = tot; i >= 1; --i)
        {
            int u = q[i];
            pointanswer[u] += (double)a[S][u] / cnt[u];
            for (int e = head[u]; e; e = edge[e].next)
            {
                int &v = edge[e].to;
                if (dis[v] + 1 == dis[u])
                {
                    edgeanswer[e / 2] += pointanswer[u] * cnt[v];
                    pointanswer[v] += pointanswer[u];
                }
            }
        }
        // for (int i = 1; i <= n; ++i)
        //     printf(" %d\n", q[i]);
        // putchar('\n');
        // for (int i = 1; i <= n; ++i)
        //     printf("%lld ", cnt[i]);
        // putchar('\n');
        // for (int i = 1; i <= n; ++i)
        //     printf(" %lf", pointanswer[i]);
        // putchar('\n');
        memset(pointanswer, 0, sizeof(pointanswer));
    }
    for (int i = 1; i <= m; ++i)
        printf("%.1LF\n", edgeanswer[i] + 1e-9);
    return 0;
}