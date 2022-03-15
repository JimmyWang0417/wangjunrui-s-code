// Problem: F. Alex and a TV Show
// Contest: Codeforces - Hello 2019
// URL: https://codeforces.com/problemset/problem/1097/F
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
int n, m;
bitset<7005> bitval[7005], bit[100005], a[7005];
int prime[7005], tot, mul[7005];
bool vis[7005];
signed main()
{
    mul[1] = 1;
    for (int i = 2; i <= 7000; ++i)
    {
        if (!vis[i])
        {
            prime[++tot] = i;
            mul[i] = -1;
        }
        for (int j = 1; j <= tot; ++j)
        {
            if (i * prime[j] > 7000)
                break;
            vis[i * prime[j]] = true;
            if (i % prime[j] == 0)
                break;
            mul[i * prime[j]] = -mul[i];
        }
    }
    for (int i = 1; i <= 7000; ++i)
    {
        for (int j = i; j <= 7000; j += i)
        {
            bitval[j][i] = true;
            a[i][j] = mul[j / i];
        }
    }
    read(n, m);
    for (int i = 1; i <= m; ++i)
    {
        int opt, x, y, z;
        read(opt, x, y);
        switch (opt)
        {
        case 1:
            bit[x] = bitval[y];
            break;
        case 2:
            read(z);
            bit[x] = bit[y] ^ bit[z];
            break;
        case 3:
            read(z);
            bit[x] = bit[y] & bit[z];
            break;
        default:
            printf("%lu", (bit[x] & a[y]).count() & 1);
        }
    }
    putchar('\n');
    return 0;
}