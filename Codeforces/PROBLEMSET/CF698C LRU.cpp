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
const int N = (1 << 20) + 5;
double p[N], dp[N];
int n, m;
inline int popcount(int x)
{
    int res = 0;
    while (x)
    {
        if (x & 1)
            ++res;
        x >>= 1;
    }
    return res;
}
double answer[N];
signed main()
{
    read(n, m);
    int cnt = 0;
    for (int i = 0; i < n; ++i)
    {
        scanf("%lf", &p[i]);
        cnt += (p[i] > 0);
    }
    if (cnt <= m)
    {
        for (int i = 0; i < n; ++i)
            printf(p[i] > 0 ? "1 " : "0 ");
        return 0;
    }
    dp[0] = 1;
    for (int S = 0; S < (1 << n); ++S)
        if (dp[S])
        {
            if (popcount(S) == m)
            {
                for (int i = 0; i < n; ++i)
                    if ((S >> i) & 1)
                        answer[i] += dp[S];
            }
            double all = 0;
            for (int i = 0; i < n; ++i)
                if (!((S >> i) & 1))
                    all += p[i];
            if (all)
                for (int i = 0; i < n; ++i)
                    if (!((S >> i) & 1))
                        dp[S | 1 << i] += dp[S] * (p[i] / all);
        }
    for (int i = 0; i < n; ++i)
        printf("%.12lf ", answer[i]);
    putchar('\n');
    return 0;
}