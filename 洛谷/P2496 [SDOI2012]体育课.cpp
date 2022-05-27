// Problem: P2496 [SDOI2012]体育课
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P2496
// Memory Limit: 125 MB
// Time Limit: 6000 ms
//
// Powered by CP Editor (https://cpeditor.org)

#include <bits/extc++.h>
#include <bits/stdc++.h>
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
const int N = 1e5 + 5, NUM = 405;
int n, m;
ll a[N];
int block, num;
pair<ll, ll> tag[N];
int belong[N], L[N], R[N];
list<pair<ll, ll>> b[N];
inline void update(int rt)
{
    while (b[rt].size() >= 2 && (++b[rt].begin())->first + (++b[rt].begin())->second * tag[rt].first >= b[rt].front().first + b[rt].front().second * tag[rt].first)
        b[rt].pop_front();
}
inline void build(int rt)
{
    b[rt].clear();
    for (int i = L[rt]; i <= R[rt]; ++i)
    {
        while (b[rt].size() >= 2 && (a[i] - b[rt].back().first) * (b[rt].back().second - (++b[rt].rbegin())->second) >= (b[rt].back().first - (++b[rt].rbegin())->first) * (i - b[rt].back().second))
            b[rt].pop_back();
        b[rt].push_back(make_pair(a[i], i));
    }
    update(rt);
}
inline void pushdown(int rt)
{
    for (int i = L[rt]; i <= R[rt]; ++i)
        a[i] += tag[rt].first * i + tag[rt].second;
    tag[rt] = make_pair(0, 0);
}
inline void update(int l, int r, int val)
{
    if (belong[l] == belong[r])
    {
        pushdown(belong[l]);
        for (int i = l; i <= r; ++i)
            a[i] += (ll)val * (i - l + 1);
        build(belong[l]);
    }
    else
    {
        pushdown(belong[l]);
        for (int i = l; i <= R[belong[l]]; ++i)
            a[i] += (ll)val * (i - l + 1);
        build(belong[l]);

        for (int i = belong[l] + 1; i < belong[r]; ++i)
        {
            tag[i].first += val;
            tag[i].second += -(ll)(l - 1) * val;
            update(i);
        }

        pushdown(belong[r]);
        for (int i = L[belong[r]]; i <= r; ++i)
            a[i] += (ll)val * (i - l + 1);
        build(belong[r]);
    }
}
inline ll query(int l, int r)
{
    if (belong[l] == belong[r])
    {
        ll res = 0;
        for (int i = l; i <= r; ++i)
            ckmax(res, a[i] + tag[belong[l]].first * i + tag[belong[l]].second);
        return res;
    }
    else
    {
        ll res = 0;
        for (int i = l; i <= R[belong[l]]; ++i)
            ckmax(res, a[i] + tag[belong[l]].first * i + tag[belong[l]].second);
        for (int i = belong[l] + 1; i < belong[r]; ++i)
            ckmax(res, b[i].front().first + b[i].front().second * tag[i].first + tag[i].second);
        for (int i = L[belong[r]]; i <= r; ++i)
            ckmax(res, a[i] + tag[belong[r]].first * i + tag[belong[r]].second);
        return res;
    }
}
signed main()
{
    read(n, m);
    for (int i = 1; i <= n; ++i)
        read(a[i]);
    block = (int)sqrt(n);
    num = (n - 1) / block + 1;
    for (int i = 1; i <= num; ++i)
    {
        L[i] = R[i - 1] + 1;
        R[i] = min(R[i - 1] + block, n);
        for (int j = L[i]; j <= R[i]; ++j)
            belong[j] = i;
        build(i);
    }
    for (int i = 1; i <= m; ++i)
    {
        int opt, x, y, z;
        read(opt, x, y);
        switch (opt)
        {
        case 1:
            printf("%lld\n", max(query(x, y) - a[1] - tag[1].first - tag[1].second, 0ll));
            break;
        case 2:
            if (belong[x] == belong[y])
            {
                pushdown(belong[x]);
                swap(a[x], a[y]);
                build(belong[x]);
            }
            else
            {
                pushdown(belong[x]), pushdown(belong[y]);
                swap(a[x], a[y]);
                build(belong[x]), build(belong[y]);
            }
            break;
        default:
            read(z);
            update(x, y, z);
        }
    }
    return 0;
}