#include <algorithm>
#include <cstdio>
#include <vector>
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
constexpr int N = 5e5 + 10;
struct Point
{
    int fa, len;
    int half;
    int ans, cnt;
    int ch[26];
} point[N];
int las = 1, tot = 1;
int len;
char str[N];
inline int getfa(int x)
{
    while (str[len] != str[len - point[x].len - 1])
        x = point[x].fa;
    return x;
}
inline int gethalf(int x, int l)
{
    while (point[x].len + 2 > l || str[len] != str[len - point[x].len - 1])
        x = point[x].fa;
    return x;
}
inline int insert(int c)
{
    int cur = getfa(las);
    int now = point[cur].ch[c];
    if (!now)
    {
        now = ++tot;
        point[now].len = point[cur].len + 2;
        point[now].fa = point[getfa(point[cur].fa)].ch[c];
        if (point[now].len < 2)
            point[now].half = 0;
        else
            point[now].half = point[gethalf(point[cur].half, point[now].len / 2)].ch[c];
        if (point[point[now].half].len % 2 == 0 && point[point[now].half].len * 2 == point[now].len)
        {
            point[now].ans = point[now].len;
            point[now].cnt = point[point[now].fa].cnt + 1;
        }
        else
        {
            point[now].ans = point[point[now].fa].ans;
            point[now].cnt = point[point[now].fa].cnt;
        }
        point[cur].ch[c] = now;
    }
    return las = now;
}
pair<int, int> a[N];
int cnt;
signed main()
{
#ifdef ONLINE_JUDGE
    freopen("giveup.in", "r", stdin);
    freopen("giveup.out", "w", stdout);
#endif
    point[1].len = -1;
    point[0].fa = 1;
    scanf("%s", str + 1);
    ll answer = 0;
    for (len = 1; str[len]; ++len)
    {
        int u = insert(str[len] - 'a');
        answer += point[u].cnt + 1;
        if (point[u].ans)
            a[++cnt] = make_pair(len - point[u].ans + 1, len);
        else
            a[++cnt] = make_pair(len, len);
    }
    --len;
    int type;
    read(type);
    if (type & 1)
        printf("%lld ", answer);
    sort(a + 1, a + 1 + cnt);
    int id = 1, mx = 0;
    int res = 0;
    for (int r = 1; r <= len; r++)
    {
        while (a[id].first <= r && id <= cnt)
            mx = max(mx, a[id].second), ++id;
        r = mx, ++res;
    }
    if (type & 2)
        printf("%d\n", res);
    return 0;
}