/**
 *    unicode: UTF-8
 *    name:    #536. 「后缀数组」棕发少女
 *    author:  whitepaperdog (蒟蒻wjr)
 *    located: Changle District, Fuzhou City, Fujian Province, China
 *    created: 2023.02.07 周二 14:51:29 (Asia/Shanghai)
 **/
#include <bits/stl_pair.h>
#include <iostream>
#include <string>
typedef long long ll;
typedef unsigned long long ull;
__extension__ typedef __int128 int128;
template <typename T>
inline void ckmin(T &_x, T _y)
{
    if (_x > _y)
        _x = _y;
}
template <typename T>
inline void ckmax(T &_x, T _y)
{
    if (_x < _y)
        _x = _y;
}
using namespace std;
constexpr int N = 2e6 + 5;
constexpr int M = 55;
int lens;
string a, b, s;
string str[4];
string f[M];
int lenf[M], cntf, cntg;
int leng[M], cntA[M], cntB[M], cnt[M][4];
bool L[M], R[M];
namespace SA
{
    int n;
    int str[N];
    int wa[N], wb[N], ws[N];
    int sa[N], rk[N], height[N];
    int Log[N], dp[N][25];
    inline void solve(int m)
    {
        int *x = wa, *y = wb;

        for (int i = 1; i <= n; ++i)
            ++ws[x[i] = str[i]];
        for (int i = 2; i <= m; ++i)
            ws[i] += ws[i - 1];
        for (int i = n; i >= 1; --i)
            sa[ws[x[i]]--] = i;
        fill(ws + 1, ws + 1 + m, 0);
        for (int j = 1, p = 0; p < n; m = p, j <<= 1)
        {
            p = 0;
            for (int i = n - j + 1; i <= n; ++i)
                y[++p] = i;
            for (int i = 1; i <= n; ++i)
                if (sa[i] > j)
                    y[++p] = sa[i] - j;

            for (int i = 1; i <= n; ++i)
                ++ws[x[i]];
            for (int i = 2; i <= m; ++i)
                ws[i] += ws[i - 1];
            for (int i = n; i >= 1; --i)
                sa[ws[x[y[i]]]--] = y[i];
            fill(ws + 1, ws + 1 + m, 0);

            swap(x, y);
            p = 0;
            for (int i = 1; i <= n; ++i)
                x[sa[i]] = y[sa[i - 1]] == y[sa[i]] && y[sa[i - 1] + j] == y[sa[i] + j] ? p : ++p;
        }
        for (int i = 1; i <= n; ++i)
            rk[sa[i]] = i;
        for (int i = 1, j = 0; i <= n; ++i)
        {
            if (j)
                --j;
            while (str[i + j] == str[sa[rk[i] - 1] + j])
                ++j;
            height[rk[i]] = j;
        }
        Log[0] = -1;
        for (int i = 1; i <= n; ++i)
        {
            dp[i][0] = height[i];
            Log[i] = Log[i >> 1] + 1;
        }
        for (int j = 0; j < Log[n]; ++j)
            for (int i = 1; i + (2 << j) - 1 <= n; ++i)
                dp[i][j + 1] = min(dp[i][j], dp[i + (1 << j)][j]);
    }
    inline int _lcp(int x, int y)
    {
        ++x;
        int k = Log[y - x + 1];
        return min(dp[x][k], dp[y - (1 << k) + 1][k]);
    }
    inline int lcp(int x, int y)
    {
        x = rk[x], y = rk[y];
        if (x > y)
            swap(x, y);
        return _lcp(x, y);
    }
    struct Tree
    {
        int l, r;
        int size;
    } tree[N * 50];
#define lc(rt) tree[rt].l
#define rc(rt) tree[rt].r
    int root[N], cnt;
    inline void update(int pre, int &rt, int l, int r, int pos)
    {
        rt = ++cnt;
        tree[rt] = tree[pre];
        ++tree[rt].size;
        if (l == r)
            return;
        int mid = (l + r) >> 1;
        if (pos <= mid)
            update(lc(pre), lc(rt), l, mid, pos);
        else
            update(rc(pre), rc(rt), mid + 1, r, pos);
    }
    inline int query(int rootl, int rootr, int l, int r, int x, int y)
    {
        if (r < x || l > y)
            return 0;
        if (x <= l && r <= y)
            return tree[rootr].size - tree[rootl].size;
        int mid = (l + r) >> 1;
        return query(lc(rootl), lc(rootr), l, mid, x, y) + query(rc(rootl), rc(rootr), mid + 1, r, x, y);
    }
    inline void build()
    {
        for (int i = 1; i <= n; ++i)
            update(root[i - 1], root[i], 1, n, rk[i]);
    }
    inline void print()
    {
        for (int i = 1; i <= n; ++i)
            printf("%d ", rk[i]);
        putchar('\n');
        for (int i = 1; i <= n; ++i)
            printf("%d ", height[i]);
        putchar('\n');
    }
}
int wheres, where[N];
int whereA, whereB, wherestr[4];
int p[N], tot, lpos, rpos;
inline void solve(int n, int l, int r)
{
    // cout << n << ' ' << l << ' ' << r << endl;
    if (l == 1 && r == leng[n])
    {
        p[++tot] = n;
        return;
    }
    // printf("%d %d %d\n", n, l, r);
    if (n <= 1)
    {
        p[++tot] = n;
        if (l != 1)
            lpos = l;
        if (r != leng[n])
            rpos = r;
        return;
    }
    int mid = leng[n - 1];
    if (l <= mid)
        solve(n - 1, l, min(r, mid));
    if (r > mid)
        solve(n - 2, max(l - mid, 1), r - mid);
}
signed main()
{
#ifdef PAPERDOG
    freopen("project.in", "r", stdin);
    freopen("project.out", "w", stdout);
#else
    freopen("string.in", "r", stdin);
    freopen("string.out", "w", stdout);
#endif
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    cin >> a >> b >> s;
    lenf[0] = (int)a.length();
    lenf[1] = (int)b.length();
    lens = (int)s.length();
    f[0] = a, f[1] = b;
    for (int &i = cntf = 2;; ++i)
    {
        lenf[i] = lenf[i - 1] + lenf[i - 2];
        f[i] = f[i - 1] + f[i - 2];
        if (lenf[i - 1] >= lens)
            break;
    }
    leng[0] = lenf[cntf - 1];
    leng[1] = lenf[cntf];
    cntA[0] = cntB[1] = 1;
    L[0] = R[0] = 0;
    L[1] = R[1] = 1;
    // cout << f[cntf] << ' ' << f[cntf - 1] << endl;
    for (int &i = cntg = 2;; ++i)
    {
        leng[i] = leng[i - 1] + leng[i - 2];
        L[i] = L[i - 1], R[i] = R[i - 2];
        cntA[i] = cntA[i - 1] + cntA[i - 2];
        cntB[i] = cntB[i - 1] + cntB[i - 2];
        for (int j = 0; j < 4; ++j)
            cnt[i][j] = cnt[i - 1][j] + cnt[i - 2][j];
        ++cnt[i][(R[i - 1] << 1) | L[i - 2]];
        if (leng[i] > (int)1e9)
            break;
    }
    // cout << f[cntf] << endl;
    int m = 26;
    for (int i = 0; i <= cntf; ++i)
    {
        where[i] = SA::n;
        for (int j : f[i])
            SA::str[++SA::n] = j - 'a' + 1;
        SA::str[++SA::n] = ++m;
    }

    wheres = SA::n;
    for (auto i : s)
        SA::str[++SA::n] = i - 'a' + 1;
    SA::str[++SA::n] = ++m;

    str[0] = f[cntf - 1] + f[cntf - 1];
    str[1] = f[cntf - 1] + f[cntf];
    str[2] = f[cntf] + f[cntf - 1];
    str[3] = f[cntf] + f[cntf];
    for (int i = 0; i < 4; ++i)
    {
        wherestr[i] = SA::n;
        for (auto j : str[i])
            SA::str[++SA::n] = j - 'a' + 1;
        SA::str[++SA::n] = ++m;
    }
    whereA = where[cntf - 1];
    whereB = where[cntf];
    SA::solve(m);
    SA::build();
    int q;
    cin >> q;
    while (q--)
    {
        int n, l, r, x, y;
        cin >> n >> l >> r >> x >> y;
        if (r - l + 1 < y - x + 1)
        {
            cout << 0 << endl;
            continue;
        }
        if (n <= cntf)
        {
            int pos = SA::rk[x + wheres], len = y - x + 1;
            r = r - len + 1;
            int _l = 1, _r = pos - 1, ansl = pos;
            while (_l <= _r)
            {
                int mid = (_l + _r) >> 1;
                if (SA::_lcp(mid, pos) >= len)
                {
                    ansl = mid;
                    _r = mid - 1;
                }
                else
                    _l = mid + 1;
            }
            _l = pos + 1, _r = SA::n;
            int ansr = pos;
            while (_l <= _r)
            {
                int mid = (_l + _r) >> 1;
                if (SA::_lcp(pos, mid) >= len)
                {
                    ansr = mid;
                    _l = mid + 1;
                }
                else
                    _r = mid - 1;
            }
            cout << SA::query(SA::root[where[n] + l - 1], SA::root[where[n] + r], 1, SA::n, ansl, ansr) << endl;
        }
        else
        {
            int pos = SA::rk[x + wheres], len = y - x + 1;
            int _l = 1, _r = pos - 1, ansl = pos;
            while (_l <= _r)
            {
                int mid = (_l + _r) >> 1;
                if (SA::_lcp(mid, pos) >= len)
                {
                    ansl = mid;
                    _r = mid - 1;
                }
                else
                    _l = mid + 1;
            }
            _l = pos + 1, _r = SA::n;
            int ansr = pos;
            while (_l <= _r)
            {
                int mid = (_l + _r) >> 1;
                if (SA::_lcp(pos, mid) >= len)
                {
                    ansr = mid;
                    _l = mid + 1;
                }
                else
                    _r = mid - 1;
            }
            tot = lpos = rpos = 0;
            solve(n - cntf + 1, l, r);
            int valA = SA::query(SA::root[whereA], SA::root[whereA + leng[0]], 1, SA::n, ansl, ansr);
            int valB = SA::query(SA::root[whereB], SA::root[whereB + leng[1]], 1, SA::n, ansl, ansr);
            int valstr[] = {
                SA::query(SA::root[wherestr[0]], SA::root[wherestr[0] + leng[0] + leng[0]], 1, SA::n, ansl, ansr) - valA - valA,
                SA::query(SA::root[wherestr[1]], SA::root[wherestr[1] + leng[0] + leng[1]], 1, SA::n, ansl, ansr) - valA - valB,
                SA::query(SA::root[wherestr[2]], SA::root[wherestr[2] + leng[1] + leng[0]], 1, SA::n, ansl, ansr) - valB - valA,
                SA::query(SA::root[wherestr[3]], SA::root[wherestr[3] + leng[1] + leng[1]], 1, SA::n, ansl, ansr) - valB - valB};
            int answer = 0;
            for (int i = 1; i <= tot; ++i)
            {
                int u = p[i];
                l = (i == 1 && lpos) ? lpos : 1, r = (i == tot && rpos) ? rpos : leng[u];
                if (l == 1 && r == leng[u])
                {
                    answer += valA * cntA[u] + valB * cntB[u];
                    for (int j = 0; j < 4; ++j)
                        answer += cnt[u][j] * valstr[j];
                }
                else
                {
                    if (r - l + 1 >= len)
                    {
                        int rt = !u ? whereA : whereB;
                        answer += SA::query(SA::root[rt + l - 1], SA::root[rt + r - len + 1], 1, SA::n, ansl, ansr);
                    }
                }
            }
            for (int i = 1; i < tot; ++i)
            {
                int u = p[i], v = p[i + 1];
                l = (i == 1 && lpos) ? lpos : 1, r = leng[R[u]] + ((i + 1 == tot && rpos) ? rpos : leng[L[v]]);
                if (l == 1 && r == leng[R[u]] + leng[L[v]])
                    answer += valstr[(R[u] << 1) | L[v]];
                else
                {
                    int rt = wherestr[(R[u] << 1) | L[v]];
                    int rtl = max(leng[R[u]] - len + 1, l - 1), rtr = min(leng[R[u]], r - len + 1);
                    if (rtl <= rtr)
                        answer += SA::query(SA::root[rt + rtl], SA::root[rt + rtr], 1, SA::n, ansl, ansr);
                }
            }
            cout << answer << endl;
        }
    }
    return 0;
}