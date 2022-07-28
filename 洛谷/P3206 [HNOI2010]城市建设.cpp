/**
 *    unicode: UTF-8
 *    name:    P3206 [HNOI2010]城市建设
 *    author:  wangjunrui
 *    created: 2022.07.21 周四 19:07:10 (Asia/Shanghai)
 **/
#include <algorithm>
#include <cstdio>
#include <cstring>
#include <tuple>
#include <vector>
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
constexpr int N = 5e4 + 5;
int n, m, q;
struct union_set
{
    int fa[N], dep[N];
    tuple<int, int, bool> st[N];
    int top;
    inline int find(int x)
    {
        return !fa[x] ? x : find(fa[x]);
    }
    inline void unionn(int x, int y)
    {
        x = find(x), y = find(y);
        if (dep[x] > dep[y])
            swap(x, y);
        fa[x] = y;
        st[++top] = make_tuple(x, y, dep[x] == dep[y]);
        if (dep[x] == dep[y])
            ++dep[y];
    }
    inline void back(int las)
    {
        while (top > las)
        {
            int x = get<0>(st[top]), y = get<1>(st[top]);
            bool flag = get<2>(st[top]);
            fa[x] = 0;
            if (flag)
                --dep[y];
            --top;
        }
    }
} fa, belong;
int a[25][N], qwq[N];
bool exist[N];
tuple<int, int, int> e[N];
pair<int, int> b[N];
ll answer[N];
inline void cdq(int l, int r, int dep, ll res)
{
    if (l < r)
        for (int i = l; i <= r; ++i)
            exist[b[i].first] = true;
    else
        get<2>(e[b[l].first]) = b[l].second;

    int las = belong.top;
    copy(a[dep - 1], a[dep - 1] + 1 + a[dep - 1][0], a[dep]);
    auto compare1 = [](int x, int y)
    {
        x = (exist[x] ? ~0x7fffffff : get<2>(e[x]));
        y = (exist[y] ? ~0x7fffffff : get<2>(e[y]));
        return x < y;
    };
    sort(a[dep] + 1, a[dep] + 1 + a[dep][0], compare1);
    for (int i = 1; i <= a[dep][0]; ++i)
    {
        int x = fa.find(belong.find(get<0>(e[a[dep][i]]))),
            y = fa.find(belong.find(get<1>(e[a[dep][i]]))),
            w = get<2>(e[a[dep][i]]);
        if (x == y)
            continue;
        fa.unionn(x, y);
        if (!exist[a[dep][i]])
        {
            belong.unionn(get<0>(e[a[dep][i]]), get<1>(e[a[dep][i]]));
            res += w;
        }
    }
    fa.back(0);
    auto compare2 = [](int x, int y)
    {
        x = (exist[x] ? 0x7fffffff : get<2>(e[x]));
        y = (exist[y] ? 0x7fffffff : get<2>(e[y]));
        return x < y;
    };
    sort(a[dep] + 1, a[dep] + 1 + a[dep][0], compare2);
    qwq[0] = 0;
    for (int i = 1; i <= a[dep][0]; ++i)
    {
        int x = fa.find(belong.find(get<0>(e[a[dep][i]]))),
            y = fa.find(belong.find(get<1>(e[a[dep][i]])));
        if (x == y)
        {
            if (exist[a[dep][i]])
                qwq[++qwq[0]] = a[dep][i];
            continue;
        }
        fa.unionn(x, y);
        qwq[++qwq[0]] = a[dep][i];
    }
    fa.back(0);
    copy(qwq, qwq + 1 + qwq[0], a[dep]);
    if (l < r)
        for (int i = l; i <= r; ++i)
            exist[b[i].first] = false;
    else
    {
        answer[l] = res;
        belong.back(las);
        return;
    }

    int mid = (l + r) >> 1;
    cdq(l, mid, dep + 1, res);
    cdq(mid + 1, r, dep + 1, res);

    belong.back(las);
}
signed main()
{
    read(n, m, q);
    for (int i = 1; i <= m; ++i)
    {
        int u, v, w;
        read(u, v, w);
        e[i] = make_tuple(u, v, w);
    }
    for (int i = 1; i <= q; ++i)
    {
        int x, y;
        read(x, y);
        b[i] = make_pair(x, y);
    }
    a[0][0] = m;
    for (int i = 1; i <= m; ++i)
        a[0][i] = i;
    cdq(1, q, 1, 0);
    for (int i = 1; i <= q; ++i)
        printf("%lld\n", answer[i]);
    return 0;
}