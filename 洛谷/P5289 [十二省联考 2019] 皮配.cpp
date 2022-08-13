/**
 *    unicode: UTF-8
 *    name:    b. 选择信封
 *    author:  wangjunrui
 *    created: 2022.08.03 周三 17:01:55 (Asia/Shanghai)
 **/
#include <cstdio>
#include <cstring>
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
constexpr int N = 1005, M = 2505, K = 305;
constexpr int mod = 998244353;
template <typename T>
inline void add(T &x, T y)
{
    x += y;
    if (x >= mod)
        x -= mod;
}
int n, m, q, limit;
int c0, c1, d0, d1;
int belong[N], a[N], b[N], c[N], d[N];
vector<int> have[N];
int f[M], g[M];
int h[M][K];
int _buf[K], __buf[M][K];
inline void work()
{
    read(n, m);
    read(c0, c1, d0, d1);
    for (int i = 1; i <= n; ++i)
    {
        read(belong[i], b[i]);
        a[belong[i]] += b[i];
        limit += b[i];
    }
    read(q);
    for (int i = 1; i <= q; ++i)
    {
        int pos, val;
        read(pos, val);
        c[belong[pos]] = true;
        have[belong[pos]].push_back(pos);
        d[pos] = 1 << val;
    }
    f[0] = 1;
    for (int kase = 1; kase <= m; ++kase)
        if (!c[kase] && a[kase])
        {
            for (int i = c0 - a[kase]; i >= 0; --i)
                if (f[i])
                    add(f[i + a[kase]], f[i]);
        }
    for (int i = c0; i >= 1; --i)
        add(f[i - 1], f[i]);
    g[0] = 1;
    for (int kase = 1; kase <= n; ++kase)
        if (!d[kase])
        {
            for (int i = d0 - b[kase]; i >= 0; --i)
                if (g[i])
                    add(g[i + b[kase]], g[i]);
        }
    for (int i = d0; i >= 1; --i)
        add(g[i - 1], g[i]);
    h[0][0] = 1;
    int sum = 0;
    for (int i = 1; i <= m; ++i)
    {
        if (!c[i])
            continue;
        memcpy(__buf, h, sizeof(__buf));
        for (int j : have[i])
        {
            for (int k = 0; k <= c0; ++k)
            {
                memcpy(_buf, __buf[k], sizeof(_buf));
                memset(__buf[k], 0, sizeof(__buf[k]));
                for (int l = 0; l <= sum; ++l)
                    if (_buf[l])
                    {
                        if (!(d[j] & 1))
                            add(__buf[k][l + b[j]], _buf[l]);
                        if (!(d[j] >> 1 & 1))
                            add(__buf[k][l], _buf[l]);
                    }
                memcpy(_buf, h[k], sizeof(_buf));
                memset(h[k], 0, sizeof(h[k]));
                for (int l = 0; l <= sum; ++l)
                    if (_buf[l])
                    {
                        if (!(d[j] >> 2 & 1))
                            add(h[k][l + b[j]], _buf[l]);
                        if (!(d[j] >> 3 & 1))
                            add(h[k][l], _buf[l]);
                    }
            }
            sum += b[j];
        }
        for (int k = a[i]; k <= c0; ++k)
            for (int l = 0; l <= sum; ++l)
                add(h[k][l], __buf[k - a[i]][l]);
    }
    ll res = 0;
    for (int i = 0; i <= c0; ++i)
        for (int j = 0; j <= sum && j <= d0; ++j)
            if (h[i][j])
            {
                int l = max(0, limit - c1 - i), r = c0 - i;
                if (l > r)
                    continue;
                int F = f[l] - f[r + 1];
                l = max(0, limit - d1 - j), r = d0 - j;
                if (l > r)
                    continue;
                int G = g[l] - g[r + 1];
                (res += (ll)F * G % mod * h[i][j]) %= mod;
            }
    printf("%lld\n", (res + mod) % mod);
    memset(a, 0, sizeof(a));
    memset(f, 0, sizeof(f));
    memset(g, 0, sizeof(g));
    memset(h, 0, sizeof(h));
    memset(c, 0, sizeof(c));
    memset(d, 0, sizeof(d));
    for (int i = 1; i <= m; ++i)
        have[i].clear();
    limit = 0;
}
signed main()
{
#ifdef PAPERDOG
    freopen("project.in", "r", stdin);
    freopen("project.out", "w", stdout);
#endif
    int T;
    read(T);
    while (T--)
        work();
    return 0;
}