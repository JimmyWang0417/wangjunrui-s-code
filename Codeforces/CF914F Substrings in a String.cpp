/**
 *    unicode: UTF-8
 *    name:    CF914F Substrings in a String
 *    author:  wangjunrui
 *    created: 2022.07.01 周五 21:39:25 (Asia/Shanghai)
 **/
#include <algorithm>
#include <cstdio>
#include <cstring>
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
constexpr int N = 1e5 + 5, BLOCK = 320;
int n, m;
int block, num, belong[N];
char str[N], qwq[N];
struct SAM
{
    bool tag;
    int L, R;
    struct Point
    {
        int ch[26], fa;
        int len;
    } point[BLOCK * 2];
    int las, tot;
    inline void init()
    {
        las = tot = 1;
    }
    int dp[BLOCK * 2];
    inline void insert(int c)
    {
        int p = las, np = las = ++tot;
        point[np].len = point[p].len + 1;
        dp[np] = 1;
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
    int ws[BLOCK];
    int que[BLOCK * 2];
    inline void solve()
    {
        for (int i = L; i <= R; ++i)
            insert(str[i] - 'a');
        for (int i = 1; i <= tot; ++i)
            ++ws[point[i].len];
        for (int i = 1; i <= R - L + 1; ++i)
            ws[i] += ws[i - 1];
        for (int i = tot; i >= 1; --i)
            que[ws[point[i].len]--] = i;
        for (int i = tot; i >= 1; --i)
        {
            int u = que[i];
            dp[point[u].fa] += dp[u];
        }
        fill(ws, ws + 1 + (R - L + 1), 0);
    }
    inline void build()
    {
        init();
        solve();
    }
    inline void rebuild()
    {
        fill(dp + 1, dp + 1 + tot, 0);
        fill(point + 1, point + 1 + tot, point[0]);
        build();
    }
    inline int query()
    {
        if (tag)
            rebuild();
        int u = 1;
        for (int i = 1; i <= m; ++i)
        {
            u = point[u].ch[qwq[i] - 'a'];
            if (!u)
                return 0;
        }
        return dp[u];
    }
} tree[N / BLOCK + 10];
int fail[N];
inline void init()
{
    fail[1] = 0;
    for (int i = 2, j = 0; i <= m; ++i)
    {
        while (j && qwq[i] != qwq[j + 1])
            j = fail[j];
        if (qwq[i] == qwq[j + 1])
            ++j;
        fail[i] = j;
    }
}
inline int solve(int l, int r)
{
    int res = 0;
    for (int i = l, j = 0; i <= r; ++i)
    {
        while (j && str[i] != qwq[j + 1])
            j = fail[j];
        if (str[i] == qwq[j + 1])
            ++j;
        if (j == m)
            ++res;
    }
    return res;
}
signed main()
{
    scanf("%s", str + 1);
    n = (int)strlen(str + 1);
    block = (int)__builtin_sqrt(n);
    num = (n - 1) / block + 1;
    for (int i = 1; i <= num; ++i)
    {
        tree[i].L = tree[i - 1].R + 1;
        tree[i].R = min(tree[i - 1].R + block, n);
        for (int j = tree[i].L; j <= tree[i].R; ++j)
            belong[j] = i;
        tree[i].tag = true;
    }
    int q;
    read(q);
    while (q--)
    {
        int opt;
        read(opt);
        if (opt == 1)
        {
            int pos;
            read(pos);
            scanf("%s", qwq);
            str[pos] = qwq[0];
            tree[belong[pos]].tag = true;
        }
        else
        {
            int l, r;
            read(l, r);
            scanf("%s", qwq + 1);
            m = (int)strlen(qwq + 1);
            init();
            if (m <= block)
            {
                if (belong[l] + 1 >= belong[r])
                    printf("%d\n", solve(l, r));
                else
                {
                    int res = 0;
                    for (int i = belong[l] + 1; i < belong[r]; ++i)
                        res += tree[i].query();
                    res += solve(l, tree[belong[l] + 1].L + m - 2);
                    res += solve(tree[belong[r] - 1].R - m + 2, r);
                    if (m > 1)
                        for (int i = belong[l] + 2; i < belong[r]; ++i)
                            res += solve(tree[i - 1].R - m + 2, tree[i].L + m - 2);
                    printf("%d\n", res);
                }
            }
            else
                printf("%d\n", solve(l, r));
        }
    }
    return 0;
}