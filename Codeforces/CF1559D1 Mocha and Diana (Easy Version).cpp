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
const int N = 1e5 + 5;
int n, m1, m2;
int fa1[N], fa2[N];
inline int find1(int x)
{
    return !fa1[x] ? x : fa1[x] = find1(fa1[x]);
}
inline int find2(int x)
{
    return !fa2[x] ? x : fa2[x] = find2(fa2[x]);
}
vector<pair<int, int>> answer;
int a[N], cnta, b[N], cntb;
signed main()
{
    read(n, m1, m2);
    for (int i = 1; i <= m1; ++i)
    {
        int u, v;
        read(u, v);
        fa1[find1(u)] = find1(v);
    }
    for (int i = 1; i <= m2; ++i)
    {
        int u, v;
        read(u, v);
        fa2[find2(u)] = find2(v);
    }
    for (int i = 2; i <= n; ++i)
        if (find1(1) != find1(i) && find2(1) != find2(i))
        {
            answer.emplace_back(1, i);
            fa1[find1(i)] = find1(1);
            fa2[find2(i)] = find2(1);
        }
    for (int i = 2; i <= n; ++i)
        if (find1(1) != find1(i))
        {
            a[++cnta] = i;
            fa1[find1(i)] = find1(1);
        }
        else if (find2(1) != find2(i))
        {
            b[++cntb] = i;
            fa2[find2(i)] = find2(1);
        }
    for (int i = 1; i <= cnta && i <= cntb; ++i)
        answer.emplace_back(a[i], b[i]);
    printf("%lu\n", answer.size());
    for (auto u : answer)
        printf("%d %d\n", u.first, u.second);
    return 0;
}