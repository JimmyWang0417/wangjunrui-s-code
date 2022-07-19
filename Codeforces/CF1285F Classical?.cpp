/**
 *    unicode: UTF-8
 *    name:    CF1285F Classical?
 *    author:  wangjunrui
 *    created: 2022.07.13 周三 00:12:47 (Asia/Shanghai)
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
constexpr int N = 1e5 + 5;
int n, m;
int a[N];
bool b[N];
int prime[N], tot;
int mul[N];
bool vis[N];
vector<int> g[N];
inline void getprimes(int limit)
{
    mul[1] = 1;
    for (int i = 2; i <= limit; ++i)
    {
        if (!vis[i])
        {
            mul[i] = -1;
            prime[++tot] = i;
        }
        for (int j = 1; j <= tot; ++j)
        {
            if (i * prime[j] > limit)
                break;
            vis[i * prime[j]] = true;
            if (i % prime[j] == 0)
                break;
            mul[i * prime[j]] = -mul[i];
        }
    }
}
int st[N], top;
int cnt[N];
signed main()
{
    read(n);
    for (int i = 1; i <= n; ++i)
    {
        read(a[i]);
        ckmax(m, a[i]);
        b[a[i]] = true;
    }
    getprimes(m);
    ll ans = m;
    for (int i = 1; i <= m; ++i)
    {
        if (mul[i])
            for (int j = i; j <= m; j += i)
            {
                g[j].push_back(i);
                b[i] = (b[i] || b[j]);
            }
        else
            for (int j = i; j <= m; j += i)
                b[i] = (b[i] || b[j]);
    }
    for (int i = m; i >= 1; --i)
    {
        if (!b[i])
            continue;
        int res = 0;
        for (int j : g[i])
            res += mul[j] * cnt[j];
        while (res)
        {
            int lst = res;
            for (int j : g[st[top]])
            {
                --cnt[j];
                if (i % j == 0)
                    res -= mul[j];
            }
            if (res < lst)
                ckmax(ans, (ll)i * st[top]);
            --top;
        }
        for (int j : g[i])
            ++cnt[j];
        st[++top] = i;
    }
    printf("%lld\n", ans);
    return 0;
}