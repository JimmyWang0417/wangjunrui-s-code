#include <cstdio>
#include <vector>
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
signed main()
{
    ll l, r;
    read(l, r);
    if (l == r)
        printf("1\n");
    else
    {
        for (int i = 62; i >= 0; --i)
            if (((l >> i) & 1) != ((r >> i) & 1))
            {
                l &= (1ll << (i + 1)) - 1;
                r &= (1ll << (i + 1)) - 1;
                for (int j = i - 1; j >= 0; --j)
                    if ((r >> j) & 1)
                    {
                        r = (1ll << i) + (1ll << (j + 1)) - 1;
                        break;
                    }
                if (l + (1ll << i) <= r)
                    printf("%lld\n", (1ll << (i + 1)) - l);
                else
                    printf("%lld\n", (r - l + 1) + ((1ll << i) - l));
                break;
            }
    }
    return 0;
}
