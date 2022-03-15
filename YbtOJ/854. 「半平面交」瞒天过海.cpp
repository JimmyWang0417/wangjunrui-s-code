#include <bits/stdc++.h>
#include <bits/extc++.h>
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
constexpr int N = 605, M = N * N;
constexpr double eps = 1e-8;
struct Edge
{
    int next, to;
} edge[M];
int head[N], num_edge;
inline void add_edge(int from, int to)
{
    edge[++num_edge].next = head[from];
    edge[num_edge].to = to;
    head[from] = num_edge;
}
struct Point
{
    double x, y;
    Point(double _x = 0, double _y = 0) : x(_x), y(_y) {}
    inline Point operator+(const Point &rhs) const
    {
        return Point(x + rhs.x, y + rhs.y);
    }
    inline Point operator-(const Point &rhs) const
    {
        return Point(x - rhs.x, y - rhs.y);
    }
    inline Point operator*(const double &rhs) const
    {
        return Point(x * rhs, y * rhs);
    }
    inline Point operator/(const double &rhs) const
    {
        return Point(x / rhs, y / rhs);
    }
    inline double operator*(const Point &rhs) const
    {
        return x * rhs.x + y * rhs.y;
    }
    inline double operator^(const Point &rhs) const
    {
        return x * rhs.y - rhs.x * y;
    }
    inline double norm() const
    {
        return sqrt(x * x + y * y);
    }
    inline Point calc()
    {
        return Point(-y, x);
    }
} point[N];
struct Line
{
    Point x, y;
    double theta;
    int id;
    Line(Point _x = Point(), Point _y = Point(), int _id = 0) : x(_x), y(_y), id(_id)
    {
        theta = atan2((y - x).y, (y - x).x);
    }
    inline friend Point intersection(const Line &x, const Line &y)
    {
        const Point &a = x.x, &b = x.y, &c = y.x, &d = y.y;
        double s1 = (c - a) ^ (d - a), s2 = (d - b) ^ (c - b);
        Point add = (b - a) * (s1 / (s1 + s2));
        return a + add;
    }
    inline Point calc()
    {
        return y - x;
    }
    inline bool operator<(const Line &rhs) const
    {
        if (fabs(theta - rhs.theta) > eps)
            return theta < rhs.theta;
        return ((y - x) ^ (rhs.y - x)) < 0;
    }
} a[M], line[M], q[M];
inline bool check(Line aa, Line b, Line c)
{
    Point p = intersection(aa, b);
    return (c.calc() ^ (p - c.x)) < 0;
}
inline void solve(int u, int tot)
{
    sort(line + 1, line + tot + 1);
    int cnt = 0;
    a[cnt = 1] = line[1];
    for (int i = 2; i <= tot; ++i)
        if (a[cnt].theta != line[i].theta)
            a[++cnt] = line[i];
    int hea = 1, tail = 0;
    for (int i = 1; i <= cnt; ++i)
    {
        while (hea < tail && check(q[tail - 1], q[tail], a[i]))
            --tail;
        while (hea < tail && check(q[hea], q[hea + 1], a[i]))
            ++hea;
        q[++tail] = a[i];
    }
    while (hea < tail && check(q[tail - 1], q[tail], q[hea]))
        --tail;
    while (hea < tail && check(q[hea], q[hea + 1], q[tail]))
        ++hea;
    for (int i = hea; i <= tail; ++i)
        add_edge(q[i].id, u);
}
bool vis[N];
int need;
inline int bfs()
{
    queue<pair<int, int>> que;
    que.push(make_pair(0, 0));
    while (!que.empty())
    {
        int u = que.front().first, dis = que.front().second;
        que.pop();
        if (u == need)
            return dis;
        for (int i = head[u]; i; i = edge[i].next)
        {
            int &v = edge[i].to;
            if (!vis[v])
            {
                que.push(make_pair(v, dis + 1));
                vis[v] = true;
            }
        }
    }
    return 0;
}
int n, w, h;
signed main()
{
#ifdef ONLINE_JUDGE
    freopen("sea.in","r",stdin);
    freopen("sea.out","w",stdout);
#endif
    read(n, w, h);
    for (int i = 0; i <= n; ++i)
        scanf("%lf%lf", &point[i].x, &point[i].y);
    for (int i = 1; i <= n; ++i)
    {
        int tot = 0;
        line[++tot] = Line(Point(0, 0), Point(w, 0));
        line[++tot] = Line(Point(w, 0), Point(w, h));
        line[++tot] = Line(Point(w, h), Point(0, h));
        line[++tot] = Line(Point(0, h), Point(0, 0));
        for (int j = 1; j <= n; ++j)
        {
            if (i == j)
                continue;
            Point x = (point[j] - point[i]).calc(), y = (point[i] + point[j]) / 2;
            line[++tot] = Line(y, x + y, j);
        }
        solve(i, tot);
    }
    need = 1;
    for (int i = 2; i <= n; ++i)
        if ((point[0] - point[need]).norm() > (point[0] - point[i]).norm())
            need = i;
    printf("%d\n", bfs());
    return 0;
}
