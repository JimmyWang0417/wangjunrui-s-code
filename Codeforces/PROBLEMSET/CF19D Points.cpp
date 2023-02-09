#include <algorithm>
#include <cstdio>
#include <set>
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
constexpr int N = 2e5 + 5;
int n;
int p[N], tot;
set<int> a[N];
#define lc (rt << 1)
#define rc (rt << 1 | 1)
int tree[N * 4];
inline void pushup(int rt)
{
    tree[rt] = max(tree[lc], tree[rc]);
}
inline void update(int rt, int l, int r, int pos, int val)
{
    if (l == r)
    {
        ckmax(tree[rt], val);
        return;
    }
    int mid = (l + r) >> 1;
    if (pos <= mid)
        update(lc, l, mid, pos, val);
    else
        update(rc, mid + 1, r, pos, val);
    pushup(rt);
}
inline void change(int rt, int l, int r, int pos, int val)
{
    if (l == r)
    {
        tree[rt] = val;
        return;
    }
    int mid = (l + r) >> 1;
    if (pos <= mid)
        change(lc, l, mid, pos, val);
    else
        change(rc, mid + 1, r, pos, val);
    pushup(rt);
}
inline int query(int rt, int l, int r, int x, int y)
{
    if (l == r)
        return tree[rt] > y ? l : 0;
    int mid = (l + r) >> 1, res = 0;
    if (x <= mid && tree[lc] > y)
        res = query(lc, l, mid, x, y);
    if (res)
        return res;
    if (tree[rc] > y)
        return query(rc, mid + 1, r, x, y);
    return 0;
}
struct node
{
    int opt, x, y;
} q[N];
signed main()
{
    read(n);
    for (int i = 1; i <= n; ++i)
    {
        static char str[10];
        scanf("%s", str);
        read(q[i].x, q[i].y);
        if (str[0] == 'a')
        {
            q[i].opt = 1;
            p[++tot] = q[i].x;
        }
        else if (str[0] == 'r')
            q[i].opt = 2;
        else
            q[i].opt = 3;
    }
    sort(p + 1, p + 1 + tot);
    tot = (int)(unique(p + 1, p + 1 + tot) - p - 1);
    for (int i = 1; i <= n; ++i)
    {
        if (q[i].opt == 1)
        {
            q[i].x = (int)(lower_bound(p + 1, p + 1 + tot, q[i].x) - p);
            update(1, 1, tot, q[i].x, q[i].y);
            a[q[i].x].insert(q[i].y);
        }
        else if (q[i].opt == 2)
        {
            q[i].x = (int)(lower_bound(p + 1, p + 1 + tot, q[i].x) - p);
            a[q[i].x].erase(a[q[i].x].find(q[i].y));
            change(1, 1, tot, q[i].x, a[q[i].x].empty() ? 0 : *a[q[i].x].rbegin());
        }
        else
        {
            q[i].x = (int)(upper_bound(p + 1, p + 1 + tot, q[i].x) - p);
            int res = q[i].x > tot ? 0 : query(1, 1, tot, q[i].x, q[i].y);
            if (!res)
                printf("-1\n");
            else
                printf("%d %d\n", p[res], *a[res].upper_bound(q[i].y));
        }
    }
    return 0;
}