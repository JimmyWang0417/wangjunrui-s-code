#include <cstdio>
#include <ext/pb_ds/priority_queue.hpp>
#define ll long long
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
int n;
pair<int, int> a[N];
struct Node
{
    int k;
    ll b;
    inline ll calc(int x)
    {
        return (ll)k * x + b;
    }
} b[N];
int tree[N * 4];
#define lc (rt << 1)
#define rc (rt << 1 | 1)
inline void update(int rt, int l, int r, int x, int y, int id)
{
    if (r < x || l > y)
        return;
    int mid = (l + r) >> 1;
    if (x <= l && r <= y)
    {
        double res = b[id].calc(mid), ans = b[tree[rt]].calc(mid);
        if (l == r)
        {
            if (res > ans)
                tree[rt] = id;
            return;
        }
        if (b[tree[rt]].k < b[id].k)
        {
            if (res > ans)
            {
                update(lc, l, mid, x, y, tree[rt]);
                tree[rt] = id;
            }
            else
                update(rc, mid + 1, r, x, y, id);
        }
        else if (b[tree[rt]].k > b[id].k)
        {
            if (res > ans)
            {
                update(rc, mid + 1, r, x, y, tree[rt]);
                tree[rt] = id;
            }
            else
                update(lc, l, mid, x, y, id);
        }
        else
        {
            if (b[tree[rt]].b < b[id].b)
                tree[rt] = id;
        }
        return;
    }
    update(lc, l, mid, x, y, id);
    update(rc, mid + 1, r, x, y, id);
}
inline ll query(int rt, int l, int r, int pos)
{
    if (l == r)
        return b[tree[rt]].calc(pos);
    int mid = (l + r) >> 1;
    return max(b[tree[rt]].calc(pos), (pos <= mid ? query(lc, l, mid, pos) : query(rc, mid + 1, r, pos)));
}
__gnu_pbds::priority_queue<int> L;
__gnu_pbds::priority_queue<int>::point_iterator itl[N];
__gnu_pbds::priority_queue<int, greater<int>> R;
__gnu_pbds::priority_queue<int, greater<int>>::point_iterator itr[N];
ll dp[N];
ll g[N];
int q[N];
int nmsl[N];
int where[N];
signed main()
{
#ifdef ONLINE_JUDGE
    freopen("development.in", "r", stdin);
    freopen("development.out", "w", stdout);
#endif
    read(n);
    for (int i = 1; i <= n; ++i)
        read(a[i].first, a[i].second);
    for (int i = 1, now = 0, j = 1; i <= n; ++i)
    {
        itl[i] = L.push(a[i].first);
        itr[i] = R.push(a[i].second);
        while (L.top() >= R.top())
        {
            L.erase(itl[j]);
            R.erase(itr[j]);
            ++j;
        }
        while (now <= n && now < j)
            nmsl[now++] = i;
        where[i] = j - 1;
    }
    for (int i = 0; i <= n; ++i)
    {
        nmsl[i] = nmsl[i - 1];
        while (where[nmsl[i]] <= i)
            ++nmsl[i];
        --nmsl[i];
    }
    int cnt = 0;
    b[0].b = -1e18;
    ++cnt;
    update(1, 1, n, 1, nmsl[0], cnt);
    for (int i = 1; i <= n; ++i)
    {
        dp[i] = query(1, 1, n, i) + (ll)i * i - i;
        ++cnt;
        b[cnt].k = -2 * i, b[cnt].b = dp[i] + (ll)i * i + i;
        update(1, 1, n, i + 1, nmsl[i], cnt);
    }
    printf("%lld\n", dp[n] / 2);
    return 0;
}
