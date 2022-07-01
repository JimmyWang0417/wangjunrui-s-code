/**
 *    unicode: UTF-8
 *    name:    CF1270F Awesome Substrings
 *    author:  wangjunrui
 *    created: 2022.06.30 周四 00:22:45
 **/
#include <algorithm>
#include <cstdio>
#include <cstring>
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
constexpr int N = 2e5 + 5, M = 505;
char str[N];
int n, sum[N], nxt[N];
int mp[N * M];
signed main()
{
    scanf("%s", str + 1);
    n = (int)strlen(str + 1);
    int block = (int)__builtin_sqrt(n);
    for (int i = 1; i <= n; ++i)
        sum[i] = sum[i - 1] + (str[i] == '1');
    nxt[n + 1] = n + 1;
    for (int i = n; i >= 1; --i)
        nxt[i] = str[i] == '1' ? i : nxt[i + 1];
    ll answer = 0;
    for (int i = 1; i <= block; ++i)
    {
        for (int j = 0; j <= n; ++j)
            answer += mp[i * sum[j] - j + n]++;
        for (int j = 0; j <= n; ++j)
            mp[i * sum[j] - j + n] = 0;
    }
    for (int i = 1; i <= n; ++i)
    {
        for (int j = 1, l = nxt[i], r = nxt[l + 1]; j <= n / block && l <= n; ++j, l = r, r = nxt[l + 1])
        {
            int ql = max(l - i + 1, j * block + 1), qr = r - i;
            if (ql <= qr)
                answer += qr / j - (ql - 1) / j;
        }
    }
    printf("%lld\n", answer);
    return 0;
}