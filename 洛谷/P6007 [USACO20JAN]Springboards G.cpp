#include <bits/stdc++.h>
#define ll long long
#define ull unsigned ll
#define lowbit(x) (x & (-x))
using namespace std;
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
const int N = 1e5 + 5;
int n, m;
struct node
{
    int x1, y1, x2, y2;
} a[N];
int first[N], second[N];
int p[N], tot;
struct Tree_array
{
    int c[N];
    inline void update(int pos, int val)
    {
        for (int i = pos; i <= tot; i += lowbit(i))
            ckmin(c[i], val);
    }
    inline int query(int pos)
    {
        int res = 0;
        for (int i = pos; i; i -= lowbit(i))
            ckmin(res, c[i]);
        return res;
    }
} tree;
int dp[N];
signed main()
{
    read(n, m);
    p[++tot] = 0;
    for (int i = 1; i <= m; ++i)
    {
        first[i] = second[i] = i;
        read(a[i].x1, a[i].y1, a[i].x2, a[i].y2);
        p[++tot] = a[i].y2;
    }
    sort(p + 1, p + 1 + tot);
    tot = (int)(unique(p + 1, p + 1 + tot) - p - 1);
    sort(first + 1, first + 1 + m, [](const int &x, const int &y)
         { return a[x].x1 == a[y].x1 ? a[x].y1 < a[y].y1 : a[x].x1 < a[y].x1; });
    sort(second + 1, second + 1 + m, [](const int &x, const int &y)
         { return a[x].x2 == a[y].x2 ? a[x].y2 < a[y].y2 : a[x].x2 < a[y].x2; });
    int ans = 0x7fffffff;
    for (int i = 1, j = 0; i <= m; ++i)
    {
        while (j <= m && (a[first[i]].x1 > a[second[j]].x2 || (a[first[i]].x1 == a[second[j]].x2 && a[first[i]].y1 > a[second[j]].y2)))
        {
            tree.update((int)(lower_bound(p + 1, p + 1 + tot, a[second[j]].y2) - p), dp[second[j]]);
            ++j;
        }
        dp[first[i]] = tree.query((int)(upper_bound(p + 1, p + 1 + tot, a[first[i]].y1) - p - 1)) + a[first[i]].x1 + a[first[i]].y1 - a[first[i]].x2 - a[first[i]].y2;
        ckmin(ans, dp[first[i]]);
    }
    printf("%d\n", ans + 2 * n);
    return 0;
}