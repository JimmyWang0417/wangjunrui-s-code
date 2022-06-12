#include <bits/stdc++.h>
#define int ll
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
using namespace std;
constexpr int N = 1e5 + 5;
signed main()
{
    int T;
    read(T);
    while (T--)
    {
        int A, B, C, D;
        read(A, B, C, D);
        int len = (max(A, B) - 1) / (min(A, B) + 1) + 1, x;
        if (len != 1)
            x = max((len * (A + len) - B - 1) / (len * len - 1), 1ll);
        else
            x = (A >= B ? A : 0);
        for (int i = C; i <= D; ++i)
        {
            if (i <= A + B - (B - x + 1) - (B - x + 1) / len)
                putchar(i % (len + 1) ? 'A' : 'B');
            else
                putchar((A + B - i + 1) % (len + 1) ? 'B' : 'A');
        }
        putchar('\n');
    }
    return 0;
}