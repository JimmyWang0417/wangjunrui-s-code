#include <algorithm>
#include <cstdio>
#include <cstring>
#define ll long long
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
constexpr int N = 2e5 + 5, M = (N * 7) * 2 + 5, MAX = 28e5, ADD = 14e5;
int m, n, a[5][N], b[5][N];
namespace subtask1
{
    inline void main()
    {
        ll sum = 0;
        for (int kase = 1; kase <= 2; ++kase)
        {
            for (int i = 1; i <= n; ++i)
                sum += a[kase][i];
        }
        printf("%lld\n", 2 * n * sum);
    }
}
namespace subtask2
{
    struct tree_array
    {
        ll c[M];
        int d[M];
        inline void update(int pos, int val)
        {
            for (int i = pos; i <= MAX; i += lowbit(i))
            {
                c[i] += val;
                ++d[i];
            }
        }
        inline ll query(int pos)
        {
            ll res = 0;
            for (int i = pos; i; i -= lowbit(i))
                res += c[i];
            return res;
        }
        inline int count(int pos)
        {
            int res = 0;
            for (int i = pos; i; i -= lowbit(i))
                res += d[i];
            return res;
        }
        inline void clear()
        {
            memset(c, 0, sizeof(c));
            memset(d, 0, sizeof(d));
        }
    } tree;
    int id[N];
    int nmsl[N], wdnmd[N];
    inline void main()
    {
        for (int i = 1; i <= m; ++i)
            id[i] = i;
        ll answer = 0, sum = 0;
        for (int i = 1; i <= m; ++i)
            for (int j = 1; j <= n; ++j)
                sum += a[i][j];
        do
        {
            for (int i = 1; i <= n; ++i)
                nmsl[i] = wdnmd[i] = i;
            sort(nmsl + 1, nmsl + 1 + n, [](int x, int y)
                 { return b[id[1]][x] - b[id[2]][x] < b[id[1]][y] - b[id[2]][y]; });
            sort(wdnmd + 1, wdnmd + 1 + n, [](int x, int y)
                 { return b[id[2]][x] - b[id[1]][x] < b[id[2]][y] - b[id[1]][y]; });
            for (int i = 1, j = 1; i <= n; ++i)
            {
                while (j <= n && b[id[1]][nmsl[j]] - b[id[2]][nmsl[j]] < b[id[2]][wdnmd[i]] - b[id[1]][wdnmd[i]])
                {
                    tree.update(b[id[2]][nmsl[j]] - b[id[3]][nmsl[j]] + ADD, a[id[2]][nmsl[j]]);
                    ++j;
                }
                answer += tree.query(b[id[3]][wdnmd[i]] - b[id[2]][wdnmd[i]] + ADD) + (ll)tree.count(b[id[3]][wdnmd[i]] - b[id[2]][wdnmd[i]] + ADD) * a[id[2]][wdnmd[i]];
            }
            tree.clear();
        } while (next_permutation(id + 1, id + 1 + m));
        printf("%lld\n", 2 * n * sum - (m == 3 ? answer : answer / 2));
    }
}
signed main()
{
    read(m, n);
    for (int i = 1; i <= m; ++i)
        for (int j = 1; j <= n; ++j)
        {
            read(a[i][j]);
            b[i][j] = (a[i][j] - 1) * 7 + i;
        }
    if (m == 2)
        subtask1::main();
    else
        subtask2::main();
    return 0;
}