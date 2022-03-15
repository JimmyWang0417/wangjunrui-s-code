#include <bits/stdc++.h>
#define ll long long
#define ull unsigned ll
#define lowbit(x) (x & (-x))
using namespace std;
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
int a1, a2, a3, a4, a5, a6, a7;
signed main()
{
    read(a1, a2, a3, a4, a5, a6, a7);
    int s = a1 + a2 + a3 + a4 + a5 + a6 + a7;
    printf("%.3lf\n", 5040.0 * a1 / s * a2 / (s - 1) * a3 / (s - 2) * a4 / (s - 3) * a5 / (s - 4) * a6 / (s - 5) * a7);
    return 0;
}