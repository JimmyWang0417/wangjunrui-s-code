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
int n, h[N];
ll sum[N], g[N], dp[N];
int id[N];
int q[N];
inline void cdq(int l, int r)
{
    if (l == r)
    {
        g[l] = dp[l] - sum[l] + (ll)h[l] * h[l];
        return;
    }
    int mid = (l + r) >> 1;
    cdq(l, mid);
    for (int i = l; i <= r; ++i)
        id[i] = i;
    sort(id + l, id + mid + 1, [](const int &lhs, const int &rhs)
         { return h[lhs] == h[rhs] ? g[lhs] < g[rhs] : h[lhs] < h[rhs]; });
    sort(id + mid + 1, id + r + 1, [](const int &lhs, const int &rhs)
         { return h[lhs] == h[rhs] ? g[lhs] < g[rhs] : h[lhs] < h[rhs]; });
    int tail;
    q[tail = 1] = id[l];
    for (int i = l + 1; i <= mid; ++i)
    {
        if (h[id[i]] == h[id[i - 1]])
            continue;
        while (tail > 1 && (h[q[tail]] - h[q[tail - 1]]) * (g[id[i]] - g[q[tail]]) <= (h[id[i]] - h[q[tail]]) * (g[q[tail]] - g[q[tail - 1]]))
            --tail;
        q[++tail] = id[i];
    }
    int head = 1;
    for (int i = mid + 1; i <= r; ++i)
    {
        while (head < tail && g[q[head + 1]] - g[q[head]] <= 2ll * h[id[i]] * (h[q[head + 1]] - h[q[head]]))
            ++head;
        ckmin(dp[id[i]], dp[q[head]] + (sum[id[i] - 1] - sum[q[head]]) + (ll)(h[id[i]] - h[q[head]]) * (h[id[i]] - h[q[head]]));
    }
    cdq(mid + 1, r);
}
signed main()
{
    read(n);
    for (int i = 1; i <= n; ++i)
        read(h[i]);
    for (int i = 1; i <= n; ++i)
    {
        int x;
        read(x);
        sum[i] = sum[i - 1] + x;
    }
    memset(dp, 0x3f, sizeof(dp));
    dp[1] = 0;
    cdq(1, n);
    printf("%lld\n", dp[n]);
    return 0;
}