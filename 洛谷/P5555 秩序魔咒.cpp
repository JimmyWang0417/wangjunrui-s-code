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
const int N = 260817 + 5;
class PAM
{
public:
    char str[N];
    struct Point
    {
        int ch[26];
        int len, fa;
    } point[N];
    int tot = 1, las = 0;
    inline int getfa(int x, int where)
    {
        while (str[where] != str[where - point[x].len - 1])
            x = point[x].fa;
        return x;
    }
    inline void insert(int c, int where)
    {
        int cur = getfa(las, where);
        int now = point[cur].ch[c];
        if (!now)
        {
            now = ++tot;
            point[now].len = point[cur].len + 2;
            point[now].fa = point[getfa(point[cur].fa, where)].ch[c];
            point[cur].ch[c] = now;
        }
        las = now;
    }
    inline void build()
    {
        point[0].fa = 1;
        point[1].len = -1;
        scanf("%s", str + 1);
        for (int i = 1; str[i]; ++i)
            insert(str[i] - 'a', i);
    }
} S, T;
char str[N];
int n, m;
int answer = -114514, cnt = -1919810;
inline void dfs(int Su, int Tu)
{
    if (S.point[Su].len > answer)
    {
        answer = S.point[Su].len;
        cnt = 1;
    }
    else if (S.point[Su].len == answer)
        ++cnt;
    for (int i = 0; i < 26; ++i)
        if (S.point[Su].ch[i] && T.point[Tu].ch[i])
            dfs(S.point[Su].ch[i], T.point[Tu].ch[i]);
}
signed main()
{
    read(n, m);
    S.build(), T.build();
    dfs(0, 0), dfs(1, 1);
    printf("%d %d\n", answer, cnt);
    return 0;
}