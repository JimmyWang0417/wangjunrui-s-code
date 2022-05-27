#include <bits/stdc++.h>
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
#define ws nmsl
using namespace std;
const int N = 4e5 + 5;
int wa[N], wb[N], ws[N], rk[N], sa[N], height[N];
inline bool cmp(int *r, int a, int b, int l)
{
    return r[a] == r[b] && r[a + l] == r[b + l];
}
inline void solve(char *str, int n, int m)
{
    int *x = wa, *y = wb;

    for (int i = 1; i <= n; ++i)
        ++ws[x[i] = str[i]];
    for (int i = 2; i <= m; ++i)
        ws[i] += ws[i - 1];
    for (int i = n; i >= 1; --i)
        sa[ws[x[i]]--] = i;
    fill(ws + 1, ws + 1 + m, 0);

    for (int j = 1, p; j < n; j <<= 1, m = p)
    {
        p = 0;
        for (int i = n - j + 1; i <= n; ++i)
            y[++p] = i;
        for (int i = 1; i <= n; ++i)
            if (sa[i] > j)
                y[++p] = sa[i] - j;

        for (int i = 1; i <= n; ++i)
            ++ws[x[i]];
        for (int i = 2; i <= m; ++i)
            ws[i] += ws[i - 1];
        for (int i = n; i >= 1; --i)
            sa[ws[x[y[i]]]--] = y[i];
        fill(ws + 1, ws + 1 + m, 0);

        swap(x, y);
        p = 0;
        for (int i = 1; i <= n; ++i)
            x[sa[i]] = cmp(y, sa[i], sa[i - 1], j) ? p : ++p;
    }
    for (int i = 1; i <= n; ++i)
        rk[sa[i]] = i;
    for (int i = 1, h = 0; i <= n; ++i)
    {
        if (h)
            --h;
        while (str[i + h] == str[sa[rk[i] - 1] + h])
            ++h;
        height[rk[i]] = h;
    }
}
int n, q;
char str[N];
int f[N][25];
int Log[N];
inline int query(int l, int r)
{
    if (l == r)
        return n - sa[l] + 1;
    if (l > r)
        swap(l, r);
    ++l;
    int k = Log[r - l + 1];
    return min(f[l][k], f[r - (1 << k) + 1][k]);
}
int m, k;
int a[N], b[N];
struct node
{
    int cnt, now;
    node(int _cnt = 0, int _now = 0) : cnt(_cnt), now(_now) {}
} st[N];
int top;
inline void work()
{
    read(m, k);
    for (int i = 1; i <= m; ++i)
    {
        read(a[i]);
        a[i] = rk[a[i]];
    }
    for (int i = 1; i <= k; ++i)
    {
        read(b[i]);
        b[i] = rk[b[i]];
    }
    sort(a + 1, a + 1 + m);
    sort(b + 1, b + 1 + k);
    ll ans = 0, now = 0;
    for (int i = 1, j = 1; i <= m; ++i)
    {
        while (j <= k && a[i] >= b[j])
        {
            if (j > 1)
            {
                int cnt = 0, x = query(b[j - 1], b[j]);
                while (top && st[top].now > x)
                {
                    cnt += st[top].cnt;
                    now -= (ll)st[top].now * st[top].cnt;
                    --top;
                }

                now += (ll)cnt * x;
                st[++top] = node(cnt, x);
            }
            int cnt = 1, x = query(b[j], b[j]);
            while (top && st[top].now > x)
            {
                cnt += st[top].cnt;
                now -= (ll)st[top].now * st[top].cnt;
                --top;
            }
            if (cnt)
            {
                now += (ll)cnt * x;
                st[++top] = node(cnt, x);
            }
            ++j;
        }
        if (j == 1)
            continue;
        int cnt = 0, x = query(a[i], b[j - 1]);
        while (top && st[top].now > x)
        {
            cnt += st[top].cnt;
            now -= (ll)st[top].now * st[top].cnt;
            --top;
        }
        if (cnt)
        {
            now += (ll)cnt * x;
            st[++top] = node(cnt, x);
        }
        ans += now;
    }
    top = 0;
    reverse(a + 1, a + 1 + m);
    reverse(b + 1, b + 1 + k);
    now = 0;
    for (int i = 1, j = 1; i <= m; ++i)
    {
        while (j <= k && a[i] < b[j])
        {
            if (j > 1)
            {
                int cnt = 0, x = query(b[j - 1], b[j]);
                while (top && st[top].now > x)
                {
                    cnt += st[top].cnt;
                    now -= (ll)st[top].now * st[top].cnt;
                    --top;
                }

                now += (ll)cnt * x;
                st[++top] = node(cnt, x);
            }
            int cnt = 1, x = query(b[j], b[j]);
            while (top && st[top].now > x)
            {
                cnt += st[top].cnt;
                now -= (ll)st[top].now * st[top].cnt;
                --top;
            }
            if (cnt)
            {
                now += (ll)cnt * x;
                st[++top] = node(cnt, x);
            }
            ++j;
        }
        if (j == 1)
            continue;
        int cnt = 0, x = query(a[i], b[j - 1]);
        while (top && st[top].now > x)
        {
            cnt += st[top].cnt;
            now -= (ll)st[top].now * st[top].cnt;
            --top;
        }
        if (cnt)
        {
            now += (ll)cnt * x;
            st[++top] = node(cnt, x);
        }
        ans += now;
    }
    top = 0;
    printf("%lld\n", ans);
}
signed main()
{
    read(n, q);
    scanf("%s", str + 1);
    solve(str, n, 256);
    Log[0] = -1;
    for (int i = 1; i <= n; ++i)
        Log[i] = Log[i >> 1] + 1;
    for (int i = 1; i <= n; ++i)
        f[i][0] = height[i];
    for (int j = 1; j <= Log[n]; ++j)
        for (int i = 1; i + (1 << j) - 1 <= n; ++i)
            f[i][j] = min(f[i][j - 1], f[i + (1 << (j - 1))][j - 1]);
    while (q--)
        work();
    return 0;
}
