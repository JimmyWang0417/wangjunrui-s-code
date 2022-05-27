#include <bits/extc++.h>
#include <bits/stdc++.h>
#define re register
using namespace std;

inline int read()
{
    int X = 0, w = 1;
    char c = getchar();
    while (c < '0' || c > '9')
    {
        if (c == '-')
            w = -1;
        c = getchar();
    }
    while (c >= '0' && c <= '9')
        X = (X << 3) + (X << 1) + c - '0', c = getchar();
    return X * w;
}

struct Edge
{
    int v, w, nxt;
};
Edge e[500010];
int head[100010], cnt = 0;

inline void addEdge(int u, int v, int w)
{
    e[++cnt].v = v;
    e[cnt].w = w;
    e[cnt].nxt = head[u];
    head[u] = cnt;
}

int n, m, s;
int dis[100010];

struct node //�ѽڵ�
{
    int u, d;
    bool operator<(const node &rhs) const
    {
        return d > rhs.d;
    }
};
__gnu_pbds::priority_queue<pair<int, int>, greater<pair<int, int>>, __gnu_pbds::pairing_heap_tag>::point_iterator its[N];
inline void Dijkstra()
{
    __gnu_pbds::priority_queue<pair<int, int>, greater<pair<int, int>>, __gnu_pbds::pairing_heap_tag> Q;
    for (re int i = 1; i <= n; i++)
    {
        its[i] = Q.push(make_pair(2147483647, i));
        dis[i] = 2147483647;
    }
    Q.modify(its[s], make_pair(dis[s] = 0, s));
    while (!Q.empty())
    {
        int u = Q.top();
        Q.pop();
        for (re int i = head[u]; i; i = e[i].nxt)
        {
            int v = e[i].v, w = e[i].w;
            if (dis[u] + w < dis[v])
                Q.modify(its[v], make_pair(dis[v] = dis[u] + w, v));
        }
    }
}

int main()
{
    n = read(), m = read(), s = read();
    for (re int i = 1; i <= m; i++)
    {
        int X = read(), Y = read(), Z = read();
        addEdge(X, Y, Z);
    }
    Dijkstra();
    for (re int i = 1; i <= n; i++)
        printf("%d ", dis[i]);
    return 0;
}
