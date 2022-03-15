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
const int N = 2505;
int n, m, q;
ull sum[N][N];
inline void update(int x, int y, ull v)
{
    for (int i = x; i <= n; i += lowbit(i))
        for (int j = y; j <= m; j += lowbit(j))
            sum[i][j] += v;
}
inline void update(int x1, int y1, int x2, int y2, ull v)
{
    update(x1, y1, v);
    update(x2 + 1, y1, -v);
    update(x1, y2 + 1, -v);
    update(x2 + 1, y2 + 1, v);
}
inline ull query(int x, int y)
{
    ull res = 0;
    for (int i = x; i; i -= lowbit(i))
        for (int j = y; j; j -= lowbit(j))
            res += sum[i][j];
    return res;
}
inline ull query(int x1, int y1, int x2, int y2)
{
    return query(x2, y2) - query(x1 - 1, y2) - query(x2, y1 - 1) - query(x1 - 1, y1 - 1);
}
signed main()
{
    random_device rd;
    mt19937 rnd(rd());
    uniform_int_distribution<ull> randd(114514, 1919810);
    const ull base = randd(rnd);
    read(n, m, q);
    for (int i = 1; i <= q; ++i)
    {
        int opt, x1, y1, x2, y2;
        read(opt, x1, y1, x2, y2);
        if (opt == 1)
            update(x1, y1, x2, y2, x1 * base * base * base + y1 * base * base + x2 * base + y2);
        else if (opt == 2)
            update(x1, y1, x2, y2, -(x1 * base * base * base + y1 * base * base + x2 * base + y2));
        else
            puts(query(x1, y1) == query(x2, y2) ? "Yes" : "No");
    }
    return 0;
}