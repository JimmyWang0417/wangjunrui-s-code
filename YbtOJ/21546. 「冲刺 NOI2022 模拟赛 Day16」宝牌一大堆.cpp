#include <cstdio>
#include <cstring>
#include <queue>
#define int ll
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
constexpr int N = 105;
int n, ans;
int a[N], b[N];
int C[N][N];
int b1[N] = {0, 1, 9, 10, 18, 19, 27, 28, 29, 30, 31, 32, 33, 34};
int b3[N] = {0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1};
int f[40][5][2][5][5][5];
inline void work1()
{
    int maxx = 0;
    for (int i = 1; i <= 13; i++)
    {
        int res = 13;
        for (int j = 1; j <= 13; j++)
        {
            int x = b1[j];
            res = res * C[a[x]][1 + (i == j)] * b[x] * (i == j ? b[x] : 1);
        }
        ckmax(maxx, res);
    }
    ckmax(ans, maxx);
}
inline void work2()
{
    priority_queue<int> q;
    int maxx = 7;
    for (int i = 1; i <= 34; i++)
    {
        q.push(C[a[i]][2] * b[i] * b[i]);
    }
    for (int i = 1; i <= 7; i++)
    {
        int x = q.top();
        q.pop();
        maxx *= x;
    }
    ckmax(ans, maxx);
}
inline void work3()
{
    memset(f, 0, sizeof(f));
    f[1][0][0][0][0][0] = 1;
    for (int i = 1; i <= 34; i++)
        for (int j = 0; j <= 4; j++)
            for (int k = 0; k <= 4; k++)
                for (int l = 0; l <= 2; l++)
                    for (int m = 0; m <= 2; m++)
                    {
                        if (!f[i][j][0][k][l][m] && !f[i][j][1][k][l][m])
                            continue;
                        if (a[i] - k >= 2)
                            ckmax(f[i][j][1][k + 2][l][m], f[i][j][0][k][l][m] / C[a[i]][k] * C[a[i]][k + 2] * b[i] * b[i]);
                        if (j < 4)
                        {
                            if (a[i] - k >= 3)
                                ckmax(f[i][j + 1][0][k + 3][l][m], f[i][j][0][k][l][m] / C[a[i]][k] * C[a[i]][k + 3] * b[i] * b[i] * b[i]),
                                    ckmax(f[i][j + 1][1][k + 3][l][m], f[i][j][1][k][l][m] / C[a[i]][k] * C[a[i]][k + 3] * b[i] * b[i] * b[i]);

                            if (!b3[i] && a[i] - k >= 1 && a[i + 1] - l >= 1 && a[i + 2] - m >= 1 && l != 2 && m != 2)
                                ckmax(f[i][j + 1][0][k + 1][l + 1][m + 1], f[i][j][0][k][l][m] / C[a[i]][k] * C[a[i]][k + 1] * b[i] / C[a[i + 1]][l] * C[a[i + 1]][l + 1] * b[i + 1] / C[a[i + 2]][m] * C[a[i + 2]][m + 1] * b[i + 2]),
                                    ckmax(f[i][j + 1][1][k + 1][l + 1][m + 1], f[i][j][1][k][l][m] / C[a[i]][k] * C[a[i]][k + 1] * b[i] / C[a[i + 1]][l] * C[a[i + 1]][l + 1] * b[i + 1] / C[a[i + 2]][m] * C[a[i + 2]][m + 1] * b[i + 2]);
                        }
                        ckmax(f[i + 1][j][0][l][m][0], f[i][j][0][k][l][m]);
                        ckmax(f[i + 1][j][1][l][m][0], f[i][j][1][k][l][m]);

                        if (j == 4)
                            ckmax(ans, f[i][j][1][k][l][m]);
                    }
}
signed main()
{
#ifdef ONLINE_JUDGE
    freopen("b.in","r",stdin);
    freopen("b.out","w",stdout);
#endif
    int T;
    read(T);
    while (T--)
    {
        ans = 0;
        memset(C, 0, sizeof(C));
        memset(a, 0, sizeof(a));
        memset(b, 0, sizeof(b));
        for (int i = 0; i <= 4; i++)
            for (int j = 0; j <= 4; j++)
                if (j == 0)
                    C[i][j] = 1;
                else
                    C[i][j] = C[i - 1][j] + C[i - 1][j - 1];
        for (int i = 1; i <= 34; i++)
            a[i] = 4, b[i] = 1;
        while (1)
        {
            char s[10];
            scanf("%s", s);
            if (s[0] == '0')
                break;
            if (s[1] == 'm')
                a[s[0] - '0']--;
            if (s[1] == 'p')
                a[s[0] - '0' + 9]--;
            if (s[1] == 's')
                a[s[0] - '0' + 18]--;

            if (s[0] == 'E')
                a[28]--;
            if (s[0] == 'S')
                a[29]--;
            if (s[0] == 'W')
                a[30]--;
            if (s[0] == 'N')
                a[31]--;

            if (s[0] == 'Z')
                a[32]--;
            if (s[0] == 'B')
                a[33]--;
            if (s[0] == 'F')
                a[34]--;
        }
        while (1)
        {
            char s[10];
            scanf("%s", s);
            if (s[0] == '0')
                break;
            if (s[1] == 'm')
                b[s[0] - '0'] = 2;
            if (s[1] == 'p')
                b[s[0] - '0' + 9] = 2;
            if (s[1] == 's')
                b[s[0] - '0' + 18] = 2;

            if (s[0] == 'E')
                b[28] = 2;
            if (s[0] == 'S')
                b[29] = 2;
            if (s[0] == 'W')
                b[30] = 2;
            if (s[0] == 'N')
                b[31] = 2;

            if (s[0] == 'Z')
                b[32] = 2;
            if (s[0] == 'B')
                b[33] = 2;
            if (s[0] == 'F')
                b[34] = 2;
        }
        work1();
        work2();
        work3();
        printf("%lld\n", ans);
    }
}
