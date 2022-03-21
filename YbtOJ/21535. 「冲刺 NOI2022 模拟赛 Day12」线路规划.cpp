#include <bits/extc++.h>
#include <bits/stdc++.h>
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
constexpr int N = 1005;
constexpr ll INF = 0x3f3f3f3f3f3f3f3f;

class Network
{
public:
    void init()
    {
        tot = 1;
        source = 0;
        sink = N - 1;
    }

    void link(int x, int y, ll c)
    {
        net[++tot] = {head[x], y, c};
        head[x] = tot;
        net[++tot] = {head[y], x, 0ll};
        head[y] = tot;
    }

    ll maxflow()
    {
        ll res = 0;
        while (bfs())
            res += dfs(source, INF);
        return res;
    }

    int getSource() const { return source; }

    int getSink() const { return sink; }

private:
    struct Edge
    {
        int next, to;
        ll cap;
    };

    Edge net[N * 10];
    int tot, head[N];
    int cur[N], dis[N];
    int source, sink;

    bool bfs()
    {
        queue<int> q;
        q.push(source);
        for (int i = source; i <= sink; ++i)
            dis[i] = 0;
        dis[source] = 1;
        while (!q.empty())
        {
            int x = q.front();
            q.pop();
            cur[x] = head[x];
            for (int i = head[x], y; y = net[i].to, i; i = net[i].next)
            {
                if (net[i].cap <= 0 || dis[y])
                    continue;
                dis[y] = dis[x] + 1;
                q.push(y);
            }
        }
        return dis[sink];
    }

    ll dfs(int x, ll in)
    {
        if (x == sink)
            return in;
        ll res = 0;
        for (int &i = cur[x], y; y = net[i].to, i; i = net[i].next)
        {
            if (net[i].cap <= 0 || dis[y] != dis[x] + 1)
                continue;
            ll f = dfs(y, min(net[i].cap, in - res));
            if (f > 0)
            {
                net[i].cap -= f;
                net[i ^ 1].cap += f;
                res += f;
                if (res == in)
                    break;
            }
        }
        if (res != in)
            dis[x] = 0;
        return res;
    }
};

struct Edge
{
    int to, cap;

    bool operator<(const Edge &rhs) const { return to < rhs.to; }
};

int n, m, k;
int c[N];
int fa[N];
Network net;
vector<Edge> edges[N];
vector<int> col[N];
int tot, id;

int find(int x) { return (x == fa[x] ? x : fa[x] = find(fa[x])); }

void merge(int x, int y)
{
    x = find(x);
    y = find(y);

    if (x != y)
        fa[x] = y;
}

void build(int l, int r, int fa)
{
    for (int x = l; x < r;)
    {
        if (x != l)
            col[c[x]].push_back(fa);

        if (edges[x].empty())
        {
            net.link(fa, net.getSink(), INF);

            for (int i = l + 1; i < r; ++i)
                col[c[i]].push_back(fa);

            return;
        }
        else
        {
            ++id;
            net.link(fa, id, edges[x].back().cap);
            net.link(id, fa, INF);
            int y = edges[x].back().to;
            edges[x].pop_back();
            build(x, y, id);
            x = y;
        }
    }
}

void build()
{
    net.init();

    for (int i = 2; i < n; ++i)
    {
        if (!c[find(i)])
            c[find(i)] = ++tot;
        c[i] = c[find(i)];
    }

    for (int i = 1; i <= n; ++i)
        sort(edges[i].begin(), edges[i].end());

    build(1, n, net.getSource());

    for (int i = 0; i <= tot; ++i)
    {
        for (int j = 0; j < (int)col[i].size() - 1; ++j)
        {
            net.link(col[i][j], col[i][j + 1], INF);
            net.link(col[i][j + 1], col[i][j], INF);
        }
    }
}

int main()
{
#ifdef ONLINE_JUDGE
    freopen("underground.in","r",stdin);
    freopen("underground.out","w",stdout);
#endif
    read(n, m, k);
    for (int i = 1; i <= n; ++i)
        fa[i] = i;
    for (int i = 1; i <= m; ++i)
    {
        int x, y, c;
        read(x, y, c);
        edges[x].push_back({y, c});
    }
    for (int i = 1; i <= k; ++i)
    {
        int x, y;
        read(x, y);
        merge(x, y);
    }
    build();
    ll ans = net.maxflow();
    if (ans < INF / 2)
        printf("%lld\n", ans);
    else
        printf("-1\n");
    return 0;
}
