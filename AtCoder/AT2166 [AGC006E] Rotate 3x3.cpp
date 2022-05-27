#include <cstdio>
#include <cstring>
#include <vector>
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
constexpr int N = 1e5 + 5;
int n, a[N][3];
pair<int, bool> b[N];
struct node
{
    int c[N];
    inline void update(int pos)
    {
        for (int i = pos; i <= n; i += lowbit(i))
            ++c[i];
    }
    inline int query(int pos)
    {
        int res = 0;
        for (int i = pos; i; i -= lowbit(i))
            res += c[i];
        return res;
    }
    inline void clear()
    {
        memset(c, 0, sizeof(c));
    }
} tree;
int c[N];
signed main()
{
    read(n);
    for (int i = 0; i < 3; ++i)
        for (int j = 1; j <= n; ++j)
            read(a[j][i]);
    for (int i = 1; i <= n; ++i)
        if (a[i][0] % 3 == 0)
        {
            if (a[i][1] % 3 != 2)
            {
                printf("No\n");
                return 0;
            }
            if ((a[i][1] - 1) / 3 != (a[i][0] - 1) / 3 || (a[i][2] - 1) / 3 != (a[i][0] - 1) / 3)
            {
                printf("No\n");
                return 0;
            }
            if ((i & 1) == (((a[i][1] - 1) / 3) & 1))
            {
                printf("No\n");
                return 0;
            }
            b[(a[i][0] - 1) / 3 + 1] = make_pair(i, true);
        }
        else if (a[i][0] % 3 == 1)
        {
            if (a[i][1] % 3 != 2)
            {
                printf("No\n");
                return 0;
            }
            if ((a[i][1] - 1) / 3 != (a[i][0] - 1) / 3 || (a[i][2] - 1) / 3 != (a[i][0] - 1) / 3)
            {
                printf("No\n");
                return 0;
            }
            if ((i & 1) == (((a[i][1] - 1) / 3) & 1))
            {
                printf("No\n");
                return 0;
            }
            b[(a[i][0] - 1) / 3 + 1] = make_pair(i, false);
        }
        else
        {
            printf("No\n");
            return 0;
        }
    for (int i = 1; i <= n; i += 2)
    {
        c[i] = tree.query(n) - tree.query(b[i].first);
        tree.update(b[i].first);
    }
    tree.clear();
    ll sum1 = 0;
    int cnt1 = 0;
    for (int i = n - (!(n & 1)); i >= 1; i -= 2)
    {
        int x = tree.query(b[i].first);
        sum1 += x;
        cnt1 += (b[i].second ^ ((x + c[i]) & 1));
        tree.update(b[i].first);
    }
    tree.clear();
    for (int i = 2; i <= n; i += 2)
    {
        c[i] = tree.query(n) - tree.query(b[i].first);
        tree.update(b[i].first);
    }
    tree.clear();
    ll sum2 = 0;
    int cnt2 = 0;
    for (int i = n - (n & 1); i >= 1; i -= 2)
    {
        int x = tree.query(b[i].first);
        sum2 += x;
        cnt2 += (b[i].second ^ ((x + c[i]) & 1));
        tree.update(b[i].first);
    }
    tree.clear();
    if ((sum1 & 1) != (cnt2 & 1) || (sum2 & 1) != (cnt1 & 1))
    {
        printf("No\n");
        return 0;
    }
    printf("Yes\n");
    return 0;
}