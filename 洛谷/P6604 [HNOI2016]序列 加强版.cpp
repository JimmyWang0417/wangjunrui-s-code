/**
 *    unicode: UTF-8
 *    name:    P6604 [HNOI2016]序列 加强版
 *    author:  whitepaperdogdog
 *    created: 2022.07.02 周六 15:49:08 (Asia/Shanghai)
 **/
#include <algorithm>
#include <cstdio>
#define ll long long
#define ull unsigned ll
#define lowbit(x) (x & (-x))
using namespace std;
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
using namespace std;
const int N = 1e5 + 5;
int n, m, a[N];
ll fl[N], fr[N], gl[N], gr[N];
int st[N], top;
int Log[N], best[N][20];
inline int calc(int x, int y)
{
    return a[x] < a[y] ? x : y;
}
inline int query(int l, int r)
{
    int k = Log[r - l + 1];
    return calc(best[l][k], best[r - (1 << k) + 1][k]);
}
int type;
namespace gen
{
    ull s, a, b, c, lastans = 0;
    inline void init()
    {
        read(s, a, b, c);
    }
    ull rand()
    {
        return s ^= (a + b * lastans) % c;
    }
}
signed main()
{
    read(n, m, type);
    Log[0] = -1;
    for (int i = 1; i <= n; ++i)
    {
        read(a[i]);
        Log[i] = Log[i >> 1] + 1;
        best[i][0] = i;
    }
    for (int j = 1; j <= Log[n]; ++j)
        for (int i = 1; i + (1 << j) - 1 <= n; ++i)
            best[i][j] = calc(best[i][j - 1], best[i + (1 << (j - 1))][j - 1]);
    a[0] = a[n + 1] = ~0x7fffffff;
    st[top = 1] = 0;
    for (int i = 1; i <= n; ++i)
    {
        while (a[st[top]] > a[i])
            --top;
        fr[i] = fr[st[top]] + (ll)a[i] * (i - st[top]);
        gr[i] = gr[i - 1] + fr[i];
        st[++top] = i;
    }
    st[top = 1] = n + 1;
    for (int i = n; i >= 1; --i)
    {
        while (a[st[top]] > a[i])
            --top;
        fl[i] = fl[st[top]] + (ll)a[i] * (st[top] - i);
        gl[i] = gl[i + 1] + fl[i];
        st[++top] = i;
    }
    ull answer = 0;
    if (!type)
        for (int i = 1; i <= m; ++i)
        {
            int l, r;
            read(l, r);
            int p = query(l, r);
            answer ^= (ll)(p - l + 1) * (r - p + 1) * a[p] + gl[l] - gl[p] - (ll)fl[p] * (p - l) + gr[r] - gr[p] - (ll)fr[p] * (r - p);
        }
    else
    {
        gen::init();
        for (int i = 1; i <= m; ++i)
        {
            int l = (int)(gen::rand() % n + 1), r = (int)(gen::rand() % n + 1);
            if (l > r)
                swap(l, r);
            int p = query(l, r);
            answer ^= (gen::lastans = (ll)(p - l + 1) * (r - p + 1) * a[p] + gl[l] - gl[p] - (ll)fl[p] * (p - l) + gr[r] - gr[p] - (ll)fr[p] * (r - p));
        }
    }
    printf("%lld\n", answer);
    return 0;
}