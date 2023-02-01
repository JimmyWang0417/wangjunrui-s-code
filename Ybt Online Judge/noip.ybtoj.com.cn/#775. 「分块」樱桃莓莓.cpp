#include "blackbox.h"
#include <algorithm>
#include <cstdio>
#include <set>
#include <vector>

typedef unsigned long long ull;
using namespace std;
constexpr int N = 2005;
int n, m;
ull a[N];
int L[N], R[N], num, belong[N];
ull pre[N], suf[N];
ull qwq[N];
struct Tree
{
    vector<ull> pre, suf;
} tree[N * 4];
#define lc (rt << 1)
#define rc (rt << 1 | 1)
inline void build(int rt, int l, int r)
{
    if (l == r)
        return;
    int mid = (l + r) >> 1;
    tree[rt].pre.push_back(pre[R[mid]]);
    for (int i = mid - 1; i >= l; --i)
        tree[rt].pre.push_back(magic(tree[rt].pre.back(), pre[R[i]]));
    tree[rt].suf.push_back(pre[R[mid + 1]]);
    for (int i = mid + 2; i <= r; ++i)
        tree[rt].suf.push_back(magic(tree[rt].suf.back(), pre[R[i]]));
    build(lc, l, mid);
    build(rc, mid + 1, r);
}
inline ull query(int rt, int l, int r, int x, int y)
{
    if (l == r)
        return pre[R[l]];
    int mid = (l + r) >> 1;
    if (x <= mid && mid < y)
    {
        ull res = 0;
        for (int i = x; i <= y; ++i)
            res += a[i];
        // printf("%d %d %llu %llu\n", x, mid, magic(tree[rt].pre[mid - x], tree[rt].suf[y - mid - 1]), res);
        return magic(tree[rt].pre[mid - x], tree[rt].suf[y - mid - 1]);
    }
    if (y <= mid)
        return query(lc, l, mid, x, y);
    else
        return query(rc, mid + 1, r, x, y);
}
void init(std::vector<ull> _a, int _m)
{
    n = (int)_a.size();
    m = _m;
    for (int i = 1; i <= n; ++i)
        a[i] = _a[i - 1];
    num = (n - 1) / 8 + 1;
    for (int i = 1; i <= num; ++i)
    {
        L[i] = R[i - 1] + 1;
        R[i] = R[i - 1] + 8;
    }
    R[num] = n;
    for (int i = 1; i <= num; ++i)
    {
        pre[L[i]] = a[L[i]];
        for (int j = L[i] + 1; j <= R[i]; ++j)
            pre[j] = magic(pre[j - 1], a[j]);
        suf[R[i]] = a[R[i]];
        for (int j = R[i] - 1; j >= L[i]; --j)
            suf[j] = magic(suf[j + 1], a[j]);
        if (L[i] + 4 <= R[i])
        {
            qwq[L[i] + 3] = a[L[i] + 3];
            for (int j = L[i] + 2; j >= L[i]; --j)
                qwq[j] = magic(qwq[j + 1], a[j]);
            qwq[L[i] + 4] = a[L[i] + 4];
            for (int j = L[i] + 5; j <= R[i]; ++j)
                qwq[j] = magic(qwq[j - 1], a[j]);
        }
        for (int j = L[i]; j <= R[i]; ++j)
            belong[j] = i;
    }
    build(1, 1, num);
}
ull query(int l, int r)
{
    if (belong[l] == belong[r])
    {
        if (l - L[belong[l]] + 1 <= 4 && 5 <= r - L[belong[r]] + 1)
            return magic(qwq[l], qwq[r]);
        ull res = a[l];
        for (int i = l + 1; i <= r; ++i)
            res = magic(res, a[i]);
        return res;
    }
    if (belong[l] + 1 == belong[r])
        return magic(suf[l], pre[r]);
    return magic(suf[l], magic(query(1, 1, num, belong[l] + 1, belong[r] - 1), pre[r]));
}
ull query(vector<int> fuck)
{
    sort(fuck.begin(), fuck.end());
    bool first = true;
    ull ans = 0;
    if (1 <= fuck.front())
    {
        if (first)
        {
            ans = query(1, fuck.front());
            first = false;
        }
        else
            ans = magic(ans, query(1, fuck.front()));
    }
    for (int i = 1; i < (int)fuck.size(); ++i)
    {
        if (fuck[i - 1] + 1 < fuck[i])
        {
            ull res = 0;
            for (int j = fuck[i - 1] + 2; j <= fuck[i]; ++j)
                res ^= a[j];
            if (first)
            {
                ans = query(fuck[i - 1] + 2, fuck[i]);
                first = false;
            }
            else
                ans = magic(ans, query(fuck[i - 1] + 2, fuck[i]));
        }
    }
    if (fuck.back() + 1 < n)
    {
        if (first)
        {
            ans = query(fuck.back() + 2, n);
            first = false;
        }
        else
            ans = magic(ans, query(fuck.back() + 2, n));
    }
    return ans;
}