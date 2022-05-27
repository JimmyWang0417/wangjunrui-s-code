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
const int N = 1e5 + 5;
struct node
{
    int u, v;
} e[N * 2];
vector<int> tree[N * 4];
#define lc (rt << 1)
#define rc (rt << 1 | 1)
int dist[N], fa[N];
inline int find(int x)
{
    return !fa[x] ? x : find(fa[x]);
}
inline void update(int rt, int l, int r, int x, int y, int id)
{
    if (r < x || l > y)
        return;
    if (x <= l && r <= y)
    {
        tree[rt].push_back(id);
        return;
    }
    int mid = (l + r) >> 1;
    update(lc, l, mid, x, y, id);
    update(rc, mid + 1, r, x, y, id);
}
int n, m, q;
bool ans[N];
int top;
pair<pair<int, int>, bool> st[N];
inline void solve(int rt, int l, int r, int cur)
{
    int lastop = top;
    for (auto i : tree[rt])
    {
        int u = find(e[i].u), v = find(e[i].v);
        if (u == v)
            continue;
        if (dist[u] < dist[v])
            swap(u, v);
        st[++top] = make_pair(make_pair(u, v), dist[u] == dist[v]);
        fa[v] = u;
        if (dist[u] == dist[v])
            ++dist[u];
        ++cur;
    }
    if (l == r)
        ans[l] = (cur == n);
    else
    {
        int mid = (l + r) >> 1;
        solve(lc, l, mid, cur);
        solve(rc, mid + 1, r, cur);
    }
    while (top > lastop)
    {
        fa[st[top].first.second] = 0;
        dist[st[top].first.first] -= st[top].second;
        --cur;
        --top;
    }
}
int las[N];
signed main()
{
    read(n, m);
    for (int i = 1; i <= m; ++i)
        read(e[i].u, e[i].v);
    read(q);
    for (int i = 1; i <= q; ++i)
    {
        int cnt;
        read(cnt);
        while (cnt--)
        {
            int x;
            read(x);
            if (las[x] + 1 < i)
                update(1, 1, q, las[x] + 1, i - 1, x);
            las[x] = i;
        }
    }
    for (int i = 1; i <= m; ++i)
        if (las[i] < q)
            update(1, 1, q, las[i] + 1, q, i);
    solve(1, 1, q, 1);
    for (int i = 1; i <= q; ++i)
        puts(ans[i] ? "Connected" : "Disconnected");
    return 0;
}
