#include <bits/stdc++.h>
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
constexpr int N = 505;
int H, W, h, w, a[N][N];
signed main()
{
    read(H, W, h, w);
    ll res = H * W * 500;
    for (int i = h; i <= H; i += h)
        for (int j = w; j <= W; j += w)
        {
            a[i][j] = -((h * w - 1) * 500 + 1);
            res -= ((h * w - 1) * 500 + 1) + 500;
        }
    if (res <= 0)
        printf("No\n");
    else
    {
        printf("Yes\n");
        for (int i = 1; i <= H; ++i)
        {
            for (int j = 1; j <= W; ++j)
                printf("%d ", a[i][j] ? a[i][j] : 500);
            putchar('\n');
        }
    }
    return 0;
}
