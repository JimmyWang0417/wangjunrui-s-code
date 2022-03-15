// Problem: P3273 [SCOI2011]棘手的操作
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P3273
// Memory Limit: 125 MB
// Time Limit: 1000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

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
const int N = 3e5 + 5;
int n, m, fa[N];
inline int find(int x)
{
    return !fa[x] ? x : fa[x] = find(fa[x]);
}

int tag[N];
__gnu_pbds::priority_queue<pair<int, int>> q[N];
__gnu_pbds::priority_queue<pair<int, int>>::point_iterator its[N];

int alltag;
__gnu_pbds::priority_queue<int> all;
__gnu_pbds::priority_queue<int>::point_iterator itsheap[N];

signed main()
{
    read(n);
    for (int i = 1; i <= n; ++i)
    {
        int x;
        read(x);
        its[i] = q[i].push(make_pair(x, i));
        itsheap[i] = all.push(q[i].top().first);
    }
    read(m);
    for (int i = 1; i <= m; ++i)
    {
        static char opt[10];
        scanf("%s", opt);
        if (opt[0] == 'U')
        {
            int x, y;
            read(x, y);
            x = find(x), y = find(y);
            if (x == y)
                continue;
            if (q[x].size() < q[y].size())
                swap(x, y);
            all.erase(itsheap[x]), all.erase(itsheap[y]);
            while (!q[y].empty())
            {
                pair<int, int> u = q[y].top();
                its[u.second] = q[x].push(make_pair(u.first + tag[y] - tag[x], u.second));
                q[y].pop();
            }
            itsheap[x] = all.push(q[x].top().first + tag[x]);
            fa[y] = x;
        }
        else if (opt[0] == 'A')
        {
            if (opt[1] == '1')
            {
                int x, v;
                read(x, v);
                all.erase(itsheap[find(x)]);
                pair<int, int> u = *its[x];
                q[find(x)].erase(its[x]);
                u.first += v;
                its[x] = q[find(x)].push(u);
                itsheap[find(x)] = all.push(q[find(x)].top().first + tag[find(x)]);
            }
            else if (opt[1] == '2')
            {
                int x, v;
                read(x, v);
                x = find(x);
                all.erase(itsheap[x]);
                tag[x] += v;
                itsheap[x] = all.push(q[x].top().first + tag[x]);
            }
            else
            {
                int v;
                read(v);
                alltag += v;
            }
        }
        else if (opt[0] == 'F')
        {
            if (opt[1] == '1')
            {
                int x;
                read(x);
                printf("%d\n", its[x]->first + tag[find(x)] + alltag);
            }
            else if (opt[1] == '2')
            {
                int x;
                read(x);
                x = find(x);
                printf("%d\n", q[x].top().first + tag[x] + alltag);
            }
            else
                printf("%d\n", all.top() + alltag);
        }
    }
    return 0;
}