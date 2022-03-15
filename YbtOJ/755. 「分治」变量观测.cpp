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
const int N = 1e6 + 5;
int n, m, q;
struct node
{
    int t, k, q[3];
    __gnu_pbds::priority_queue<pair<int, int>, greater<pair<int, int>>, __gnu_pbds::binomial_heap_tag>::point_iterator its[3];
} a[N];
__gnu_pbds::priority_queue<pair<int, int>, greater<pair<int, int>>, __gnu_pbds::binomial_heap_tag> que[N];
int tag[N];
int nmsl[N], tot;
int las[N];
signed main()
{
    freopen("obs.in", "r", stdin);
    freopen("obs.out", "w", stdout);
    read(n, q);
    int lastans = 0;
    list<int>vec;
    while (q--)
    {
        int opt;
        read(opt);
        if (opt == 1)
        {
            int u = ++m;
            read(a[u].t, a[u].k);
            a[u].t ^= lastans;
            for (int i = 0; i < a[u].k; ++i)
            {
                read(a[u].q[i]), a[u].q[i] ^= lastans;
                a[u].its[i] = que[a[u].q[i]].push(make_pair(a[u].t / a[u].k + tag[a[u].q[i]], u));
            }
            las[u] = a[u].t;
            for (int i = 0; i < a[u].k; ++i)
                a[u].t += tag[a[u].q[i]];
        }
        else
        {
            int x, y;
            read(x, y);
            x ^= lastans, y ^= lastans;
            tag[x] += y;
            tot = 0;
            while (!que[x].empty() && que[x].top().first <= tag[x])
            {
                int u = que[x].top().second;
                for (int i = 0; i < a[u].k; ++i)
                {
                    a[u].t -= tag[a[u].q[i]];
                    que[a[u].q[i]].erase(a[u].its[i]);
                }
                if (a[u].t <= 0)
                {
                    nmsl[++tot] = u;
                    continue;
                }
                vec.push_back(u);
            }
            for(auto u:vec)
            {
                for (int i = 0; i < a[u].k; ++i)
                    a[u].its[i] = que[a[u].q[i]].push(make_pair(a[u].t / a[u].k + tag[a[u].q[i]], u));
                for (int i = 0; i < a[u].k; ++i)
                    a[u].t += tag[a[u].q[i]];
            }
            vec.clear();
            sort(nmsl + 1, nmsl + 1 + tot);
            printf("%d", lastans = tot);
            for (int i = 1; i <= tot; ++i)
                printf(" %d", nmsl[i]);
            putchar('\n');
        }
    }
    return 0;
}