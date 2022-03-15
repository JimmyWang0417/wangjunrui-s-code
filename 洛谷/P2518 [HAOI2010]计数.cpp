#include <bits/stdc++.h>
#define ll long long
#define ull unsigned ll
#define lowbit(x) (x & (-x))
using namespace std;
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
const int N = 55;
int sum[N];
inline void update(int pos)
{
    for (int i = pos; i <= 11; i += lowbit(i))
        ++sum[i];
}
inline int query(int pos)
{
    int res = 0;
    for (int i = pos; i; i -= lowbit(i))
        res += sum[i];
    return res;
}
int mp[N];
char str[N];
signed main()
{
    scanf("%s", str);
    __int128 s = 0, t = 1;
    int n = (int)strlen(str);
    for (int i = n - 1; i >= 0; --i)
    {
        int c = str[i] - '0' + 1, x = query(c - 1);
        if (!c)
            t = t * (n - i) / (++mp[c]);
        else
        {
            s += t * x / (++mp[c]);
            t = t * (n - i) / (mp[c]);
        }
        update(c);
    }
    printf("%lld\n", (ll)s);
    return 0;
}