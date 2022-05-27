#include <bits/stdc++.h>
#define ll long long
#define ull unsigned ll
#define lowbit(x) (x & (-x))
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
const int N = 1005, M = N * N;
const int mod = 998244353;
int n, m, a[N][N];
int p[M], tot;
struct node
{
    int x, y, v;
    inline bool operator<(const node &rhs) const
    {
        return v < rhs.v;
    }
} b[M];
int cnt;
int sumx[M], sumy[M], size[M];
ll sumxx[M], sumyy[M], sum[M];
int r, c;
ll inv[M];
signed main()
{
    read(n, m);
    inv[1] = 1;
    for (int i = 2; i <= n * m; ++i)
        inv[i] = (mod - mod / i) * inv[mod % i] % mod;
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= m; ++j)
        {
            read(a[i][j]);
            p[++tot] = a[i][j];
            ++cnt;
            b[cnt].x = i, b[cnt].y = j, b[cnt].v = a[i][j];
        }
    read(r, c);
    sort(p + 1, p + 1 + tot);
    tot = (int)(unique(p + 1, p + 1 + tot) - p - 1);
    sort(b + 1, b + 1 + cnt);
    b[0].v = -1;
    for (int i = 1, now = 0; i <= cnt; ++i)
    {
        if (b[i].v != b[i - 1].v)
        {
            ++now;
            size[now] = size[now - 1] + 1;
            sumx[now] = sumx[now - 1] + b[i].x;
            sumy[now] = sumy[now - 1] + b[i].y;
            sumxx[now] = sumxx[now - 1] + b[i].x * b[i].x;
            sumyy[now] = sumyy[now - 1] + b[i].y * b[i].y;
        }
        else
        {
            ++size[now];
            sumx[now] += b[i].x;
            sumy[now] += b[i].y;
            sumxx[now] += b[i].x * b[i].x;
            sumyy[now] += b[i].y * b[i].y;
        }
    }
    int now = (int)(lower_bound(p + 1, p + 1 + tot, a[r][c]) - p);
    if (!size[now - 1])
    {
        printf("0\n");
        return 0;
    }
    ll ans = (r * r + c * c + (sumxx[now - 1] + sumyy[now - 1] - 2ll * sumx[now - 1] * r - 2ll * sumy[now - 1] * c) % mod * inv[size[now - 1]] % mod) % mod;
    sum[now - 1] = inv[size[now - 1]];
    int i = cnt;
    for (; b[i].v >= p[now]; --i)
        ;
    for (; i >= 1; --i)
    {
        if (b[i].v != b[i + 1].v)
        {
            --now;
            if (!size[now - 1])
                break;
            sum[now] += sum[now + 1];
            (ans += ((b[i].x * b[i].x + b[i].y * b[i].y + (sumxx[now - 1] + sumyy[now - 1] - 2ll * sumx[now - 1] * b[i].x - 2ll * sumy[now - 1] * b[i].y) % mod * inv[size[now - 1]] % mod) * inv[size[now]] % mod)) %= mod;
            sum[now - 1] += inv[size[now - 1]];
        }
        else
        {
            (ans += ((b[i].x * b[i].x + b[i].y * b[i].y + (sumxx[now - 1] + sumyy[now - 1] - 2ll * sumx[now - 1] * b[i].x - 2ll * sumy[now - 1] * b[i].y) % mod * inv[size[now - 1]] % mod) * inv[size[now]] % mod)) %= mod;
            sum[now - 1] += inv[size[now - 1]];
        }
    }
    printf("%lld\n", (ans + mod) % mod);
    return 0;
}