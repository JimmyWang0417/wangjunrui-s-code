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
const int N = 7e5 + 5;
int n, m, a[N];
struct Tree_array
{
    ll c[N];
    inline void update(int pos, int val)
    {
        for (int i = pos; i <= n; i += lowbit(i))
            c[i] += val;
    }
    inline ll query(int pos)
    {
        ll res = 0;
        for (int i = pos; i; i -= lowbit(i))
            res += c[i];
        return res;
    }
    inline void clear(int pos)
    {
        for (int i = pos; i <= n && c[i]; i += lowbit(i))
            c[i] = 0;
    }
} tree;
struct node
{
    int opt, l, r, v;
} b[N], c[N];
set<int> se[N];
ll answer[N];
inline void cdq(int l, int r)
{
    if (l == r)
        return;
    int mid = (l + r) >> 1;
    cdq(l, mid), cdq(mid + 1, r);
    int now = l - 1;
    int i = l, j = mid + 1;
    for (; j <= r; ++j)
    {
        while (i <= mid && b[i].l >= b[j].l)
        {
            if (b[i].opt == 1)
                tree.update(b[i].r, b[i].v);
            c[++now] = b[i++];
        }
        if (b[j].opt == 2)
            answer[b[j].v] += tree.query(b[j].r);
        c[++now] = b[j];
    }
    while (i <= mid)
        c[++now] = b[i++];
    for (int i = l; i <= mid; ++i)
        tree.clear(b[i].r);
    for (int i = l; i <= r; ++i)
        b[i] = c[i];
}
signed main()
{
    read(n, m);
    int tot = 0;
    for (int i = 1; i <= n; ++i)
    {
        int &x = a[i];
        read(x);
        if (se[x].empty())
            se[x].insert(i);
        else
        {
            ++tot;
            b[tot].opt = 1;
            b[tot].l = *se[x].rbegin(), b[tot].r = i;
            b[tot].v = b[tot].r - b[tot].l;
            se[x].insert(i);
        }
    }
    int qtime = 0;
    for (int i = 1; i <= m; ++i)
    {
        int opt;
        read(opt);
        if (opt == 1)
        {
            int x, y;
            read(x, y);
            auto it = se[a[x]].find(x);
            if (it != se[a[x]].begin())
            {
                ++tot;
                auto now = it;
                --it;
                ++now;
                b[tot].opt = 1;
                b[tot].l = *it;
                b[tot].r = x;
                b[tot].v = b[tot].l - b[tot].r;
                if (now != se[a[x]].end())
                {
                    ++tot;
                    b[tot].opt = 1;
                    b[tot].l = x;
                    b[tot].r = *now;
                    b[tot].v = b[tot].l - b[tot].r;
                    b[tot].opt = 1;
                    b[tot].l = *it;
                    b[tot].r = *now;
                    b[tot].v = b[tot].r - b[tot].l;
                }
            }
            else
            {
                ++it;
                if (it != se[a[x]].end())
                {
                    ++tot;
                    b[tot].opt = 1;
                    b[tot].l = x;
                    b[tot].r = *it;
                    b[tot].v = b[tot].l - b[tot].r;
                }
            }
            se[a[x]].erase(a[x]);
            a[x] = y;
            se[a[x]].insert(x);
            it = se[a[x]].lower_bound(x);
            if (it != se[a[x]].begin())
            {
                --it;
                ++tot;
                b[tot].opt = 1;
                b[tot].l = *it;
                b[tot].r = x;
                b[tot].v = b[tot].r - b[tot].l;
                auto now = se[a[x]].upper_bound(x);
                if (now != se[a[x]].end())
                {
                    ++tot;
                    b[tot].opt = 1;
                    b[tot].l = x;
                    b[tot].r = *now;
                    b[tot].v = b[tot].r - b[tot].l;
                    ++tot;
                    b[tot].opt = 1;
                    b[tot].l = *it;
                    b[tot].r = *now;
                    b[tot].v = b[tot].l - b[tot].r;
                }
            }
            else
            {
                it = se[a[x]].upper_bound(x);
                if (it != se[a[x]].end())
                {
                    ++tot;
                    b[tot].opt = 1;
                    b[tot].l = x;
                    b[tot].r = *it;
                    b[tot].v = b[tot].r - b[tot].l;
                }
            }
        }
        else
        {
            ++tot;
            b[tot].opt = 2;
            read(b[tot].l, b[tot].r);
            b[tot].v = ++qtime;
        }
    }
    cdq(1, tot);
    for (int i = 1; i <= qtime; ++i)
        printf("%lld\n", answer[i]);
    return 0;
}