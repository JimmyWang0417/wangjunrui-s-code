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
constexpr int N = (1 << 20) + 5;
constexpr int mod = 1e9 + 7;
template <typename T>
inline void add(T &x, T y)
{
    x += y;
    if (x >= mod)
        x -= mod;
}
template <typename T>
inline void dec(T &x, T y)
{
    x -= y;
    if (x < 0)
        x += mod;
}
int n, m;
inline void FWTOR(int *dp)
{
    for (int i = 1; (i << 1) <= m; i <<= 1)
        for (int j = 0; j < m; j += i << 1)
            for (int k = 0; k < i; ++k)
                add(dp[i + j + k], dp[j + k]);
}
inline void UFWTOR(int *dp)
{
    for (int i = 1; (i << 1) <= m; i <<= 1)
        for (int j = 0; j < m; j += i << 1)
            for (int k = 0; k < i; ++k)
                dec(dp[i + j + k], dp[j + k]);
}
inline void FWTAND(int *dp)
{
    for (int i = 1; (i << 1) <= m; i <<= 1)
        for (int j = 0; j < m; j += i << 1)
            for (int k = 0; k < i; ++k)
                add(dp[i + j], dp[i + j + k]);
}
int A[N], B[N], C[N];
signed main()
{
    read(n);
    m = 1 << n;
    for (int i = 0; i < m; ++i)
        read(A[i]);
    for (int i = 0; i < m; ++i)
        read(B[i]);
    for (int i = 0; i < m; ++i)
        read(C[i]);
    FWTOR(A), FWTOR(B), FWTOR(C);
    for (int i = 0; i < m; ++i)
        A[i] = (int)((ll)A[i] * B[i] % mod * C[i] % mod);
    UFWTOR(A);
    FWTAND(A);
    int res = 0;
    for (int i = 0; i < m; ++i)
        add(res, A[i]);
    printf("%d\n", res);
    return 0;
}