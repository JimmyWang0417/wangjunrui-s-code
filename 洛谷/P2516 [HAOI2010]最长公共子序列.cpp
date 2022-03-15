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
const int N = 5005, mod = 1e8;
char a[N], b[N];
int f[2][N], g[2][N];
inline void add(int &x, int y)
{
    x += y;
    if (x >= mod)
        x -= mod;
}
signed main()
{
    //	freopen("lcs.in","r",stdin),freopen("lcs.out","w",stdout);
    scanf("%s%s", a + 1, b + 1);
    a[strlen(a + 1)] = b[strlen(b + 1)] = 0;
    int n = (int)strlen(a + 1), m = (int)strlen(b + 1);
    g[0][0] = 1;
    int now = 0, nxt = 1;
    for (int i = 1; i <= m; ++i)
        g[now][i] = 1;
    for (int i = 1; i <= n; ++i, swap(now, nxt))
    {
        memset(f[nxt], 0, sizeof(f[nxt]));
        memset(g[nxt], 0, sizeof(g[nxt]));
        g[nxt][0] = 1;
        for (int j = 1; j <= m; ++j)
        {
            if (a[i] == b[j])
            {
                f[nxt][j] = f[now][j - 1] + 1;
                g[nxt][j] = g[now][j - 1];
            }
            else
                f[nxt][j] = max(f[nxt][j - 1], f[now][j]);
            if (f[nxt][j - 1] == f[nxt][j])
                add(g[nxt][j], g[nxt][j - 1]);
            if (f[now][j] == f[nxt][j])
                add(g[nxt][j], g[now][j]);
            if (f[now][j - 1] == f[nxt][j])
                add(g[nxt][j], mod - g[now][j - 1]);
        }
    }
    //	printf("%d\n",(sizeof(f)+sizeof(g))/(1<<20));
    printf("%d\n%d\n", f[now][m], g[now][m]);
    return 0;
}
