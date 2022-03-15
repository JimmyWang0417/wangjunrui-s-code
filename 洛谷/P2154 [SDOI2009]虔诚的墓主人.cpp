#include <bits/stdc++.h>
#define int ll
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
using namespace std;
const int N = 1e6 + 5;
const int mod = 2189535058ll;
struct Point
{
    int x, y;
    inline bool operator<(const Point &rhs) const
    {
        return x == rhs.x ? y < rhs.y : x < rhs.x;
    }
} point[N];
int h, w, n, k;
int p[N], tot;
int C[N][15];
struct Tree_array
{
    int sum[N];
    inline void update(int pos, int val)
    {
        for (int i = pos; i <= tot; i += lowbit(i))
            (sum[i] += val);
    }
    inline int query(int pos)
    {
        int res = 0;
        for (int i = pos; i; i -= lowbit(i))
            (res += sum[i]);
        return res;
    }
} tree;
int cnt1[N], cnt2[N];
signed main()
{
    read(h, w, n);
    for (int i = 1; i <= n; ++i)
        read(point[i].x, point[i].y);
    read(k);
    for (int i = C[0][0] = 1; i <= n; ++i)
    {
        for (int j = C[i][0] = 1; j <= i && j <= k; ++j)
            C[i][j] = (C[i - 1][j] + C[i - 1][j - 1]) % mod;
    }
    for (int i = 1; i <= n; ++i)
        p[i] = point[i].y;
    sort(p + 1, p + 1 + n);
    tot = (int)(unique(p + 1, p + 1 + n) - p - 1);
    for (int i = 1; i <= n; ++i)
        ++cnt1[point[i].y = (int)(lower_bound(p + 1, p + 1 + tot, point[i].y) - p)];
    sort(point + 1, point + 1 + n);
    ll ans = 0;
    point[n+1].y=tot+1;
    for (int l = 1, r; l <= n; l = r)
    {
        r = l + 1;
        while (point[l].x == point[r].x && r <= n)
            ++r;
        for (int i = l; i < r; ++i)
            (ans += C[i - l + 1][k] * C[r - i - 1][k] % mod * ((tree.query(point[i + 1].y - 1) - tree.query(point[i].y) + mod) % mod) % mod) %= mod;
        for (int i = l; i < r; ++i)
        {
            tree.update(point[i].y, (mod - C[cnt2[point[i].y]][k] * C[cnt1[point[i].y] - cnt2[point[i].y]][k] % mod) % mod);
            ++cnt2[point[i].y];
            tree.update(point[i].y, C[cnt2[point[i].y]][k] * C[cnt1[point[i].y] - cnt2[point[i].y]][k]);
        }
    }
    printf("%lld\n", ans);
    return 0;
}