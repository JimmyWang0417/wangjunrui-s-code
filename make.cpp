#include <cstdio>
#include <random>
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
constexpr int N = 1e5 + 5;
random_device rd;
mt19937 rnd(rd());
int a[N];
signed main()
{
    freopen("ans.in", "w", stdout);
    int n = 5000;
    printf("%d\n", n);
    uniform_int_distribution<int> dis(1, n);
    for (int i = 1; i <= n; ++i)
        a[i] = i;
    for (int i = 1; i <= 1e7; ++i)
        swap(a[dis(rnd)], a[dis(rnd)]);
    for (int i = 1; i <= n; ++i)
        printf("%d ", a[i]);
    return 0;
}
