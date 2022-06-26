#include <algorithm>
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
constexpr int N = 1e5 + 5, BLOCK = 505;

int n, m, q, a[N];

int block, num;
int belong[N], L[N], R[N];

int nblock;
int nbelong[N], nL[N], nR[N];

int cnt[BLOCK][N];
int blockcnt[BLOCK][BLOCK];

int root[BLOCK][N];
int fa[N];
inline int find(int x)
{
    return !fa[x] ? x : fa[x] = find(fa[x]);
}
int st[N], top;
inline void update(int l, int r, int x, int y)
{
    int bl = nbelong[l], br = nbelong[r];

    if (bl == br)
    {
        int now = 0;
        top = 0;
        for (int i = nL[bl]; i <= nR[bl]; ++i)
        {
            a[i] = a[find(i)];
            if (a[i] == x || a[i] == y)
                st[++top] = i;
        }
        for (int i = l; i <= r; ++i)
            if (a[i] == x)
            {
                ++now;
                a[i] = y;
            }
        root[bl][x] = root[bl][y] = 0;
        for (int i = 1; i <= top; ++i)
            fa[st[i]] = 0;
        for (int i = 1; i <= top; ++i)
        {
            int u = st[i];
            if (root[bl][a[u]])
                fa[u] = root[bl][a[u]];
            else
                root[bl][a[u]] = u;
        }
        for (int i = bl; i <= m; ++i)
        {
            cnt[i][x] -= now;
            cnt[i][y] += now;
            blockcnt[i][belong[x]] -= now;
            blockcnt[i][belong[y]] += now;
        }
        return;
    }

    top = 0;
    for (int i = nL[bl]; i <= nR[bl]; ++i)
    {
        a[i] = a[find(i)];
        if (a[i] == x || a[i] == y)
            st[++top] = i;
    }
    int now = 0;
    for (int i = nR[bl]; i >= l; --i)
        if (a[i] == x)
        {
            ++now;
            a[i] = y;
        }
    root[bl][x] = root[bl][y] = 0;
    for (int i = 1; i <= top; ++i)
        fa[st[i]] = 0;
    for (int i = 1; i <= top; ++i)
    {
        int u = st[i];
        if (root[bl][a[u]])
            fa[u] = root[bl][a[u]];
        else
            root[bl][a[u]] = u;
    }
    int las = cnt[bl][x];
    cnt[bl][x] -= now;
    cnt[bl][y] += now;
    blockcnt[bl][belong[x]] -= now;
    blockcnt[bl][belong[y]] += now;
    for (int i = bl + 1; i < br; ++i)
    {
        if (root[i][x])
        {
            if (root[i][y])
                fa[root[i][x]] = root[i][y];
            else
                a[root[i][y] = root[i][x]] = y;
            int qwq = cnt[i][x] - las;
            now += qwq;
            root[i][x] = 0;
        }
        las = cnt[i][x];
        cnt[i][x] -= now;
        cnt[i][y] += now;
        blockcnt[i][belong[x]] -= now;
        blockcnt[i][belong[y]] += now;
    }
    top = 0;
    for (int i = nL[br]; i <= nR[br]; ++i)
    {
        a[i] = a[find(i)];
        if (a[i] == x || a[i] == y)
            st[++top] = i;
    }
    for (int i = nL[br]; i <= r; ++i)
        if (a[i] == x)
        {
            ++now;
            a[i] = y;
        }
    root[br][x] = root[br][y] = 0;
    for (int i = 1; i <= top; ++i)
        fa[st[i]] = 0;
    for (int i = 1; i <= top; ++i)
    {
        int u = st[i];
        if (root[br][a[u]])
            fa[u] = root[br][a[u]];
        else
            root[br][a[u]] = u;
    }
    for (int i = br; i <= m; ++i)
    {
        cnt[i][x] -= now;
        cnt[i][y] += now;
        blockcnt[i][belong[x]] -= now;
        blockcnt[i][belong[y]] += now;
    }
}
inline int ask(int k_th)
{
    for (int i = 1; i <= num; k_th -= blockcnt[m + 1][i++])
        if (k_th <= blockcnt[m + 1][i])
        {
            for (int j = L[i]; j <= R[i]; k_th -= cnt[m + 1][j++])
                if (k_th <= cnt[m + 1][j])
                    return j;
        }
    return 0;
}
inline int ask(int l, int r, int k_th)
{
    for (int i = 1; i <= num; k_th -= blockcnt[m + 1][i] + blockcnt[r][i] - blockcnt[l - 1][i], ++i)
        if (k_th <= blockcnt[m + 1][i] + blockcnt[r][i] - blockcnt[l - 1][i])
        {
            for (int j = L[i]; j <= R[i]; k_th -= cnt[m + 1][j] + cnt[r][j] - cnt[l - 1][j], ++j)
                if (k_th <= cnt[m + 1][j] + cnt[r][j] - cnt[l - 1][j])
                    return j;
        }
    return 0;
}
inline int query(int l, int r, int k_th)
{
    int bl = belong[l], br = belong[r];

    if (bl + 1 >= br)
    {
        for (int i = l; i <= r; ++i)
        {
            int v = a[find(i)];
            ++cnt[m + 1][v];
            ++blockcnt[m + 1][belong[v]];
        }
        int res = ask(k_th);
        for (int i = l; i <= r; ++i)
        {
            int v = a[find(i)];
            cnt[m + 1][v] = blockcnt[m + 1][belong[v]] = 0;
        }
        return res;
    }

    for (int i = R[bl]; i >= l; --i)
    {
        int v = a[find(i)];
        ++cnt[m + 1][v];
        ++blockcnt[m + 1][belong[v]];
    }
    for (int i = L[br]; i <= r; ++i)
    {
        int v = a[find(i)];
        ++cnt[m + 1][v];
        ++blockcnt[m + 1][belong[v]];
    }

    int res = ask(bl + 1, br - 1, k_th);

    for (int i = R[bl]; i >= l; --i)
    {
        int v = a[find(i)];
        cnt[m + 1][v] = blockcnt[m + 1][belong[v]] = 0;
    }
    for (int i = L[br]; i <= r; ++i)
    {
        int v = a[find(i)];
        cnt[m + 1][v] = blockcnt[m + 1][belong[v]] = 0;
    }

    return res;
}
signed main()
{
    read(n, q);
    block = (int)__builtin_sqrt(100000);
    num = (100000 - 1) / block + 1;
    for (int i = 1; i <= num; ++i)
    {
        L[i] = R[i - 1] + 1;
        R[i] = min(R[i - 1] + block, 100000);
        for (int j = L[i]; j <= R[i]; ++j)
            belong[j] = i;
    }
    nblock = block;
    m = (n - 1) / nblock + 1;
    for (int i = 1; i <= m; ++i)
    {
        nL[i] = nR[i - 1] + 1;
        nR[i] = min(nR[i - 1] + block, n);
        for (int j = nL[i]; j <= nR[i]; ++j)
            nbelong[j] = i;
    }

    for (int i = 1; i <= n; ++i)
    {
        int bl = nbelong[i];
        read(a[i]);
        if (nbelong[i - 1] != bl)
        {
            memcpy(cnt[bl], cnt[bl - 1], sizeof(cnt[bl]));
            memcpy(blockcnt[bl], blockcnt[bl - 1], sizeof(blockcnt[bl]));
        }
        ++cnt[bl][a[i]];
        ++blockcnt[bl][belong[a[i]]];
        if (root[bl][a[i]])
            fa[i] = root[bl][a[i]];
        else
            root[bl][a[i]] = i;
    }
    for (int i = 1; i <= q; ++i)
    {
        int opt, l, r, x, y;
        read(opt, l, r, x);
        if (opt == 1)
        {
            read(y);
            if (x != y)
                update(l, r, x, y);
        }
        else
            printf("%d\n", query(l, r, x));
    }
    return 0;
}