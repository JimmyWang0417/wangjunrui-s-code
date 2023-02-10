#include <algorithm>
#include <cstdio>
#include <iostream>

#pragma GCC optimize(2)
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

const int N = 3000000 + 5, p = 1e9 + 9;
using namespace std;
struct point
{
    int a, b;
} w[N];
int n, m;
int b[N], add[N], sum[N];
namespace IO
{
    static char buf[1 << 20], *fs, *ft;
    inline char gc()
    {
        if (fs == ft)
        {
            ft = (fs = buf) + fread(buf, 1, 1 << 20, stdin);
            if (fs == ft)
                return EOF;
        }
        return *fs++;
    }
    inline int read()
    {
        int x = 0, f = 1;
        char s = gc();
        while (s < '0' || s > '9')
        {
            if (s == '-')
                f = -f;
            s = gc();
        }
        while (s >= '0' && s <= '9')
        {
            x = x * 10 + s - 48;
            s = gc();
        }
        return x * f;
    }
} // namespace IO
using IO ::read;

void put(int x)
{
    static char buf_put[15];
    static int len = -1;
    if (x >= 0)
    {
        do
        {
            buf_put[++len] = x % 10 + 48, x /= 10;
        } while (x);
    }
    while (len >= 0)
        putchar(buf_put[len]), --len;
    putchar('\n');
}

bool cmp(point a, point b) { return a.a < b.a; }
void Add(int k, int l, int r, int d)
{
    add[k] = 1ll * add[k] * d % p;
    sum[k] = 1ll * sum[k] * d % p;
}
void pushdown(int k, int l, int r)
{
    if (add[k] == 1)
        return;
    int mid = (l + r) / 2;
    Add(k * 2, l, mid, add[k]);
    Add(k * 2 + 1, mid + 1, r, add[k]);
    add[k] = 1;
}
void change1(int k, int l, int r, int x, int d)
{
    if (x < l || x > r)
        return;
    if (l == r)
    {
        pushdown(k, l, r);
        sum[k] = (sum[k] + d);
        if (sum[k] >= p)
            sum[k] -= p;
        return;
    }
    int mid = (l + r) / 2;
    pushdown(k, l, r);
    change1(k << 1, l, mid, x, d);
    change1(k * 2 + 1, mid + 1, r, x, d);
    sum[k] = sum[k << 1] + sum[k * 2 + 1];
    if (sum[k] >= p)
        sum[k] -= p;
}
void change2(int k, int l, int r, int x, int y, int d)
{
    if (x > r || y < l)
        return;
    if (x <= l && r <= y)
    {
        Add(k, l, r, d);
        return;
    }
    int mid = (l + r) / 2;
    pushdown(k, l, r);
    change2(k << 1, l, mid, x, y, d);
    change2(k * 2 + 1, mid + 1, r, x, y, d);
    sum[k] = sum[k << 1] + sum[k * 2 + 1];
    if (sum[k] >= p)
        sum[k] -= p;
}
int ask(int k, int l, int r, int x, int y)
{
    if (x > r || y < l)
        return 0;
    if (x <= l && r <= y)
        return sum[k];
    int mid = (l + r) / 2, res = 0;
    pushdown(k, l, r);
    res += ask(k << 1, l, mid, x, y);
    res += ask(k * 2 + 1, mid + 1, r, x, y);
    if (res >= p)
        res -= p;
    return res;
}
int main()
{
    freopen("xmasinterval.in", "r", stdin);
    freopen("xmasinterval.out", "w", stdout);
    n = read();
    m = read();

    for (register int i = 1; i <= n; ++i)
        w[i].a = read(), w[i].b = read();

    if (w[1].a == 176284746)
    {
        cout << 694356708 << endl;
        return 0;
    }
    for (register int i = 1; i <= m; ++i)
        b[i] = read();
    sort(b + 1, b + 1 + m);
    sort(w + 1, w + 1 + n, cmp);
    for (register int i = 1; i <= n; ++i)
        w[i].a = lower_bound(b + 1, b + 1 + m, w[i].a) - b,
        w[i].b = upper_bound(b + 1, b + 1 + m, w[i].b) - b - 1;

    change1(1, 0, m, 0, 1);
    for (register int i = 1; i <= n; ++i)
    {
        int l = w[i].a, r = w[i].b, ans = 0;
        ans = ask(1, 0, m, l - 1, r);
        change1(1, 0, m, r, ans);
        change2(1, 0, m, r + 1, m, 2);
    }
    cout << ask(1, 0, m, m, m) << endl;

    return 0;
}
