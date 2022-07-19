/**
 *    unicode: UTF-8
 *    name:    CF487D Conveyor Belts
 *    author:  wangjunrui
 *    created: 2022.07.09 周六 20:30:55 (Asia/Shanghai)
 **/
#include <algorithm>
#include <cstdio>
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
constexpr int N = 1e5 + 5, M = 15;
int n, m, q;
int block, num, belong[N], L[N], R[N];
char str[N][M];
int ed[N][M];
pair<int, int> blockend[N][M];
inline void build(int rt)
{
    for (int i = 1; i <= m; ++i)
        if (str[rt][i] == '^')
            ed[rt][i] = i;
        else if (str[rt][i] == '<')
        {
            if (i > 1 && str[rt][i - 1] == '>')
                ed[rt][i] = -1;
            else
                ed[rt][i] = ed[rt][i - 1];
        }
    for (int i = m; i >= 1; --i)
        if (str[rt][i] == '>')
        {
            if (i < m && str[rt][i + 1] == '<')
                ed[rt][i] = -1;
            else
                ed[rt][i] = ed[rt][i + 1];
        }
}
inline void update(int rt)
{
    if (rt == L[belong[rt]])
    {
        for (int i = 0; i <= m + 1; ++i)
            if (ed[rt][i] == -1)
                blockend[rt][i] = make_pair(-1, -1);
            else
                blockend[rt][i] = make_pair(rt, ed[rt][i]);
    }
    else
    {
        for (int i = 0; i <= m + 1; ++i)
            if (str[rt][i] == '^')
                blockend[rt][i] = blockend[rt - 1][i];
            else if (ed[rt][i] == -1)
                blockend[rt][i] = make_pair(-1, -1);
            else if (ed[rt][i] == i)
                blockend[rt][i] = make_pair(rt, i);
        for (int i = 1; i <= m; ++i)
            if (ed[rt][i] != -1 && ed[rt][i] != i)
                blockend[rt][i] = blockend[rt][ed[rt][i]];
    }
}
signed main()
{
    read(n, m, q);
    for (int i = 1; i <= n; ++i)
        scanf("%s", str[i] + 1);
    block = (int)__builtin_sqrt(n);
    num = (n - 1) / block + 1;
    for (int i = 1; i <= num; ++i)
    {
        L[i] = R[i - 1] + 1;
        R[i] = min(R[i - 1] + block, n);
        for (int j = L[i]; j <= R[i]; ++j)
            belong[j] = i;
    }
    for (int i = 1; i <= n; ++i)
    {
        ed[i][m + 1] = m + 1;
        build(i);
        update(i);
    }
    while (q--)
    {
        static char opt[10];
        scanf("%s", opt);
        int x, y;
        read(x, y);
        if (opt[0] == 'A')
        {
            while (x && y)
            {
                pair<int, int> qwq = blockend[x][y];
                x = qwq.first, y = qwq.second;
                if (x < 1 || str[x][y] != '^')
                    break;
                --x;
            }
            if (x <= 0)
                printf("%d %d\n", x, y);
            else
                printf("%d %d\n", x, ed[x][y]);
        }
        else
        {
            scanf("%s", opt);
            str[x][y] = opt[0];
            build(x);
            for (int i = x; i <= R[belong[x]]; ++i)
                update(i);
        }
    }
    return 0;
}