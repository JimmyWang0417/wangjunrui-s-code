#include <algorithm>
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
constexpr int N = 2e5 + 5;
template <int MAX>
struct union_set
{
    int fa[MAX];
    inline int find(int x)
    {
        return fa[x] ? fa[x] = find(fa[x]) : x;
    }
    inline bool check(int x, int y)
    {
        return find(x) == find(y);
    }
    inline void unionn(int x, int y)
    {
        x = find(x), y = find(y);
        if (x == y)
            return;
        fa[x] = y;
    }
};
union_set<N> fa[55];
union_set<N * 55> all;
inline int calc(int x, int y)
{
    return (x - 1) * 100000 + y;
}
bool exist[55][N];
signed main()
{
    int T;
    read(T);
    while (T--)
    {
        int opt, x1, y1, x2, y2;
        read(opt, x1, y1, x2, y2);
        if (opt)
            printf("%d\n", all.check(calc(x1, y1), calc(x2, y2)) && exist[x1][y1] && exist[x2][y2]);
        else
        {
            if (x1 > x2)
                swap(x1, x2);
            if (y1 > y2)
                swap(y1, y2);
            for (int i = x1; i <= x2; ++i)
                for (int j = fa[i].find(y1); j <= y2; j = fa[i].find(j + 1))
                {
                    exist[i][j] = true;
                    if (exist[i - 1][j])
                        all.unionn(calc(i - 1, j), calc(i, j));
                    if (exist[i][j - 1])
                        all.unionn(calc(i, j - 1), calc(i, j));
                    if (exist[i + 1][j])
                        all.unionn(calc(i + 1, j), calc(i, j));
                    if (exist[i][j + 1])
                        all.unionn(calc(i, j + 1), calc(i, j));
                    fa[i].unionn(j, j + 1);
                }
        }
    }
    return 0;
}