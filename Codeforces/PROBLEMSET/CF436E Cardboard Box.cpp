/**
 *    unicode: UTF-8
 *    name:    CF436E Cardboard Box
 *    author:  whitepaperdogdog
 *    created: 2022.07.18 周一 21:50:04 (Asia/Shanghai)
 **/
#include <cstdio>
#include <queue>
#include <vector>
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
constexpr int N = 3e5 + 5;
int n, m;
int a[N], b[N];
int vis[N];
struct node
{
    int opt;
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> q;
    inline void update()
    {
        while (!q.empty() && vis[q.top().second] != opt)
            q.pop();
    }
    inline bool empty()
    {
        update();
        return q.empty();
    }
    inline void push(const pair<int, int> &x)
    {
        q.push(x);
    }
    inline pair<int, int> top()
    {
        update();
        return q.top();
    }
} c, d, e, f, g;
inline void push0(int x)
{
    vis[x] = 0;
    c.push(make_pair(a[x], x));
    d.push(make_pair(b[x], x));
}
inline void push1(int x)
{
    vis[x] = 1;
    e.push(make_pair(b[x] - a[x], x));
    f.push(make_pair(-a[x], x));
}
inline void push2(int x)
{
    vis[x] = 2;
    g.push(make_pair(a[x] - b[x], x));
}
signed main()
{
    read(n, m);
    c.opt = d.opt = 0;
    e.opt = f.opt = 1;
    g.opt = 2;
    for (int i = 1; i <= n; ++i)
    {
        read(a[i], b[i]);
        push0(i);
    }
    ll res = 0;
    for (int i = 1; i <= m; ++i)
    {
        int minn = 0x3f3f3f3f, opt = 0, x = 0, y = 0;
        if (!c.empty() && c.top().first < minn)
        {
            minn = c.top().first;
            x = c.top().second;
            opt = 1;
        }
        if (!e.empty() && e.top().first < minn)
        {
            minn = e.top().first;
            x = e.top().second;
            opt = 2;
        }
        if (!d.empty() && !f.empty() && d.top().first + f.top().first < minn)
        {
            minn = d.top().first + f.top().first;
            x = d.top().second;
            y = f.top().second;
            opt = 3;
        }
        if (!d.empty() && !g.empty() && d.top().first + g.top().first < minn)
        {
            minn = d.top().first + g.top().first;
            x = d.top().second;
            y = g.top().second;
            opt = 4;
        }
        res += minn;
        if (opt == 1)
            push1(x);
        else if (opt == 2)
            push2(x);
        else if (opt == 3)
        {
            push2(x);
            push0(y);
        }
        else
        {
            push2(x);
            push1(y);
        }
    }
    printf("%lld\n", res);
    for (int i = 1; i <= n; ++i)
        printf("%d", vis[i]);
    putchar('\n');
    return 0;
}