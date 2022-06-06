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
int n, m, a[N];
int dep;
int L[20][N], R[20][N];
int exl[N * 4], exr[N * 4];
pair<int, int> p[N];
int tot;
bool answer[N];
signed main()
{
    read(n, m);
    a[0] = INT_MIN / 2;
    for (int i = 1; i <= n; ++i)
        read(a[i]);
    a[n + 1] = INT_MAX / 2;
    for (int l = m;; l >>= 1, ++dep)
    {
        for (int i = 1; i <= n; ++i)
            L[dep][i] = a[i] - a[i - 1] <= l ? L[dep][i - 1] : i;
        R[dep][n + 1] = n + 1;
        for (int i = n; i >= 1; --i)
            R[dep][i] = a[i + 1] - a[i] <= l ? R[dep][i + 1] : i;
        if (l == 0)
        {
            ++dep;
            break;
        }
    }
    for (int i = 1; i <= n; ++i)
        p[i] = make_pair(L[0][i], R[0][i]);
    sort(p + 1, p + 1 + n);
    tot = (int)(unique(p + 1, p + 1 + n) - p - 1);
    for (int i = 0; i < (1 << dep); i += 2)
        exr[i] = n + 1;
    for (int i = 2; i < (1 << dep); ++i)
        for (int j = 1; j < dep; ++j)
            if ((i >> j) & 1)
            {
                ckmax(exl[i], R[j][exl[i ^ (1 << j)] + 1]);
                ckmin(exr[i], L[j][exr[i ^ (1 << j)] - 1]);
            }
    int all = ((1 << (dep - 1)) - 1) << 1;
    for (int i = 1; i <= tot; ++i)
        for (int j = 0; j < (1 << dep); j += 2)
            if (exl[j] >= p[i].first - 1 && p[i].second >= exr[all ^ j] - 1)
            {
                for (int k = p[i].first; k <= p[i].second; ++k)
                    answer[k] = true;
            }
    for (int i = 1; i <= n; ++i)
        puts(answer[i] ? "Possible" : "Impossible");
    return 0;
}