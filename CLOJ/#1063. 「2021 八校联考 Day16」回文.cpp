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
const int N = 1e5 + 5;
char str[N];
bool check(int l, int r)
{
    if (l > r)
        return true;
    for (int i = l, j = r; i <= j; ++i, --j)
        if (str[i] != str[j])
            return false;
    return true;
}
inline void work()
{
    scanf("%s", str + 1);
    int n = (int)strlen(str + 1);
    if (!check(1, n))
        printf("2\n1 %d\n", n + 1);
    else
    {
        int len = 0;
        for (int i = 1; i < n; ++i)
        {
            if (str[i] != str[i + 1])
            {
                len = i;
                break;
            }
        }
        if (len)
        {
            if (!check(1, len + 1) && !check(len + 2, n))
                printf("3\n1 %d %d\n", len + 2, n + 1);
            else if (!check(1, len + 2) && !check(len + 3, n))
                printf("3\n1 %d %d\n", len + 3, n + 1);
            else
                printf("-1\n");
        }
        else
            printf("-1\n");
    }
}
signed main()
{
    int T;
    read(T);
    while (T--)
        work();
    return 0;
}
