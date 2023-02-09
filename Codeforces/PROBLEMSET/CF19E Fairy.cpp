#include <bits/stdc++.h>
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
constexpr int N = 1e4 + 5;
int n, m;
struct node
{
    int u, v;
} a[N];
int fa[N], lasfa[N];
bitset<N> dis, lasdis;
inline int find(int x)
{
    if (!fa[x])
        return x;
    int _fa = find(fa[x]);
    dis[x] = dis[x] ^ dis[fa[x]];
    return fa[x] = _fa;
}
int block, num;
int answerp[N], answertot;
inline void solve(int bl)
{
    memset(fa, 0, sizeof(fa));
    dis.reset();
    int l = (bl - 1) * block + 1, r = min(bl * block, m);
    for (int i = 1; i < l; ++i)
    {
        int x = find(a[i].u), y = find(a[i].v);
        if (x != y)
        {
            fa[x] = y;
            dis[x] = dis[a[i].u] ^ dis[a[i].v] ^ 1;
        }
        else if (dis[a[i].u] == dis[a[i].v])
            return;
    }
    for (int i = r + 1; i <= m; ++i)
    {
        int x = find(a[i].u), y = find(a[i].v);
        if (x != y)
        {
            fa[x] = y;
            dis[x] = dis[a[i].u] ^ dis[a[i].v] ^ 1;
        }
        else if (dis[a[i].u] == dis[a[i].v])
            return;
    }
    memcpy(lasfa, fa, sizeof(fa));
    lasdis = dis;
    for (int i = l; i <= r; ++i)
    {
        memcpy(fa, lasfa, sizeof(fa));
        dis = lasdis;
        bool flag = false;
        for (int j = l; j < i; ++j)
        {
            int x = find(a[j].u), y = find(a[j].v);
            if (x != y)
            {
                fa[x] = y;
                dis[x] = dis[a[j].u] ^ dis[a[j].v] ^ 1;
            }
            else if (dis[a[j].u] == dis[a[j].v])
            {
                flag = true;
                break;
            }
        }
        if (flag)
            continue;
        for (int j = i + 1; j <= r; ++j)
        {
            int x = find(a[j].u), y = find(a[j].v);
            if (x != y)
            {
                fa[x] = y;
                dis[x] = dis[a[j].u] ^ dis[a[j].v] ^ 1;
            }
            else if (dis[a[j].u] == dis[a[j].v])
            {
                flag = true;
                break;
            }
        }
        if (flag)
            continue;
        answerp[++answertot] = i;
    }
}
signed main()
{
    read(n, m);
    if (m == 0)
    {
        printf("0\n");
        return 0;
    }
    for (int i = 1; i <= m; ++i)
        read(a[i].u, a[i].v);
    block = (int)sqrt(m);
    num = (m - 1) / block + 1;
    for (int i = 1; i <= num; ++i)
        solve(i);
    printf("%d\n", answertot);
    for (int i = 1; i <= answertot; ++i)
        printf("%d ", answerp[i]);
    putchar('\n');
    return 0;
}