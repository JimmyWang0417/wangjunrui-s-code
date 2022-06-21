#include <algorithm>
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
constexpr int N = 4e6 + 5;
constexpr int mod = 51123987;
template <typename T>
inline void add(T &x, T y)
{
    x += y;
    if (x >= mod)
        x -= mod;
}
int n;
char str[N];
int tot;
inline void get()
{
    char ch = (char)getchar();
    while (ch < 'a' || ch > 'z')
        ch = (char)getchar();
    str[0] = '@';
    while (ch >= 'a' && ch <= 'z')
    {
        str[++tot] = '|';
        str[++tot] = ch;
        ch = (char)getchar();
    }
    str[++tot] = '|';
    str[tot + 1] = '#';
}
int p[N];
int pre[N], suf[N];
signed main()
{
    read(n);
    get();
    int res = 0;
    for (int i = 1, mid = 0, maxx = 0; i <= tot; ++i)
    {
        p[i] = maxx > i ? min(maxx - i, p[mid * 2 - i]) : 1;
        while (str[i - p[i]] == str[i + p[i]])
            ++p[i];
        if (i + p[i] > maxx)
        {
            mid = i;
            maxx = i + p[i];
        }
        add(res, p[i] / 2);
        if (i & 1)
        {
            ++pre[(i + 1) / 2];
            --pre[(i + 1) / 2 + p[i] / 2];
            ++suf[(i - 1) / 2];
            --suf[(i - 1) / 2 - p[i] / 2];
        }
        else
        {
            ++pre[i / 2];
            --pre[i / 2 + (p[i] + 1) / 2];
            ++suf[i / 2];
            --suf[i / 2 - (p[i] + 1) / 2];
        }
    }
    ll ans = (ll)res * (res - 1) / 2 % mod;
    for (int i = 1; i <= n; ++i)
        add(pre[i], pre[i - 1]);
    for (int i = 1; i <= n; ++i)
        add(pre[i], pre[i - 1]);
    for (int i = n; i >= 1; --i)
        add(suf[i], suf[i + 1]);
    for (int i = 1; i < n; ++i)
        (ans -= (ll)pre[i] * suf[i + 1]) %= mod;
    printf("%lld\n", (ans + mod) % mod);
    return 0;
}