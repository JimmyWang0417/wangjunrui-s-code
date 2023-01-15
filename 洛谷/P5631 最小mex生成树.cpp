/**
 *    unicode: UTF-8
 *    name:    P5631 最小mex生成树
 *    author:  whitepaperdog
 *    created: 2022.07.06 周三 23:31:33 (Asia/Shanghai)
 **/
#include <cstdio>
#include <cstdlib>
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
constexpr int N = 1e6 + 5;
int n, m;
vector<pair<int, int>> g[N];
int size[N], fa[N];
inline int find(int x)
{
    return !fa[x] ? x : find(fa[x]);
}
pair<int, int> st[N];
int top;
inline void cdq(int l, int r)
{
    if (l == r)
    {
        if (size[find(1)] == n)
        {
            printf("%d\n", l);
            exit(0);
        }
        return;
    }
    int mid = (l + r) >> 1;
    int las = top;
    for (int i = mid + 1; i <= r; ++i)
        for (auto j : g[i])
        {
            int x = find(j.first), y = find(j.second);
            if (x == y)
                continue;
            if (size[x] > size[y])
                swap(x, y);
            fa[x] = y;
            size[y] += size[x];
            st[++top] = make_pair(x, y);
        }
    cdq(l, mid);
    while (top > las)
    {
        fa[st[top].first] = 0;
        size[st[top].second] -= size[st[top].first];
        --top;
    }
    for (int i = l; i <= mid; ++i)
        for (auto j : g[i])
        {
            int x = find(j.first), y = find(j.second);
            if (x == y)
                continue;
            if (size[x] > size[y])
                swap(x, y);
            fa[x] = y;
            size[y] += size[x];
            st[++top] = make_pair(x, y);
        }
    cdq(mid + 1, r);
    while (top > las)
    {
        fa[st[top].first] = 0;
        size[st[top].second] -= size[st[top].first];
        --top;
    }
}
signed main()
{
    read(n, m);
    fill(size + 1, size + 1 + n, 1);
    for (int i = 1; i <= m; ++i)
    {
        int u, v, w;
        read(u, v, w);
        g[w].emplace_back(u, v);
    }
    int maxx = 0;
    while (!g[maxx].empty())
        ++maxx;
    for (int i = maxx + 1; i <= 1e5; ++i)
        for (auto j : g[i])
        {
            int x = find(j.first), y = find(j.second);
            if (x == y)
                continue;
            if (size[x] > size[y])
                swap(x, y);
            fa[x] = y;
            size[y] += size[x];
            st[++top] = make_pair(x, y);
        }
    cdq(0, maxx);
    return 0;
}