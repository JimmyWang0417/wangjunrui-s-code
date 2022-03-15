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
const int N = 1005;
int n, m, a[N], b[N], ta[N], s[N], ans, sum, mid, t;
bool check(int last, int x)
{
    if (x <= 0)
        return 1;
    if (sum - t < s[mid])
        return 0;
    for (int i = last; i <= n; i++)
    {
        if (ta[i] >= b[x])
        {
            ta[i] -= b[x];
            if (ta[i] < b[1])
                t += ta[i];
            if (b[x - 1] == b[x])
            {
                if (check(i, x - 1))
                    return 1;
            }
            else if (check(1, x - 1))
                return 1;
            if (ta[i] < b[1])
                t -= ta[i];
            ta[i] += b[x];
        }
    }
    return 0;
}
int main()
{
    read(n);
    for (int i = 1; i <= n; i++)
        read(a[i]),sum += a[i];
    read(m);
    for (int i = 1; i <= m; i++)
        read(b[i]);
    sort(a + 1, a + 1 + n);
    sort(b + 1, b + 1 + m);
    for (int i = 1; i <= m; i++)
        s[i] = s[i - 1] + b[i];
    while (sum < s[m])
        m--;
    int L = 1, R = m;
    while (L <= R)
    {
        for (int i = 1; i <= n; i++)
            ta[i] = a[i];
        t = 0;
        mid = (L + R) / 2;
        if (check(1, mid))
            L = mid + 1, ans = mid;
        else
            R = mid - 1;
    }
    printf("%d\n", ans);
    return 0;
}