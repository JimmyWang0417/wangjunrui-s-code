#include <algorithm>
#include <cstdio>
#include <list>
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
constexpr int N = 1e4 + 5, M = 205;

int n, m, H;

int h[N];

namespace ST
{
    int logx[N];
    int f[14][N];
    void build()
    {
        logx[0] = -1;
        for (int i = 1; i <= n; i++)
            logx[i] = logx[i >> 1] + 1;
        for (int i = 1; i <= n; i++)
            f[0][i] = H - h[i];
        for (int j = 1; j <= 13; j++)
            for (int i = 1; i <= n - (1 << j) + 1; i++)
                f[j][i] = max(f[j - 1][i], f[j - 1][i + (1 << (j - 1))]);
    }
    int query(int l, int r)
    {
        int k = logx[r - l + 1];
        return max(f[k][l], f[k][r - (1 << k) + 1]);
    }
} // namespace ST
int len, mapval[M * 2];
int turn(int x) { return lower_bound(mapval + 1, mapval + 1 + len, x) - mapval; }
int qL(int x, int a)
{
    int l = 1, r = x;
    while (l < r)
    {
        int mid = (l + r) >> 1;
        if (a > ST::query(mid + 1, x))
            r = mid;
        else
            l = mid + 1;
    }
    return l;
}
int qR(int x, int a)
{
    int l = x, r = n;
    while (l < r)
    {
        int mid = (l + r + 1) >> 1;
        if (a > ST::query(x, mid - 1))
            l = mid;
        else
            r = mid - 1;
    }
    return l;
}
struct range
{
    int l, r;
} seq[M];
int cnt[M * 2];
ll f[M * 2][M * 2];
int main()
{
#ifdef ONLINE_JUDGE
    freopen("strange.in", "r", stdin);
    freopen("strange.out", "w", stdout);
#endif
    read(n, m, H);
    for (int i = 1; i <= n; i++)
        read(h[i]);
    ST::build();
    for (int i = 1, x, a; i <= m; i++)
    {
        read(x), read(a);
        seq[i].l = qL(x, a), seq[i].r = qR(x, a);
        mapval[++len] = seq[i].l, mapval[++len] = seq[i].r;
    }
    sort(mapval + 1, mapval + 1 + len);
    len = unique(mapval + 1, mapval + 1 + len) - mapval - 1;
    for (int i = 1; i <= m; i++)
        seq[i].l = turn(seq[i].l), seq[i].r = turn(seq[i].r);
    for (int length = 1; length <= len; length++)
    {
        for (int l = 1; l <= len - length + 1; l++)
        {
            int r = l + length - 1;
            for (int i = l; i <= r; i++)
                cnt[i] = 0;
            for (int i = 1; i <= m; i++)
                if (seq[i].l >= l && seq[i].r <= r)
                    cnt[seq[i].l]++, cnt[seq[i].r + 1]--;
            for (int i = l + 1; i <= r; i++)
                cnt[i] += cnt[i - 1];
            for (int i = l; i <= r; i++)
                f[l][r] = max(f[l][r], f[l][i - 1] + f[i + 1][r] + 1ll * cnt[i] * (cnt[i] - 1) / 2);
        }
    }
    printf("%lld\n", f[1][len]);
    return 0;
}
