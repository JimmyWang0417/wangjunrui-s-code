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
const int N = 2e5 + 5;
priority_queue<int, vector<int>, greater<int>> q;
int n;
vector<int> g[N];
signed main()
{
    int T;
    read(T);
    while (T--)
    {
        read(n);
        for (int i = 1; i <= n; ++i)
        {
            int x, y;
            read(x, y);
            g[x].push_back(y);
        }
        int tot = n, now = 0;
        ll res = 0;
        for (int i = n; i >= 0; --i)
        {
            tot -= (int)g[i].size();
            for (auto u : g[i])
                q.push(u);
            g[i].clear();
            while (now + tot < i)
            {
                ++now;
                res += q.top();
                q.pop();
            }
        }
        while (!q.empty())
            q.pop();
        printf("%lld\n", res);
    }
    return 0;
}