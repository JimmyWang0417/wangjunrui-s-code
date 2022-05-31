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
int n, a[N], b[N];
ll sum;
signed main()
{
    read(n);
    ll c = (ll)n * (n + 1) / 2;
    for (int i = 1; i <= n; ++i)
    {
        read(a[i]);
        sum += a[i];
    }
    if (sum % c != 0)
    {
        printf("NO\n");
        return 0;
    }
    sum /= c;
    for (int i = 1; i <= n; ++i)
        b[i] = a[i % n + 1] - a[i];
    for (int i = 1; i <= n; ++i)
        if (b[i] > sum || (sum - b[i]) % n != 0)
        {
            printf("NO\n");
            return 0;
        }
    printf("YES\n");
    return 0;
}