/**
 *    unicode: UTF-8
 *    name:    CF442D Adam and Tree
 *    author:  wangjunrui
 *    created: 2022.07.08 周五 21:59:58 (Asia/Shanghai)
 **/
#include <algorithm>
#include <cstdio>
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
int n;
int fa[N];
int first[N], second[N];
signed main()
{
    read(n);
    for (int u = 2; u <= n + 1; ++u)
    {
        read(fa[u]);
        int v = u;
        while (fa[v])
        {
            int las = max(first[fa[v]], second[fa[v]] + 1), now = max(first[v], second[v] + 1);
            if (first[fa[v]] < now)
            {
                second[fa[v]] = first[fa[v]];
                first[fa[v]] = now;
            }
            else if (second[fa[v]] < now)
                second[fa[v]] = now;
            if (las == max(first[fa[v]], second[fa[v]] + 1))
                break;
            v = fa[v];
        }
        printf("%d ", first[1]);
    }
    putchar('\n');
    return 0;
}