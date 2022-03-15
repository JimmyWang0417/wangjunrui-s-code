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
const int N = 1e5 + 5;
int n, m, k;
char str[N];
signed main()
{
    read(n, m, k);
    scanf("%s", str + 1);
    m += k;
    for (int i = 1; i <= m; i++)
    {
        int opt, l, r, c;
        read(opt, l, r, c);
        if (opt == 1)
            memset(str + l, c + '0', r - l + 1);
        else
            puts(strncmp(str + l, str + l + c, r - l - c + 1) ? "NO" : "YES");
    }
    return 0;
}