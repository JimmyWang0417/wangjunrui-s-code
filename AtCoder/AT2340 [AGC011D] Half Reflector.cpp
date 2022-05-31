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
int n, k;
char str[N];
bool mp[N];
signed main()
{
    read(n, k);
    scanf("%s", str);
    for (int i = 0; i < n; ++i)
        mp[i] = str[i] == 'A';
    bool flag = true;
    int pos = 0;
    if (k > n * 2)
        k = ((k - n * 2) & 1) + n * 2;
    while (k--)
    {
        if (mp[pos] == flag)
            mp[pos] ^= 1;
        else
        {
            flag ^= 1;
            pos = (pos + 1) % n;
        }
    }
    for (int i = 0; i < n; ++i, pos = (pos + 1) % n)
        putchar('A' + (mp[pos] ^ flag));
    putchar('\n');
    return 0;
}