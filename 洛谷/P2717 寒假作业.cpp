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
const int N = 1e5 + 5;
int n, k, a[N];
ll answer = 0;
ll suml[N], sumr[N];
inline void cdq(int l, int r)
{
    if (l == r)
    {
        if (a[l] >= 0)
            ++answer;
        return;
    }
    int mid = (l + r) >> 1;
    cdq(l, mid), cdq(mid + 1, r);
    int len1 = mid - l + 1, len2 = r - mid;
    for (int i = 1, j = mid + 1; j <= r; ++i, ++j)
        sumr[i] = sumr[i - 1] + a[j];
    for (int i = 1, j = mid; j >= l; ++i, --j)
        suml[i] = suml[i - 1] + a[j];
    sort(suml + 1, suml + 1 + len1);
    sort(sumr + 1, sumr + 1 + len2, greater<int>());
    for (int i = 1, j = 1; i <= len1; ++i)
    {
        while (j <= len2 && suml[i] + sumr[j] >= 0)
            ++j;
        answer += j - 1;
    }
}
signed main()
{
    read(n, k);
    for (int i = 1; i <= n; ++i)
    {
        read(a[i]);
        a[i] -= k;
    }
    cdq(1, n);
    printf("%lld\n", answer);
    return 0;
}