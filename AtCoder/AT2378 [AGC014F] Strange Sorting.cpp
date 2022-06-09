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
constexpr int N = 2e5 + 5;
int n;
int pos[N];
signed main()
{
    read(n);
    for (int i = 1; i <= n; ++i)
    {
        int x;
        read(x);
        pos[x] = i;
    }
    int res = 0, now = 0;
    for (int i = n - 1; i >= 1; --i)
    {
        if (!res)
        {
            if (pos[i] > pos[i + 1])
            {
                ++res;
                now = i + 1;
            }
        }
        else
        {
            if (pos[i] <= pos[i + 1] && pos[i + 1] <= pos[now])
                continue;
            if (pos[i + 1] <= pos[now] && pos[now] <= pos[i])
                continue;
            if (pos[now] <= pos[i] && pos[i] <= pos[i + 1])
                continue;
            ++res;
            now = i + 1;
        }
    }
    printf("%d\n", res);
    return 0;
}