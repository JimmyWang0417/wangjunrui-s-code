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
const int N = 5e5 + 5;
int n, m, a[N];
int d[N], id[N];
inline void insert(int val, int _id)
{
    for (int i = 20; i >= 0; --i)
        if ((val >> i) & 1)
        {
            if (!d[i])
            {
                d[i] = val;
                id[i] = _id;
                break;
            }
            else
            {
                if (id[i] < _id)
                {
                    swap(d[i], val);
                    swap(id[i], _id);
                }
                val ^= d[i];
            }
        }
}
struct Query
{
    int l, r, id;
    inline bool operator<(const Query &rhs) const
    {
        return r < rhs.r;
    }
} q[N];
int answer[N];
inline int calc(int _id)
{
    int ans = 0;
    for (int i = 20; i >= 0; --i)
    {
        if (id[i] >= _id && (ans ^ d[i]) > ans)
            ans ^= d[i];
    }
    return ans;
}
signed main()
{
    read(n);
    for (int i = 1; i <= n; ++i)
        read(a[i]);
    read(m);
    for (int i = 1; i <= m; ++i)
    {
        read(q[i].l, q[i].r);
        q[i].id = i;
    }
    sort(q + 1, q + 1 + m);
    for (int i = 1, j = 1; i <= m; ++i)
    {
        while (j <= n && j <= q[i].r)
        {
            insert(a[j], j);
            ++j;
        }
        answer[q[i].id] = calc(q[i].l);
    }
    for (int i = 1; i <= m; ++i)
        printf("%d\n", answer[i]);
    return 0;
}
