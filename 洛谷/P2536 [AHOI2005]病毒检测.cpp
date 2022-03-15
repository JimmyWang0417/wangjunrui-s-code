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
const int N = 505;
int n, m;
char s0[N], str[N];
inline int calc(char c)
{
    return c == 'A' ? 0 : (c == 'C' ? 1 : (c == 'T' ? 2 : 3));
}
int ch[N * N][4], tot;
int id[N];
inline int insert(char *s)
{
    int u = 0;
    for (int i = 0; s[i]; ++i)
    {
        int c = calc(s[i]);
        if (!ch[u][c])
            ch[u][c] = ++tot;
        u = ch[u][c];
    }
    return u;
}
bool bo[N][N * N];
signed main()
{
    scanf("%s", s0);
    read(n);
    m = strlen(s0);
    for (int i = 0; i < n; ++i)
    {
        scanf("%s", str);
        id[i] = insert(str);
    }
    bo[0][0] = true;
    for (int i = 0; i < m; ++i)
    {
        if (s0[i] == '*')
        {
            for (int j = 0; j <= tot; ++j)
                if (bo[i][j])
                {
                    for (int c = 0; c < 4; ++c)
                        if (ch[j][c])
                            bo[i][ch[j][c]] = true;
                    bo[i + 1][j] = true;
                }
        }
        else if (s0[i] == '?')
        {
            for (int j = 0; j <= tot; ++j)
                if (bo[i][j])
                {
                    for (int c = 0; c < 4; ++c)
                        if (ch[j][c])
                            bo[i + 1][ch[j][c]] = true;
                }
        }
        else
        {
            for (int j = 0, c = calc(s0[i]); j <= tot; ++j)
                if (bo[i][j])
                {
                    if (ch[j][c])
                        bo[i + 1][ch[j][c]] = true;
                }
        }
    }
    int res = 0;
    for (int i = 0; i < n; ++i)
    {
        if (!bo[m][id[i]])
            ++res;
    }
    printf("%d\n", res);
    return 0;
}