// Problem: D. Reachable Strings
// Contest: Codeforces - Codeforces Round #625 (Div. 1, based on Technocup 2020 Final Round)
// URL: https://codeforces.com/problemset/problem/1320/D
// Memory Limit: 256 MB
// Time Limit: 3000 ms
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
constexpr int N = 2e5 + 5;
constexpr int mod1 = 1e9 + 7, mod2 = 1e9 + 9, base = 13331;
int n, m;
char str[N];
int cnt[N];
ll hash1[N][2], hash2[N][2];
ll power1[N], power2[N];
inline ll calc1(int l, int r, int k)
{
    return (hash1[r][k] - hash1[l - 1][k] * power1[cnt[r] - cnt[l - 1]] % mod1 + mod1) % mod1;
}
inline ll calc2(int l, int r, int k)
{
    return (hash2[r][k] - hash2[l - 1][k] * power2[cnt[r] - cnt[l - 1]] % mod2 + mod2) % mod2;
}
signed main()
{
    read(n);
    scanf("%s", str + 1);
    power1[0] = power2[0] = 1;
    for (int i = 1; i <= n; ++i)
    {
        power1[i] = power1[i - 1] * base % mod1;
        power2[i] = power2[i - 1] * base % mod2;
    }
    for (int i = 1; i <= n; ++i)
    {
        if (str[i] == '1')
        {
            hash1[i][0] = hash1[i - 1][0], hash1[i][1] = hash1[i - 1][1];
            hash2[i][0] = hash2[i - 1][0], hash2[i][1] = hash2[i - 1][1];
            cnt[i] = cnt[i - 1];
        }
        else
        {
            hash1[i][0] = (hash1[i - 1][0] * base + (i & 1)) % mod1, hash1[i][1] = (hash1[i - 1][1] * base + ((i & 1) ^ 1)) % mod1;
            hash2[i][0] = (hash2[i - 1][0] * base + (i & 1)) % mod2, hash2[i][1] = (hash2[i - 1][1] * base + ((i & 1) ^ 1)) % mod2;
            cnt[i] = cnt[i - 1] + 1;
        }
    }
    read(m);
    for (int i = 1; i <= m; ++i)
    {
        int x, y, len;
        read(x, y, len);
        if (cnt[x + len - 1] - cnt[x - 1] == cnt[y + len - 1] - cnt[y - 1] && calc1(x, x + len - 1, x & 1) == calc1(y, y + len - 1, y & 1) && calc2(x, x + len - 1, x & 1) == calc2(y, y + len - 1, y & 1))
            printf("Yes\n");
        else
            printf("No\n");
    }
    return 0;
}