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
int n, m, a[N];
int b[N], tot;
signed main()
{
    read(m, n);
    if (n == 1)
    {
        if (m == 1)
            printf("1\n1\n1\n");
        else
            printf("%d\n2\n1 %d\n", m, m - 1);
        return 0;
    }
    for (int i = 1; i <= n; ++i)
    {
        read(a[i]);
        if (a[i] & 1)
        {
            if (!tot)
                b[tot = 1] = a[i];
            else if (!b[n])
                b[n] = a[i];
            else
            {
                printf("Impossible\n");
                return 0;
            }
        }
    }
    for (int i = 1; i <= n; ++i)
    {
        if (a[i] & 1)
            continue;
        b[++tot] = a[i];
    }
    for (int i = 1; i <= n; ++i)
        printf("%d ", b[i]);
    putchar('\n');
    ++b[1], --b[n];
    if (!b[n])
        --n;
    printf("%d\n", n);
    for (int i = 1; i <= n; ++i)
        printf("%d ", b[i]);
    putchar('\n');
    return 0;
}