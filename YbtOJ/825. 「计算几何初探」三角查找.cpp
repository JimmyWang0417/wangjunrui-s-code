// Problem: D. Large Triangle
// Contest: Codeforces - Codeforces Round #503 (by SIS, Div. 1)
// URL: https://codeforces.com/problemset/problem/1019/D
// Memory Limit: 256 MB
// Time Limit: 3000 ms
//
// Powered by CP Editor (https://cpeditor.org)

#include <bits/stdc++.h>
#include <bits/extc++.h>
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
constexpr int N = 4e6 + 5;
int n;
ll m;
struct Point
{
    int x, y, id;
    inline bool operator<(const Point &rhs) const
    {
        return x < rhs.x;
    }
} point[N];
struct node
{
    int x, y;
    double k;
    inline bool operator<(const node &rhs) const
    {
        return k < rhs.k;
    }
} a[N];
int tot;
int pos[N];
inline void solve1(int l, int r, int x, int y)
{
    while (l <= r)
    {
        int mid = (l + r) >> 1;
        ll S = abs((ll)(point[mid].x - point[x].x) * (point[mid].y - point[y].y) - (ll)(point[mid].x - point[y].x) * (point[mid].y - point[x].y));
        if (S == m * 2)
        {
            printf("Yes\n%d %d\n%d %d\n%d %d\n", point[mid].x, point[mid].y, point[x].x, point[x].y, point[y].x, point[y].y);
            exit(0);
        }
        else if (S < m * 2)
            r = mid - 1;
        else
            l = mid + 1;
    }
}
inline void solve2(int l, int r, int x, int y)
{
    while (l <= r)
    {
        int mid = (l + r) >> 1;
        ll S = abs((ll)(point[mid].x - point[x].x) * (point[mid].y - point[y].y) - (ll)(point[mid].x - point[y].x) * (point[mid].y - point[x].y));
        if (S == m * 2)
        {
            printf("Yes\n%d %d\n%d %d\n%d %d\n", point[mid].x, point[mid].y, point[x].x, point[x].y, point[y].x, point[y].y);
            exit(0);
        }
        else if (S < m * 2)
            l = mid + 1;
        else
            r = mid - 1;
    }
}
signed main()
{
    freopen("triangle.in", "r", stdin);
    freopen("triangle.out", "w", stdout);
    read(n, m);
    for (int i = 1; i <= n; ++i)
        read(point[i].x, point[i].y);
    sort(point + 1, point + 1 + n);
    for (int i = 1; i <= n; ++i)
        pos[point[i].id = i] = i;
    for (int i = 1; i <= n; ++i)
        for (int j = i + 1; j <= n; ++j)
        {
            ++tot;
            a[tot].x = i, a[tot].y = j;
            if (point[i].x == point[j].x)
                a[tot].k = 1e40;
            else
                a[tot].k = (double)(point[j].y - point[i].y) / (point[j].x - point[i].x);
        }
    sort(a + 1, a + 1 + tot);
    for (int i = 1; i <= tot; ++i)
    {
        int minn = min(pos[a[i].x], pos[a[i].y]), maxx = max(pos[a[i].x], pos[a[i].y]);
        swap(point[minn], point[maxx]), swap(pos[a[i].x], pos[a[i].y]);
        if (minn > 1)
            solve1(1, minn - 1, pos[a[i].x], pos[a[i].y]);
        if (maxx < n)
            solve2(maxx + 1, n, pos[a[i].x], pos[a[i].y]);
    }
    printf("No\n");
    return 0;
}