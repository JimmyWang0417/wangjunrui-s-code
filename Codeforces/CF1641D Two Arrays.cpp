/**
 *    unicode: UTF-8
 *    name:    CF1641D Two Arrays
 *    author:  wangjunrui
 *    created: 2022.07.09 周六 23:18:42 (Asia/Shanghai)
 **/
#include <algorithm>
#include <cstdio>
#include <map>
#include <random>
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
constexpr int N = 1e5 + 5, M = (1 << 5) + 5;
constexpr int base = 1e9 + 7;
int n, m;
struct node
{
    int a[5], b;
    inline bool operator<(const node &rhs) const
    {
        return b < rhs.b;
    }
} a[N];
map<int, int> ch[N * 32];
int size[N * 32];
int tot = 1;
inline int calc(int *qwq, int pos = 0, int u = 1)
{
    if (pos == m)
        return size[u];
    int res = calc(qwq, pos + 1, u);
    if (size[ch[u][qwq[pos]]])
        res -= calc(qwq, pos + 1, ch[u][qwq[pos]]);
    return res;
}
inline void insert(int *qwq, int pos = 0, int u = 1)
{
    if (pos == m)
    {
        ++size[u];
        return;
    }
    insert(qwq, pos + 1, u);
    if (!ch[u][qwq[pos]])
        ch[u][qwq[pos]] = ++tot;
    insert(qwq, pos + 1, ch[u][qwq[pos]]);
}
inline void erase(int *qwq, int pos = 0, int u = 1)
{
    if (pos == m)
    {
        --size[u];
        return;
    }
    erase(qwq, pos + 1, u);
    erase(qwq, pos + 1, ch[u][qwq[pos]]);
}
signed main()
{
    read(n, m);
    for (int i = 1; i <= n; ++i)
    {
        for (int j = 0; j < m; ++j)
            read(a[i].a[j]);
        read(a[i].b);
        sort(a[i].a, a[i].a + m);
    }
    sort(a + 1, a + 1 + n);
    int l, r = 1;
    while (!calc(a[r].a) && r <= n)
        insert(a[r++].a);
    if (r > n)
    {
        printf("-1\n");
        return 0;
    }
    l = r - 1;
    while (calc(a[r].a))
        erase(a[l--].a);
    int res = a[l + 1].b + a[r].b;
    for (int i = r + 1; l && i <= n; ++i)
    {
        if (calc(a[i].a))
        {
            while (calc(a[i].a))
                erase(a[l--].a);
            ckmin(res, a[l + 1].b + a[i].b);
        }
    }
    printf("%d\n", res);
    return 0;
}