#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <vector>
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
constexpr int N = 2505;
int n, m, S;
int fa[N], father[N];
int deg[N];
struct node
{
    int u, v, w;
    inline bool operator<(const node &rhs) const
    {
        return w < rhs.w;
    }
} a[N];
inline int find(int x)
{
    return fa[x] == x ? x : fa[x] = find(fa[x]);
}
signed main()
{
    read(n, m, S);
    for (int i = 1; i <= n; ++i)
        fa[i] = i;
    int sum = 0;
    for (int i = 1; i <= m; ++i)
    {
        int u, v;
        read(u, v);
        fa[find(u)] = find(v);
        sum += abs(u - v);
        ++deg[u], ++deg[v];
    }
    memcpy(father, fa, sizeof(fa));
    for (int T = 1; T <= n; ++T)
    {
        memcpy(fa, father, sizeof(fa));
        ++deg[S], ++deg[T];
        fa[find(S)] = find(T);
        int res = sum;
        for (int j = 1, las = 0; j <= n; ++j)
            if (deg[j] & 1)
            {
                if (las)
                {
                    res += j - las;
                    for (int k = las; k < j; ++k)
                        fa[find(k)] = find(j);
                    las = 0;
                }
                else
                    las = j;
            }
        vector<node> g;
        for (int j = 1, las = 0; j <= n; ++j)
            if (deg[j])
            {
                if (las && find(j) != find(las))
                    g.push_back((node){j, las, j - las});
                las = j;
            }
        sort(g.begin(), g.end());
        for (int j = 0; j < (int)g.size(); ++j)
            if (find(g[j].u) != find(g[j].v))
            {
                fa[find(g[j].u)] = find(g[j].v);
                res += 2 * g[j].w;
            }
        --deg[S], --deg[T];
        printf("%d ", res);
    }
    return 0;
}