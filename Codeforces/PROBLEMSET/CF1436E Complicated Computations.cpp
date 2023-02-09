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
const int N = 1e6 + 5;
int n, m, a[N];
int belong[N], block, num, L[N], R[N];
int st[N], top;
bool mp[N];
int cnt[N], answer;
int nowcnt[N], nowanswer;
struct Query
{
    int l, r;
    inline bool operator<(const Query &rhs) const
    {
        return belong[l] == belong[rhs.l] ? r > rhs.r : l < rhs.l;
    }
} q[N];
int nmsl[N];
signed main()
{
    read(n);
    bool flag = true;
    for (int i = 1; i <= n; ++i)
    {
        read(a[i]);
        if (a[i] != 1)
            flag = false;
    }
    if (flag)
    {
        printf("1\n");
        return 0;
    }
    for (int i = 1; i <= n; ++i)
    {
        if (nmsl[a[i]] < i - 1)
        {
            ++m;
            q[m].l = nmsl[a[i]] + 1;
            q[m].r = i - 1;
        }
        nmsl[a[i]] = i;
    }
    ++m;
    q[m].l = 1, q[m].r = n;
    for (int i = 1; i <= n; ++i)
    {
        if (nmsl[a[i]] < n)
        {
            ++m;
            q[m].l = nmsl[a[i]] + 1;
            q[m].r = n;
        }
    }
    block = (int)sqrt(n);
    num = (n - 1) / block + 1;
    for (int i = 1; i <= num; ++i)
    {
        L[i] = R[i - 1] + 1;
        R[i] = min(R[i - 1] + block, n);
        for (int j = L[i]; j <= R[i]; ++j)
            belong[j] = i;
    }
    sort(q + 1, q + m + 1);
    for (int now = 1, r = -1; now <= m; ++now)
    {
        if (belong[q[now].l] == belong[q[now].r])
        {
            for (int i = q[now].l; i <= q[now].r; ++i)
                ++nowcnt[a[i]];
            nowanswer = 1;
            while (nowcnt[nowanswer])
                ++nowanswer;
            for (int i = q[now].l; i <= q[now].r; ++i)
                nowcnt[a[i]] = 0;
            mp[nowanswer] = true;
            continue;
        }
        if (belong[q[now].l] != belong[q[now - 1].l])
        {
            for (int i = L[belong[q[now - 1].l]]; i <= r; ++i)
                cnt[a[i]] = 0;
            r = q[now].r;
            for (int i = L[belong[q[now].l]]; i <= r; ++i)
                ++cnt[a[i]];
            answer = 1;
            while (cnt[answer])
                ++answer;
        }
        while (q[now].r < r)
        {
            if (!--cnt[a[r]])
                ckmin(answer, a[r]);
            --r;
        }
        nowanswer = answer;
        for (int i = L[belong[q[now].l]]; i < q[now].l; ++i)
        {
            while (!(cnt[a[i]] + (--nowcnt[a[i]])))
                ckmin(nowanswer, a[i]);
        }
        for (int i = L[belong[q[now].l]]; i < q[now].l; ++i)
            nowcnt[a[i]] = 0;
        mp[nowanswer] = true;
    }
    int res = 1;
    while (mp[res])
        ++res;
    printf("%d\n", res);
    return 0;
}