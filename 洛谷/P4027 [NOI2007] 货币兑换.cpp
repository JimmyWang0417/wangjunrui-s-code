#include <bits/stdc++.h>
#define eps 1e-18
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
struct node
{
    double a, b, r, k;
} a[N];
int n, S;
double maxx;
double dp[N];
double X[N], Y[N];
int id[N];
int q[N];
inline void cdq(int l, int r)
{
    if (l == r)
    {
        ckmax(dp[l], maxx);
        ckmax(maxx, dp[l]);
        X[l] = (dp[l] * a[l].r) / (a[l].a * a[l].r + a[l].b);
        Y[l] = dp[l] / (a[l].a * a[l].r + a[l].b);
        return;
    }
    int mid = (l + r) >> 1;
    cdq(l, mid);
    for (int i = l; i <= r; ++i)
        id[i] = i;
    sort(id + l, id + mid + 1, [](const int &lhs, const int &rhs)
         { return abs(X[lhs] - X[rhs]) < eps ? Y[lhs] > Y[rhs] : X[lhs] < X[rhs]; });
    sort(id + mid + 1, id + r + 1, [](const int &lhs, const int &rhs)
         { return a[lhs].k > a[rhs].k; });
    int head = 1, tail = 1;
    q[1] = id[l];
    for (int i = l + 1; i <= mid; ++i)
    {
        if (abs(X[id[i]] - X[id[i - 1]]) < eps)
            continue;
        while (tail > 1 && (Y[id[i]] - Y[q[tail]]) * (X[q[tail]] - X[q[tail - 1]]) >= (X[id[i]] - X[q[tail]]) * (Y[q[tail]] - Y[q[tail - 1]]))
            --tail;
        q[++tail] = id[i];
    }
    for (int i = mid + 1; i <= r; ++i)
    {
        while (head < tail && (Y[q[head + 1]] - Y[q[head]]) >= a[id[i]].k * (X[q[head + 1]] - X[q[head]]))
            ++head;
        ckmax(dp[id[i]], a[id[i]].a * X[q[head]] + a[id[i]].b * Y[q[head]]);
    }
    cdq(mid + 1, r);
}
signed main()
{
    read(n, S);
    for (int i = 1; i <= n; ++i)
    {
        scanf("%lf%lf%lf", &a[i].a, &a[i].b, &a[i].r);
        a[i].k = -a[i].a / a[i].b;
    }
    maxx = S;
    cdq(1, n);
    printf("%.3lf\n", maxx);
    return 0;
}