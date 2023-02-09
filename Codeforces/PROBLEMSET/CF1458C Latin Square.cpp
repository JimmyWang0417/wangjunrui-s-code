#include <bits/stdc++.h>
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
const int N = 1005;
int n, m, a[N][N][3];
int b[N][N];
int f[3], o[3];
char str[N * N];
inline void work()
{
    f[0] = f[1] = f[2] = 0;
    o[0] = 0, o[1] = 1, o[2] = 2;
    read(n, m);
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
        {
            a[i][j][0] = i;
            a[i][j][1] = j;
            read(a[i][j][2]);
            --a[i][j][2];
        }
    scanf("%s", str);
    for (int i = 0; i < m; ++i)
    {
        if (str[i] == 'R')
            ++f[1];
        else if (str[i] == 'L')
            --f[1];
        else if (str[i] == 'D')
            ++f[0];
        else if (str[i] == 'U')
            --f[0];
        else if (str[i] == 'I')
        {
            swap(o[1], o[2]);
            swap(f[1], f[2]);
        }
        else
        {
            swap(o[0], o[2]);
            swap(f[0], f[2]);
        }
    }
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < n; ++j)
        {
            for (int t = 0; t < 3; ++t)
                (a[i][j][o[t]] += f[t] % n + n) %= n;
            b[a[i][j][o[0]]][a[i][j][o[1]]] = a[i][j][o[2]];
        }
    }
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < n; ++j)
            printf("%d ", b[i][j] + 1);
        putchar('\n');
    }
    putchar('\n');
}
signed main()
{
    int T;
    read(T);
    while (T--)
        work();
    return 0;
}
