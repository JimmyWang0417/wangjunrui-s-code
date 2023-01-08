/**
 *    unicode: UTF-8
 *    name:    UVA1630 串折叠 Folding
 *    author:  wangjunrui
 *    created: 2022.07.28 周四 08:19:46 (Asia/Shanghai)
 **/
#include <cstdio>
#include <cstring>
#include <string>
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
constexpr int N = 105;
int n;
char str[N];
int f[N][N];
string g[N][N];
signed main()
{
    while (scanf("%s", str + 1) != EOF)
    {
        n = (int)strlen(str + 1);
        memset(f, 0x3f, sizeof(f));
        for (int i = 1; i <= n; ++i)
        {
            f[i][i] = 1;
            g[i][i] = str[i];
        }
        for (int len = 2; len <= n; ++len)
        {
            for (int l = 1; l + len - 1 <= n; ++l)
            {
                int r = l + len - 1;
                int where = 0;
                bool flag = false;
                for (int i = l; i < r; ++i)
                {
                    if (len % (i - l + 1) == 0)
                    {
                        int qwq = len / (i - l + 1);
                        int now = f[l][i] + (qwq >= 100 ? 3 : (qwq >= 10 ? 2 : 1)) + 2;
                        if (now < f[l][r] && strncmp(str + l, str + i + 1, len - (i - l + 1)) == 0)
                        {
                            f[l][r] = now;
                            where = i;
                            flag = true;
                        }
                    }
                    if (f[l][r] > f[l][i] + f[i + 1][r])
                    {
                        f[l][r] = f[l][i] + f[i + 1][r];
                        where = i;
                        flag = false;
                    }
                }
                if (flag)
                    g[l][r] = to_string(len / (where - l + 1)) + "(" + g[l][where] + ")";
                else
                    g[l][r] = g[l][where] + g[where + 1][r];
            }
        }
        printf("%s\n", g[1][n].c_str());
    }
    return 0;
}