/**
 *    unicode: UTF-8
 *    name:    P5471 [NOI2019] 弹跳
 *    author:  wangjunrui
 *    created: 2022.07.27 周三 16:14:27 (Asia/Shanghai)
 **/
#include <cstdio>
#include <cstring>
#include <ext/pb_ds/priority_queue.hpp>
#include <set>
#include <vector>
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
constexpr int N = 7e4 + 5, M = 1.5e5 + 5;
int n, m;
pair<int, int> a[N];
set<pair<int, int>> se[N * 4];
#define lc (rt << 1)
#define rc (rt << 1 | 1)
inline void add(int rt, int l, int r, int pos)
{
    se[rt].insert(make_pair(a[pos].second, pos));
    if (l == r)
        return;
    int mid = (l + r) >> 1;
    if (a[pos].first <= mid)
        add(lc, l, mid, pos);
    else
        add(rc, mid + 1, r, pos);
}
inline void del(int rt, int l, int r, int pos)
{
    se[rt].erase(make_pair(a[pos].second, pos));
    if (l == r)
        return;
    int mid = (l + r) >> 1;
    if (a[pos].first <= mid)
        del(lc, l, mid, pos);
    else
        del(rc, mid + 1, r, pos);
}
struct Edge
{
    int next, to, dis;
} edge[M];
int head[N], num_edge;
inline void add_edge(int from, int to, int dis)
{
    edge[++num_edge].next = head[from];
    edge[num_edge].to = to;
    edge[num_edge].dis = dis;
    head[from] = num_edge;
}
struct node
{
    int l, r, d, u;
} b[M];
int dis[M];
int dist[N];
bool vis[M];
int st[N], top;
__gnu_pbds::priority_queue<pair<int, int>, greater<pair<int, int>>> q;
inline void query(int rt, int l, int r, int pos)
{
    if (r < b[pos].l || l > b[pos].r)
        return;
    if (b[pos].l <= l && r <= b[pos].r)
    {
        for (auto it = se[rt].lower_bound(make_pair(b[pos].d, 0));
             it != se[rt].end() && it->first <= b[pos].u; ++it)
        {
            int u = it->second;
            dist[st[++top] = u] = dis[pos];
            for (int i = head[u]; i; i = edge[i].next)
            {
                int v = edge[i].to;
                if (dis[v] > dis[pos] + edge[i].dis)
                    q.push(make_pair(dis[v] = dis[pos] + edge[i].dis, v));
            }
        }
        while (top)
            del(1, 1, n, st[top--]);
        return;
    }
    int mid = (l + r) >> 1;
    query(lc, l, mid, pos);
    query(rc, mid + 1, r, pos);
}
signed main()
{
    int w, h;
    read(n, m, w, h);
    for (int i = 1; i <= n; ++i)
    {
        read(a[i].first, a[i].second);
        add(1, 1, w, i);
    }
    for (int i = 1; i <= m; ++i)
    {
        int pos, val;
        read(pos, val, b[i].l, b[i].r, b[i].d, b[i].u);
        add_edge(pos, i, val);
    }
    memset(dis, 0x3f, sizeof(dis));
    b[0].l = b[0].r = a[1].first;
    b[0].d = b[0].u = a[1].second;
    q.push(make_pair(dis[0] = 0, 0));
    while (!q.empty())
    {
        int u = q.top().second;
        q.pop();
        if (vis[u])
            continue;
        vis[u] = true;
        query(1, 1, w, u);
    }
    for (int i = 2; i <= n; ++i)
        printf("%d\n", dist[i]);
    return 0;
}