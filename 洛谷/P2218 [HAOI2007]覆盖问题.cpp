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
using namespace std;
const int N = 1005;
inline void ckmax(int &x, int y)
{
    if (x < y)
        x = y;
}
int n, m, a, b, c, d;
int sum[N][N];
inline int solve(int x, int y)
{
    return sum[x][y] - sum[x - a][y] - sum[x][y - b] + sum[x - a][y - b];
}
inline int calc(int x, int y)
{
    return sum[x][y] - sum[x - c][y] - sum[x][y - d] + sum[x - c][y - d];
}
struct Tree
{
    int q[N], g[N], head, tail;
    inline void clear()
    {
        head = 1, tail = 0;
    }
    inline void update(int pos)
    {
        while (head <= tail && q[head] < pos)
            ++head;
    }
    inline void insert(int pos, int val)
    {
        while (head <= tail && g[tail] > val)
            --tail;
        q[++tail] = pos;
        g[tail] = val;
    }
    inline int query()
    {
        return g[head];
    }
} q[N], all;
signed main()
{
    read(n, m, a, b, c, d);
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= m; ++j)
        {
            int x;
            read(x);
            sum[i][j] = sum[i - 1][j] + sum[i][j - 1] - sum[i - 1][j - 1] + x;
        }
    for (int i = c + 1; i < a; ++i)
    {
        for (int j = d + 1; j <= m; ++j)
            q[j].insert(i, calc(i, j));
    }
    int ans = 0;
    for (int i = a; i <= n; ++i)
    {
        for (int j = d + 1; j < m; ++j)
            q[j].update(i - a + c + 1);
        all.clear();
        for (int j = d + 1; j < b; ++j)
            all.insert(j, q[j].query());
        for (int j = b; j <= m; ++j)
        {
            all.update(j - b + d + 1);
            ckmax(ans, solve(i, j) - all.query());
            all.insert(j, q[j].query());
        }
        for (int j = d + 1; j <= m; ++j)
            q[j].insert(i, calc(i, j));
    }
    printf("%d\n", ans);
    return 0;
}