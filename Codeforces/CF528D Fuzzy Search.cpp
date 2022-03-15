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
const int N = 2e5 + 5;
int n, m, k;
inline int calc(char c)
{
    return c == 'A' ? 0 : (c == 'T' ? 1 : (c == 'G' ? 2 : 3));
}
int a[N][4];
bitset<N> bit[4], answer;
char S[N], T[N];
signed main()
{
    read(n, m, k);
    scanf("%s%s", S, T);
    for (int i = 0; i < n; ++i)
    {
        ++a[max(0, i - k)][calc(S[i])];
        --a[min(n, i + k + 1)][calc(S[i])];
    }
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < 4; ++j)
        {
            if (i)
                a[i][j] += a[i - 1][j];
            if (a[i][j])
                bit[j][i] = 1;
            else
                bit[j][i] = 0;
        }
    }
    answer.set();
    for (int i = 0; i < m; ++i)
        answer &= bit[calc(T[i])] >> i;
    printf("%lu\n", answer.count());
    return 0;
}