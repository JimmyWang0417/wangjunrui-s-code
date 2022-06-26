#include <algorithm>
#include <cstdio>
#include <cstring>
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
constexpr int N = 1e5 + 5;
int n, m, k, a[N];
int block, belong[N];
struct Query
{
    int l, r, id;
    Query(int _l = 0, int _r = 0, int _id = 0) : l(_l), r(_r), id(_id) {}
    inline bool operator<(const Query &rhs) const
    {
        return belong[l] == belong[rhs.l] ? (belong[l] & 1 ? r < rhs.r : r > rhs.r) : l < rhs.l;
    }
} q[N];
ll answer[N];
int cnt[N];
int p[N], tot;
int dp[N];
vector<Query> g[N];
signed main()
{
    read(n, m, k);
    if (k > 14)
    {
        for (int i = 1; i <= m; ++i)
            printf("0\n");
        return 0;
    }
    block = (int)__builtin_sqrt((double)n / m * n);
    for (int i = 1; i <= n; ++i)
    {
        read(a[i]);
        belong[i] = (i - 1) / block + 1;
    }
    for (int i = 1; i <= m; ++i)
    {
        read(q[i].l, q[i].r);
        q[i].id = i;
    }
    sort(q + 1, q + 1 + m);
    if (k == 0)
    {
        ll res = 0;
        for (int i = 1, l = 1, r = 0; i <= m; ++i)
        {
            const int &ql = q[i].l, &qr = q[i].r;
            while (l > ql)
                res += cnt[a[--l]]++;
            while (r < qr)
                res += cnt[a[++r]]++;
            while (l < ql)
                res -= --cnt[a[l++]];
            while (r > qr)
                res -= --cnt[a[r--]];
            answer[q[i].id] = res;
        }
    }
    else
    {
        for (int i = 0; i < 16384; ++i)
            if (__builtin_popcount(i) == k)
                p[++tot] = i;
        for (int i = 1; i <= n; ++i)
        {
            dp[i] = cnt[a[i]];
            for (int j = 1; j <= tot; ++j)
                ++cnt[a[i] ^ p[j]];
        }
        memset(cnt, 0, sizeof(cnt));
        for (int i = 1, l = 1, r = 0; i <= m; ++i)
        {
            const int &ql = q[i].l, &qr = q[i].r;
            if (l > ql)
            {
                g[r].push_back(Query(ql, l - 1, i));
                do
                    answer[q[i].id] -= dp[--l];
                while (l > ql);
            }
            if (r < qr)
            {
                g[l - 1].push_back(Query(r + 1, qr, -i));
                do
                    answer[q[i].id] += dp[++r];
                while (r < qr);
            }
            if (l < ql)
            {
                g[r].push_back(Query(l, ql - 1, -i));
                do
                    answer[q[i].id] += dp[l++];
                while (l < ql);
            }
            if (r > qr)
            {
                g[l - 1].push_back(Query(qr + 1, r, i));
                do
                    answer[q[i].id] -= dp[r--];
                while (r > qr);
            }
        }
        for (int i = 1; i <= n; ++i)
        {
            for (int j = 1; j <= tot; ++j)
                ++cnt[a[i] ^ p[j]];
            for (auto u : g[i])
            {
                int l = u.l, r = u.r, id = u.id;
                ll res = 0;
                for (int j = l; j <= r; ++j)
                    res += cnt[a[j]];
                if (id < 0)
                    answer[q[-id].id] -= res;
                else
                    answer[q[id].id] += res;
            }
        }
        for (int i = 2; i <= m; ++i)
            answer[q[i].id] += answer[q[i - 1].id];
    }
    for (int i = 1; i <= m; ++i)
        printf("%lld\n", answer[i]);
    return 0;
}