#include <algorithm>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <map>
#include <queue>
#include <string>
#include <vector>
#include <ext/pb_ds/assoc_container.hpp>
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
constexpr int N = 2e5 + 5;
constexpr int base1 = 1e6 + 3, base2 = 10007;
constexpr int mod1 = 1e9 + 7, mod2 = 1e9 + 9;
typedef pair<ll, ll> node;
int n, m;
ll power1[N], power2[N];
__gnu_pbds::cc_hash_table<ll, int> mp;
struct ZANL
{
    string s;
    vector<ll> hash1, hash2;
    inline void init()
    {
        cin >> s;
        hash1.resize(s.size() + 1);
        hash2.resize(s.size() + 1);
        for (int i = 1; i <= (int)s.size(); ++i)
        {
            hash1[i] = (hash1[i - 1] * base1 + s[i - 1] - 'a' + 1) % mod1;
            hash2[i] = (hash2[i - 1] * base2 + s[i - 1] - 'a' + 1) % mod2;
        }
    }
    inline ll calc(int l, int r)
    {
        return (hash1[r] - hash1[l - 1] * power1[r - l + 1] % mod1 + mod1) % mod1 * mod2 +
               (hash2[r] - hash2[l - 1] * power2[r - l + 1] % mod2 + mod2) % mod2;
    }
} a[N];
int in[N];
struct Edge
{
    int next, to;
    char dis;
} edge[N];
int head[N], num_edge;
inline void add_edge(int from, int to, char dis = 0)
{
    edge[++num_edge].next = head[from];
    edge[num_edge].to = to;
    edge[num_edge].dis = dis;
    head[from] = num_edge;
    ++in[to];
}
int dis[N];
inline bool check(int k)
{
    mp.clear();
    memset(in, 0, sizeof(in));
    memset(head, num_edge = 0, sizeof(head));
    m = 0;
    for (int kase = 1; kase <= n; ++kase)
    {
        if ((int)a[kase].s.size() < k)
            continue;
        ll nmsl = a[kase].calc(1, k - 1);
        for (int i = k, las = (mp[nmsl] ? mp[nmsl] : mp[nmsl] = ++m); i <= (int)a[kase].s.size(); ++i)
        {
            nmsl = a[kase].calc(i - k + 2, i);
            int u = (mp[nmsl] ? mp[nmsl] : mp[nmsl] = ++m);
            add_edge(u, las);
            las = u;
        }
    }
    queue<int> q;
    for (int i = 1; i <= m; ++i)
        if (!in[i])
            q.push(i);
    while (!q.empty())
    {
        int u = q.front();
        q.pop();
        for (int i = head[u]; i; i = edge[i].next)
        {
            int &v = edge[i].to;
            if (!--in[v])
                q.push(v);
        }
    }
    for (int i = 1; i <= m; ++i)
        if (in[i])
            return false;
    return true;
}
int where[N], L[N];
char e[N];
int pre[N];
inline void solve(int k)
{
    mp.clear();
    memset(in, 0, sizeof(in));
    memset(dis, 0, sizeof(dis));
    memset(pre, 0, sizeof(pre));
    memset(e, 0, sizeof(e));
    memset(head, num_edge = 0, sizeof(head));
    m = 0;
    for (int kase = 1; kase <= n; ++kase)
    {
        if ((int)a[kase].s.size() < k)
            continue;
        ll nmsl = a[kase].calc(1, k - 1);
        int las;
        if (mp[nmsl])
            las = mp[nmsl];
        else
        {
            las = mp[nmsl] = ++m;
            where[m] = kase;
            L[m] = 0;
        }
        for (int i = k; i <= (int)a[kase].s.size(); ++i)
        {
            nmsl = a[kase].calc(i - k + 2, i);
            int u;
            if (mp[nmsl])
                u = mp[nmsl];
            else
            {
                u = mp[nmsl] = ++m;
                where[m] = kase;
                L[m] = i - k + 1;
            }
            add_edge(u, las, a[kase].s[i - 1]);
            las = u;
        }
    }
    queue<int> q;
    for (int i = 1; i <= m; ++i)
        if (!in[i])
            q.push(i);
    int res = 0, beg = 0;
    string wdnmd;
    while (!q.empty())
    {
        int u = q.front();
        q.pop();
        ckmax(res, dis[u]);
        for (int i = head[u]; i; i = edge[i].next)
        {
            int &v = edge[i].to;
            if (dis[v] < dis[u] + 1)
            {
                e[v] = edge[i].dis;
                pre[v] = u;
                dis[v] = dis[u] + 1;
            }
            else if (dis[v] == dis[u] + 1 && e[v] > edge[i].dis)
            {
                e[v] = edge[i].dis;
                pre[v] = u;
            }
            if (!--in[v])
                q.push(v);
        }
    }
    for (int i = 1; i <= m; ++i)
        if (res == dis[i])
        {
            string tmp = a[where[i]].s.substr(L[i], k - 1);
            if (wdnmd.empty() || tmp < wdnmd)
            {
                wdnmd = tmp;
                beg = i;
            }
        }
    cout << wdnmd;
    for (int u = beg; pre[u]; u = pre[u])
        cout << e[u];
    cout << endl;
}
inline void work()
{
    cin >> n;
    int sum = 0, maxx = 0;
    for (int kase = 1; kase <= n; ++kase)
    {
        a[kase].init();
        sum += (int)a[kase].s.size();
        ckmax(maxx, (int)a[kase].s.size());
    }
    int l = 1, r = sum, ans = sum + 1;
    while (l <= r)
    {
        int mid = (l + r) >> 1;
        if (check(mid))
        {
            ans = mid;
            r = mid - 1;
        }
        else
            l = mid + 1;
    }
    cout << ans << endl;
    if (ans > maxx)
    {
        for (int i = 1; i < ans; ++i)
            cout << 'a';
        cout << endl;
    }
    else
        solve(ans);
}
signed main()
{
#ifdef ONLINE_JUDGE
    freopen("string.in", "r", stdin);
    freopen("string.out", "w", stdout);
#endif
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    power1[0] = power2[0] = 1;
    for (int i = 1; i <= 2e5; ++i)
    {
        power1[i] = power1[i - 1] * base1 % mod1;
        power2[i] = power2[i - 1] * base2 % mod2;
    }
    int T = 1;
    cin >> T;
    while (T--)
        work();
    return 0;
}
