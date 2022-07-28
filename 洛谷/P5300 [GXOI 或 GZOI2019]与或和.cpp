/**
 *    unicode: UTF-8
 *    name:    P5300 [GXOI/GZOI2019]与或和
 *    author:  wangjunrui
 *    created: 2022.07.24 周日 17:18:10 (Asia/Shanghai)
 **/
#include <cstdio>
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
constexpr int N = 1005;
constexpr int mod = 1e9 + 7;
int n;
int a[N][N], b[N][N];
pair<int, int> st[N];
int top;
signed main()
{
    read(n);
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= n; ++j)
            read(a[i][j]);
    ll ans1 = 0, ans2 = 0;
    for (int kase = 0; kase <= 30; ++kase)
    {
        ll res = 0, now = 0;
        for (int i = 1; i <= n; ++i)
        {
            now = top = 0;
            for (int j = 1; j <= n; ++j)
            {
                b[i][j] = (a[i][j] >> kase) & 1 ? b[i - 1][j] + 1 : 0;
                if (b[i][j])
                {
                    int cnt = 1;
                    while (top && b[i][st[top].first] > b[i][j])
                    {
                        (now -= b[i][st[top].first] * st[top].second) %= mod;
                        (cnt += st[top].second) %= mod;
                        --top;
                    }
                    (now += (ll)b[i][j] * cnt) %= mod;
                    (res += now) %= mod;
                    st[++top] = make_pair(j, cnt);
                }
                else
                    now = top = 0;
            }
        }
        (ans1 += res * (1 << kase)) %= mod;
    }
    for (int kase = 0; kase <= 30; ++kase)
    {
        ll res = 0, now = 0;
        for (int i = 1; i <= n; ++i)
        {
            now = top = 0;
            for (int j = 1; j <= n; ++j)
            {
                b[i][j] = (a[i][j] >> kase) & 1 ? 0 : b[i - 1][j] + 1;
                if (b[i][j])
                {
                    int cnt = 1;
                    while (top && b[i][st[top].first] > b[i][j])
                    {
                        (now -= b[i][st[top].first] * st[top].second) %= mod;
                        (cnt += st[top].second) %= mod;
                        --top;
                    }
                    (now += (ll)b[i][j] * cnt) %= mod;
                    (res += now) %= mod;
                    st[++top] = make_pair(j, cnt);
                }
                else
                    now = top = 0;
            }
        }
        (ans2 += ((ll)(n * (n + 1) / 2) * (n * (n + 1) / 2) % mod - res) * (1 << kase)) %= mod;
    }
    printf("%lld %lld\n", (ans1 + mod) % mod, (ans2 + mod) % mod);
    return 0;
}