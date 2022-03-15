#include <bits/stdc++.h>
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
const int N = 1e7 + 5;
const int mod = 1e9 + 7;
inline void add(int &x, int y)
{
    x += y;
    if (x >= mod)
        x -= mod;
}
inline void del(int &x, int y)
{
    x -= y;
    if (x < 0)
        x += mod;
}
int n, A[N];
inline void FWT()
{
    for (int k = 1; (k << 1) <= 1048576; k <<= 1)
        for (int i = 0; i < 1048576; i += (k << 1))
            for (int j = 0; j < k; ++j)
                add(A[i + j], A[i + j + k]);
}
inline void UFWT()
{
    for (int k = 1; (k << 1) <= 1048576; k <<= 1)
        for (int i = 0; i < 1048576; i += (k << 1))
            for (int j = 0; j < k; ++j)
                del(A[i + j], A[i + j + k]);
}
int power[N];
signed main()
{
    read(n);
    power[0] = 1;
    for (int i = 1; i <= n; ++i)
    {
        power[i] = power[i - 1];
        add(power[i], power[i - 1]);
    }
    for (int i = 1; i <= n; ++i)
    {
        int x;
        read(x);
        ++A[x];
    }
    FWT();
    for (int i = 0; i < 1048576; ++i)
        A[i] = power[A[i]] - 1;
    UFWT();
    printf("%d\n", A[0]);
    return 0;
}