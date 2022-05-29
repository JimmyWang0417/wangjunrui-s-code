#include <bits/stdc++.h>
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
constexpr int N = 1e6 + 5;
int n;
char S[N], T[N];
signed main()
{
    read(n);
    scanf("%s%s", S, T);
    if (!strncmp(S, T, n))
    {
        printf("0\n");
        return 0;
    }
    queue<int> q;
    int res = 0;
    for (int up = n - 1, down = n - 1; down >= 0; --down)
    {
        while (down && T[down - 1] == T[down])
            --down;
        ckmin(up, down);
        while (up >= 0 && S[up] != T[down])
            --up;
        if (up < 0)
        {
            printf("-1\n");
            return 0;
        }
        while (!q.empty() && q.front() - (int)q.size() >= down)
            q.pop();
        if (up != down)
            q.push(up);
        ckmax(res, (int)q.size());
    }
    printf("%d\n", res + 1);
    return 0;
}