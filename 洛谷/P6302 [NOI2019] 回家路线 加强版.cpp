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
const int N = 1e6 + 5;
struct Query
{
    int u, v, p, q;
    inline bool operator<(const Query &rhs) const
    {
        return p == rhs.p ? p < rhs.p : q < rhs.q;
    }
} e[N];
struct Point
{
    ll x, y;
    Point(ll _x = 0, ll _y = 0) : x(_x), y(_y) {}
    inline ll operator^(const Point &rhs) const
    {
        return x * rhs.y - y * rhs.x;
    }
    inline Point operator-(const Point &rhs) const
    {
        return Point(x - rhs.x, y - rhs.y);
    }
};
int n, m, A, B, C;
struct Queue
{
    vector<Point> q;
    vector<int> id;
    int head, tail;
    inline void init()
    {
        head = 0, tail = -1;
        q.clear();
        id.clear();
    }
    inline void insert(int _id, Point val)
    {
        while (head < tail && ((q[tail - 1] - q[tail]) ^ (val - q[tail])) >= 0)
        {
            q.pop_back();
            id.pop_back();
            --tail;
        }
        q.push_back(val);
        id.push_back(_id);
        ++tail;
    }
    inline void gettop(ll k)
    {
        while (head < tail && (q[head + 1].y - q[head].y) <= k * (q[head + 1].x - q[head].x))
            ++head;
    }
    inline bool empty()
    {
        return q.empty();
    }
} a[N];
vector<int> g[N];
vector<pair<pair<int, int>, Point>> G[N];
ll dp[N];
signed main()
{
    int maxT = 0;
    read(n, m, A, B, C);
    for (int i = 1; i <= n; ++i)
        a[i].init();
    G[0].push_back(make_pair(make_pair(1, 0), Point(0, 0)));
    for (int i = 1; i <= m; ++i)
    {
        read(e[i].u, e[i].v, e[i].p, e[i].q);
        g[e[i].p].push_back(i);
        if (e[i].v == n)
            maxT = max(maxT, e[i].q);
    }
    ll ans = 1e18;
    for (int T = 0; T <= maxT; ++T)
    {
        for (auto v : G[T])
            a[v.first.first].insert(v.first.second, v.second);
        for (auto i : g[T])
        {
            const int &u = e[i].u, &v = e[i].v, &p = e[i].p, &q = e[i].q;
            if (a[u].empty())
                continue;
            a[u].gettop(2ll * A * p);
            int where = a[u].id[a[u].head];
            ll &now = dp[i] = dp[where] + (ll)A * (p - e[where].q) * (p - e[where].q) + (ll)B * (p - e[where].q) + C;
            G[q].push_back(make_pair(make_pair(v, i), Point(q, now + (ll)A * q * q - (ll)B * q)));
            if (v == n)
                ans = min(ans, now + q);
        }
    }
    printf("%lld\n", ans);
    return 0;
}
