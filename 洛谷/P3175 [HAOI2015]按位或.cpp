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
constexpr int N = 25, M = (1 << 20) + 5;
int n;
double f[M];
inline void FWT(double *dp)
{
    for (int i = 0; i < n; ++i)
        for (int S = 0; S < (1 << n); ++S)
            if ((S >> i) & 1)
                dp[S] += dp[S ^ (1 << i)];
}
signed main()
{
    read(n);
    for (int i = 0; i < (1 << n); ++i)
        scanf("%lf", &f[i]);
    FWT(f);
    int all = (1 << n) - 1;
    double answer = 0;
    for (int S = 1; S < (1 << n); ++S)
    {
        if (1 - f[all ^ S] < 1e-8)
        {
            printf("INF\n");
            return 0;
        }
        if (__builtin_popcount(S) & 1)
            answer += 1 / (1 - f[all ^ S]);
        else
            answer -= 1 / (1 - f[all ^ S]);
    }
    printf("%.10lf\n", answer);
    return 0;
}