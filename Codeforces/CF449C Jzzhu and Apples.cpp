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
const int N = 1e5 + 5;
bool vis[N];
int prime[N], tot;
inline void getprime(int n)
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
int p[N];
vector<pair<int, int>> answer;
signed main()
{
    int n;
    read(n);
    getprime(n / 2);
    memset(vis, 0, sizeof(vis));
    for (int i = tot; i >= 1; --i)
    {
        tot = 0;
        for (int j = prime[i]; j <= n; j += prime[i])
        {
            if (vis[j])
                continue;
            p[++tot] = j;
        }
        if (tot & 1)
        {
            swap(p[2], p[tot]);
            --tot;
        }
        for (int j = 1; j <= tot; j += 2)
        {
            answer.emplace_back(p[j], p[j + 1]);
            vis[p[j]] = vis[p[j + 1]] = true;
        }
    }
    printf("%lu\n", answer.size());
    for (auto u : answer)
        printf("%d %d\n", u.first, u.second);
    return 0;
}