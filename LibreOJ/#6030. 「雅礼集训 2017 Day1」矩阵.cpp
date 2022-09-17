#include <cstdio>
#include <vector>
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
constexpr int N = 1e3 + 5;
int n;
bool mp[N][N];
char str[N];
int cnt[N];
bool exist[N];
signed main()
{
    read(n);
    for (int i = 1; i <= n; ++i)
    {
        scanf("%s", str + 1);
        for (int j = 1; j <= n; ++j)
            if (str[j] == '#')
            {
                mp[i][j] = true;
                ++cnt[j];
                exist[i] = true;
            }
    }
    vector<pair<int, int>> answer, now;
    answer.resize(114514);
    for (int i = 1; i <= n; ++i)
    {
        int where = 0;
        for (int j = 1; j <= n; ++j)
            if (mp[j][i])
            {
                where = j;
                break;
            }
        if (!where)
        {
            if (exist[i])
            {
                now.emplace_back(i, i);
                for (int j = 1; j <= n; ++j)
                    if (mp[i][j])
                        where = j;
                for (int j = 1; j <= n; ++j)
                    if (!mp[i][j] && i != j)
                        now.emplace_back(where, j);
                if (!mp[i][i])
                    now.emplace_back(where, i);
                for (int j = 1; j <= n; ++j)
                    if (cnt[j] < n)
                        now.emplace_back(i, j);
            }
            else
                continue;
        }
        else
        {
            for (int j = 1; j <= n; ++j)
                if (!mp[i][j] && i != j)
                    now.emplace_back(where, j);
            if (!mp[i][i])
                now.emplace_back(where, i);
            for (int j = 1; j <= n; ++j)
                if (cnt[j] < n)
                    now.emplace_back(i, j);
        }
        if (now.size() < answer.size())
            answer = now;
        now.clear();
    }
    if (answer.size() == 114514)
        printf("-1");
    else
        printf("%lu\n", answer.size());
    return 0;
}
