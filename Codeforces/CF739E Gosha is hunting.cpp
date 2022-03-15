#include <bits/stdc++.h>
#define eps (1e-8)
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
const int N = 2005;
int n, A, B;
double a[N], b[N], c[N];
inline pair<int, int> check(double mida, double midb)
{
    int cnta = 0, cntb = 0;
    for (int i = 1; i <= n; ++i)
    {
        bool exista = false, existb = false;
        double res = 0;
        if (a[i] - mida > res + eps)
        {
            exista = true;
            existb = false;
            res = a[i] - mida;
        }
        if (b[i] - midb > res + eps)
        {
            exista = false;
            existb = true;
            res = b[i] - midb;
        }
        if (c[i] - mida - midb > res + eps)
        {
            exista = existb = true;
            res = c[i] - mida - midb;
        }
        cnta += exista;
        cntb += existb;
    }
    return make_pair(cnta, cntb);
}
inline double solve(double mida, double midb)
{
    int cnta = 0, cntb = 0;
    double dp = 0;
    for (int i = 1; i <= n; ++i)
    {
        double res = 0;
        if (a[i] - mida > res + eps)
            res = a[i] - mida;
        if (b[i] - midb > res + eps)
            res = b[i] - midb;
        if (c[i] - mida - midb > res + eps)
            res = c[i] - mida - midb;
        dp += res;
    }
    return dp;
}
signed main()
{
    read(n, A, B);
    for (int i = 1; i <= n; ++i)
        scanf("%lf", &a[i]);
    for (int i = 1; i <= n; ++i)
    {
        scanf("%lf", &b[i]);
        c[i] = 1 - (1 - a[i]) * (1 - b[i]);
    }
    double la = 0, ra = 1, ansa = 0, lb = 0, rb = 1, ansb = 0;
    while (fabs(ra - la) > eps)
    {
        double mida = (la + ra) / 2;
        lb = 0, rb = 1, ansb = 0;
        pair<int, int> now;
        while (fabs(rb - lb) > eps)
        {
            double midb = (lb + rb) / 2;
            now = check(mida, midb);
            if (now.second <= B)
            {
                ansb = midb;
                rb = midb;
            }
            else
                lb = midb;
        }
        now = check(mida, ansb);
        if (now.first <= A)
        {
            ansa = mida;
            ra = mida;
        }
        else
            la = mida;
    }
    printf("%.5lf\n", solve(ansa, ansb) + ansa * A + ansb * B);
    return 0;
}