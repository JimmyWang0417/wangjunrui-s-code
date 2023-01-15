/**
 *    unicode: UTF-8
 *    name:    AT3946 [AGC022A] Diverse Word
 *    author:  whitepaperdog
 *    created: 2022.07.11 周一 23:49:08 (Asia/Shanghai)
 **/
#include <algorithm>
#include <cstdio>
#include <cstring>
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
char str[114514], qwq[114514];
bool mp[1919810];
signed main()
{
    scanf("%s", str);
    if (strlen(str) == 26)
    {
        memcpy(qwq, str, sizeof(qwq));
        if (!next_permutation(qwq, qwq + 26))
            printf("-1\n");
        else
        {
            for (int i = 0; str[i]; ++i)
            {
                putchar(qwq[i]);
                if (qwq[i] > str[i])
                    break;
            }
            putchar('\n');
        }
    }
    else
    {
        printf("%s", str);
        for (int i = 0; str[i]; ++i)
            mp[str[i] - 'a'] = true;
        for (int i = 0; i < 26; ++i)
            if (!mp[i])
            {
                putchar('a' + i);
                break;
            }
        putchar('\n');
    }
    return 0;
}