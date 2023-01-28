#include <algorithm>
#include <cstdio>
#include <set>
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
constexpr int N = 6e5 + 5;
int n, m;
struct Point
{
    int x, y, t;
    inline bool operator<(const Point &rhs) const
    {
        return y == rhs.y ? t > rhs.t : y > rhs.y;
    }
} point[N];
set<pair<int, int>> se;
int fa[N], size[N];
inline int find(int x)
{
    return !fa[x] ? x : fa[x] = find(fa[x]);
}
inline void unionn(int x, int y)
{
    x = find(x), y = find(y);
    if (x == y)
        return;
    size[y] += size[x];
    fa[x] = y;
}
int father[N];
int answer[N];
signed main()
{
#ifdef ONLINE_JUDGE
    freopen("monkey.in", "r", stdin);
    freopen("monkey.out", "w", stdout);
#endif
    read(n);
    for (int i = 1; i <= n; ++i)
        read(point[i].x, point[i].y);
    read(m);
    for (int i = 1; i <= m; ++i)
    {
        read(point[i + n].x, point[i + n].y);
        point[i + n].t = i;
    }
    sort(point + 1, point + 1 + n + m);
    for (int i = 1; i <= n + m; ++i)
    {
        if (!point[i].t)
        {
            auto it = se.lower_bound({point[i].x, 0});
            if (it != se.end())
                ++size[it->second];
        }
        else
        {
            auto it = se.emplace(point[i].x, point[i].t).first;
            if (++it != se.end())
                father[point[i].t] = it->second;
            while (1)
            {
                it = se.lower_bound({point[i].x, point[i].t});
                if (it == se.begin())
                    break;
                --it;
                if (it->second > point[i].t)
                    se.erase(it);
                else
                    break;
            }
        }
    }
    for (int i = m; i >= 1; --i)
    {
        answer[i] = size[find(i)];
        if (father[i])
            unionn(i, father[i]);
    }
    for (int i = 1; i <= m; ++i)
        printf("%d\n", answer[i]);
    return 0;
}