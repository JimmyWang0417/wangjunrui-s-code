/**
 *    unicode: UTF-8
 *    name:    P2622 关灯问题II
 *    author:  wangjunrui
 *    created: 2022.08.14 周日 08:44:12 (Asia/Shanghai)
 **/
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
constexpr int N = (1 << 10) + 5;
int n, m;
int dis[N];
bool vis[N];
int qwq[N], QwQ[N];
signed main()
{
    read(n, m);
    for (int i = 0; i < m; ++i)
    {
        for (int j = 0; j < n; ++j)
        {
            int x;
            read(x);
            if (x == -1)
                qwq[i] |= 1 << j;
            else if (x == 1)
                QwQ[i] |= 1 << j;
        }
    }
    queue<int> q;
    q.push((1 << n) - 1);
    vis[(1 << n) - 1] = true;
    while (!q.empty())
    {
        int u = q.front();
        q.pop();
        for (int i = 0; i < m; ++i)
        {
            int v = u ^ ((~u) & qwq[i]) ^ (u & QwQ[i]);
            if (!vis[v])
            {
                vis[v] = true;
                dis[v] = dis[u] + 1;
                q.push(v);
            }
        }
    }
    if (vis[0])
        printf("%d\n", dis[0]);
    else
        printf("-1\n");
    return 0;
}