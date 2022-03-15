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
using namespace std;
const int N = (1 << 11) + 5;
int n, m;
struct Tree_array
{
    int c[4][N][N];
    inline void update(int x, int y, int val)
    {
        for (int i = x; i <= n; i += lowbit(i))
            for (int j = y; j <= m; j += lowbit(j))
            {
                c[0][i][j] += val;
                c[1][i][j] += x * val;
                c[2][i][j] += y * val;
                c[3][i][j] += x * y * val;
            }
    }
    inline void update(int x1, int y1, int x2, int y2, int val)
    {
        update(x1, y1, val);
        update(x1, y2 + 1, -val);
        update(x2 + 1, y1, -val);
        update(x2 + 1, y2 + 1, val);
    }
    inline int query(int x, int y)
    {
        int res = 0;
        for (int i = x; i; i -= lowbit(i))
            for (int j = y; j; j -= lowbit(j))
                res += c[0][i][j] * (x + 1) * (y + 1) - c[1][i][j] * (y + 1) - c[2][i][j] * (x + 1) + c[3][i][j];
        return res;
    }
    inline int query(int x1, int y1, int x2, int y2)
    {
        return query(x2, y2) - query(x1 - 1, y2) - query(x2, y1 - 1) + query(x1 - 1, y1 - 1);
    }
} tree;
signed main()
{
    char opt[10];
    scanf("%s", opt);
    read(n, m);
    while (scanf("%s", opt) != EOF)
    {
        int x1, y1, x2, y2, val;
        read(x1, y1, x2, y2);
        if (opt[0] == 'L')
        {
            read(val);
            tree.update(x1, y1, x2, y2, val);
        }
        else
            printf("%d\n", tree.query(x1, y1, x2, y2));
    }
    return 0;
}