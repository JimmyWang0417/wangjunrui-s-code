#include <bits/stdc++.h>
#define int ll
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
using namespace std;
constexpr int N = 2e5 + 5;
int n;
unordered_map<ll, int> mp;
signed main()
{
    ll answer = 0, sum = 0;
    read(n);
    mp[0] = 1;
    for (int i = 1; i <= n; ++i)
    {
        int x;
        read(x);
        sum += x;
        answer += mp[sum];
        ++mp[sum];
    }
    printf("%lld\n", answer);
    return 0;
}