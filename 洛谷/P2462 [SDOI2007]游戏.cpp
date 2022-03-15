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
const int N = 1e4 + 5;
struct node
{
    int ch[26], len;
    char str[105];
    inline bool operator<(const node &rhs) const
    {
        for (int i = 0; i < 26; ++i)
        {
            if (ch[i] < rhs.ch[i])
                return true;
            if (ch[i] > rhs.ch[i])
                return false;
        }
        return false;
    }
    inline void solve()
    {
        memset(ch, 0, sizeof(ch));
        for (len = 0; str[len]; ++len)
            ++ch[str[len] - 'a'];
    }
} a[N];
map<node, int> mp;
int cnt = 0;
int dp[N];
int pre[N];
inline void dfs(int u)
{
    if (!u)
        return;
    dfs(pre[u]);
    printf("%s\n", a[u].str);
}
signed main()
{
    while (scanf("%s", a[++cnt].str) != EOF)
        a[cnt].solve();
    sort(a + 1, a + cnt, [](const node &lhs, const node &rhs)
         { return lhs.len < rhs.len; });
    for (int i = 1; i < cnt; ++i)
        mp[a[i]] = i;
    int ans = 0, anspre = 0;
    for (int i = 1; i < cnt; ++i)
    {
        node tmp = a[i];
        if (ans < dp[i] + 1)
        {
            ans = dp[i] + 1;
            anspre = i;
        }
        for (int j = 0; j < 26; ++j)
        {
            ++tmp.ch[j];
            int x = mp[tmp];
            if (x)
            {
                if (dp[x] < dp[i] + 1)
                {
                    dp[x] = dp[i] + 1;
                    pre[x] = i;
                }
            }
            --tmp.ch[j];
        }
    }
    printf("%d\n", ans);
    dfs(anspre);
    return 0;
}