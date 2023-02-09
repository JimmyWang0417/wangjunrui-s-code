#include <bits/extc++.h>
#include <bits/stdc++.h>
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
const int N = 1e6 + 5;
char str[N];
int n, m;
int L[N], R[N];
int size[N][2];
int answer;
int fa[N];
inline int find(int x)
{
    return fa[x] == x ? x : fa[x] = find(fa[x]);
}
inline void merge(int x, int y)
{
    x = find(x), y = find(y);
    if (x == y)
        return;
    answer -= min(size[x][0], size[x][1]) + min(size[y][0], size[y][1]);
    size[x][0] += size[y][0], size[x][1] += size[y][1];
    fa[y] = x;
    answer += min(size[x][0], size[x][1]);
}
signed main()
{
    read(n, m);
    scanf("%s", str + 1);
    for (int i = 1; i <= m; ++i)
    {
        int cnt;
        read(cnt);
        while (cnt--)
        {
            int x;
            read(x);
            if (!L[x])
                L[x] = i;
            else
                R[x] = i;
        }
    }
    ++m;
    for (int i = 0; i < m; ++i)
    {
        size[i][0] = 1;
        fa[i] = i;
    }
    for (int i = m; i < 2 * m; ++i)
    {
        size[i][1] = 1;
        fa[i] = i;
    }
    for (int i = 1; i <= n; ++i)
    {
        if (str[i] == '0')
        {
            merge(L[i], R[i] + m);
            merge(L[i] + m, R[i]);
        }
        else
        {
            merge(L[i], R[i]);
            merge(L[i] + m, R[i] + m);
        }
        int x = find(0);
        printf("%d\n", answer / 2 + (size[x][0] < size[x][1] ? size[x][1] - size[x][0] : 0));
    }
    return 0;
}