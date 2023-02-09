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
using namespace std;
const int N = 2e5 + 5;
int n, m;
int pos[N];
int a[N];
int block, num, L[N], R[N], belong[N];
vector<int> g[N];
inline void init()
{
    block = (int)sqrt(n);
    num = (n - 1) / block + 1;
    for (int i = 1; i <= num; ++i)
    {
        L[i] = R[i - 1] + 1;
        R[i] = min(R[i - 1] + block, n);
        for (int j = L[i]; j <= R[i]; ++j)
            belong[j] = i;
    }
    for (int j = 1; j <= num; ++j)
    {
        for (int i = L[j]; i <= R[j]; ++i)
            g[j].push_back(a[i]);
        sort(g[j].begin(), g[j].end());
    }
}
inline void update(int x, int y)
{
    g[belong[x]].erase(lower_bound(g[belong[x]].begin(), g[belong[x]].end(), a[x]));
    g[belong[y]].erase(lower_bound(g[belong[y]].begin(), g[belong[y]].end(), a[y]));
    swap(a[x], a[y]);
    g[belong[x]].insert(lower_bound(g[belong[x]].begin(), g[belong[x]].end(), a[x]), a[x]);
    g[belong[y]].insert(lower_bound(g[belong[y]].begin(), g[belong[y]].end(), a[y]), a[y]);
}
inline int query(int l, int r, int x, int y)
{
    if (belong[l] == belong[r])
    {
        int res = 0;
        for (int i = l; i <= r; ++i)
            if (x <= a[i] && a[i] <= y)
                ++res;
        return res;
    }
    int res = 0;
    for (int i = l; i <= R[belong[l]]; ++i)
        if (x <= a[i] && a[i] <= y)
            ++res;
    for (int i = belong[l] + 1; i < belong[r]; ++i)
        res += (int)(upper_bound(g[i].begin(), g[i].end(), y) - lower_bound(g[i].begin(), g[i].end(), x));
    for (int i = L[belong[r]]; i <= r; ++i)
        if (x <= a[i] && a[i] <= y)
            ++res;
    return res;
}
signed main()
{
    read(n, m);
    for (int i = 1; i <= n; ++i)
    {
        int x;
        read(x);
        pos[x] = i;
    }
    for (int i = 1; i <= n; ++i)
    {
        int x;
        read(x);
        a[i] = pos[x];
    }
    init();
    for (int i = 1; i <= m; ++i)
    {
        int opt;
        read(opt);
        if (opt == 1)
        {
            int x, y, l, r;
            read(x, y, l, r);
            printf("%d\n", query(l, r, x, y));
        }
        else
        {
            int x, y;
            read(x, y);
            update(x, y);
        }
    }
    return 0;
}
