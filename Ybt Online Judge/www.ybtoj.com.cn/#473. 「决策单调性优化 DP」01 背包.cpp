#include <bits/stdc++.h>
#define int ll

#define lowbit(x) ((x) & (-(x)))

#define re register

#define ll long long

#define ull unsigned long long

#define rep(i, a, b) for (re int i = a; i <= b; ++i)

#define per(i, a, b) for (re int i = a; i >= b; --i)

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
inline void clear(T *array, int l, int r, int val)
{
    memset(&array[l], val, sizeof(T) * (r - l + 1));
}
using namespace std;
const int N = 1e6 + 5, M = 5e4 + 5, W = 305;
const int INF = 0x3f3f3f3f;
int n, m;
struct node
{
    int s, v;
    inline bool operator<(const node &rhs) const
    {
        return s == rhs.s ? v > rhs.v : s < rhs.s;
    }
} a[N];
int f[W][M], sum[N];
int tot;
inline int calc(int s, int i, int t)
{
    return f[s][i] + sum[t];
}
inline int get(int s1, int s2, int i, int j)
{
    int add = (j - i) / s2, l = 0, r = min(tot, (m - j) / s2), res = -1;
    while (l <= r)
    {
        int mid = (l + r) >> 1;
        if (calc(s1, i, mid + add) <= calc(s1, j, mid))
        {
            res = mid;
            r = mid - 1;
        }
        else
            l = mid + 1;
    }
    return res == -1 ? INF : j + res * s2;
}
int q[N];
signed main()
{
    freopen("jewelry.in", "r", stdin);
    freopen("jewelry.out", "w", stdout);
    read(n, m);
    for (int i = 1; i <= n; ++i)
        read(a[i].s, a[i].v);
    sort(a + 1, a + 1 + n);
    for (int i = 1; i <= n; ++i)
        if (a[i].s != a[i - 1].s)
        {
            tot = 0;
            for (int j = i; j <= n && a[j].s == a[i].s; ++j)
            {
                ++tot;
                sum[tot] = sum[tot - 1] + a[j].v;
            }
            //			for(int i=1; i<=tot; ++i)
            //				printf("%d ",sum[i]);
            //			putchar('\n');
            for (int j = 0; j <= m; ++j)
                f[a[i].s][j] = f[a[i - 1].s][j];
            for (int j = 0; j < a[i].s; ++j)
            {
                int head = 1, tail = 1;
                q[1] = j;
                for (int k = j + a[i].s; k <= m; k += a[i].s)
                {
                    while (head < tail && get(a[i - 1].s, a[i].s, q[head], q[head + 1]) <= k)
                        ++head;
                    f[a[i].s][k] = max(f[a[i].s][k], calc(a[i - 1].s, q[head], min(tot, (k - q[head]) / a[i].s)));
                    while (head < tail && get(a[i - 1].s, a[i].s, q[tail - 1], q[tail]) >= get(a[i - 1].s, a[i].s, q[tail], k))
                        --tail;
                    q[++tail] = k;
                }
            }
        }
    for (int i = 1; i <= m; ++i)
        printf("%lld ", f[a[n].s][i]);
    return 0;
}
