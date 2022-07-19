/**
 *    unicode: UTF-8
 *    name:    AT3949 [AGC022D] Shopping
 *    author:  wangjunrui
 *    created: 2022.07.12 周二 10:23:24 (Asia/Shanghai)
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
constexpr int N = 3e5 + 5;
int n, m, a[N], b[N];
bool exist[N], L[N], R[N];
signed main()
{
    read(n, m);
    for (int i = 1; i <= n; ++i)
        read(a[i]);
    int res = n + 1;
    for (int i = 1; i <= n; ++i)
    {
        read(b[i]);
        res += b[i] / (m << 1);
        b[i] %= m << 1;
        if (!b[i])
        {
            --res;
            continue;
        }
        L[i] = (2 * (m - a[i]) >= b[i]);
        R[i] = (2 * a[i] >= b[i]);
        exist[i] = (L[i] || R[i]);
    }
    res -= L[n];
    int sum = 0, top = 0, pos = n;
    for (int i = 1; i < n; ++i)
        if (exist[i])
        {
            if (!L[i])
            {
                pos = i;
                break;
            }
            if (R[i])
                ++top;
            else if (top)
            {
                --top;
                --res;
            }
        }
    sum += top;
    top = 0;
    for (int i = n - 1; i >= pos; --i)
        if (exist[i])
        {
            if (!R[i])
                break;
            if (L[i])
                ++top;
            else if (top)
            {
                --top;
                --res;
            }
        }
    sum += top;
    res -= sum / 2;
    printf("%lld\n", 2ll * m * res);
    return 0;
}