#include <algorithm>
#include <cmath>
#include <cstdio>
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
constexpr int N = 1e5 + 5;
int n, m, T;
int a[N];
signed main()
{
    read(n, m, T);
    int id = 0;
    for (int i = 0; i < n; ++i)
    {
        int x, d;
        read(x, d);
        if (d == 1)
        {
            (id += (int)floor((double)(x + T) / m)) %= n;
            a[i] = (x + T) % m;
        }
        else
        {
            (id += (int)floor((double)(x - T) / m)) %= n;
            (id += n) %= n;
            a[i] = ((x - T) % m + m) % m;
        }
    }
    sort(a, a + n);
    for (int i = 0; i < n; ++i)
        printf("%d\n", a[(i + id) % n]);
    return 0;
}
