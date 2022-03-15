#include <bits/stdc++.h>
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
using namespace std;
const int N = 1.2e6 + 5;
int fa[N], size[N], mp[N];
int n;
int kase = 1;
inline void solve()
{
    for (int i = n; i >= 1; --i)
    {
        ++size[i];
        size[fa[i]] += size[i];
        ++mp[size[i]];
    }
    for (int i = 1; i <= n; ++i)
        if (n % i == 0)
        {
            int res = 0;
            for (int j = i; j <= n; j += i)
                res += mp[j];
            if (n == res * i)
                printf("%d\n", i);
        }
    memset(size, 0, sizeof(size));
    memset(mp, 0, sizeof(mp));
}
signed main()
{
    read(n);
    for (int i = 2; i <= n; ++i)
        read(fa[i]);
    printf("Case #1:\n");
    solve();
    for (int i = 2; i <= 10; ++i)
    {
        printf("Case #%d:\n", i);
        for (int j = 2; j <= n; ++j)
            fa[j] = (fa[j] + 19940105) % (j - 1) + 1;
        solve();
    }
    return 0;
}