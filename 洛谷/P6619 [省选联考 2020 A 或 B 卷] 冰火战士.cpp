#include <algorithm>
#include <cmath>
#include <cstdio>
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
constexpr int N = 2e6 + 5;
int n, m;
struct query
{
    int opt, t, x, y;
} a[N];
int p[N], tot;
int all;
struct tree_array
{
    int c[N];
    inline int operator[](const int &x)
    {
        return c[x];
    }
    inline void update(int pos, int val)
    {
        for (int i = pos; i <= tot; i += lowbit(i))
            c[i] += val;
    }
} tree1, tree2;
inline void solve()
{
    int pos = 0, sum1 = 0, sum2 = 0;
    for (int i = m; i >= 0; --i)
    {
        int nxt = pos | 1 << i;
        if (nxt <= tot && sum1 + tree1[nxt] + sum2 + tree2[nxt] <= all)
        {
            pos = nxt;
            sum1 += tree1[nxt], sum2 += tree2[nxt];
        }
    }
    int res = min(sum1, all - sum2), where = pos;
    if (pos < tot)
    {
        sum1 = 0, sum2 = 0;
        for (int i = pos + 1; i >= 1; i -= lowbit(i))
        {
            sum1 += tree1[i];
            sum2 += tree2[i];
        }
        int now = min(sum1, all - sum2);
        pos = 0;
        if (res <= now)
        {
            res = now;
            int v1 = 0, v2 = 0;
            for (int i = m; i >= 0; --i)
            {
                int nxt = pos | 1 << i;
                if (nxt <= tot && all - v2 - tree2[nxt] >= now)
                {
                    pos = nxt;
                    v1 += tree1[nxt], v2 += tree2[nxt];
                }
            }
            where = pos;
        }
    }
    if (!res)
        printf("Peace\n");
    else
        printf("%d %d\n", p[where], res * 2);
}
signed main()
{
    read(n);
    for (int i = 1; i <= n; ++i)
    {
        read(a[i].opt);
        if (a[i].opt == 1)
        {
            read(a[i].t, a[i].x, a[i].y);
            p[++tot] = a[i].x;
        }
        else
            read(a[i].x);
    }
    sort(p + 1, p + 1 + tot);
    tot = (int)(unique(p + 1, p + 1 + tot) - p - 1);
    m = (int)log2(tot);
    for (int i = 1; i <= n; ++i)
    {
        if (a[i].opt == 1)
        {
            if (!a[i].t)
                tree1.update(lower_bound(p + 1, p + 1 + tot, a[i].x) - p, a[i].y);
            else
            {
                tree2.update(upper_bound(p + 1, p + 1 + tot, a[i].x) - p, a[i].y);
                all += a[i].y;
            }
        }
        else
        {
            int id = a[i].x;
            if (!a[id].t)
                tree1.update(lower_bound(p + 1, p + 1 + tot, a[id].x) - p, -a[id].y);
            else
            {
                tree2.update(upper_bound(p + 1, p + 1 + tot, a[id].x) - p, -a[id].y);
                all -= a[id].y;
            }
        }
        solve();
    }
    return 0;
}