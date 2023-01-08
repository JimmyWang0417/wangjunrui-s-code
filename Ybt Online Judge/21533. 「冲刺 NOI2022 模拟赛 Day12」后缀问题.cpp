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
constexpr int N = 4e5 + 5;
int n;
char str[N];
struct Edge
{
    int next, to;
} edge[N * 2];
int head[N], num_edge;
inline void add_edge(int from, int to)
{
    edge[++num_edge].next = head[from];
    edge[num_edge].to = to;
    head[from] = num_edge;
}
struct Point
{
    int ch[26], fa;
    int len;
} point[N];
int las = 1, tot = 1;
bool exist[N];
inline void init()
{
    memset(head, 0, sizeof(head));
    memset(point, 0, sizeof(Point) * (tot + 1));
    memset(exist, 0, sizeof(exist));
    las = tot = 1;
    num_edge = 0;
    point[0].len = -1;
}
inline void insert(int c)
{
    int p = las, np = las = ++tot;
    exist[np] = true;
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
            point[nq] = point[q];
            point[nq].len = point[p].len + 1;
            point[np].fa = point[q].fa = nq;
            for (; p && point[p].ch[c] == q; p = point[p].fa)
                point[p].ch[c] = nq;
        }
    }
}
inline double calc(int u)
{
    if (exist[u])
    {
        return point[u].len;
    }
    double sum = 0;
    for (int i = head[u]; i; i = edge[i].next)
    {
        int &v = edge[i].to;
        sum += 1 / (calc(v) - point[u].len);
    }
    return 1 / sum + point[u].len;
}
inline void work()
{
    init();
    scanf("%s", str + 1);
    n = (int)strlen(str + 1);
    for (int i = n; i >= 1; --i)
        insert(str[i] - 'a');
    for (int i = 2; i <= tot; ++i)
        add_edge(point[i].fa, i);
    printf("%.11lf\n", calc(1));
}
signed main()
{
#ifdef ONLINE_JUDGE
    freopen("suffix.in", "r", stdin);
    freopen("suffix.out", "w", stdout);
#endif
    int T;
    read(T);
    while (T--)
        work();
    return 0;
}
