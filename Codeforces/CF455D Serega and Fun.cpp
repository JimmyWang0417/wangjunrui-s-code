// Problem: D. Serega and Fun
// Contest: Codeforces - Codeforces Round #260 (Div. 1)
// URL: http://codeforces.com/problemset/problem/455/D
// Memory Limit: 256 MB
// Time Limit: 4000 ms
//
// Powered by CP Editor (https://cpeditor.org)

#include <cmath>
#include <cstdio>
#include <deque>
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
inline void read(T &x, T1 &... x1)
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
constexpr int N = 1e5 + 5, BLOCK = 320;
int n, m, a[N];
int cnt[BLOCK][N];
deque<int> q[BLOCK];
int block, num;
int belong[N], L[BLOCK], R[BLOCK];
inline void move(int l, int r)
{
    if (belong[l] == belong[r])
    {
        int val = q[belong[r]][r - L[belong[r]]];
        q[belong[r]].erase(q[belong[r]].begin() + (r - L[belong[r]]));
        q[belong[l]].insert(q[belong[l]].begin() + (l - L[belong[l]]), val);
        return;
    }
    int val = q[belong[r]][r - L[belong[r]]];
    q[belong[l]].insert(q[belong[l]].begin() + (l - L[belong[l]]), val);
    ++cnt[belong[l]][val];
    q[belong[r]].erase(q[belong[r]].begin() + (r - L[belong[r]]));
    --cnt[belong[r]][val];

    for (int i = belong[l]; i < belong[r]; ++i)
    {
        int val = q[i].back();
        q[i].pop_back(), --cnt[i][val];
        q[i + 1].push_front(val), ++cnt[i + 1][val];
    }
}
inline int query(int l, int r, int v)
{
    if (belong[l] == belong[r])
    {
        int res = 0;
        for (int i = l; i <= r; ++i)
            if (q[belong[l]][i - L[belong[l]]] == v)
                ++res;
        return res;
    }
    int res = 0;
    for (int i = belong[l] + 1; i < belong[r]; ++i)
        res += cnt[i][v];
    for (int i = l; i <= R[belong[l]]; ++i)
        if (q[belong[l]][i - L[belong[l]]] == v)
            ++res;
    for (int i = L[belong[r]]; i <= r; ++i)
        if (q[belong[r]][i - L[belong[r]]] == v)
            ++res;
    return res;
}
inline void print()
{
    for (int i = 1; i <= num; ++i)
        for (auto u : q[i])
            printf("%d ", u);
    puts("");
}
signed main()
{
    read(n);
    block = (int)sqrt(n);
    num = (n - 1) / block + 1;
    for (int i = 1; i <= n; ++i)
        read(a[i]);
    for (int i = 1; i <= num; ++i)
    {
        L[i] = R[i - 1] + 1;
        R[i] = min(R[i - 1] + block, n);
        for (int j = L[i]; j <= R[i]; ++j)
        {
            belong[j] = i;
            ++cnt[i][a[j]];
            q[i].push_back(a[j]);
        }
    }
    read(m);
    int lastans = 0;
    for (int i = 1; i <= m; ++i)
    {
        int opt, l, r, v;
        read(opt, l, r);
        l = (l + lastans - 1) % n + 1;
        r = (r + lastans - 1) % n + 1;
        if (l > r)
            swap(l, r);
        if (opt == 1)
        {
            move(l, r);
        }
        else
        {
            read(v);
            v = (v + lastans - 1) % n + 1;
            // if (++cnt == 47)
            // printf("%d %d %d\n", l, r, v), print();
            printf("%d\n", lastans = query(l, r, v));
        }
    }
    return 0;
}