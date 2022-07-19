/**
 *    unicode: UTF-8
 *    name:    AT3947 [AGC022B] GCD Sequence
 *    author:  wangjunrui
 *    created: 2022.07.11 周一 23:59:43 (Asia/Shanghai)
 **/
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
int n;
signed main()
{
    read(n);
    printf("2 3 29995 ");
    if (n % 2 == 0)
        printf("30000 "), --n;
    n -= 3, n /= 2;
    for (int i = 6; n--;)
    {
        for (; !(i % 2 == 0 || i % 3 == 0 || i % 5 == 0); ++i)
            ;
        printf("%d %d ", i, 30000 - i);
        ++i;
    }
    return 0;
}