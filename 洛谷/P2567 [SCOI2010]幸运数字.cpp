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
const int N = 5050;
inline ll lcm(ll x, ll y)
{
    return x / __gcd(x, y) * y;
}
ll prime[N];
int tot;
ll l, r;
ll answer;
inline void dfs(ll val, int pos, int flag = -1)
{
    if (pos > tot)
    {
        if (val != 1)
            answer += flag * (r / val - l / val);
        return;
    }
    dfs(val, pos + 1, flag);
    ll res = prime[pos] / __gcd(val, prime[pos]);
    if (res > 1e8 && val > 1e8)
        return;
    res *= val;
    if (res <= r)
        dfs(res, pos + 1, -flag);
}
signed main()
{
    read(l, r);
    --l;
    queue<int> q;
    if (r >= 6)
        prime[++tot] = 6;
    if (r >= 8)
        prime[++tot] = 8;
    for (int i = 1; i <= tot; ++i)
    {
        ll res = prime[i] * 10 + 6;
        if (r >= res)
            prime[++tot] = res;
        res = prime[i] * 10 + 8;
        if (r >= res)
            prime[++tot] = res;
    }
    int cnt = 0;
    for (int i = 1; i <= tot; ++i)
    {
        bool flag = true;
        for (int j = 1; j < i; ++j)
            if (prime[i] % prime[j] == 0)
            {
                flag = false;
                break;
            }
        if (flag)
        {
            if (prime[i] <= r / 3)
                prime[++cnt] = prime[i];
            else
                answer += r / prime[i] - l / prime[i];
        }
    }
    tot = cnt;
    dfs(1, 1);
    printf("%lld\n", answer);
    return 0;
}