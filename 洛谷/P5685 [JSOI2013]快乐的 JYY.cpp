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
const int N = 5e4 + 5;
class PAM
{
public:
    char str[N];
    struct Point
    {
        int ch[26];
        int fa, len;
    } point[N];
    int tot = 1, las = 0;
    int dp[N];
    inline int getfa(int x, int where)
    {
        while (str[where] != str[where - point[x].len - 1])
            x = point[x].fa;
        return x;
    }
    inline void insert(int c, int where)
    {
        int cur = getfa(las, where);
        int now = point[cur].ch[c];
        if (!now)
        {
            now = ++tot;
            point[now].fa = point[getfa(point[cur].fa, where)].ch[c];
            point[now].len = point[cur].len + 2;
            point[cur].ch[c] = now;
        }
        ++dp[las = now];
    }
    inline void init()
    {
        point[0].fa = 1;
        point[1].len = -1;
        for (int i = 1; str[i]; ++i)
            insert(str[i] - 'A', i);
        for (int i = tot; i >= 2; --i)
            dp[point[i].fa] += dp[i];
    }
} A, B;
inline void work()
{
    ll ans = 0;
    queue<pair<int, int>, list<pair<int, int>>> q;
    q.push(make_pair(0, 0));
    q.push(make_pair(1, 1));
    while (!q.empty())
    {
        int u = q.front().first, v = q.front().second;
        q.pop();
        for (int c = 0; c < 26; ++c)
        {
            int x = A.point[u].ch[c], y = B.point[v].ch[c];
            if (x && y)
            {
                ans += (ll)A.dp[x] * B.dp[y];
                q.push(make_pair(x, y));
            }
        }
    }
    printf("%lld\n", ans);
}
signed main()
{
    scanf("%s%s", A.str + 1, B.str + 1);
    A.init(), B.init();
    work();
    return 0;
}