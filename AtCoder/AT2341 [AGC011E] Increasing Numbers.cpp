#include <cstdio>
#include <cstring>
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
constexpr int N = 5e5 + 5;
char str[N];
int a[N];
signed main()
{
    scanf("%s", str);
    a[0] = (int)strlen(str);
    int sum = 0;
    for (int i = 1; i <= a[0]; ++i)
    {
        a[i] += (str[a[0] - i] - '0') * 9;
        a[i + 1] += a[i] / 10;
        a[i] %= 10;
        sum += a[i];
    }
    while (a[a[0] + 1])
        sum += a[++a[0]];
    for (int kase = 1;; ++kase)
    {
        sum += 9;
        a[1] += 9;
        for (int i = 1; a[i] >= 10; ++i)
        {
            sum -= a[i + 1];
            a[i + 1] += a[i] / 10;
            sum += a[i + 1];
            sum -= a[i];
            a[i] %= 10;
            sum += a[i];
        }
        while (a[a[0] + 1])
            sum += a[++a[0]];
        if (sum <= 9 * kase)
        {
            printf("%d\n", kase);
            return 0;
        }
    }
    return 0;
}
