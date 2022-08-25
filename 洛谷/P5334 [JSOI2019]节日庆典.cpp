/**
 *    unicode: UTF-8
 *    name:    P5334 [JSOI2019]节日庆典
 *    author:  wangjunrui
 *    created: 2022.08.20 周六 15:53:54 (Asia/Shanghai)
 **/
#include <algorithm>
#include <cstdio>
#include <cstring>
#include <vector>
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
constexpr int N = 3e6 + 5;
int n;
int z[N];
char str[N];
signed main()
{
    scanf("%s", str + 1);
    n = (int)(strlen(str + 1));
    z[1] = n;
    for (int i = 2, l = 0, r = 0; i <= n; ++i)
    {
        if (i <= r)
            z[i] = min(z[i - l + 1], r - i);
        while (str[z[i] + 1] == str[i + z[i]])
            ++z[i];
        if (i + z[i] > r)
        {
            l = i;
            r = i + z[i];
        }
    }
    auto compare = [](int x, int y)
    {
        if (x + z[x] > y)
            return 0;
        return str[z[x] + 1] < str[x + z[x]] ? 1 : -1;
    };
    auto calc = [compare](int x, int y, int r)
    {
        int res;
        if ((res = compare(y + r - x + 1, r)))
            return res > 0 ? x : y;
        if ((res = compare(x - y + 1, y - 1)))
            return res > 0 ? y : x;
        return y;
    };
    vector<int> f, g;
    for (int i = 1; i <= n; ++i)
    {
        swap(f, g);
        f.push_back(i);
        for (auto x : g)
        {
            while (!f.empty() && str[x + i - f.back()] < str[i])
                f.pop_back();
            if (f.empty())
                f.push_back(x);
            else if (str[x + i - f.back()] == str[i])
            {
                while (!f.empty() && (i - f.back() + 1) * 2 >= (i - x + 1))
                    f.pop_back();
                f.push_back(x);
            }
        }
        g.clear();
        int res = f.front();
        for (auto it = next(f.begin()); it != f.end(); ++it)
            res = calc(res, *it, i);
        printf("%d ", res);
    }
    putchar('\n');
    return 0;
}