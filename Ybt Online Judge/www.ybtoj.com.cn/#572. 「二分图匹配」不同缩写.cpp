#include <bits/stdc++.h>
#define lowbit(x) ((x) & (-(x)))
#define re register
#define ll long long
#define ull unsigned long long
#define rep(i, a, b) for (re int i = a; i <= b; ++i)
#define per(i, a, b) for (re int i = a; i >= b; --i)
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
inline void clear(T *array, int l, int r, int val)
{
    memset(&array[l], val, sizeof(T) * (r - l + 1));
}
using namespace std;
const int N = 305 + 5, M = N * N;
int n;
int maxlen;
struct node
{
    char s[N];
    int len;
    int nxt[N][26];
    int begin[26];

    int cnt;
    string ss[N];

    pair<string, int> q[N];
    int head, tail;
    inline void dfs(int pos, string now)
    {
        if (cnt >= n)
            return;
        if (pos == len)
            return;
        now.push_back(s[pos]);
        if ((int)now.length() > maxlen)
            return;
        ss[++cnt] = now;
        for (int i = 0; i < 26; ++i)
            dfs(nxt[pos][i], now);
    }

    inline void init()
    {
        len = (int)strlen(s);
        int end = len - 1;
        for (int c = 0; c < 26; ++c)
            nxt[end][c] = end + 1;
        for (int i = end - 1; i >= 0; --i)
        {
            for (int c = 0; c < 26; ++c)
                nxt[i][c] = nxt[i + 1][c];
            nxt[i][s[i + 1] - 'a'] = i + 1;
        }
        for (int i = 0; i < 26; ++i)
            begin[i] = nxt[0][i];
        begin[s[0] - 'a'] = 0;
    }
    inline void solve()
    {
        cnt = 0;
        head = 1, tail = 0;
        for (int i = 0; i < 26; ++i)
            if (begin[i] != len)
                q[++tail] = make_pair(((string) "\0" + (char)(i + 'a')), begin[i]);
        //		for(int i=0;i<26;++i)
        //		cout<<begin[i]<<' ';
        //		cout<<endl;
        //		for(int i=0; i<26; ++i)
        //			cout<<((string)"\0"+(char)(i+'a'))<<' ';
        //		cout<<endl;
        while (head <= tail)
        {
            ss[++cnt] = q[head].first;
            //			cout<<q[head].first<<' '<<q[head].second<<endl;
            for (int i = 0; i < 26; ++i)
                if (nxt[q[head].second][i] != len && tail < n)
                {
                    pair<string, int> now = make_pair(q[head].first + (char)(i + 'a'), nxt[q[head].second][i]);
                    if (now.first.length() > maxlen)
                        continue;
                    q[++tail] = now;
                }
            ++head;
        }
        //		cout<<endl;
    }
} a[N];

string p[M];
struct Edge
{
    int next, to;
} edge[M];
int head[M], num_edge;
inline void add_edge(int from, int to)
{
    edge[++num_edge].next = head[from];
    edge[num_edge].to = to;
    head[from] = num_edge;
}
int belong[M];
int out[N];
bool vis[M];
inline bool find(int u)
{
    for (int i = head[u]; i; i = edge[i].next)
    {
        int &v = edge[i].to;
        if (vis[v])
            continue;
        vis[v] = true;
        if (!belong[v] || find(belong[v]))
        {
            belong[v] = u;
            out[u] = v;
            return true;
        }
    }
    return false;
}
unordered_map<string, int> mp;
inline bool check(int val)
{
    mp.clear();
    int m = 0;
    for (int i = 1; i <= n; ++i)
    {
        for (int j = 1; j <= a[i].cnt && a[i].ss[j].length() <= val; ++j)
            if (!mp.count(a[i].ss[j]))
                mp[a[i].ss[j]] = ++m;
    }
    //	cout<<"val="<<val<<' '<<m<<endl;
    //	for(int i=1; i<=n; ++i)
    //		cout<<' '<<a[i].cnt;
    //	cout<<endl;
    memset(head, 0, sizeof(head));
    num_edge = 0;
    for (int i = 1; i <= n; ++i)
    {
        for (int j = 1; j <= a[i].cnt && a[i].ss[j].length() <= val; ++j)
            add_edge(i, mp[a[i].ss[j]] + n);
    }
    memset(belong, 0, sizeof(belong));
    for (int i = 1; i <= n; ++i)
    {
        memset(vis, 0, sizeof(vis));
        if (!find(i))
            return false;
    }
    return true;
}
inline void print(int val)
{
    mp.clear();
    int m = 0;
    for (int i = 1; i <= n; ++i)
    {
        for (int j = 1; j <= a[i].cnt && a[i].ss[j].length() <= val; ++j)
            if (!mp.count(a[i].ss[j]))
            {
                mp[a[i].ss[j]] = ++m;
                p[m] = a[i].ss[j];
            }
    }
    memset(head, 0, sizeof(head));
    num_edge = 0;
    for (int i = 1; i <= n; ++i)
    {
        for (int j = 1; j <= a[i].cnt && a[i].ss[j].length() <= val; ++j)
            add_edge(i, mp[a[i].ss[j]] + n);
    }
    memset(belong, 0, sizeof(belong));
    for (int i = 1; i <= n; ++i)
    {
        memset(vis, 0, sizeof(vis));
        find(i);
    }
    for (int i = 1; i <= n; ++i)
        cout << p[out[i] - n] << endl;
}
signed main()
{
    freopen("diff.in", "r", stdin), freopen("diff.out", "w", stdout);
    scanf("%d", &n);
    maxlen = 300;
    for (int i = 1; i <= n; ++i)
    {
        scanf("%s", a[i].s);
        a[i].init();
        a[i].solve();
        //		for(int j=1; j<=a[i].cnt; ++j)
        //			cout<<a[i].ss[j]<<' ';
        //		cout<<endl;
    }
    //	printf("%d\n",check(1));
    int l = 1, r = 300, ans = -1;
    while (l <= r)
    {
        int mid = (l + r) >> 1;
        if (check(mid))
        {
            ans = mid;
            r = mid - 1;
        }
        else
            l = mid + 1;
    }
    ios::sync_with_stdio(false);
    cout << ans << endl;
    if (~ans)
        print(ans);
    return 0;
}
