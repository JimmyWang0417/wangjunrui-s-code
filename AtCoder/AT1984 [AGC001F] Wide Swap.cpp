#include <cstdio>
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
constexpr int N = 5e5 + 5;
int n, m, a[N];
int tree[N * 4];
inline int calc(int x, int y)
{
    return a[x] > a[y] ? x : y;
}
#define lc (rt << 1)
#define rc (rt << 1 | 1)
inline void pushup(int rt)
{
    tree[rt] = calc(tree[lc], tree[rc]);
}
inline void build(int rt, int l, int r)
{
    if (l == r)
    {
        tree[rt] = l;
        return;
    }
    int mid = (l + r) >> 1;
    build(lc, l, mid);
    build(rc, mid + 1, r);
    pushup(rt);
}
inline void update(int rt, int l, int r, int pos)
{
    if (l == r)
    {
        tree[rt] = 0;
        return;
    }
    int mid = (l + r) >> 1;
    if (pos <= mid)
        update(lc, l, mid, pos);
    else
        update(rc, mid + 1, r, pos);
    pushup(rt);
}
inline int query(int rt, int l, int r, int x, int y)
{
    if (r < x || l > y)
        return 0;
    if (x <= l && r <= y)
        return tree[rt];
    int mid = (l + r) >> 1;
    return calc(query(lc, l, mid, x, y), query(rc, mid + 1, r, x, y));
}
bool vis[N];
priority_queue<int> q;
inline void solve(int x)
{
    if (vis[x])
        return;
    if (query(1, 1, n, x - m + 1, x + m - 1) == x)
    {
        vis[x] = true;
        q.push(x);
    }
}
int answer[N];
signed main()
{
    read(n, m);
    a[0] = ~0x7fffffff;
    for (int i = 1; i <= n; ++i)
        read(a[i]);
    build(1, 1, n);
    for (int i = 1; i <= n; ++i)
        solve(i);
    for (int i = n; i >= 1; --i)
    {
        int u = q.top();
        q.pop();
        answer[u] = i;
        update(1, 1, n, u);
        int pos = query(1, 1, n, u - m + 1, u - 1);
        if (pos)
            solve(pos);
        pos = query(1, 1, n, u + 1, u + m - 1);
        if (pos)
            solve(pos);
    }
    for (int i = 1; i <= n; ++i)
        printf("%d\n", answer[i]);
    return 0;
}