#include <algorithm>
#include <cstdio>
#include <vector>
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
constexpr int N = 510;
int a[N * N], X[N], n;
int c[N], cnt[N];
int pos[N][N], num[N];
inline bool check()
{
    for (int i = 1; i <= n * n; i++)
        pos[a[i]][++num[a[i]]] = i;
    for (int i = 1; i <= n; i++)
        if (pos[i][i] != X[i])
            return 0;
    return 1;
}
int main()
{
    read(n);
    for (int i = 1; i <= n; i++)
        read(X[i]);
    for (int i = 1; i <= n; i++)
        c[i] = i, a[X[i]] = i;
    sort(c + 1, c + 1 + n, [](int x, int y)
         { return X[x] < X[y]; });
    for (int i = 1; i <= n; i++)
        cnt[i] = i - 1;
    for (int i = 1; i <= n * n; i++)
    {
        if (a[i])
            continue;
        for (int j = 1; j <= n; j++)
            if (cnt[c[j]])
            {
                a[i] = c[j];
                cnt[c[j]]--;
                break;
            }
    }
    for (int i = 1; i <= n; i++)
        cnt[i] = n - i;
    for (int i = n * n; i >= 1; i--)
    {
        if (a[i])
            continue;
        for (int j = n; j >= 1; j--)
            if (cnt[c[j]])
            {
                a[i] = c[j];
                cnt[c[j]]--;
                break;
            }
    }
    if (check())
    {
        printf("Yes\n");
        for (int i = 1; i <= n * n; i++)
            printf("%d ", a[i]);
    }
    else
        printf("No\n");
    return 0;
}