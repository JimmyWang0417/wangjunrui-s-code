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
const int N = 4e5 + 5;
priority_queue<int> q[4];
int n;
signed main()
{
    read(n);
    for (int i = 1; i <= n; ++i)
    {
        char s[5];
        int x;
        scanf("%s", s), read(x);
        q[(s[0] - '0') + ((s[1] - '0') << 1)].push(x);
    }
    ll ans = 0;
    int d = 0;
    while (!q[3].empty())
    {
        ans += q[3].top();
        q[3].pop();
        ++d;
    }
    if (q[1].size() < q[2].size())
        swap(q[1], q[2]);
    while (!q[2].empty())
    {
        ans += q[1].top() + q[2].top();
        q[1].pop(), q[2].pop();
    }
    while (!q[1].empty())
    {
        q[0].push(q[1].top());
        q[1].pop();
    }
    while ((d--) && !q[0].empty())
    {
        ans += q[0].top();
        q[0].pop();
    }
    printf("%lld\n", ans);
    return 0;
}
