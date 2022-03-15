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
const int N = 15, M = (1 << 9) + 5;
const int dx[4] = {1, -1, 0, 0}, dy[4] = {0, 0, 1, -1};
inline void ckmax(int &x, int y)
{
    if (x < y)
        x = y;
}
int n, m, k;
int a[N];
pair<int, int> b[N];
char str[N][N];
int g[M];
int dis[N][N][M];
bool vis[N][N][M];
struct node
{
    int x, y, S;
    node(int _x = 0, int _y = 0, int _S = 0) : x(_x), y(_y), S(_S) {}
    inline bool operator<(const node &rhs) const
    {
        return x == rhs.x ? (y == rhs.y ? S < rhs.S : y < rhs.y) : x < rhs.x;
    }
    inline bool operator>(const node &rhs) const
    {
        return x == rhs.x ? (y == rhs.y ? S > rhs.S : y > rhs.y) : x > rhs.x;
    }
};
inline int solve(int sx, int sy)
{
    queue<node> q;
    memset(vis, 0, sizeof(vis));
    q.push(node(sx, sy, 0));
    dis[sx][sy][0] = 0;
    int res = 0;
    while (!q.empty())
    {
        node u = q.front();
        q.pop();
        if (u.x == sx && u.y == sy)
            ckmax(res, g[u.S] - dis[u.x][u.y][u.S]);
        for (int d = 0; d < 4; ++d)
        {
            int x = u.x + dx[d], y = u.y + dy[d], S = u.S;
            if (1 <= x && x <= n && 1 <= y && y <= m && str[x][y] == '0')
            {
                for (int j = 0; j < k; ++j)
                    if (((u.x < b[j].first && x == b[j].first) || (u.x == b[j].first && x < b[j].first)) && y < b[j].second)
                        S ^= (1 << j);
                if (vis[x][y][S])
                    continue;
                dis[x][y][S] = dis[u.x][u.y][u.S] + 1;
                vis[x][y][S] = true;
                q.push(node(x, y, S));
            }
        }
    }
    return res;
}
signed main()
{
    read(n, m, k);
    for (int i = 0; i < k; ++i)
        read(a[i]);
    for (int i = 1; i <= n; ++i)
    {
        scanf("%s", str[i] + 1);
        for (int j = 1; j <= m; ++j)
            if ('1' <= str[i][j] && str[i][j] <= '9')
                b[str[i][j] - '1'] = make_pair(i, j);
    }
    for (int i = 0; i < k; ++i)
    {
        for (int S = 0; S < (1 << i); ++S)
            g[S | (1 << i)] = g[S] + a[i];
    }
    int ans = 0;
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= m; ++j)
            if (str[i][j] == '0')
                ckmax(ans, solve(i, j));
    printf("%d\n", ans);
    return 0;
}