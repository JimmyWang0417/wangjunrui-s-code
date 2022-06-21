#include <algorithm>
#include <cstdio>
#include <vector>
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
inline void read(T &x, T1 &... x1)
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
int n, m, k;
int a[N];
int opt[N];
pair<int, int> p[N];
vector<pair<int, int>> q[N];
vector<pair<int, double>> qwq;
vector<int> answer;
signed main()
{
    auto compare = [&](const auto &x, const auto &y) { return x.second > y.second; };
    read(n, m, k);
    for (int i = 1; i <= n; ++i)
        read(a[i]);
    for (int i = 1; i <= m; ++i)
    {
        int x, y;
        read(opt[i], x, y);
        if (opt[i] == 1)
        {
            if (p[x].second < y)
                p[x] = make_pair(i, y);
        }
        else if (opt[i] == 2)
            q[x].emplace_back(i, y);
        else
            qwq.emplace_back(i, y);
    }
    for (int i = 1; i <= n; ++i)
    {
        if (p[i].second > a[i])
            q[i].emplace_back(p[i].first, p[i].second - a[i]);
        sort(q[i].begin(), q[i].end(), compare);
        ll v = a[i];
        for (auto u : q[i])
        {
            qwq.emplace_back(u.first, (double)(u.second + v) / (double)v);
            v += u.second;
        }
    }
    sort(qwq.begin(), qwq.end(), [&](const auto &x, const auto &y) { return x.second > y.second; });
    for (int i = 0; i < k && i < (int)qwq.size(); ++i)
        answer.push_back(qwq[i].first);
    sort(answer.begin(), answer.end(), [&](const auto &x, const auto &y) { return opt[x] < opt[y]; });
    printf("%lu\n", answer.size());
    for (auto u : answer)
        printf("%d ", u);
    putchar('\n');
    return 0;
}