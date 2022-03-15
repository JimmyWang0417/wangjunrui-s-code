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
const int N = 6e5 + 5;
template <typename T>
inline void ckmax(T &x, T y)
{
    if (x < y)
        x = y;
}
struct node
{
    int min, nxtmin, max, nxtmax, size;
    node(int _min = 0x3f3f3f3f, int _nxtmin = 0x3f3f3f3f, int _max = -0x3f3f3f3f, int _nxtmax = -0x3f3f3f3f, int _size = 0) : min(_min), nxtmin(_nxtmin), max(_max), nxtmax(_nxtmax), size(_size) {}

} dp[N];
inline node operator+(node lhs, node rhs)
{
    node ans;

    if (lhs.min > rhs.min)
        swap(lhs, rhs);
    ans.min = lhs.min;
    ans.nxtmin = min(lhs.nxtmin, rhs.min);

    if (lhs.max < rhs.max)
        swap(lhs, rhs);
    ans.max = lhs.max;
    ans.nxtmax = max(lhs.nxtmax, rhs.max);

    ans.size = lhs.size + rhs.size;
    return ans;
}
struct Point
{
    int ch[26];
    int fa, len;
} point[N];
int tot = 1, las = 1;
inline void insert(int c, int v)
{
    int p = las, np = las = ++tot;
    point[np].len = point[p].len + 1;
    dp[np].min = dp[np].max = v, dp[np].size = 1;
    for (; p && !point[p].ch[c]; p = point[p].fa)
        point[p].ch[c] = np;
    if (!p)
        point[np].fa = 1;
    else
    {
        int q = point[p].ch[c];
        if (point[q].len == point[p].len + 1)
            point[np].fa = q;
        else
        {
            int nq = ++tot;
            point[nq] = point[q];
            point[nq].len = point[p].len + 1;
            point[np].fa = point[q].fa = nq;
            for (; p && point[p].ch[c] == q; p = point[p].fa)
                point[p].ch[c] = nq;
        }
    }
}
int n, a[N];
char str[N];
int nmsl[N], q[N];
ll answer1[N], answer2[N];
inline void work()
{
    for (int i = 1; i <= tot; ++i)
        ++nmsl[point[i].len];
    for (int i = 1; i <= n; ++i)
        nmsl[i] += nmsl[i - 1];
    for (int i = tot; i >= 1; --i)
        q[nmsl[point[i].len]--] = i;
    memset(answer2, ~0x3f, sizeof(answer2));
    for (int i = tot; i >= 1; --i)
    {
        int u = q[i];
        dp[point[u].fa] = dp[point[u].fa] + dp[u];
        ll res = (ll)dp[u].size * (dp[u].size - 1) / 2;
        answer1[point[u].len] += res;
        if (point[u].len)
            answer1[point[point[u].fa].len] -= res;
        if (dp[u].size >= 2)
            ckmax(answer2[point[u].len], max((ll)dp[u].min * dp[u].nxtmin, (ll)dp[u].max * dp[u].nxtmax));
    }
    // for (int i = 1; i <= tot; ++i)
    // printf("%d %d %d %d\n", point[i].len, dp[i].size, dp[i].max, dp[i].nxtmax);
    for (int i = n - 2; i >= 0; --i)
    {
        answer1[i] += answer1[i + 1];
        ckmax(answer2[i], answer2[i + 1]);
    }
    for (int i = 0; i < n; ++i)
        printf("%lld %lld\n", answer1[i], answer2[i] > -1e18 ? answer2[i] : 0);
}
signed main()
{
    read(n);
    scanf("%s", str);
    for (int i = 0; i < n; ++i)
        read(a[i]);
    reverse(str, str + n);
    reverse(a, a + n);
    for (int i = 0; i < n; ++i)
        insert(str[i] - 'a', a[i]);
    work();
    return 0;
}