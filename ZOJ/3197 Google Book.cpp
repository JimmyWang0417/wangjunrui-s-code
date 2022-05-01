#include <algorithm>
#include <cstdio>
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
constexpr int N = 5005;
int n;
pair<int, int> a[N];
inline void work()
{
    read(n);
    for (int i = 1; i <= n; ++i)
        read(a[i].first, a[i].second);
    sort(a + 1, a + 1 + n);
    int res = 0;
    for (int r = 1, maxx = 0, i = 1; r <= n; r = maxx + 1)
    {
        if (i > n || a[i].first > r)
        {
            puts("hack");
            break;
        }
        while (i <= n && a[i].first <= r)
            ckmax(maxx, a[i++].second);
        ++res;
    }
    printf("%d\n", res);
}
signed main()
{
    int T;
    read(T);
    while (T--)
        work();
    return 0;
}