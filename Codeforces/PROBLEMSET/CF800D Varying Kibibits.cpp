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
constexpr int N = 1e6 + 5;
constexpr int mod = 1e9 + 7;
inline void add(ll &A, ll &B, ll &C, ll a, ll b, ll c)
{
    A = (A * (c + 1) + a * (C + 1) + 2 * B * b) % mod;
    B = (B * (c + 1) + b * (C + 1)) % mod;
    C = ((C + 1) * (c + 1) - 1) % mod;
}
int n;
ll A[N], B[N], C[N];
int power10[10] = {1, 10, 100, 1000, 10000, 100000, 1000000};
signed main()
{
    read(n);
    for (int i = 0; i < n; ++i)
    {
        int x;
        read(x);
        add(A[x], B[x], C[x], (ll)x * x % mod, x, 1);
    }
    for (int i = 0; i < 6; ++i)
        for (int S = 1e6 - 1; S >= 0; --S)
            if (S / power10[i] % 10 < 9)
            {
                int T = S + power10[i];
                add(A[S], B[S], C[S], A[T], B[T], C[T]);
            }
    for (int i = 0; i < 6; ++i)
        for (int S = 0; S < 1e6; ++S)
            if (S / power10[i] % 10 < 9)
            {
                int T = S + power10[i];
                (A[S] += mod - A[T]) %= mod;
            }
    ll ans = 0;
    for (int i = 0; i < 1e6; ++i)
    {
        ans ^= i * A[i];
    }
    printf("%lld\n", ans);
    return 0;
}