#include <bits/stdc++.h>
#define int ll
#define lowbit(x) ((x) & (-(x)))
#define re register
#define ll long long
#define ull unsigned long long
#define rep(i, a, b) for (re int i = a; i <= b; ++i)
#define per(i, a, b) for (re int i = a; i >= b; --i)
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
inline void clear(T *array, int l, int r, int val)
{
    memset(&array[l], val, sizeof(T) * (r - l + 1));
}
using namespace std;
const int N = 1e6 + 5;
struct Point
{
    int x, y;
    Point(int _x = 0, int _y = 0) : x(_x), y(_y) {}
    inline Point operator+(const Point &rhs) const
    {
        return Point(x + rhs.x, y + rhs.y);
    }
    inline Point operator-(const Point &rhs) const
    {
        return Point(x - rhs.x, y - rhs.y);
    }
    inline int operator*(const Point &rhs) const
    {
        return x * rhs.y - y * rhs.x;
    }
    inline long double norm()
    {
        return sqrt(x * x + y * y);
    }
    inline bool operator<(const Point &rhs) const
    {
        return x == rhs.x ? y < rhs.y : x < rhs.x;
    }
    inline void print()
    {
        printf("(%d,%d)\n", x, y);
    }
    inline long double slope()
    {
        return (long double)y / (long double)x;
    }
};
set<pair<Point, int>> p;
set<pair<long double, int>> q;
int n, atk;
int S[N];
bool vis[N];
inline void insert(Point val, int id)
{
    //	printf("2begin\n");
    auto l = p.lower_bound(make_pair(val, id)), r = l--;
    if (p.size() == 0)
    {
        p.insert(make_pair(val, id));
    }
    else if (r == p.end())
    {
        //		printf("1\n");
        auto R = q.begin();
        while (l != p.begin())
        {
            auto las = l--;
            if ((l->first - val) * (las->first - val) < 0)
                break;
            if (!vis[R->second])
            {
                vis[R->second] = true;
                q.erase(R++);
            }
            p.erase(las);
        }
        p.insert(make_pair(val, id));
        l = p.find(make_pair(val, id));
        if (l != p.begin())
        {
            --l;
            q.insert(make_pair((val - l->first).slope(), id));
        }
    }
    else if (r == p.begin())
    {
        //		printf("2\n");
        auto L = q.find(make_pair((r->first - l->first).slope(), r->second));
        while (r != p.end())
        {
            auto las = r;
            ++r;
            if (r == p.end())
                break;
            if ((las->first - val) * (r->first - val) < 0)
                break;
            p.erase(las);
            if (!vis[L->second])
            {
                vis[L->second] = true;
                q.erase(L--);
            }
        }
        p.insert(make_pair(val, id));
        r = p.find(make_pair(val, id));
        ++r;
        if (r != p.end())
            q.insert(make_pair((r->first - val).slope(), r->second));
    }
    else
    {
        set<pair<long double, int>>::iterator L = q.find(make_pair((r->first - l->first).slope(), r->second)), R = L;
        ++R;
        if ((l->first - val) * (r->first - val) < 0)
            return;
        //		printf("%lf %d\n",L->first,L->second);
        if (!vis[L->second])
        {
            vis[L->second] = true;
            q.erase(L--);
        }
        while (r != p.end())
        {
            auto las = r;
            ++r;
            if (r == p.end())
                break;
            if ((las->first - val) * (r->first - val) < 0)
                break;
            p.erase(las);
            //			printf("3\n");
            //			printf("%lf %d\n",L->first,L->second);
            if (!vis[L->second])
            {
                vis[L->second] = true;
                q.erase(L--);
            }
            //			printf("4\n");
        }
        while (l != p.begin())
        {
            auto las = l--;
            if ((l->first - val) * (las->first - val) < 0)
                break;
            if (!vis[R->second])
            {
                vis[R->second] = true;
                q.erase(R++);
            }
            p.erase(las);
        }
        p.insert(make_pair(val, id));
        l = r = p.find(make_pair(val, id));
        if (l != p.begin())
        {
            --l;
            q.insert(make_pair((val - l->first).slope(), id));
        }
        ++r;
        if (r != p.end())
            q.insert(make_pair((r->first - val).slope(), r->second));
    }
    //	printf("2end\n");
}
inline int query(int k)
{
    //	printf("1begin\n");
    auto it = q.lower_bound(make_pair((long double)k, -0x3f3f3f3f));
    //	printf("1end\n");
    return it == q.end() ? 1 : it->second;
}
struct node
{
    int a, p;
    inline bool operator<(const node &rhs) const
    {
        return p * rhs.a < rhs.p * a;
    }
} a[N];
int pre[N], suf[N];
signed main()
{
    freopen("fittest.in", "r", stdin);
    freopen("fittest.out", "w", stdout);
    read(n, atk);
    for (int i = 1; i <= n; ++i)
    {
        read(a[i].a, a[i].p);
        a[i].p = (a[i].p + atk - 1) / atk;
    }
    sort(a + 1, a + 1 + n);
    for (int i = 1; i <= n; ++i)
        pre[i] = pre[i - 1] + a[i].p;
    for (int i = n; i >= 1; --i)
        suf[i] = suf[i + 1] + a[i].a;
    for (int i = 1; i <= n; ++i)
        S[i] = (pre[i] - 1) * a[i].a + suf[i + 1] * a[i].p;
    int ans = 0, res = 0;
    //	for(int i=1; i<=n; ++i)
    //		printf("%d %d\n",a[i].a,a[i].p);
    for (int i = 1; i <= n; ++i)
        ans += (pre[i] - 1) * a[i].a;
    //	printf("%d\n",ans);
    //	for(int i=1; i<=n; ++i)
    //		printf("%d ",S[i]);
    //	putchar('\n');
    p.insert(make_pair(Point(0, 0), n + 1));
    for (int i = n; i >= 1; --i)
    {
        //		printf("nmsl\n");
        int j = query(a[i].p);
        //		printf("%d\n",j);
        res = max(res, S[i] + S[j] - a[i].p * a[j].a);
        insert(Point(a[i].a, S[i]), i);
        //		printf("wdnmd\n");
    }
    printf("%lld\n", ans - res);
    return 0;
}
