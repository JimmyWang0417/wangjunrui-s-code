#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstring>
#pragma GCC optimize(3)
#pragma GCC optimize("Ofast")
#pragma GCC optimize("inline")
#pragma GCC optimize("-fgcse")
#pragma GCC optimize("-fgcse-lm")
#pragma GCC optimize("-fipa-sra")
#pragma GCC optimize("-ftree-pre")
#pragma GCC optimize("-ftree-vrp")
#pragma GCC optimize("-fpeephole2")
#pragma GCC optimize("-ffast-math")
#pragma GCC optimize("-fsched-spec")
#pragma GCC optimize("unroll-loops")
#pragma GCC optimize("-falign-jumps")
#pragma GCC optimize("-falign-loops")
#pragma GCC optimize("-falign-labels")
#pragma GCC optimize("-fdevirtualize")
#pragma GCC optimize("-fcaller-saves")
#pragma GCC optimize("-fcrossjumping")
#pragma GCC optimize("-fthread-jumps")
#pragma GCC optimize("-funroll-loops")
#pragma GCC optimize("-fwhole-program")
#pragma GCC optimize("-freorder-blocks")
#pragma GCC optimize("-fschedule-insns")
#pragma GCC optimize("inline-functions")
#pragma GCC optimize("-ftree-tail-merge")
#pragma GCC optimize("-fschedule-insns2")
#pragma GCC optimize("-fstrict-aliasing")
#pragma GCC optimize("-fstrict-overflow")
#pragma GCC optimize("-falign-functions")
#pragma GCC optimize("-fcse-skip-blocks")
#pragma GCC optimize("-fcse-follow-jumps")
#pragma GCC optimize("-fsched-interblock")
#pragma GCC optimize("-fpartial-inlining")
#pragma GCC optimize("no-stack-protector")
#pragma GCC optimize("-freorder-functions")
#pragma GCC optimize("-findirect-inlining")
#pragma GCC optimize("-frerun-cse-after-loop")
#pragma GCC optimize("inline-small-functions")
#pragma GCC optimize("-finline-small-functions")
#pragma GCC optimize("-ftree-switch-conversion")
#pragma GCC optimize("-foptimize-sibling-calls")
#pragma GCC optimize("-fexpensive-optimizations")
#pragma GCC optimize("-funsafe-loop-optimizations")
#pragma GCC optimize("inline-functions-called-once")
#pragma GCC optimize("-fdelete-null-pointer-checks")
#define re register
#define ll long long
#define ull unsigned long long
#define rep(i, a, b) for (re int i = a; i <= b; ++i)
#define per(i, a, b) for (re int i = a; i >= b; --i)
using namespace std;
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
const int N = 5e4 + 5;
int n, m, k, a[N];
int block, belong[N];
int cnt[N];
struct Queue
{
    int l, r, id;
    inline bool operator<(const Queue &rhs) const
    {
        return belong[l] == belong[rhs.l] ? (belong[l] & 1 ? r < rhs.r : r > rhs.r) : l < rhs.l;
    }
} q[N];
ll ans;
inline void add(int pos)
{
    ans += 2 * cnt[a[pos]] + 1;
    ++cnt[a[pos]];
}
inline void del(int pos)
{
    ans += -2 * cnt[a[pos]] + 1;
    --cnt[a[pos]];
}
ll answer[N];
signed main()
{
    read(n, m, k);
    block = (int)sqrt(n);
    for (re int i = 1; i <= n; ++i)
    {
        read(a[i]);
        belong[i] = (i - 1) / block + 1;
    }
    for (re int i = 1; i <= m; ++i)
    {
        read(q[i].l, q[i].r);
        q[i].id = i;
    }
    sort(q + 1, q + 1 + m);
    int l = 1, r = 0;
    for (re int i = 1; i <= m; ++i)
    {
        const int &ql = q[i].l, &qr = q[i].r;
        //		printf("%d %d\n",ql,qr);
        while (ql < l)
            add(--l);
        while (ql > l)
            del(l++);
        while (qr < r)
            del(r--);
        while (qr > r)
            add(++r);
        answer[q[i].id] = ans;
    }
    for (re int i = 1; i <= m; ++i)
        printf("%lld\n", answer[i]);
    return 0;
}
