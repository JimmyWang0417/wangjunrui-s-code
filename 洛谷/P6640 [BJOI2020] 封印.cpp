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
const int N = 4e5 + 5;
int Log[N];
int n;
struct Point
{
    int ch[26];
    int fa, len;
} point[N];
int tot = 1, las = 1;
inline void insert(int c)
{
    int p = las, np = las = ++tot;
    point[np].len = point[p].len + 1;
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
            point[q].fa = point[np].fa = nq;
            for (; p && point[p].ch[c] == q; p = point[p].fa)
                point[p].ch[c] = nq;
        }
    }
}
char S[N], T[N];
int best[N][20];
inline int query(int l, int r)
{
    int k = Log[r - l + 1];
    return max(best[l][k], best[r - (1 << k) + 1][k]);
}
signed main()
{
    scanf("%s%s", S + 1, T + 1);
    n = (int)strlen(S + 1);
    for (int i = 1; T[i]; ++i)
        insert(T[i] - 'a');
    Log[0] = -1;
    for (int i = 1, u = 1, now = 0; i <= n; ++i)
    {
        Log[i] = Log[i >> 1] + 1;
        int c = S[i] - 'a';
        if (u == 0)
            u = 1;
        while (u != 1 && !point[u].ch[c])
        {
            u = point[u].fa;
            now = point[u].len;
        }
        ++now;
        u = point[u].ch[c];
        best[i][0] = now;
        // printf("%d %d\n", u, now);
        // putchar('\n');
    }
    for (int j = 1; j <= Log[n]; ++j)
        for (int i = 1; i + (1 << j) - 1 <= n; ++i)
            best[i][j] = max(best[i][j - 1], best[i + (1 << (j - 1))][j - 1]);
    int t;
    read(t);
    while (t--)
    {
        int x, y;
        read(x, y);
        int l = 1, r = y - x + 1, ans = 0;
        while (l <= r)
        {
            int mid = (l + r) >> 1;
            if (query(x + mid - 1, y) >= mid)
            {
                ans = mid;
                l = mid + 1;
            }
            else
                r = mid - 1;
        }
        printf("%d\n", ans);
    }
    return 0;
}