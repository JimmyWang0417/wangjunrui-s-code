#include <bits/stdc++.h>
#define ll long long
#define ull unsigned ll
#define lowbit(x) (x & (-x))
using namespace std;
template <typename T>
inline void read(T &x)
{
    x = 0;
    static char s = (char)getchar();
    static bool f = false;
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
const int N = 2e5 + 5;
int n, num, w[N], fa[N], ls[N], rs[N];
ll f[N][20];   // f表示i是亮的，回到i的第j个祖先的最小花费
ll g[N][20];   // g表示i是亮的，回到i的第j个祖先的另一个儿子的最小花费
ll dis[N][20]; // dis表示从i到i的第j个祖先的距离
ll ans = 1e17;
inline int brother(int k, int x) // k的第x个祖先的另一个儿子
{
    return (k >> (x - 1)) ^ 1;
}
inline ll getans()
{
    for (int k = n; k >= 1; k--)
    {
        if (!ls[k]) // k为叶子节点
            for (int i = 1; k >> (i - 1); i++)
                g[k][i] = (dis[k][i] + dis[brother(k, i)][1]) * w[brother(k, i)];
        else if (!rs[k]) // k只有左儿子
            for (int i = 1; k >> (i - 1); i++)
                g[k][i] = dis[ls[k]][1] * w[ls[k]] + g[ls[k]][i + 1];
        else // k有两个儿子
            for (int i = 1; k >> (i - 1); i++)
                g[k][i] = min(dis[ls[k]][1] * w[ls[k]] + g[ls[k]][1] + g[rs[k]][i + 1], dis[rs[k]][1] * w[rs[k]] + g[rs[k]][1] + g[ls[k]][i + 1]);
    }
    for (int k = n; k >= 1; k--)
    {
        if (!ls[k])
            for (int i = 1; k >> (i - 1); i++)
                f[k][i] = dis[k][i] * w[k >> i];
        else if (!rs[k])
            for (int i = 1; k >> (i - 1); i++)
                f[k][i] = f[ls[k]][i + 1] + dis[ls[k]][1] * w[ls[k]];
        else
            for (int i = 1; k >> (i - 1); i++)
                f[k][i] = min(dis[ls[k]][1] * w[ls[k]] + g[ls[k]][1] + f[rs[k]][i + 1], dis[rs[k]][1] * w[rs[k]] + g[rs[k]][1] + f[ls[k]][i + 1]);
    }
    for (int k = 1; k <= n; k++)
    {
        ll sum = f[k][1];
        for (int i = 1, fa = k >> 1; fa; ++i, fa >>= 1)
        {
            int bro = brother(k, i);
            if (bro > n)
                sum += dis[fa][1] * w[fa >> 1];
            else
                sum += dis[bro][1] * w[bro] + f[bro][2];
        }
        ans = min(ans, sum);
    }
    return ans;
}
int main()
{
    read(n);
    for (int i = 1; i <= n; ++i)
        read(w[i]);
    for (int i = 2; i <= n; i++)
        read(dis[i][1]);
    for (int i = 1; i <= (n >> 1) + 1; i++) //完全二叉树
    {
        if ((i << 1) <= n)
            ls[i] = (i << 1);
        else
            break;
        if ((i << 1 | 1) <= n)
            rs[i] = (i << 1 | 1);
    }
    for (int i = 2; i <= 18; i++)
        for (int k = n; k >> i; k--)
            dis[k][i] = dis[k][i - 1] + dis[k >> (i - 1)][1];
    printf("%lld\n", getans());
    return 0;
}