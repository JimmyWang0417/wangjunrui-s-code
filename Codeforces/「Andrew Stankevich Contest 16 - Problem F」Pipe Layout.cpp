// Problem: F. Pipe Layout
// Contest: Codeforces - 2005-2006 Winter Petrozavodsk Camp, Andrew Stankevich Contest 16 (ASC 16)
// URL: https://codeforces.com/gym/100220/problem/F
// Memory Limit: 64 MB
// Time Limit: 1000 ms
//
// Powered by CP Editor (https://cpeditor.org)

#include <bits/stdc++.h>
#define lowbit(x) ((x) & (-(x)))
#define re register
#define ll long long
#define ull unsigned long long
#define rep(i, a, b) for (re int i = a; i <= b; ++i)
#define per(i, a, b) for (re int i = a; i >= b; --i)
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
inline void clear(T *array, int l, int r, int val)
{
    memset(&array[l], val, sizeof(T) * (r - l + 1));
}
using namespace std;
const int N = 15;
typedef bitset<N * 2> node;
int n, m;
unordered_map<node, ll> f[2];
int a[105][105];
signed main()
{
    freopen("pipe.in", "r", stdin);
    freopen("pipe.out", "w", stdout);
    read(n, m);
    if (n < m)
        swap(n, m);
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= m; ++j)
            a[i][j] = true;
    int now = 1, las = 0;
#define f0 f[las]
#define f1 f[now]
    ll ans = 0;
    f1[0] = 1;
    for (int i = 1; i <= n; ++i)
    {
        for (int j = 1; j <= m; ++j)
        {
            swap(now, las);
            f1.clear();
            for (auto v : f0)
            {
                const node bit = v.first;
                const ll val = v.second;
                int b1 = (bit >> ((j - 1) * 2)).to_ulong() % 4, b2 = (bit >> (j * 2)).to_ulong() % 4;
                if (!b1 && !b2)
                {
                    if (a[i + 1][j] && a[i][j + 1])
                        f1[bit | node(1) << ((j - 1) * 2) | node(2) << (j * 2)] += val;
                }
                else if (!b1 && b2)
                {
                    if (a[i][j + 1])
                        f1[bit] += val;
                    if (a[i + 1][j])
                        f1[(bit | (node(b2) << ((j - 1) * 2))) ^ (node(b2) << (j * 2))] += val;
                }
                else if (b1 && !b2)
                {
                    if (a[i + 1][j])
                        f1[bit] += val;
                    if (a[i][j + 1])
                        f1[(bit | (node(b1) << (j * 2))) ^ (node(b1) << ((j - 1) * 2))] += val;
                }
                else if (b1 == 1 && b2 == 1)
                {
                    int sum = 1;
                    for (int k = j + 1; k <= m; ++k)
                    {
                        if (((bit >> (k * 2)).to_ulong() % 4) == 1)
                            ++sum;
                        if (((bit >> (k * 2)).to_ulong() % 4) == 2)
                            --sum;
                        if (!sum)
                        {
                            f1[(bit ^ (node(1) << ((j - 1) * 2)) ^ (node(1) << (j * 2)) ^ (node(2) << (k * 2))) | (node(1) << (k * 2))] += val;
                            break;
                        }
                    }
                }
                else if (b1 == 2 && b2 == 2)
                {
                    int sum = 1;
                    for (int k = j - 2; k >= 0; --k)
                    {
                        if (((bit >> (k * 2)).to_ulong() % 4) == 1)
                            --sum;
                        if (((bit >> (k * 2)).to_ulong() % 4) == 2)
                            ++sum;
                        if (!sum)
                        {
                            f1[(bit ^ (node(2) << ((j - 1) * 2)) ^ (node(2) << (j * 2)) ^ (node(1) << (k * 2))) | (node(2) << (k * 2))] += val;
                            break;
                        }
                    }
                }
                else if (b1 == 2 && b2 == 1)
                    f1[bit ^ (node(2) << ((j - 1) * 2)) ^ (node(1) << (j * 2))] += val;
                else if (i == n && j == m)
                    ans += val;
            }
        }
        swap(now, las);
        f1.clear();
        for (auto v : f0)
            f1[v.first << 2] = v.second;
    }
    printf("%lld\n", ans);
    return 0;
}
