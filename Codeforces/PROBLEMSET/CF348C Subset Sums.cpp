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
int n, m, q;
ll a[N];
int limit;
vector<int> small, big, g[N];
int pos[N];
ll sum[N], tag[N];
int len[400][N];
bool exist[N];
signed main()
{
    read(n, m, q);
    for (int i = 1; i <= n; ++i)
        read(a[i]);
    limit = (int)sqrt(n);
    for (int i = 1; i <= m; ++i)
    {
        int cnt;
        read(cnt);
        if (cnt <= limit)
        {
            pos[i] = (int)small.size();
            small.push_back(i);
        }
        else
        {
            pos[i] = (int)big.size();
            big.push_back(i);
        }
        g[i].resize(cnt);
        for (int j = 0; j < cnt; ++j)
        {
            int x;
            read(x);
            g[i][j] = x;
            sum[i] += a[x];
        }
    }
    for (int i = 0; i < (int)big.size(); ++i)
    {
        for (auto u : g[big[i]])
            exist[u] = true;
        for (int j = 1; j <= m; ++j)
        {
            int &res = len[i][j] = 0;
            for (auto u : g[j])
                res += exist[u];
        }
        memset(exist, 0, sizeof(exist));
    }
    while (q--)
    {
        char opt[10];
        scanf("%s", opt);
        if (opt[0] == '?')
        {
            int x;
            read(x);
            if (g[x].size() <= limit)
            {
                ll res = 0;
                for (auto v : g[x])
                    res += a[v];
                for (int i = 0; i < (int)big.size(); ++i)
                    res += len[i][x] * tag[big[i]];
                printf("%lld\n", res);
            }
            else
            {
                ll res = sum[x];
                for (int i = 0; i < (int)big.size(); ++i)
                    res += len[i][x] * tag[big[i]];
                printf("%lld\n", res);
            }
        }
        else
        {
            int x, y;
            read(x, y);
            if (g[x].size() <= limit)
            {
                for (auto v : g[x])
                    a[v] += y;
                for (int i = 0; i < (int)big.size(); ++i)
                    sum[big[i]] += (ll)len[i][x] * y;
            }
            else
                tag[x] += y;
        }
    }
    return 0;
}