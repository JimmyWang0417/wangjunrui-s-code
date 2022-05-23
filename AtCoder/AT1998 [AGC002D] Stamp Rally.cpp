#include <bits/stdc++.h>
#define size qwq
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
constexpr int N = 1e5 + 5;
int n, m, q;
pair<int, int> e[N];
int fa[N], size[N];
int answer[N];
struct node
{
    int x, y, k, id;
} a[N], b[N], c[N];
pair<int, int> st[N];
int top;
inline int find(int x)
{
    return !fa[x] ? x : find(fa[x]);
}
inline void solve(int l, int r, int ql, int qr)
{
    if (ql > qr)
    {
        for (int i = l; i <= r; ++i)
        {
            int x = find(e[i].first), y = find(e[i].second);
            if (x != y)
            {
                if (size[x] < size[y])
                    swap(x, y);
                size[x] += size[y];
                fa[y] = x;
            }
        }
        return;
    }
    if (l == r)
    {
        for (int i = ql; i <= qr; ++i)
            answer[a[i].id] = l;
        int x = find(e[l].first), y = find(e[l].second);
        if (x != y)
        {
            if (size[x] < size[y])
                swap(x, y);
            size[x] += size[y];
            fa[y] = x;
        }
        return;
    }
    int mid = (l + r) >> 1;
    int cnt1 = 0, cnt2 = 0;
    for (int i = l; i <= mid; ++i)
    {
        int x = find(e[i].first), y = find(e[i].second);
        if (x != y)
        {
            if (size[x] < size[y])
                swap(x, y);
            st[++top] = make_pair(x, y);
            size[x] += size[y];
            fa[y] = x;
        }
    }
    for (int i = ql; i <= qr; ++i)
    {
        int x = find(a[i].x), y = find(a[i].y), k = a[i].k;
        if (x == y)
        {
            if (k <= size[x])
                b[++cnt1] = a[i];
            else
                c[++cnt2] = a[i];
        }
        else
        {
            if (k <= size[x] + size[y])
                b[++cnt1] = a[i];
            else
                c[++cnt2] = a[i];
        }
    }
    while (top)
    {
        size[st[top].first] -= size[st[top].second];
        fa[st[top].second] = 0;
        --top;
    }
    for (int i = 1; i <= cnt1; ++i)
        a[ql + i - 1] = b[i];
    for (int i = 1; i <= cnt2; ++i)
        a[qr - cnt2 + i] = c[i];
    solve(l, mid, ql, ql + cnt1 - 1);
    solve(mid + 1, r, ql + cnt1, qr);
}
signed main()
{
    read(n, m);
    for (int i = 1; i <= n; ++i)
        size[i] = 1;
    for (int i = 1; i <= m; ++i)
        read(e[i].first, e[i].second);
    read(q);
    for (int i = 1; i <= q; ++i)
    {
        read(a[i].x, a[i].y, a[i].k);
        a[i].id = i;
    }
    solve(1, m, 1, q);
    for (int i = 1; i <= q; ++i)
        printf("%d\n", answer[i]);
    return 0;
}