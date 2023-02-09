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
const int N = 1e3 + 5;
pair<int, int> b[N];
int n, a[N], pos[N];
vector<pair<int, int>> answer;
inline void solve(int x, int y)
{
    if (x > y)
        swap(x, y);
    swap(pos[a[x]], pos[a[y]]);
    swap(a[x], a[y]);
    answer.push_back(make_pair(x, y));
}
signed main()
{
    read(n);
    for (int i = 1; i <= n; ++i)
    {
        read(a[i]);
        b[i] = make_pair(a[i], i);
    }
    sort(b + 1, b + 1 + n);
    for (int i = 1; i <= n; ++i)
        pos[a[b[i].second] = i] = b[i].second;
    for (int i = n; i >= 1; --i)
    {
        for (int j = a[i] + 1; j <= i; ++j)
            solve(i, pos[j]);
    }
    printf("%u\n", answer.size());
    for (auto u : answer)
        printf("%d %d\n", u.first, u.second);
    return 0;
}