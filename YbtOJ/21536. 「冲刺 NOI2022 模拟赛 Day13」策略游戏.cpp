#include <bits/stdc++.h>
#include <ext/pb_ds/priority_queue.hpp>
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
constexpr int N = 3e5 + 5;
int n, m;
int fa[N];
inline int find(int x)
{
    if (!fa[x])
        return x;
    return fa[x] = find(fa[x]);
}
int a[N];
struct node
{
    int u, v, w;
} b[N];
struct query
{
    int id, w;
    bool flag;
    query(int _id = 0, int _w = 0, bool _flag = false) : id(_id), w(_w), flag(_flag) {}
    inline bool operator<(const query &rhs) const
    {
        return w > rhs.w;
    }
};
__gnu_pbds::priority_queue<query>::point_iterator its[N][2];
__gnu_pbds::priority_queue<query> g[N];
__gnu_pbds::priority_queue<int, greater<int>> q;
int root[N];
inline void merge(int &x, int y)
{
    if (g[x].size() < g[y].size())
        swap(x, y);
    while (!g[y].empty())
    {
        its[g[y].top().id][g[y].top().flag] = g[x].push(g[y].top());
        g[y].pop();
    }
}
int size[N];
list<pair<int, int>> recycle;
inline void unionn(int x, int y)
{
    x = find(x), y = find(y);
    merge(root[x], root[y]);
    size[x] += size[y];
    fa[y] = x;
    while (!g[root[x]].empty() && g[root[x]].top().w <= size[x])
    {
        int id = g[root[x]].top().id;
        int u = find(b[id].u), v = find(b[id].v);
        if (its[id][0]->w + its[id][1]->w <= size[u] + size[v])
        {
            q.push(id);
            g[root[u]].erase(its[id][0]);
            g[root[v]].erase(its[id][1]);
        }
        else
        {
            recycle.push_back(make_pair(id, its[id][0]->w + its[id][1]->w - size[u] - size[v]));
            g[root[u]].erase(its[id][0]);
            g[root[v]].erase(its[id][1]);
        }
    }
    while (!recycle.empty())
    {
        int id = recycle.front().first, w = recycle.front().second;
        recycle.pop_front();
        int u = find(b[id].u), v = find(b[id].v);
        its[id][0] = g[root[u]].push(query(id, size[u] + w / 2, false));
        its[id][1] = g[root[v]].push(query(id, size[v] + (w + 1) / 2, true));
    }
}
vector<int> answer;
signed main()
{
#ifdef ONLINE_JUDGE
    freopen("game.in", "r", stdin);
    freopen("game.out", "w", stdout);
#endif
    read(n, m);
    for (int i = 1; i <= n; ++i)
        read(a[i]);
    for (int i = 1; i <= n; ++i)
    {
        root[i] = i;
        size[i] = a[i];
    }
    for (int i = 1; i <= m; ++i)
    {
        int &u = b[i].u, &v = b[i].v, &w = b[i].w;
        read(u, v, w);
        if (size[u] + size[v] >= w)
            q.push(i);
        else
        {
            int d = w - size[u] - size[v];
            its[i][0] = g[u].push(query(i, size[u] + d / 2, false));
            its[i][1] = g[v].push(query(i, size[v] + (d + 1) / 2, true));
        }
    }
    while (!q.empty())
    {
        int id = q.top();
        q.pop();
        if (find(b[id].u) == find(b[id].v))
            continue;
        unionn(b[id].u, b[id].v);
        answer.push_back(id);
    }
    printf("%lu\n", answer.size());
    for (auto u : answer)
        printf("%d ", u);
    putchar('\n');
    return 0;
}
