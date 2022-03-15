#include <bits/stdc++.h>
#include <bits/extc++.h>
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
const int N = 4e5 + 5;
class SAM
{
public:
    int n;
    struct Point
    {
        int ch[26];
        int fa, len;
    } point[N];
    int las = 1, tot = 1;
    int pos[N];
    int f[N];
    inline int insert(int c)
    {
        int p = las, np = las = ++tot;
        point[np].len = point[p].len + 1;
        for (; p && !point[p].ch[c]; p = point[p].fa)
            point[p].ch[c] = np;
        if (!p)
            point[np].fa = 1;
        else
        {
            int q = point[p].ch[c];
            if (point[q].len == point[p].len + 1)
                point[np].fa = q;
            else
            {
                int nq = ++tot;
                point[nq] = point[q];
                point[nq].len = point[p].len + 1;
                point[q].fa = point[np].fa = nq;
                for (; p && point[p].ch[c] == q; p = point[p].fa)
                    point[p].ch[c] = nq;
            }
        }
        return np;
    }
    inline void insert(string s)
    {
        n = (int)s.length();
        for (int i = 0; i < n; ++i)
            pos[i] = insert(s[i] - 'a');
    }
    inline void update(string s)
    {
        int u = 1;
        for (int i = 0; u && i < (int)s.length(); ++i)
            u = point[u].ch[s[i] - 'a'];
        if (u)
            ++f[u];
    }
    int ws[N];
    int a[N];
    inline void init()
    {
        for (int i = 1; i <= tot; ++i)
            ++ws[point[i].len];
        for (int i = 1; i <= n; ++i)
            ws[i] += ws[i - 1];
        for (int i = tot; i >= 1; --i)
            a[ws[point[i].len]--] = i;
        for (int i = 1; i <= tot; ++i)
        {
            int u = a[i];
            f[u] += f[point[u].fa];
        }
    }
} pre, suf;
string T, S[N];
int n;
signed main()
{
    ios::sync_with_stdio(false);
    cin >> T >> n;
    for (int i = 1; i <= n; ++i)
        cin >> S[i];
    pre.insert(T);
    for (int i = 1; i <= n; ++i)
        pre.update(S[i]);
    pre.init();
    // for (int i = 0; i < pre.n; ++i)
    //     printf("%d %d %d\n", i, pre.pos[i], pre.f[pre.pos[i]]);

    reverse(T.begin(), T.end());
    suf.insert(T);
    for (int i = 1; i <= n; ++i)
    {
        reverse(S[i].begin(), S[i].end());
        suf.update(S[i]);
    }
    suf.init();
    // for (int i = suf.n - 1; i >= 0; --i)
    //     printf("%d %d %d\n", suf.n - i - 1, suf.pos[i], suf.f[suf.pos[i]]);
    ll answer = 0;
    for (int i = 0; i < pre.n - 1; ++i)
        answer += (ll)pre.f[pre.pos[i]] * suf.f[suf.pos[suf.n - i - 2]];
    printf("%lld\n", answer);
    return 0;
}