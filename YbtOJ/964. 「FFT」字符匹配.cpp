#pragma GCC optimize(3)
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
constexpr int N = 2e5;
int n, m, k;
char A[N + 5], B[N + 5];
int cnt[15];
bitset<N> bit[15], answer;
signed main()
{
#ifdef ONLINE_JUDGE
    freopen("string.in", "r", stdin);
    freopen("string.out", "w", stdout);
#endif
    read(n, m, k);
    scanf("%s%s", A, B);
    for (int i = 0, l = 0, r = -1; i < n; ++i)
    {
        while (r < min(i + k, n - 1))
            ++cnt[A[++r] - '0'];
        while (l < max(i - k, 0))
            --cnt[A[l++] - '0'];
        for (int j = 0; j < 10; ++j)
            bit[j][i] = (bool)cnt[j];
        answer[i] = true;
    }
    for (int i = 0; i < m; ++i)
        answer &= (bit[B[i] - '0'] >> i);
    printf("%lu\n", answer.count());
    return 0;
}
