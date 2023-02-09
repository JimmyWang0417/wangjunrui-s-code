#include <algorithm>
#include <cstdio>
#include <unordered_map>
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
constexpr int N = 55, M = 1e5 + 5;
constexpr int mod = 1e9 + 7;
template <typename T>
inline void add(T &x, T y)
{
    x += y;
    if (x >= mod)
        x -= mod;
}
int n, m;
struct node
{
    int x, y, w;
} c[N];
int a[N], b[N];
int tota, totb;
int pa[N], pb[N];
int cnt[N];
int mp[N][N];
unordered_map<ll, int> f[N], g[N];
ll fac[M];
signed main()
{
    read(n, m);
    for (int i = 1; i <= m; ++i)
    {
        read(c[i].x, c[i].y, c[i].w);
        pa[++tota] = c[i].x, pb[++totb] = c[i].y;
    }
    sort(pa + 1, pa + 1 + tota);
    sort(pb + 1, pb + 1 + totb);
    tota = (int)(unique(pa + 1, pa + 1 + tota) - pa - 1);
    totb = (int)(unique(pb + 1, pb + 1 + totb) - pb - 1);
    for (int i = 1; i <= m; ++i)
    {
        int x = (int)(lower_bound(pa + 1, pa + 1 + tota, c[i].x) - pa - 1),
            y = (int)(lower_bound(pb + 1, pb + 1 + totb, c[i].y) - pb - 1),
            w = (c[i].w + mod - 1) % mod;
        mp[x][y] = w;
        ++cnt[y];
    }
    f[0][0] = 1;
    for (int i = 0; i < tota; ++i)
    {
        ll all = (1ll << totb) - 1;
        for (int j = 0; j < totb; ++j)
            if (mp[i][j])
            {
                if (!--cnt[j])
                    all ^= 1ll << j;
            }
        for (int j = 0; j <= m; ++j)
            for (auto S : f[j])
            {
                add(g[j][S.first & all], S.second);
                for (int k = 0; k < totb; ++k)
                    if (!((S.first >> k) & 1) && mp[i][k])
                        add(g[j + 1][(S.first | (1ll << k)) & all], (int)((ll)S.second * mp[i][k] % mod));
            }
        for (int j = 0; j <= m; ++j)
        {
            swap(f[j], g[j]);
            g[j].clear();
        }
    }
    fac[0] = 1;
    for (int i = 1; i <= n; ++i)
        fac[i] = (ll)fac[i - 1] * i % mod;
    ll answer = 0;
    for (int i = 0; i <= m; ++i)
    {
        int now = 0;
        for (auto S : f[i])
            add(now, S.second);
        (answer += fac[n - i] * now) %= mod;
    }
    printf("%lld\n", answer);
    return 0;
}