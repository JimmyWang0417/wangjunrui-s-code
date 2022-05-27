// Problem: F. Royal Questions
// Contest: Codeforces - Codeforces Round #441 (Div. 1, by Moscow Team Olympiad)
// URL: https://codeforces.com/contest/875/problem/F
// Memory Limit: 512 MB
// Time Limit: 1500 ms
//
// Powered by CP Editor (https://cpeditor.org)

#include <bits/extc++.h>
#include <bits/stdc++.h>
#define ll long long
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
constexpr int N = 2e5 + 5;
int n, m;
struct node
{
    int u, v, w;
    inline bool operator<(const node &rhs) const { return w > rhs.w; }
} a[N];
bool flag[N];
int fa[N];
inline int find(int x)
{
    return fa[x] ? fa[x] = find(fa[x]) : x;
}
signed main()
{
    read(n, m);
    for (int i = 1; i <= m; ++i)
        read(a[i].u, a[i].v, a[i].w);
    sort(a + 1, a + 1 + m);
    int answer = 0;
    for (int i = 1; i <= m; ++i)
    {
        int u = find(a[i].u), v = find(a[i].v);
        if (u == v)
        {
            if (!flag[u])
            {
                answer += a[i].w;
                flag[u] = true;
            }
        }
        else
        {
            if (!(flag[u] && flag[v]))
            {
                answer += a[i].w;
                fa[v] = u;
                flag[u] = flag[u] | flag[v];
            }
        }
    }
    printf("%d\n", answer);
    return 0;
}