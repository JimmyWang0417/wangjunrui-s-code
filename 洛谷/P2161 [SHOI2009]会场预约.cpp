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
const int N = 2e5 + 5;
int n;
struct node
{
    int l, r;
    node(int _l = 0, int _r = 0) : l(_l), r(_r) {}
    inline bool operator<(const node &rhs) const
    {
        return r < rhs.l;
    }
};
set<node> se;
signed main()
{
    read(n);
    for (int i = 1; i <= n; ++i)
    {
        char opt[4];
        scanf("%s", opt);
        if (opt[0] == 'A')
        {
            int l, r;
            read(l, r);
            auto it = se.find(node(l, r));
            int cnt = 0;
            while (it != se.end())
            {
                ++cnt;
                se.erase(it);
                it = se.find(node(l, r));
            }
            se.insert(node(l, r));
            printf("%d\n", cnt);
        }
        else
            printf("%lu\n", se.size());
    }
    return 0;
}