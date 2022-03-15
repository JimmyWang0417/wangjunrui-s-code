#include <bits/stdc++.h>
#define ll long long
#define ull unsigned ll
#define lowbit(x) ((x) & (-(x)))
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
using namespace std;
const int N = 3e5 + 5;
int Log[N];
struct AC_automation
{
    int ch[N][26], nxt[N], cnt[N], root[25], tot, low[25];

    int n, m;
    int id[N];
    char str[N * 2];

    inline int newnode(int rt)
    {
        int u = ++tot;
        for (int c = 0; c < 26; ++c)
            ch[u][c] = rt;
        cnt[u] = 0;
        nxt[u] = rt;
        return u;
    }
    inline void insertstr(char *s, int rt)
    {
        int u = rt;
        for (int i = 0; s[i]; ++i)
        {
            int c = s[i] - 'a';
            if (ch[u][c] == rt)
                ch[u][c] = newnode(rt);
            u = ch[u][c];
        }
        ++cnt[u];
    }
    inline void build(int rt)
    {
        queue<int> q;
        for (int c = 0; c < 26; ++c)
            if (ch[rt][c] != rt)
                q.push(ch[rt][c]);
        while (!q.empty())
        {
            int u = q.front();
            q.pop();
            for (int c = 0; c < 26; ++c)
                if (ch[u][c] != rt)
                {
                    nxt[ch[u][c]] = ch[nxt[u]][c];
                    cnt[ch[u][c]] += cnt[nxt[ch[u][c]]];
                    q.push(ch[u][c]);
                }
                else
                    ch[u][c] = ch[nxt[u]][c];
        }
    }
    inline void insert(char *s)
    {
        id[++n] = m;
        for (int i = 0; s[i]; ++i)
            str[m++] = s[i];
        str[m++] = '\0';
        int len = Log[lowbit(n)];
        for (int i = 0; i < len; ++i)
            root[i] = 0;

        for (int i = len + 1; i <= 20; ++i)
            if (root[i])
            {
                tot = low[i];
                break;
            }

        root[len] = newnode(tot + 1);

        for (int i = (n ^ lowbit(n)) + 1; i <= n; ++i)
            insertstr(&str[id[i]], root[len]);
        low[len] = tot;
        build(root[len]);
    }
    inline ll query(char *s)
    {
        ll ans = 0;
        for (int i = Log[n]; i >= 0; --i)
        {
            int u = root[i];
            for (int j = 0; s[j]; ++j)
            {
                int c = s[j] - 'a';
                u = ch[u][c];
                ans += cnt[u];
            }
        }
        return ans;
    }
} add, del;
int n;
char str[N];
signed main()
{
    read(n);
    Log[0] = -1;
    for (int i = 1; i <= n; ++i)
        Log[i] = Log[i >> 1] + 1;
    for (int i = 1; i <= n; ++i)
    {
        int opt;
        read(opt);
        scanf("%s", str);
        if (opt == 1)
            add.insert(str);
        else if (opt == 2)
            del.insert(str);
        else
        {
            printf("%lld\n", add.query(str) - del.query(str));
            fflush(stdout);
        }
    }
    return 0;
}