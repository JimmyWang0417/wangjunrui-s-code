#include <cstdio>
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
constexpr int N = 1e5 + 5;
int n;
struct Edge
{
    int next, to;
} edge[N * 2];
int head[N], num_edge;
inline void add_edge(int from, int to)
{
    edge[++num_edge].next = head[from];
    edge[num_edge].to = to;
    head[from] = num_edge;
}
int answer;
inline int dfs(int u, int _fa, int len)
{
    int res = 0;
    bool flag = false;
    for (int i = head[u]; i; i = edge[i].next)
    {
        int &v = edge[i].to;
        if (v == _fa)
            continue;
        int now = dfs(v, u, len);
        if (res + 1 + now >= len)
        {
            if (!flag)
            {
                ++answer;
                flag = true;
            }
        }
        ckmax(res, now);
    }
    return flag ? 0 : res + 1;
}
inline void solve(int l, int r, int ql, int qr)
{
    if (ql > qr)
        return;
    if (l == r)
    {
        for (int i = ql; i <= qr; ++i)
            printf("%d\n", l);
        return;
    }
    int qmid = (ql + qr) >> 1;
    dfs(1, 0, qmid);
    int res = answer;
    answer = 0;
    solve(res, r, ql, qmid - 1);
    printf("%d\n", res);
    solve(l, res, qmid + 1, qr);
}
signed main()
{
    read(n);
    for (int i = 1; i < n; ++i)
    {
        int u, v;
        read(u, v);
        add_edge(u, v);
        add_edge(v, u);
    }
    printf("%d\n", n);
    solve(0, n, 2, n);
    return 0;
}