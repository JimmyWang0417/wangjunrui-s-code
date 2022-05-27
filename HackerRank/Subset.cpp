/*add x：在集合中插入一个元素 x
del x：在集合中删除一个元素 x
cnt s：输入s查询集合中有多少个元素满足x & s = x
*/
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
constexpr int N = 2e5 + 5, M = (1 << 8) + 5;
int n, a[M][M];
signed main()
{
    read(n);
    while (n--)
    {
        static char opt[10];
        static int x;
        scanf("%s", opt);
        read(x);
        int left = x >> 8, right = x & (0xff);
        if (opt[0] == 'a')
        {
            for (int S = right; S <= 0xff; S = (S + 1) | right)
                ++a[left][S];
        }
        else if (opt[0] == 'd')
        {
            for (int S = right; S <= 0xff; S = (S + 1) | right)
                --a[left][S];
        }
        else
        {
            int res = a[0][right];
            for (int S = left; S; S = (S - 1) & left)
                res += a[S][right];
            printf("%d\n", res);
        }
    }
    return 0;
}