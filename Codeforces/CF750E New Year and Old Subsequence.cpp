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
constexpr int N = 2e5 + 5;
struct node
{
    int g[5][5];
    node() { memset(g, 0x3f, sizeof(g)); }
    inline int *operator[](int x)
    {
        return g[x];
    }
    inline node operator*(const node &rhs) const
    {
        node res;
        for (int i = 0; i < 5; ++i)
            for (int k = 0; k < 5; ++k)
                for (int j = 0; j < 5; ++j)
                    ckmin(res.g[i][j], g[i][k] + rhs.g[k][j]);
        return res;
    }
} _2, _0, _1, _7, _6, ot;
int n, m;
char str[N];
node tree[N * 4];
#define lc (rt << 1)
#define rc (rt << 1 | 1)
inline void pushup(int rt)
{
    tree[rt] = tree[lc] * tree[rc];
}
inline void build(int rt, int l, int r)
{
    if (l == r)
    {
        switch (str[l] - '0')
        {
        case 2:
            tree[rt] = _2;
            break;
        case 0:
            tree[rt] = _0;
            break;
        case 1:
            tree[rt] = _1;
            break;
        case 7:
            tree[rt] = _7;
            break;
        case 6:
            tree[rt] = _6;
            break;
        default:
            tree[rt] = ot;
            break;
        }
        return;
    }
    int mid = (l + r) >> 1;
    build(lc, l, mid);
    build(rc, mid + 1, r);
    pushup(rt);
}
inline node query(int rt, int l, int r, int x, int y)
{
    if (x <= l && r <= y)
        return tree[rt];
    int mid = (l + r) >> 1;
    if (y <= mid)
        return query(lc, l, mid, x, y);
    else if (x > mid)
        return query(rc, mid + 1, r, x, y);
    else
        return query(lc, l, mid, x, y) * query(rc, mid + 1, r, x, y);
}
signed main()
{
    _2.g[0][0] = 1, _2.g[0][1] = 0, _2.g[1][1] = 0, _2.g[2][2] = 0, _2.g[3][3] = 0, _2.g[4][4] = 0;
    _0.g[1][1] = 1, _0.g[1][2] = 0, _0.g[0][0] = 0, _0.g[2][2] = 0, _0.g[3][3] = 0, _0.g[4][4] = 0;
    _1.g[2][2] = 1, _1.g[2][3] = 0, _1.g[0][0] = 0, _1.g[1][1] = 0, _1.g[3][3] = 0, _1.g[4][4] = 0;
    _7.g[3][3] = 1, _7.g[3][4] = 0, _7.g[0][0] = 0, _7.g[1][1] = 0, _7.g[2][2] = 0, _7.g[4][4] = 0;
    _6.g[3][3] = 1, _6.g[4][4] = 1, _6.g[0][0] = 0, _6.g[1][1] = 0, _6.g[2][2] = 0;
    ot.g[0][0] = 0, ot.g[1][1] = 0, ot.g[2][2] = 0, ot.g[3][3] = 0, ot.g[4][4] = 0;
    read(n, m);
    scanf("%s", str + 1);
    build(1, 1, n);
    for (int i = 1; i <= m; ++i)
    {
        int l, r;
        read(l, r);
        int res = query(1, 1, n, l, r).g[0][4];
        printf("%d\n", res <= n ? res : -1);
    }
    return 0;
}