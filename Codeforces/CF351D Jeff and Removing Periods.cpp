/**
 *    unicode: UTF-8
 *    name:    CF351D Jeff and Removing Periods
 *    author:  wangjunrui
 *    created: 2022.07.02 周六 20:27:46 (Asia/Shanghai)
 **/
#include <algorithm>
#include <cstdio>
#include <deque>
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
int n, m, a[N];
int block, belong[N];
struct Query
{
    int l, r, id;
    inline bool operator<(const Query &rhs) const
    {
        return belong[l] == belong[rhs.l] ? (belong[l] & 1 ? r < rhs.r : r > rhs.r) : l < rhs.l;
    }
} q[N];
int mp[N], las[N];
int p[N], tot;
int answer[N];
int cnt[N];
deque<int> que[N];
inline bool query(int x)
{
    return cnt[x] == 1 || (cnt[x] > 1 && p[*++que[x].begin()] == p[que[x].back()]);
}
signed main()
{
    read(n);
    block = (int)__builtin_sqrt(n);
    for (int i = 1; i <= n; ++i)
    {
        read(a[i]);
        if (mp[a[i]] && (!las[mp[a[i]]] || (i - mp[a[i]]) == las[mp[a[i]]]))
            p[i] = p[mp[a[i]]];
        else
            p[i] = ++tot;
        belong[i] = (i - 1) / block + 1;
        las[i] = i - mp[a[i]];
        mp[a[i]] = i;
    }
    read(m);
    for (int i = 1; i <= m; ++i)
    {
        read(q[i].l, q[i].r);
        q[i].id = i;
    }
    sort(q + 1, q + 1 + m);
    for (int i = 1, l = 1, r = 0, res = 0, ans = 0; i <= m; ++i)
    {
        int ql = q[i].l, qr = q[i].r;
        while (l > ql)
        {
            --l;
            res -= query(a[l]);
            if (!cnt[a[l]]++)
                ++ans;
            que[a[l]].push_front(l);
            res += query(a[l]);
        }
        while (r < qr)
        {
            ++r;
            res -= query(a[r]);
            if (!cnt[a[r]]++)
                ++ans;
            que[a[r]].push_back(r);
            res += query(a[r]);
        }
        while (l < ql)
        {
            res -= query(a[l]);
            if (!--cnt[a[l]])
                --ans;
            que[a[l]].pop_front();
            res += query(a[l]);
            ++l;
        }
        while (r > qr)
        {
            res -= query(a[r]);
            if (!--cnt[a[r]])
                --ans;
            que[a[r]].pop_back();
            res += query(a[r]);
            --r;
        }
        answer[q[i].id] = ans + !res;
    }
    for (int i = 1; i <= m; ++i)
        printf("%d\n", answer[i]);
    return 0;
}