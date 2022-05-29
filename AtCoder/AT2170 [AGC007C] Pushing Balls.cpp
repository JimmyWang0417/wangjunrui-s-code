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
constexpr int N = 2e5 + 5;
signed main()
{
    int n;
    double d, x;
    scanf("%d%lf%lf", &n, &d, &x);
    double answer = 0;
    for (int i = n; i >= 1; --i)
    {
        answer += d + ((i * 2 - 1) * x / 2);
        d += (2 * d + 5 * x) / (2 * i);
        x += x * 2 / i;
    }
    printf("%.10F\n", answer);
    return 0;
}
//优质题解：https://blog.csdn.net/qq_42101694/article/details/122696621