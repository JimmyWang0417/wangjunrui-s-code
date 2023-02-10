#include <bits/extc++.h>
#include <bits/stdc++.h>
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
constexpr int N = 1e5 + 5;

int n;
long long m;

mt19937 rnd((random_device())());

struct point
{
    long long x, y;

    friend inline point operator-(const point &a, const point &b)
    {
        return point{a.x - b.x, a.y - b.y};
    }

    friend inline long long operator*(const point &a, const point &b)
    {
        return a.x * b.y - a.y * b.x;
    }
    friend inline bool operator<(const point &a, const point &b)
    {
        return a.x == b.x ? a.y < b.y : a.x < b.x;
    }
} p[N];

int main()
{
    freopen("triangle.in", "r", stdin);
    freopen("triangle.out", "w", stdout);
    clock_t beg = clock();
    read(n, m);
    m *= 2;

    for (int i = 1; i <= n; ++i)
        read(p[i].x, p[i].y);
    sort(p + 1, p + 1 + n);
    if (n <= 100)
    {
        for (int a = 1; a <= n; ++a)
            for (int b = 1; b <= n; ++b)
                for (int c = 1; c <= n; ++c)
                {
                    long long ans = (p[b] - p[a]) * (p[c] - p[a]);

                    if (ans == m)
                    {
                        printf("Yes\n");

                        printf("%lld %lld\n%lld %lld\n%lld %lld\n",
                               p[a].x, p[a].y, p[b].x, p[b].y, p[c].x, p[c].y);
                        return 0;
                    }
                }
        printf("No\n");
    }

    else
    {
        for (int a = 1; a <= n; ++a)
            for (int b = max(1, a - 10); b <= min(a + 10, n); ++b)
                for (int c = max(1, a - 10); c <= min(a + 10, n); ++c)
                {
                    long long ans = (p[b] - p[a]) * (p[c] - p[a]);

                    if (ans == m)
                    {
                        printf("Yes\n");
                        printf("%lld %lld\n%lld %lld\n%lld %lld\n",
                               p[a].x, p[a].y, p[b].x, p[b].y, p[c].x, p[c].y);
                        return 0;
                    }
                }
        while (clock() - beg <= 900000)
        {
            random_shuffle(p + 1, p + 1 + n);
            for (int a = 1; a <= n; ++a)
                for (int b = max(1, a - 10); b <= min(a + 10, n); ++b)
                    for (int c = max(1, a - 10); c <= min(a + 10, n); ++c)
                    {
                        long long ans = (p[b] - p[a]) * (p[c] - p[a]);

                        if (ans == m)
                        {
                            printf("Yes\n");
                            printf("%lld %lld\n%lld %lld\n%lld %lld\n",
                                   p[a].x, p[a].y, p[b].x, p[b].y, p[c].x, p[c].y);
                            return 0;
                        }
                    }
        }
        printf("No\n");
    }
    return 0;
}
