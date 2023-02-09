#include <cstdio>
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
constexpr int N = 3e5 + 5;
int n, q, mod, a[N];
int answer;
int dp[N];
inline void add(int &x, int y)
{
    x += y;
    if (x >= mod)
        x -= mod;
}
inline void del(int &x, int y)
{
    x -= y;
    if (x < 0)
        x += mod;
}
signed main()
{
    read(n, q, mod);
    dp[1] = dp[2] = 1;
    for (int i = 3; i <= n; ++i)
        dp[i] = (dp[i - 1] + dp[i - 2]) % mod;
    for (int i = 1; i <= n; ++i)
        read(a[i]);
    for (int i = 1; i <= n; ++i)
    {
        int x;
        read(x);
        del(a[i], x);
    }
    answer += (bool)a[1];
    for (int i = n; i > 1; --i)
    {
        del(a[i], a[i - 1]);
        del(a[i], a[i - 2]);
        answer += (bool)a[i];
    }
    while (q--)
    {
        char str[5];
        scanf("%s", str);
        int l, r;
        read(l, r);
        if (str[0] == 'A')
        {
            answer -= (bool)a[l];
            add(a[l], 1);
            answer += (bool)a[l];
            if (r < n)
            {
                answer -= (bool)a[r + 1];
                del(a[r + 1], dp[r - l + 2]);
                answer += (bool)a[r + 1];
                if (r + 1 < n)
                {
                    answer -= (bool)a[r + 2];
                    del(a[r + 2], dp[r - l + 1]);
                    answer += (bool)a[r + 2];
                }
            }
        }
        else
        {
            answer -= (bool)a[l];
            del(a[l], 1);
            answer += (bool)a[l];
            if (r < n)
            {
                answer -= (bool)a[r + 1];
                add(a[r + 1], dp[r - l + 2]);
                answer += (bool)a[r + 1];
                if (r + 1 < n)
                {
                    answer -= (bool)a[r + 2];
                    add(a[r + 2], dp[r - l + 1]);
                    answer += (bool)a[r + 2];
                }
            }
        }
        printf(answer ? "No\n" : "Yes\n");
    }
    return 0;
}