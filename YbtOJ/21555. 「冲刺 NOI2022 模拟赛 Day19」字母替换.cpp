// Problem: I. Yet Another String Matching Problem
// Contest: Codeforces - Educational Codeforces Round 40 (Rated for Div. 2)
// URL: https://codeforces.com/problemset/problem/954/I
// Memory Limit: 256 MB
// Time Limit: 4000 ms
//
// Powered by CP Editor (https://cpeditor.org)

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
constexpr int mod = 998244353, inv3 = (mod + 1) / 3;
inline ll quickpow(ll a, int b)
{
    ll res = 1;
    while (b)
    {
        if (b & 1)
            (res *= a) %= mod;
        (a *= a) %= mod;
        b >>= 1;
    }
    return res;
}
int limit, len, rk[N];
inline void NTT(ll *A)
{
    for (int i = 0; i < limit; ++i)
        if (i < rk[i])
            swap(A[i], A[rk[i]]);
    for (int mid = 1; mid < limit; mid <<= 1)
    {
        ll gn = quickpow(3, (mod - 1) / (mid << 1));
        for (int j = 0; j < limit; j += (mid << 1))
        {
            ll g = 1;
            for (int i = 0; i < mid; ++i, (g *= gn) %= mod)
            {
                ll x = A[i + j], y = A[i + j + mid] * g % mod;
                A[i + j] = (x + y) % mod;
                A[i + j + mid] = (x - y + mod) % mod;
            }
        }
    }
}
inline void INTT(ll *A)
{
    for (int i = 0; i < limit; ++i)
        if (i < rk[i])
            swap(A[i], A[rk[i]]);
    for (int mid = 1; mid < limit; mid <<= 1)
    {
        ll gn = quickpow(inv3, (mod - 1) / (mid << 1));
        for (int j = 0; j < limit; j += (mid << 1))
        {
            ll g = 1;
            for (int i = 0; i < mid; ++i, (g *= gn) %= mod)
            {
                ll x = A[i + j], y = A[i + j + mid] * g % mod;
                A[i + j] = (x + y) % mod;
                A[i + j + mid] = (x - y + mod) % mod;
            }
        }
    }
    ll inv = quickpow(limit, mod - 2);
    for (int i = 0; i < limit; ++i)
        A[i] = A[i] * inv % mod;
}
char S[N], T[N];
int lenS, lenT;
ll A[6][N], B[6][N], C[N];
vector<pair<char, char>> g[N];
int fa[N];
inline int find(int x)
{
    return fa[x] == x ? x : fa[x] = find(fa[x]);
}
signed main()
{
    freopen("Antetokounmpo.in", "r", stdin);
    freopen("Antetokounmpo.out", "w", stdout);
    scanf("%s%s", S, T);
    lenS = (int)strlen(S), lenT = (int)strlen(T);
    limit = 1;
    while (limit <= lenS + lenT - 2)
    {
        limit <<= 1;
        ++len;
    }
    for (int i = 0; i < limit; ++i)
        rk[i] = (rk[i >> 1] >> 1) | ((i & 1) << (len - 1));
    for (int j = 0; j < 6; ++j)
    {
        for (int i = 0; i < lenS; ++i)
            A[j][i] = (S[i] == 'a' + j);
        for (int i = 0; i < lenT; ++i)
            B[j][lenT - i - 1] = (T[i] == 'a' + j);
        NTT(A[j]), NTT(B[j]);
    }
    for (int a = 0; a < 6; ++a)
        for (int b = 0; b < 6; ++b)
        {
            if (a == b)
                continue;
            for (int i = 0; i < limit; ++i)
                (C[i] = A[a][i] * B[b][i]) %= mod;
            INTT(C);
            for (int i = 0; i <= lenS - lenT; ++i)
                if (C[i + lenT - 1])
                    g[i].emplace_back(a, b);
        }
    for (int i = 0; i <= lenS - lenT; ++i)
    {
        for (int j = 0; j < 6; ++j)
            fa[j] = j;
        int res = 0;
        for (auto u : g[i])
        {
            int x = find(u.first), y = find(u.second);
            if (x == y)
                continue;
            fa[x] = y;
            ++res;
        }
        printf("%d ", res);
    }
    putchar('\n');
    return 0;
}
