#include <cstdio>
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
constexpr int N = 2005;
int n, m, q;
int sum[N][N], sumn[N][N], summ[N][N];
char str[N][N];
signed main()
{
    read(n, m, q);
    for (int i = 1; i <= n; ++i)
    {
        scanf("%s", str[i] + 1);
        for (int j = 1; j <= m; ++j)
            if (str[i][j] == '1')
            {
                sum[i][j] = 1;
                if (str[i - 1][j] == '1')
                    sumn[i][j] = 1;
                if (str[i][j - 1] == '1')
                    summ[i][j] = 1;
            }
    }
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= m; ++j)
        {
            sum[i][j] += sum[i - 1][j] + sum[i][j - 1] - sum[i - 1][j - 1];
            sumn[i][j] += sumn[i - 1][j] + sumn[i][j - 1] - sumn[i - 1][j - 1];
            summ[i][j] += summ[i - 1][j] + summ[i][j - 1] - summ[i - 1][j - 1];
        }
    while (q--)
    {
        int x1, y1, x2, y2;
        read(x1, y1, x2, y2);
        printf("%d\n", (sum[x2][y2] - sum[x1 - 1][y2] - sum[x2][y1 - 1] + sum[x1 - 1][y1 - 1]) -
                           (sumn[x2][y2] - sumn[x1][y2] - sumn[x2][y1 - 1] + sumn[x1][y1 - 1]) -
                           (summ[x2][y2] - summ[x1 - 1][y2] - summ[x2][y1] + summ[x1 - 1][y1]));
    }
    return 0;
}