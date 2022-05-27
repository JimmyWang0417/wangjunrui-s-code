#include <bits/extc++.h>
#include <bits/stdc++.h>
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
const int N = 5e5 + 5, M = 1100;
int n, m;
int block, num;
int L[M], R[M], belong[N];
ll tag[M];
pair<ll, int> a[N];
inline void update(int l, int r, int x)
{
    if (belong[l] == belong[r])
    {
        for (int i = L[belong[l]]; i <= R[belong[r]]; ++i)
            if (l <= a[i].second && a[i].second <= r)
                a[i].first += x;
        sort(a + L[belong[l]], a + R[belong[r]] + 1);
        return;
    }
    for (int i = L[belong[l]]; i <= R[belong[l]]; ++i)
        if (l <= a[i].second)
            a[i].first += x;
    sort(a + L[belong[l]], a + R[belong[l]] + 1);
    for (int i = belong[l] + 1; i < belong[r]; ++i)
        tag[i] += x;
    for (int i = L[belong[r]]; i <= R[belong[r]]; ++i)
        if (a[i].second <= r)
            a[i].first += x;
    sort(a + L[belong[r]], a + R[belong[r]] + 1);
}
inline int query(int x)
{
    int minn = 0, maxx = 0;
    for (int i = 1; i <= num; ++i)
    {
        ll y = x - tag[i];
        int pos = (int)(lower_bound(a + L[i], a + R[i] + 1, make_pair(y, 0)) - a);
        if (pos <= R[i] && a[pos].first == y)
        {
            minn = a[pos].second;
            break;
        }
    }
    for (int i = num; i >= 1; --i)
    {
        ll y = x - tag[i];
        int pos = (int)(lower_bound(a + L[i], a + R[i] + 1, make_pair(y + 1, 0)) - a - 1);
        if (L[i] <= pos && a[pos].first == y)
        {
            maxx = a[pos].second;
            break;
        }
    }
    // for (int i = 1; i <= num; i++)
    //     if (tag[i] <= x)
    //     {
    //         const int y = x - tag[i];
    //         int l = std::lower_bound(a + L[i], a + R[i] + 1, make_pair(y, 0)) - a;
    //         if (l <= R[i] && a[l].first == y)
    //         {
    //             int r = std::lower_bound(a + L[i], a + R[i] + 1, make_pair(y + 1, 0)) - a - 1;
    //             if (!minn)
    //                 minn = a[l].second;
    //             maxx = a[r].second;
    //         }
    //     }
    if (!minn)
        return -1;
    return maxx - minn;
}
signed main()
{
    read(n, m);
    for (int i = 1; i <= n; ++i)
    {
        int x;
        read(x);
        a[i] = make_pair(x, i);
    }
    block = (int)(1.5 * sqrt(n));
    num = (n - 1) / block + 1;
    for (int i = 1; i <= num; ++i)
    {
        L[i] = R[i - 1] + 1;
        R[i] = min(R[i - 1] + block, n);
        for (int j = L[i]; j <= R[i]; ++j)
            belong[j] = i;
        sort(a + L[i], a + R[i] + 1);
    }
    for (int i = 1; i <= m; ++i)
    {
        int opt;
        read(opt);
        if (opt == 1)
        {
            int l, r, x;
            read(l, r, x);
            update(l, r, x);
        }
        else
        {
            int x;
            read(x);
            printf("%d\n", query(x));
        }
    }
    return 0;
}