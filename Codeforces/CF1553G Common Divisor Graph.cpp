/**
 *    unicode: UTF-8
 *    name:    project
 *    author:  CF1553G Common Divisor Graph
 *    created: 2022.07.04 周一 21:29:35 (Asia/Shanghai)
 **/
#include <algorithm>
#include <cstdio>
#include <list>
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
int n, m;
int a[N];
int fa[N];
inline int find(int x)
{
    return fa[x] ? fa[x] = find(fa[x]) : x;
}
inline void unionn(int x, int y)
{
    x = find(x), y = find(y);
    if (x == y)
        return;
    fa[x] = y;
}
int prime[N], tot;
bool vis[N];
vector<int> b[N];
list<int> p[N];
int st[N], top;
inline void getprimes(int limit)
{
    for (int i = 2; i <= limit; ++i)
    {
        if (!vis[i])
        {
            prime[++tot] = i;
            p[i].push_back(i);
        }
        for (int j = 1; j <= tot && i * prime[j] <= limit; ++j)
        {
            vis[i * prime[j]] = true;
            p[i * prime[j]] = p[i];
            if (i % prime[j] == 0)
                break;
            p[i * prime[j]].push_back(prime[j]);
        }
    }
    for (int i = 1; i <= n; ++i)
    {
        int las = p[a[i]].front();
        for (auto it = ++p[a[i]].begin(); it != p[a[i]].end(); ++it)
            unionn(las, *it);
    }
    for (int i = 1; i <= n; ++i)
    {
        top = 0;
        st[++top] = find(p[a[i]].front());
        for (auto u : p[a[i] + 1])
            st[++top] = find(u);
        for (int j = 1; j <= top; ++j)
            for (int k = j + 1; k <= top; ++k)
                b[st[j]].push_back(st[k]);
    }
    for (int i = 1; i <= limit; ++i)
    {
        if (b[i].empty())
            continue;
        sort(b[i].begin(), b[i].end());
        b[i].erase(unique(b[i].begin(), b[i].end()), b[i].end());
    }
}
signed main()
{
    read(n, m);
    for (int i = 1; i <= n; ++i)
        read(a[i]);
    getprimes(*max_element(a + 1, a + 1 + n) + 1);
    for (int i = 1; i <= m; ++i)
    {
        int x, y;
        read(x, y);
        x = find(p[a[x]].front()), y = find(p[a[y]].front());
        if (x == y)
            puts("0");
        else
        {
            auto it = lower_bound(b[x].begin(), b[x].end(), y);
            if (it != b[x].end() && *it == y)
                puts("1");
            else
            {
                it = lower_bound(b[y].begin(), b[y].end(), x);
                if (it != b[y].end() && *it == x)
                    puts("1");
                else
                    puts("2");
            }
        }
    }
    return 0;
}