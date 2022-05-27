#include <cstdio>
#include <cstring>
#include <queue>
#define ll long long
#define lll __int128
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
constexpr int N = 1e5 + 8 + 5;
int n, a[N];
struct Edge
{
    int next, to, dis;
} edge[N * 5];
int head[N], num_edge;
inline void add_edge(int from, int to, int dis)
{
    edge[++num_edge].next = head[from];
    edge[num_edge].to = to;
    edge[num_edge].dis = dis;
    head[from] = num_edge;
}
int dis[8][N];
bool exist[N];
char str[N];
inline void spfa(int *dist, int S)
{
    dist[S] = 0;
    queue<int> q;
    q.push(S);
    while (!q.empty())
    {
        int u = q.front();
        q.pop();
        exist[u] = false;
        for (int i = head[u]; i; i = edge[i].next)
        {
            int &v = edge[i].to;
            if (dist[v] > dist[u] + edge[i].dis)
            {
                dist[v] = dist[u] + edge[i].dis;
                if (!exist[v])
                {
                    q.push(v);
                    exist[v] = true;
                }
            }
        }
    }
}
int dp[1005][256];
signed main()
{
#ifdef ONLINE_JUDGE
    freopen("map.in", "r", stdin);
    freopen("map.out", "w", stdout);
#endif
    memset(dis, 0x3f, sizeof(dis));
    read(n);
    scanf("%s", str + 1);
    for (int i = 1; i <= n; ++i)
    {
        int c = str[i] - 'a' + 1 + n;
        add_edge(c, i, 0);
        add_edge(i, c, 1);
    }
    for (int i = 1; i < n; ++i)
    {
        add_edge(i, i + 1, 1);
        add_edge(i + 1, i, 1);
    }
    for (int i = 0; i < 8; ++i)
        spfa(dis[i], i + n + 1);
    for (int i = 1; i <= n; ++i)
        for (int j = 0; j < 8; ++j)
            if (dis[str[i] - 'a'][j + 1 + n] <= dis[j][i] && j != str[i] - 'a')
                a[i] |= 1 << j;
    ;
    int ans = 0;
    long long cnt = 0;
    for (int i = 1; i <= n; ++i)
    {
        for (int j = max(i - 15, 1); j < i; ++j)
        {
            int res = i - j;
            for (int c = 0; c < 8; ++c)
                ckmin(res, dis[c][i] + dis[c][j] + 1);
            if (res > ans)
            {
                ans = res;
                cnt = 1;
            }
            else if (res == ans)
                ++cnt;
        }
        if (i > 16)
            ++dp[str[i - 16] - 'a'][a[i - 16]];
        for (int j = 0; j < 8; ++j)
        {
            for (int k = 0; k < 256; ++k)
                if (dp[j][k])
                {
                    int res = 0x7fffffff;
                    for (int l = 0; l < 8; ++l)
                        ckmin(res, dis[j][l + n + 1] + (j == l) + dis[l][i] + ((k >> l) & 1));
                    if (res > ans)
                    {
                        ans = res;
                        cnt = dp[j][k];
                    }
                    else if (res == ans)
                    {
                        cnt += dp[j][k];
                    }
                }
        }
    }
    printf("%d %lld\n", ans, cnt);
    return 0;
}
