#include <bits/stdc++.h>
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
constexpr int N = 1e5 + 5;
constexpr ll MAX = 1e18;
int prime[N], tot;
bool vis[N];
inline void getprimes(int n)
{
    for (int i = 2; i <= n; ++i)
    {
        if (!vis[i])
            prime[++tot] = i;
        for (int j = 1; j <= tot; ++j)
        {
            if (i * prime[j] > n)
                break;
            vis[i * prime[j]] = true;
            if (i % prime[j] == 0)
                break;
        }
    }
}
int answer = 0;
inline pair<ll, ll> calc(ll x)
{
    ll res = 1, sub = 1;
    for (int i = 1; i <= tot && (ll)prime[i] * prime[i] <= x; ++i)
        if (x % prime[i] == 0)
        {
            int cnt = 0;
            while (x % prime[i] == 0)
            {
                cnt = (cnt + 1) % 3;
                x /= prime[i];
            }
            if (cnt == 1)
            {
                res *= prime[i];
                if ((ll)prime[i] * prime[i] > MAX / sub)
                {
                    ++answer;
                    return make_pair(0, 0);
                }
                sub *= (ll)prime[i] * prime[i];
            }
            else if (cnt == 2)
            {
                res *= (ll)prime[i] * prime[i];
                if (prime[i] > MAX / sub)
                {
                    ++answer;
                    return make_pair(0, 0);
                }
                sub *= prime[i];
            }
        }
    if (x > 1)
    {
        res *= x;
        if (x > MAX / sub / x)
        {
            ++answer;
            return make_pair(0, 0);
        }
        sub *= (ll)x * x;
    }
    return make_pair(res, sub);
}
unordered_map<ll, int> mp;
unordered_map<ll, ll> cor;
unordered_map<ll, bool> qwq;
vector<pair<ll, int>> a;
int n;
signed main()
{
    getprimes(1e5);
    read(n);
    for (int i = 1; i <= n; ++i)
    {
        ll x;
        read(x);
        pair<ll, ll> now = calc(x);
        if (now.first)
        {
            cor[now.first] = now.second;
            ++mp[now.first];
        }
    }
    for (auto u : mp)
    {
        if (u.first == 1)
        {
            ++answer;
            continue;
        }
        a.push_back(u);
    }
    sort(a.begin(), a.end(), [](pair<ll, int> x, pair<ll, int> y)
         { return x.second > y.second; });
    for (auto u : a)
    {
        ll v = cor[u.first];
        if (qwq[u.first])
            continue;
        qwq[v] = true;
        answer += u.second;
    }
    printf("%d\n", answer);
    return 0;
}