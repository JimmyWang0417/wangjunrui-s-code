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
const int N = 1e3 + 5, M = 2e3 + 5;
int n, m;
bitset<N> a[M];
char str[N];
bool answer[N];
inline void solve()
{
    int ans = 0;
    for (int i = 1; i <= n; ++i)
    {
        int where = -1;
        for (int j = i; j <= m; ++j)
            if (a[j][i])
            {
                where = j;
                break;
            }
        if (where == -1)
        {
            printf("Cannot Determine\n");
            return;
        }
        ans = max(ans, where);
        if (where != i)
            swap(a[where], a[i]);
        for (int j = i + 1; j <= m; ++j)
            if (a[j][i])
                a[j] ^= a[i];
    }
    for (int i = n; i >= 1; --i)
    {
        answer[i] = a[i][0];
        for (int j = i + 1; j <= n; ++j)
            if (a[i][j])
                answer[i] ^= answer[j];
    }
    printf("%d\n", ans);
    for (int i = 1; i <= n; ++i)
        puts(answer[i] ? "?y7M#" : "Earth");
}
signed main()
{
    read(n, m);
    for (int i = 1; i <= m; ++i)
    {
        int v;
        scanf("%s", str + 1), read(v);
        for (int j = 1; j <= n; ++j)
            a[i][j] = str[j] - '0';
        a[i][0] = v;
    }
    solve();
    return 0;
}