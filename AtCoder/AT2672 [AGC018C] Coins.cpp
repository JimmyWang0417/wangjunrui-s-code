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
constexpr int N = 1e5 + 5;
int A, B, C;
pair<int, int> a[N];
inline pair<int, int> solve(int mida, int midb)
{
    int cnta = 0, cntb = 0;
    for (int i = 1; i <= A + B + C; ++i)
    {
        bool flaga = false, flagb = false;
        int res = 0;
        if (res < a[i].first + mida)
        {
            flaga = true, flagb = false;
            res = a[i].first + mida;
        }
        if (res < a[i].second + midb)
        {
            flaga = false, flagb = true;
            res = a[i].second + midb;
        }
        cnta += flaga, cntb += flagb;
    }
    return make_pair(cnta, cntb);
}
inline ll calc(int mida, int midb)
{
    ll ans = 0;
    for (int i = 1; i <= A + B + C; ++i)
        ans += max(0, max(a[i].first + mida, a[i].second + midb));
    return ans;
}
signed main()
{
    ll sum = 0;
    read(A, B, C);
    for (int i = 1; i <= A + B + C; ++i)
    {
        int x, y, z;
        read(x, y, z);
        sum += x;
        a[i] = make_pair(y - x, z - x);
    }
    int la = -1e9, ra = 1e9, ansa = 0, ansb = 0;
    while (la <= ra)
    {
        int mida = (la + ra) / 2;
        int lb = -1e9, rb = 1e9, ans = 0;
        while (lb <= rb)
        {
            int midb = (lb + rb) / 2;
            if (solve(mida, midb).second <= C)
            {
                ans = midb;
                lb = midb + 1;
            }
            else
                rb = midb - 1;
        }
        if (solve(mida, ans).first <= B)
        {
            ansa = mida;
            ansb = ans;
            la = mida + 1;
        }
        else
            ra = mida - 1;
    }
    printf("%lld\n", sum + calc(ansa, ansb) - (ll)B * ansa - (ll)C * ansb);
    return 0;
}
