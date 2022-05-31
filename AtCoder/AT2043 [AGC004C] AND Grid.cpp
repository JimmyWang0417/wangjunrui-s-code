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
constexpr int N = 505;
int n, m;
char A[N][N], B[N][N];
signed main()
{
    read(n, m);
    for (int i = 1; i <= n; ++i)
    {
        scanf("%s", A[i] + 1);
        for (int j = 1; j <= m; ++j)
            B[i][j] = A[i][j];
    }
    for (int i = 1; i <= n; ++i)
        A[i][1] = B[i][m] = '#';
    for (int i = 1; i <= n; i += 2)
        for (int j = 2; j < m; ++j)
            A[i][j] = '#';
    for (int i = 2; i <= n; i += 2)
        for (int j = 2; j < m; ++j)
            B[i][j] = '#';
    for (int i = 1; i <= n; ++i)
        printf("%s\n", A[i] + 1);
    putchar('\n');
    for (int i = 1; i <= n; ++i)
        printf("%s\n", B[i] + 1);
    putchar('\n');
    return 0;
}