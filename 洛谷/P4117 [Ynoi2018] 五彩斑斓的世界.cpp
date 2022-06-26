#include <cstdio>
#include <cstring>
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
constexpr int N = 1e6 + 5;
int n, m, a[N];
int block, num;
int belong[N], L[N], R[N];
struct node
{
    int opt, l, r, x, answer;
} b[N];
int cnt[N];
int root[N];
int fa[N];
inline int find(int x)
{
    return !fa[x] ? x : fa[x] = find(fa[x]);
}
inline void solve(int bl)
{
    int maxx = 0;
    for (int i = L[bl]; i <= R[bl]; ++i)
    {
        ckmax(maxx, a[i]);
        ++cnt[a[i]];
        if (root[a[i]])
            fa[i] = root[a[i]];
        else
            root[a[i]] = i;
    }
    int tag = 0;
    for (int kase = 1; kase <= m; ++kase)
    {
        int opt = b[kase].opt, l = b[kase].l, r = b[kase].r, x = b[kase].x, &res = b[kase].answer;
        ckmax(l, L[bl]);
        ckmin(r, R[bl]);
        if (l > r)
            continue;
        if (x + tag > maxx)
            continue;
        if (opt == 1)
        {
            if (l != L[bl] || r != R[bl])
            {
                for (int i = L[bl]; i <= R[bl]; ++i)
                {
                    a[i] = a[find(i)];
                    root[a[i]] = cnt[a[i]] = 0;
                }
                for (int i = L[bl]; i <= R[bl]; ++i)
                    a[i] -= tag;
                tag = maxx = 0;
                for (int i = l; i <= r; ++i)
                    if (a[i] > x)
                        a[i] -= x;
                for (int i = L[bl]; i <= R[bl]; ++i)
                {
                    ckmax(maxx, a[i]);
                    ++cnt[a[i]];
                    if (root[a[i]])
                        fa[i] = root[a[i]];
                    else
                        fa[root[a[i]] = i] = 0;
                }
            }
            else
            {
                if (x * 2 <= maxx - tag)
                {
                    for (int i = tag + 1; i <= tag + x; ++i)
                        if (root[i])
                        {
                            if (root[i + x])
                                fa[root[i]] = root[i + x];
                            else
                                a[root[i + x] = root[i]] = i + x;
                            cnt[i + x] += cnt[i];
                            root[i] = cnt[i] = 0;
                        }
                    tag += x;
                }
                else
                {
                    for (int i = maxx; i > tag + x; --i)
                        if (root[i])
                        {
                            if (root[i - x])
                                fa[root[i]] = root[i - x];
                            else
                                a[root[i - x] = root[i]] = i - x;
                            cnt[i - x] += cnt[i];
                            root[i] = cnt[i] = 0;
                        }
                    if (tag + x < maxx)
                        maxx = tag + x;
                }
            }
        }
        else
        {
            if (l != L[bl] || r != R[bl])
            {
                for (int i = l; i <= r; ++i)
                    if (a[find(i)] == tag + x)
                        ++res;
            }
            else
                res += cnt[tag + x];
        }
    }
    for (int i = L[bl]; i <= R[bl]; ++i)
        root[a[i]] = cnt[a[i]] = 0;
}
signed main()
{
    read(n, m);
    for (int i = 1; i <= n; ++i)
        read(a[i]);
    block = (int)__builtin_sqrt(n);
    num = (n - 1) / block + 1;
    for (int i = 1; i <= num; ++i)
    {
        L[i] = R[i - 1] + 1;
        R[i] = R[i - 1] + block;
        ckmin(R[i], n);
        for (int j = L[i]; j <= R[i]; ++j)
            belong[j] = i;
    }
    for (int i = 1; i <= m; ++i)
        read(b[i].opt, b[i].l, b[i].r, b[i].x);
    for (int i = 1; i <= num; ++i)
        solve(i);
    for (int i = 1; i <= m; ++i)
        if (b[i].opt == 2)
            printf("%d\n", b[i].answer);
    return 0;
}