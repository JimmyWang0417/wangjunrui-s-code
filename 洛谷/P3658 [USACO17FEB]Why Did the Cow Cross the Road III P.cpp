#include <cstdio>
#include <cstring>
#include <algorithm>
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
using std::min;
const int N = 1e5 + 5;
int n, m;
struct node
{
    int val, pos;
} a[N], b[N];
int mp[N];
int c[N];
inline void update(int pos)
{
    for (int i = pos; i <= n; i += lowbit(i))
        ++c[i];
}
inline int query(int pos)
{
    int res = 0;
    for (int i = pos; i; i -= lowbit(i))
        res += c[i];
    return res;
}
inline void clear(int pos)
{
    for (int i = pos; i <= n && c[i]; i += lowbit(i))
        c[i] = 0;
}
ll answer = 0;
inline void cdq(int l, int r)
{
    if (l == r)
        return;
    int mid = (l + r) >> 1;
    cdq(l, mid), cdq(mid + 1, r);
    int i = l, j = mid + 1, now = 0;
    while (i <= mid && j <= r)
    {
        if (a[i].pos > a[j].pos)
        {
            update(a[i].val);
            b[++now] = a[i++];
        }
        else
        {
            answer += query(n) - (query(min(a[j].val + m, n)) - query(max(a[j].val - m - 1, 0)));
            b[++now] = a[j++];
        }
    }
    while (i <= mid)
        b[++now] = a[i++];
    while (j <= r)
    {
        answer += query(n) - (query(min(a[j].val + m, n)) - query(max(a[j].val - m, 1) - 1));
        b[++now] = a[j++];
    }
    for (i = l; i <= mid; ++i)
        clear(a[i].val);
    memcpy(a + l, b + 1, (r - l + 1) * sizeof(node));
}
signed main()
{
    read(n, m);
    for (int i = 1; i <= n; ++i)
    {
        int x;
        read(x);
        mp[x] = i;
    }
    for (int i = 1; i <= n; ++i)
    {
        read(a[i].val);
        a[i].pos = mp[a[i].val];
    }
    cdq(1, n);
    printf("%lld\n", answer);
    return 0;
}