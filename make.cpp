#include <cstdio>
#include <random>
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
mt19937 rnd((random_device())());
signed main()
{
    freopen("project.out", "w", stdout);
    int n = 20, m = 5000;
    uniform_int_distribution<int> dis(1, n);
    printf("%d %d 0\n", m, n);
    for (int i = 1; i <= m; ++i)
    {
        if (rnd() & 1)
            printf("1 %d %d %d\n", dis(rnd), dis(rnd), dis(rnd));
        else
            printf("2 %d %d\n", dis(rnd), dis(rnd));
    }
    return 0;
}