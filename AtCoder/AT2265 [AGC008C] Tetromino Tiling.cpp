#include <cstdio>
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
constexpr int N = 1e5 + 5;
signed main()
{
    unsigned i, o, t, j, l, s, z;
    read(i, o, t, j, l, s, z);
    unsigned res = (i >> 1 << 1) + o + (j >> 1 << 1) + (l >> 1 << 1);
    if (i && j && l)
    {
        --i, --j, --l;
        ckmax(res, (i >> 1 << 1) + o + (j >> 1 << 1) + (l >> 1 << 1) + 3);
    }
    printf("%u\n", res);
    return 0;
}