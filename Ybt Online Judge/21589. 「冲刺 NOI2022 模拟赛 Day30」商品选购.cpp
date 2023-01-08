#include <bitset>
#include <climits>
#include <cstdio>
#include <ext/pb_ds/priority_queue.hpp>
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
constexpr int N = 2e5 + 5;
int n, k, limit;
int a[N], b[N];
struct cmp1
{
    inline bool operator()(int x, int y)
    {
        return a[x] < a[y];
    }
};
struct cmp2
{
    inline bool operator()(int x, int y)
    {
        return b[x] < b[y];
    }
};
struct cmp3
{
    inline bool operator()(int x, int y)
    {
        return a[x] + b[x] < a[y] + b[y];
    }
};
bool visa[N], visb[N];
void work()
{
    __gnu_pbds::priority_queue<int, cmp1, __gnu_pbds::binary_heap_tag> a0, a1;
    __gnu_pbds::priority_queue<int, cmp2, __gnu_pbds::binary_heap_tag> b0, b1;
    __gnu_pbds::priority_queue<int, cmp3, __gnu_pbds::binary_heap_tag> ab;
    read(n, k, limit);
    limit = k - limit;
    for (int i = 1; i <= n; ++i)
        read(a[i]);
    for (int i = 1; i <= n; ++i)
        read(b[i]);
    for (int i = 1; i <= n; ++i)
    {
        visa[i] = visb[i] = false;
        a0.push(i);
        b0.push(i);
        ab.push(i);
    }
    int cnt = 0;
    ll ans = 0;
    while (k--)
    {
        while (!a0.empty() && visa[a0.top()])
            a0.pop();
        while (!b0.empty() && visb[b0.top()])
            b0.pop();
        while (!a1.empty() && (visa[a1.top()] || !visb[a1.top()]))
            a1.pop();
        while (!b1.empty() && (!visa[b1.top()] || visb[b1.top()]))
            b1.pop();
        while (!ab.empty() && (visa[ab.top()] || visb[ab.top()]))
            ab.pop();
        int ans1 = ab.empty() ? INT_MIN : a[ab.top()] + b[ab.top()];
        int ans2 = a0.empty() || b0.empty() || cnt == limit ? INT_MIN : a[a0.top()] + b[b0.top()];
        int ans3 = a1.empty() || b0.empty() ? INT_MIN : a[a1.top()] + b[b0.top()];
        int ans4 = a0.empty() || b1.empty() ? INT_MIN : a[a0.top()] + b[b1.top()];
        int ans5 = a1.empty() || b1.empty() ? INT_MIN : a[a1.top()] + b[b1.top()];
        int res = max(max(ans1, ans2), max(ans3, max(ans4, ans5)));
        ans += res;
        if (res == ans5)
        {
            --cnt;
            visa[a1.top()] = visb[b1.top()] = true;
        }
        else if (res == ans1)
            visa[ab.top()] = visb[ab.top()] = true;
        else if (res == ans3)
        {
            visa[a1.top()] = visb[b0.top()] = true;
            if (!visa[b0.top()])
                a1.push(b0.top());
        }
        else if (res == ans4)
        {
            visa[a0.top()] = visb[b1.top()] = true;
            if (!visb[a0.top()])
                b1.push(a0.top());
        }
        else
        {
            ++cnt;
            visa[a0.top()] = visb[b0.top()] = true;
            if (!visa[b0.top()])
                a1.push(b0.top());
            if (!visb[a0.top()])
                b1.push(a0.top());
        }
    }
    printf("%lld\n", ans);
}
signed main()
{
#ifdef ONLINE_JUDGE
    freopen("goods.in", "r", stdin);
    freopen("goods.out", "w", stdout);
#endif
    int T;
    read(T);
    while (T--)
        work();
    return 0;
}
