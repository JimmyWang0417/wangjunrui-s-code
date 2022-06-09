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
constexpr int N = 2e5 + 5;
int n, m, a[N];
int cnt[N];
int sum[N], answer;
signed main()
{
    read(n, m);
    for (int i = 1; i <= n; ++i)
    {
        read(a[i]);
        ++cnt[a[i]];
    }
    for (int i = 1; i <= n; ++i)
    {
        ++sum[max(1, i - cnt[i] + 1)];
        --sum[i + 1];
    }
    for (int i = 1; i <= n; ++i)
    {
        sum[i] += sum[i - 1];
        answer += !sum[i];
    }
    for (int i = 1; i <= m; ++i)
    {
        int x, y;
        read(x, y);
        --cnt[a[x]];
        if (a[x] - cnt[a[x]] >= 1 && !--sum[a[x] - cnt[a[x]]])
            ++answer;
        a[x] = y;
        if (a[x] - cnt[a[x]] >= 1 && !sum[a[x] - cnt[a[x]]]++)
            --answer;
        ++cnt[a[x]];
        printf("%d\n", answer);
    }
    return 0;
}