#include <bits/stdc++.h>
#define int ll
#define ll long long
#define ull unsigned ll
#define lowbit(x) (x & (-x))
using namespace std;
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
const int N = (1 << 17) + 5;
const int mod = 998244353;
const int inv2 = (mod + 1) / 2;
inline void add(int &x, int y)
{
    x += y;
    if (x >= mod)
        x -= mod;
}
inline void del(int &x, int y)
{
    x -= y;
    if (x < 0)
        x += mod;
}
int n, m, a[N], b[N];
int A[N], B[N], C[N];
inline void FWROR(int *X)
{
    for (int k = 1; (k << 1) <= m; k <<= 1)
        for (int i = 0; i < m; i += (k << 1))
            for (int j = 0; j < k; ++j)
                add(X[i + j + k], X[i + j]);
}
inline void UFWROR(int *X)
{
    for (int k = 1; (k << 1) <= m; k <<= 1)
        for (int i = 0; i < m; i += (k << 1))
            for (int j = 0; j < k; ++j)
                del(X[i + j + k], X[i + j]);
}
inline void FWRAND(int *X)
{
    for (int k = 1; (k << 1) <= m; k <<= 1)
        for (int i = 0; i < m; i += (k << 1))
            for (int j = 0; j < k; ++j)
                add(X[i + j], X[i + j + k]);
}
inline void UFWRAND(int *X)
{
    for (int k = 1; (k << 1) <= m; k <<= 1)
        for (int i = 0; i < m; i += (k << 1))
            for (int j = 0; j < k; ++j)
                del(X[i + j], X[i + j + k]);
}
inline void FWRXOR(int *X)
{
    for (int k = 1; (k << 1) <= m; k <<= 1)
        for (int i = 0; i < m; i += (k << 1))
            for (int j = 0; j < k; ++j)
            {
                int t1 = X[i + j], t2 = X[i + j + k];
                X[i + j] = (t1 + t2) % mod;
                X[i + j + k] = (t1 - t2 + mod) % mod;
            }
}
inline void UFWRXOR(int *X)
{
    for (int k = 1; (k << 1) <= m; k <<= 1)
        for (int i = 0; i < m; i += (k << 1))
            for (int j = 0; j < k; ++j)
            {
                int t1 = X[i + j], t2 = X[i + j + k];
                X[i + j] = (ll)(t1 + t2) * inv2 % mod;
                X[i + j + k] = (ll)(t1 - t2 + mod) * inv2 % mod;
            }
}
inline void OR()
{
    for (int i = 0; i < m; ++i)
    {
        A[i] = a[i];
        B[i] = b[i];
    }
    FWROR(A), FWROR(B);
    for (int i = 0; i < m; ++i)
        (A[i] *= B[i]) %= mod;
    UFWROR(A);
    for (int i = 0; i < m; ++i)
        printf("%lld ", A[i]);
    putchar('\n');
}
inline void AND()
{
    for (int i = 0; i < m; ++i)
    {
        A[i] = a[i];
        B[i] = b[i];
    }
    FWRAND(A), FWRAND(B);
    for (int i = 0; i < m; ++i)
        (A[i] *= B[i]) %= mod;
    UFWRAND(A);
    for (int i = 0; i < m; ++i)
        printf("%lld ", A[i]);
    putchar('\n');
}
inline void XOR()
{
    for (int i = 0; i < m; ++i)
    {
        A[i] = a[i];
        B[i] = b[i];
    }
    FWRXOR(A), FWRXOR(B);
    for (int i = 0; i < m; ++i)
        (A[i] *= B[i]) %= mod;
    UFWRXOR(A);
    for (int i = 0; i < m; ++i)
        printf("%lld ", A[i]);
    putchar('\n');
}
signed main()
{
    read(n);
    m = 1 << n;
    for (int i = 0; i < m; ++i)
        read(a[i]);
    for (int i = 0; i < m; ++i)
        read(b[i]);
    OR();
    AND();
    XOR();
    return 0;
}