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
using namespace std;
const int N = 1e5 + 5;
int n, m;
unordered_map<int, int> mp;
int cnt;
vector<int> g[N * 2];
int a[N];
signed main()
{
    read(n, m);
    for (int i = 1; i <= n; ++i)
    {
        read(a[i]);
        if (!mp[a[i]])
            mp[a[i]] = ++cnt;
        a[i] = mp[a[i]];
        g[a[i]].push_back(i);
    }
    for (int i = 1; i <= m; ++i)
    {
        char opt[4];
        scanf("%s", opt);
        if (opt[0] == 'Q')
        {
            int l, r, c;
            read(l, r, c);
            c = mp[c];
            if (!c)
                printf("0\n");
            else
                printf("%ld\n", upper_bound(g[c].begin(), g[c].end(), r) - lower_bound(g[c].begin(), g[c].end(), l));
        }
        else
        {
            int pos, val;
            read(pos, val);
            g[a[pos]].erase(lower_bound(g[a[pos]].begin(), g[a[pos]].end(), pos));
            if (!mp[val])
                mp[val] = ++cnt;
            val = mp[val];
            a[pos]=val;
            g[a[pos]].insert(lower_bound(g[a[pos]].begin(), g[a[pos]].end(), pos), pos);
        }
    }
    return 0;
}