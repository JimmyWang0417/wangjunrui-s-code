/**
 *    unicode: UTF-8
 *    name:    P5471 [NOI2019] 弹跳
 *    author:  wangjunrui
 *    created: 2022.07.26 周二 09:38:58 (Asia/Shanghai)
 **/
#include <algorithm>
#include <cstdio>
#include <cstring>
#include <ext/pb_ds/priority_queue.hpp>
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
typedef pair<int, int> node;
constexpr int N = 1.5e5 + 5, M = 1e6 + 5;
int n, m;
struct Edge
{
    int next, to, dis;
} edge[M];
int head[N], num_edge;
inline void add_edge(int from, int to, int dis)
{
    ++num_edge;
    edge[num_edge].next = head[from];
    edge[num_edge].to = to;
    edge[num_edge].dis = dis;
    head[from] = num_edge;
}
node a[N];
int b[N];
struct Tree
{
    int l, r;
    int maxx, maxy;
    int minx, miny;
} tree[N];
#define lc(rt) tree[rt].l
#define rc(rt) tree[rt].r
int root;
inline void pushup(int rt)
{
    tree[rt].minx = tree[rt].maxx = a[rt].first;
    tree[rt].miny = tree[rt].maxy = a[rt].second;
    if (lc(rt))
    {
        ckmin(tree[rt].minx, tree[lc(rt)].minx);
        ckmin(tree[rt].miny, tree[lc(rt)].miny);
        ckmax(tree[rt].maxx, tree[lc(rt)].maxx);
        ckmax(tree[rt].maxy, tree[lc(rt)].maxy);
    }
    if (rc(rt))
    {
        ckmin(tree[rt].minx, tree[rc(rt)].minx);
        ckmin(tree[rt].miny, tree[rc(rt)].miny);
        ckmax(tree[rt].maxx, tree[rc(rt)].maxx);
        ckmax(tree[rt].maxy, tree[rc(rt)].maxy);
    }
}
inline void build(int &rt, int l, int r, bool flag)
{
    int mid = (l + r) >> 1;
    nth_element(b + l, b + mid, b + 1 + r, [flag](int x, int y)
                { return flag ? a[x].first < a[y].first : a[x].second < a[y].second; });
    rt = b[mid];
    if (l < mid)
        build(lc(rt), l, mid - 1, flag ^ 1);
    if (mid < r)
        build(rc(rt), mid + 1, r, flag ^ 1);
    pushup(rt);
}
int p[N], tot;
inline void query(int rt, int x1, int y1, int x2, int y2)
{
    if (x1 > tree[rt].maxx || tree[rt].minx > x2 || y1 > tree[rt].maxy || tree[rt].miny > y2)
        return;
    if (x1 <= tree[rt].minx && tree[rt].maxx <= x2 && y1 <= tree[rt].miny && tree[rt].maxy <= y2)
    {
        p[++tot] = rt + n;
        return;
    }
    if (x1 <= a[rt].first && y1 <= a[rt].second &&
        a[rt].first <= x2 && a[rt].second <= y2)
        p[++tot] = rt;
    if (lc(rt))
        query(lc(rt), x1, y1, x2, y2);
    if (rc(rt))
        query(rc(rt), x1, y1, x2, y2);
}
struct Query
{
    int x1, y1, x2, y2;
} c[N];
int dis[N];
bool vis[N];
inline void dijkstra()
{
    __gnu_pbds::priority_queue<pair<int, int>, greater<pair<int, int>>> q;
    memset(dis, 0x3f, sizeof(dis));
    q.push(make_pair(dis[1] = 0, 1));
    while (!q.empty())
    {
        int u = q.top().second;
        q.pop();
        if (vis[u])
            continue;
        vis[u] = true;
        if (u > n)
        {
            int v = u - n;
            if (dis[v] > dis[u])
                q.push(make_pair(dis[v] = dis[u], v));
            if (lc(u - n))
            {
                v = lc(u - n) + n;
                if (dis[v] > dis[u])
                    q.push(make_pair(dis[v] = dis[u], v));
            }
            if (rc(u - n))
            {
                v = rc(u - n) + n;
                if (dis[v] > dis[u])
                    q.push(make_pair(dis[v] = dis[u], v));
            }
        }
        else
            for (int i = head[u]; i; i = edge[i].next)
            {
                int w = edge[i].to;
                tot = 0;
                query(root, c[w].x1, c[w].y1, c[w].x2, c[w].y2);
                for (int j = 1; j <= tot; ++j)
                {
                    int v = p[j];
                    if (dis[v] > dis[u] + edge[i].dis)
                        q.push(make_pair(dis[v] = dis[u] + edge[i].dis, v));
                }
            }
    }
}
signed main()
{
    freopen("jump.in", "r", stdin);
    freopen("jump.out", "w", stdout);
    int w, h;
    read(n, m, w, h);
    for (int i = 1; i <= n; ++i)
    {
        read(a[i].first, a[i].second);
        b[i] = i;
    }
    build(root, 1, n, true);
    for (int i = 1; i <= m; ++i)
    {
        int pos, val;
        read(pos, val, c[i].x1, c[i].x2, c[i].y1, c[i].y2);
        add_edge(pos, i, val);
    }
    dijkstra();
    for (int i = 2; i <= n; ++i)
        printf("%d\n", dis[i]);
    return 0;
}