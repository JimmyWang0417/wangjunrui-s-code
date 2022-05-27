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
constexpr int N = 105;
int n;
int cnt[N];
signed main()
{
    read(n);
    int maxx = 0, minn = 0x7fffffff;
    for (int i = 1; i <= n; ++i)
    {
        int x;
        read(x);
        ckmin(minn, x);
        ckmax(maxx, x);
        ++cnt[x];
    }
    if (minn < (maxx + 1) / 2)
    {
        printf("Impossible\n");
        return 0;
    }
    if (maxx & 1)
    {
        if (cnt[(maxx + 1) / 2] != 2)
        {
            printf("Impossible\n");
            return 0;
        }
    }
    else
    {
        if (cnt[maxx / 2] != 1)
        {
            printf("Impossible\n");
            return 0;
        }
    }
    for (int i = (maxx + 1) / 2 + 1; i <= maxx; ++i)
        if (cnt[i] < 2)
        {
            printf("Impossible\n");
            return 0;
        }
    printf("Possible\n");
    return 0;
}