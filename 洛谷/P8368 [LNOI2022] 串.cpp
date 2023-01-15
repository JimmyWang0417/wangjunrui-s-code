/**
 *    unicode: UTF-8
 *    name:    P8368 [LNOI2022] 串
 *    author:  whitepaperdog (蒟蒻wjr)
 *    located: Changle District, Fuzhou City, Fujian Province, China
 *    created: 2022.08.28 周日 10:23:39 (Asia/Shanghai)
 **/
#include <cstdio>
#include <cstring>
#define ll long long
#define lll __int128
#define ull unsigned ll
#define lowbit(x) (x & (-x))
inline void read(char *x)
{
    char s = (char)getchar_unlocked();
    int len = 0;
    while (!(s >= 'a' && s <= 'z'))
        s = (char)getchar_unlocked();
    while (s >= 'a' && s <= 'z')
    {
        x[len++] = s;
        s = (char)getchar_unlocked();
    }
    x[len] = '\0';
}
template <typename T>
inline void read(T &x)
{
    x = 0;
    char s = (char)getchar_unlocked();
    bool f = false;
    while (!(s >= '0' && s <= '9'))
    {
        if (s == '-')
            f = true;
        s = (char)getchar_unlocked();
    }
    while (s >= '0' && s <= '9')
    {
        x = (x << 1) + (x << 3) + s - '0';
        s = (char)getchar_unlocked();
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
constexpr int N = 5e5 + 5;
namespace SAM
{
    struct Point
    {
        int ch[26];
        int fa;
        int len;
    } point[N * 2];
    int tot, las;
    int minpos[N * 2], size[N * 2];
    inline void insert(int c, int id)
    {
        int p = las, np = las = ++tot;
        size[np] = 1;
        minpos[np] = id;
        point[np].len = point[p].len + 1;
        for (; p && !point[p].ch[c]; p = point[p].fa)
            point[p].ch[c] = np;
        if (!p)
            point[np].fa = 1;
        else
        {
            int q = point[p].ch[c];
            if (point[q].len == point[p].len + 1)
                point[np].fa = q;
            else
            {
                int nq = ++tot;
                minpos[nq] = 0x7fffffff;
                point[nq] = point[q];
                point[q].fa = point[np].fa = nq;
                point[nq].len = point[p].len + 1;
                for (; p && point[p].ch[c] == q; p = point[p].fa)
                    point[p].ch[c] = nq;
            }
        }
    }
    int ws[N];
    int q[N * 2];
    inline void init(char *str)
    {
        tot = las = 1;
        for (int i = 1; str[i]; ++i)
            insert(str[i] - 'a', i);
    }
    inline int solve(int n)
    {
        for (int i = 1; i <= tot; ++i)
            ++ws[point[i].len];
        for (int i = 1; i <= n; ++i)
            ws[i] += ws[i - 1];
        for (int i = tot; i >= 1; --i)
            q[ws[point[i].len]--] = i;
        int res = n / 2;
        for (int i = tot; i >= 2; --i)
        {
            int u = q[i], fa = point[u].fa;
            if (size[u] > 1)
                ckmax(res, (n - minpos[u]) / 2 + point[u].len);
            size[fa] += size[u];
            ckmin(minpos[fa], minpos[u]);
        }
        memset(ws, 0, sizeof(int) * (n + 1));
        return res;
    }
    inline void clear()
    {
        memset(point + 1, 0, sizeof(Point) * tot);
        memset(size + 1, 0, sizeof(int) * tot);
    }
}
int n;
char str[N];
signed main()
{
    int T = 1;
    read(T);
    while (T--)
    {
        read(str + 1);
        SAM::init(str);
        printf("%d\n", SAM::solve((int)strlen(str + 1)));
        SAM::clear();
    }
    return 0;
}