#include <bits/stdc++.h>
#include <bits/extc++.h>
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
constexpr int N = 1e6 + 5;
ull f[N], all;
int prime[N], tot;
bool vis[N];
inline void getprime(int n)
{
    uniform_int_distribution<ull> range(0, ULONG_LONG_MAX);
    mt19937 rnd(1919810 / 114514);
    for (int i = 2; i <= n; ++i)
    {
        if (!vis[i])
        {
            prime[++tot] = i;
            f[i] = range(rnd);
        }
        for (int j = 1; j <= tot; ++j)
        {
            if (i * prime[j] > n)
                break;
            vis[i * prime[j]] = true;
            f[i * prime[j]] = f[i] ^ f[prime[j]];
            if (i % prime[j] == 0)
                break;
        }
    }
    for (int i = 1; i <= n; ++i)
    {
        f[i] ^= f[i - 1];
        all ^= f[i];
    }
}
int n;
signed main()
{
#ifdef ONLINE_JUDGE
    freopen("square.in", "r", stdin);
    freopen("square.out", "w", stdout);
#endif
    read(n);
    getprime(n);
    if (all == 0)
    {
        printf("%d\n", n);
        for (int i = 1; i <= n; ++i)
            printf("%d ", i);
        putchar('\n');
        return 0;
    }
    if (n % 4 == 0)
    {
        printf("%d\n", n - 1);
        for (int i = 1; i <= n; ++i)
            if (i != n / 2)
                printf("%d ", i);
        putchar('\n');
        return 0;
    }
    for (int i = 1; i <= n; ++i)
        if (f[i] == all)
        {
            printf("%d\n", n - 1);
            for (int j = 1; j <= n; ++j)
                if (i != j)
                    printf("%d ", j);
            putchar('\n');
            return 0;
        }
    if (n % 2 == 0)
    {
        printf("%d\n", n - 2);
        for (int i = 1; i <= n; ++i)
            if (i != 2 && i != n / 2)
                printf("%d ", i);
        putchar('\n');
    }
    __gnu_pbds::cc_hash_table<ull, int> mp;
    for (int i = 1; i <= n; ++i)
    {
        if (mp[all ^ f[i]])
        {
            printf("%d\n", n - 2);
            int las = mp[all ^ f[i]];
            for (int j = 1; j <= n; ++j)
                if (j != i && j != las)
                    printf("%d ", j);
            putchar('\n');
            return 0;
        }
        mp[f[i]] = i;
    }
    printf("%d\n", n - 3);
    for (int i = 1; i < n; ++i)
        if (i != 2 && i != n / 2)
            printf("%d ", i);
    putchar('\n');
    return 0;
}
