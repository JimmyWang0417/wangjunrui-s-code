#include <bits/stdc++.h>
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
const int MaxN = 2e3 + 5;
const int MaxM = 3e6 + 5;
struct point
{
    int x, y;
    point() {}
    point(int _x, int _y) : x(_x), y(_y) {}
    inline point operator+(point rhs) const
    {
        return point(x + rhs.x, y + rhs.y);
    }
    inline point operator-(point rhs) const
    {
        return point(x - rhs.x, y - rhs.y);
    }
    inline bool operator<(point rhs) const
    {
        return x < rhs.x || (x == rhs.x && y < rhs.y);
    }
    inline bool operator!=(point rhs) const
    {
        return x != rhs.x || y != rhs.y;
    }
    inline ll operator*(point rhs) const
    {
        return 1LL * x * rhs.y - 1LL * y * rhs.x;
    }

    inline void scan()
    {
        read(x, y);
    }
    inline point rotate() const
    {
        return point(-y, x);
    }
    inline ll norm() const
    {
        return 1LL * x * x + 1LL * y * y;
    }
    inline friend ll dot(point lhs, point rhs)
    {
        return 1LL * lhs.x * rhs.x + 1LL * lhs.y * rhs.y;
    }

    inline void simplify()
    {
        int d = __gcd(abs(x), abs(y));
        x /= d, y /= d;
        if (x < 0 || (!x && y < 0))
            x = -x, y = -y;
    }
} a[MaxN];

inline bool where(point a)
{
    return a.y < 0 || (a.y == 0 && a.x < 0);
}

inline bool cmp_angle(point a, point b)
{
    if (where(a) != where(b))
        return where(a) < where(b);
    else
        return a * b > 0;
}

struct seg
{
    point st, dir;
    seg() {}
    seg(point _st, point _dir) : st(_st), dir(_dir) { dir.simplify(); }

    inline bool operator<(const seg &rhs) const
    {
        if (dir != rhs.dir)
            return dir < rhs.dir;
        else if (st * dir != rhs.st * dir)
            return st * dir < rhs.st * dir;
        else
            return st < rhs.st;
    }
} s[MaxM];

int n, m;
ll cur_S;

inline int find(point a, point b)
{
    if (b < a)
        swap(a, b);

    seg t1(a + a, b - a), t2(b + b, b - a);
    int l = upper_bound(s + 1, s + m + 1, t1) - s;
    int r = lower_bound(s + 1, s + m + 1, t2) - s;
    return max(0, r - l);
}

signed main()
{
#ifdef orzczk
    freopen("fish.in", "r", stdin);
    freopen("fish.out", "w", stdout);
#endif

    read(n);
    for (int i = 1; i <= n; ++i)
        a[i].scan();
    for (int i = 1; i < n; ++i)
        for (int j = i + 1; j <= n; ++j)
            s[++m] = seg(a[i] + a[j], (a[j] - a[i]).rotate());
    sort(s + 1, s + m + 1);

    ll ans = 0;
    for (int D = 1; D <= n; ++D)
    {
        int cnt = 0;
        static point b[MaxN];
        for (int i = 1; i <= n; ++i)
            if (i != D)
                b[++cnt] = point(a[i] - a[D]);
        sort(b + 1, b + cnt + 1, cmp_angle);
        for (int i = 1; i <= cnt; ++i)
            b[cnt + i] = b[i];

        unordered_map<ll, int> S;
        S.clear();
        cur_S = 0;

        int l = 1, r = 1; //[l, r)
        for (int A = 1; A <= cnt; ++A)
        {
            while (b[A] * b[r] > 0 || (b[A] * b[r] == 0 && r <= cnt) || dot(b[A], b[r]) < 0)
                cur_S += S[b[r++].norm()]++;
            while (l < r && dot(b[l], b[A]) >= 0)
                cur_S -= --S[b[l++].norm()];

            if (cur_S)
                ans += 1LL * cur_S * find(a[D], a[D] + b[A]);
        }
    }
    printf("%lld\n", ans * 4);
    return 0;
}