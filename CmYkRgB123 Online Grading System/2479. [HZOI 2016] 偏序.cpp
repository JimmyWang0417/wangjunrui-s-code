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
const int N = 5e4 + 5;
int n;
struct Tree_array
{
    int sum[N];
    inline void update(int pos, int val)
    {
        for (int i = pos; i <= n; i += lowbit(i))
            sum[i] += val;
    }
    inline int query(int pos)
    {
        int res = 0;
        for (int i = pos; i; i -= lowbit(i))
            res += sum[i];
        return res;
    }
    inline void clear(int pos)
    {
        for (int i = pos; i <= n; i += lowbit(i))
            sum[i] = 0;
    }
} tree;
struct node
{
    int opt;
    int a, b, c;
    int ans;
} a[N], b[N], c[N];
inline void solve(int l, int r)
{
    if (l == r)
        return;
    //	printf("%d %d\n",l,r);
    int mid = (l + r) >> 1;
    solve(l, mid), solve(mid + 1, r);
    //	printf("begin\n");
    int i = l, j = mid + 1, now = l;
    while (i <= mid && j <= r)
    {
        if (b[i].b < b[j].b)
        {
            if (!b[i].opt)
                tree.update(b[i].c, 1);
            c[now++] = b[i++];
        }
        else
        {
            if (b[j].opt)
                b[j].ans += tree.query(b[j].c);
            c[now++] = b[j++];
        }
    }
    while (i <= mid)
    {
        if (!b[i].opt)
            tree.update(b[i].c, 1);
        c[now++] = b[i++];
    }
    while (j <= r)
    {
        if (b[j].opt)
            b[j].ans += tree.query(b[j].c);
        c[now++] = b[j++];
    }
    //	printf("end\n");
    //	printf(" %d %d\n",l,r);
    for (i = l; i <= r; ++i)
    {
        //		printf("%d %d\n",i,c[i].c);
        tree.clear(c[i].c);
        b[i] = c[i];
    }
    //	printf("nmsl\n");
}
inline void cdq(int l, int r)
{
    if (l == r)
        return;
    int mid = (l + r) >> 1;
    cdq(l, mid), cdq(mid + 1, r);
    int i = l, j = mid + 1, now = l;
    while (i <= mid && j <= r)
    {
        if (a[i].a < a[j].a)
        {
            a[i].opt = false;
            b[now++] = a[i++];
        }
        else
        {
            a[j].opt = true;
            b[now++] = a[j++];
        }
    }
    while (i <= mid)
    {
        a[i].opt = false;
        b[now++] = a[i++];
    }
    while (j <= r)
    {
        a[j].opt = true;
        b[now++] = a[j++];
    }
    solve(l, r);
    for (i = l; i <= r; ++i)
        a[i] = b[i];
    sort(a + l, a + 1 + r, [](node x, node y)
         { return x.a < y.a; });
}
signed main()
{
    freopen("partial_order.in", "r", stdin), freopen("partial_order.out", "w", stdout);
    read(n);
    for (int i = 1; i <= n; ++i)
        read(a[i].a);
    for (int i = 1; i <= n; ++i)
        read(a[i].b);
    for (int i = 1; i <= n; ++i)
        read(a[i].c);
    cdq(1, n);
    //	for(int i=1; i<=n; ++i)
    //		printf("%d %d %d %d\n",a[i].a,a[i].b,a[i].c,a[i].ans);
    ll ans = 0;
    for (int i = 1; i <= n; ++i)
        ans += a[i].ans;
    printf("%lld\n", ans);
    return 0;
}
