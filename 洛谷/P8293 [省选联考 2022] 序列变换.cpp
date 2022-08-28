/**
 *    unicode: UTF-8
 *    name:    P8293 [省选联考 2022] 序列变换
 *    author:  wangjunrui (蒟蒻wjr)
 *    located: Changle District, Fuzhou City, Fujian Province, China
 *    created: 2022.08.26 周五 17:02:33 (Asia/Shanghai)
 **/
#include <cstdio>
#include <set>
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
constexpr int N = 4e5 + 5;
int n, x, y;
int a[N];
char str[N * 2];
vector<int> g[N];
multiset<int> se;
pair<int, int> b[N];
int sze[N];
signed main()
{
    read(n, x, y);
    scanf("%s", str + 1);
    for (int i = 1; i <= n; ++i)
        read(a[i]);
    for (int i = 1, dep = 0, j = 0; i <= 2 * n; ++i)
        if (str[i] == '(')
        {
            ++dep;
            g[dep].push_back(a[++j]);
        }
        else
            --dep;
    if (!x)
    {
        if (!y)
            printf("0\n");
        else
        {
            ll res = 0, sum = 0;
            for (int i = 1; i < n; ++i)
            {
                for (int j : g[i])
                {
                    se.insert(j);
                    sum += j;
                }
                res += (sum -= *--se.end());
                se.erase(--se.end());
            }
            printf("%lld\n", res);
        }
    }
    else
    {
        if (y)
        {
            ll res = 0, sum = 0;
            for (int i = 1; i < n; ++i)
            {
                for (int j : g[i])
                {
                    se.insert(j);
                    sum += j;
                }
                res += (ll)*se.begin() * (se.size() - 2) + sum;
                sum -= *--se.end();
                se.erase(--se.end());
            }
            printf("%lld\n", res);
        }
        else
        {
            sze[0] = 1;
            for (int i = 1; i < n; ++i)
                sze[i] = sze[i - 1] + (int)g[i].size() - 1;
            int l = 1, r;
            while (l <= n && sze[l] == 1)
                ++l;
            r = l;
            while (r <= n && sze[r] == 2)
                ++r;
            b[l - 1] = b[r - 1] = make_pair(0x7fffffff, 0);
            ll sum = 0;
            for (int i = r; i < n; ++i)
            {
                b[i] = b[i - 1];
                for (int j : g[i])
                {
                    ckmin(b[i].first, j);
                    ckmax(b[i].second, j);
                    sum += j;
                }
            }
            for (int i = l; i < r; ++i)
            {
                b[i] = b[i - 1];
                for (int j : g[i])
                {
                    ckmin(b[i].first, j);
                    ckmax(b[i].second, j);
                    sum += j;
                }
            }
            ll res1 = sum - b[n - 1].second, res2 = sum - max(b[r - 1].second, b[n - 1].second);
            for (int i = r; i < n; ++i)
            {
                res1 += (ll)(sze[i] - 2) * min(b[r - 1].first, b[i].first);
                res2 += (ll)(sze[i] - 2) * b[i].first;
            }
            printf("%lld\n", min(res1, res2));
        }
    }
    return 0;
}