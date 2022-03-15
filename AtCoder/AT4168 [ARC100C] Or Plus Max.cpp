#include <bits/stdc++.h>
#include <bits/extc++.h>
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
const int N = (1 << 18) + 5;
int n, m;
pair<int, int> a[N];
inline void solve()
{
    for (int i = 1; i * 2 <= m; i <<= 1)
    {
        for (int j = 0; j < m; j += i * 2)
            for (int k = 0; k < i; ++k)
            {
                if (a[j + k].first > a[i + j + k].first)
                {
                    a[i + j + k].second = max(a[i + j + k].first, a[j + k].second);
                    a[i + j + k].first = a[j + k].first;
                }
                else if (a[j + k].first > a[i + j + k].second)
                    a[i + j + k].second = a[j + k].first;
            }
    }
    int res = 0;
    for (int i = 1; i < m; ++i)
    {
        ckmax(res, a[i].first + a[i].second);
        printf("%d\n", res);
    }
}
signed main()
{
    read(n);
    m = (1 << n);
    for (int i = 0; i < m; ++i)
        read(a[i].first);
    solve();
    return 0;
}