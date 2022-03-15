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
const int N = 4005;
char S[N], T[N];
class SAM
{
public:
    struct Point
    {
        int ch[26], fa, len;
    } point[N];
    int tot, las;
    inline void init()
    {
        tot = las = 1;
    }
    inline void insert(int c)
    {
        int p = las, np = las = ++tot;
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
    inline void insertstr(char *s)
    {
        init();
        for (int i = 0; s[i]; ++i)
            insert(s[i] - 'a');
    }
} A, C;
class SQAM
{
public:
    int ch[N][26], len;
    inline void insertstr(char *s)
    {
        len = (int)strlen(s);
        for (int i = 0; i < 26; ++i)
            ch[len][i] = len + 1;
        for (int i = (int)strlen(s) - 1; i >= 0; --i)
        {
            memcpy(ch[i], ch[i + 1], sizeof(ch[i]));
            ch[i][s[i] - 'a'] = i + 1;
        }
    }
} B, D;
struct node
{
    int x, y, l;
    node(int _x = 0, int _y = 0, int _l = 0) : x(_x), y(_y), l(_l) {}
};
bool vis[N][N];
int dis[N][N];
inline int solve1()
{
    memset(vis, 0, sizeof(vis));
    queue<node> q;
    q.push(node(1, 1, 0));
    while (!q.empty())
    {
        int u = q.front().x, v = q.front().y, l = q.front().l;
        q.pop();
        if (!v)
            return l;
        for (int c = 0; c < 26; ++c)
        {
            int x = A.point[u].ch[c], y = C.point[v].ch[c];
            if (x && !vis[x][y])
            {
                vis[x][y] = true;
                q.push(node(x, y, l + 1));
            }
        }
    }
    return -1;
}
inline int solve2()
{
    memset(vis, 0, sizeof(vis));
    queue<node> q;
    q.push(node(1, 0, 0));
    while (!q.empty())
    {
        int u = q.front().x, v = q.front().y, l = q.front().l;
        q.pop();
        if (v > D.len)
            return l;
        for (int c = 0; c < 26; ++c)
        {
            int x = A.point[u].ch[c], y = D.ch[v][c];
            if (x && !vis[x][y])
            {
                vis[x][y] = true;
                q.push(node(x, y, l + 1));
            }
        }
    }
    return -1;
}
inline int solve3()
{
    memset(vis, 0, sizeof(vis));
    queue<node> q;
    q.push(node(0, 1, 0));
    while (!q.empty())
    {
        int u = q.front().x, v = q.front().y, l = q.front().l;
        q.pop();
        if (!v)
            return l;
        for (int c = 0; c < 26; ++c)
        {
            int x = B.ch[u][c], y = C.point[v].ch[c];
            if (x <= B.len && !vis[x][y])
            {
                vis[x][y] = true;
                q.push(node(x, y, l + 1));
            }
        }
    }
    return -1;
}
inline int solve4()
{
    memset(vis, 0, sizeof(vis));
    queue<node> q;
    q.push(node(0, 0, 0));
    while (!q.empty())
    {
        int u = q.front().x, v = q.front().y, l = q.front().l;
        q.pop();
        if (v > D.len)
            return l;
        for (int c = 0; c < 26; ++c)
        {
            int x = B.ch[u][c], y = D.ch[v][c];
            if (x <= B.len && !vis[x][y])
            {
                vis[x][y] = true;
                q.push(node(x, y, l + 1));
            }
        }
    }
    return -1;
}
signed main()
{
    scanf("%s%s", S, T);
    A.insertstr(S), B.insertstr(S);
    C.insertstr(T), D.insertstr(T);
    printf("%d\n%d\n%d\n%d\n", solve1(), solve2(), solve3(), solve4());
    return 0;
}