#include <bits/stdc++.h>
#define int ll
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
const int N = 1005;
int n, m, sum[2][2][N][N];
inline void update(int x, int y, int w)
{
    for (int i = x; i <= n; i += lowbit(i))
        for (int j = y; j <= n; j += lowbit(j))
            sum[x & 1][y & 1][i][j] ^= w;
}
inline void update(int x1, int y1, int x2, int y2, int w)
{
    update(x1, y1, w);
    update(x2 + 1, y1, w);
    update(x1, y2 + 1, w);
    update(x2 + 1, y2 + 1, w);
}
inline int query(int x, int y)
{
    int res = 0;
    for (int i = x; i; i -= lowbit(i))
        for (int j = y; j; j -= lowbit(j))
            res ^= sum[x & 1][y & 1][i][j];
    return res;
}
inline int query(int x1, int y1, int x2, int y2)
{
    return query(x2, y2) ^ query(x1 - 1, y2) ^ query(x2, y1 - 1) ^ query(x1 - 1, y1 - 1);
}
signed main()
{
    read(n, m);
    for (int i = 1; i <= m; ++i)
    {
        int opt, x1, y1, x2, y2;
        read(opt, x1, y1, x2, y2);
        if (opt == 1)
            printf("%lld\n", query(x1, y1, x2, y2));
        else
        {
            int w;
            read(w);
            update(x1, y1, x2, y2, w);
        }
    }
    return 0;
}
