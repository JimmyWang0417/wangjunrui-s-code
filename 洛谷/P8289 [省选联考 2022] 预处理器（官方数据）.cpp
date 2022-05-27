#include <cstdio>
#include <cstring>
#include <iostream>
#include <string>
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
constexpr int N = 1005;
int n;
string str[N];
pair<string, string> p[N];
bool vis[N];
int tot;
inline bool check(char c)
{
    if ('0' <= c && c <= '9')
        return true;
    if ('a' <= c && c <= 'z')
        return true;
    if ('A' <= c && c <= 'Z')
        return true;
    if (c == '_')
        return true;
    return false;
}
inline string calc(string s)
{
    string later;
    int bg = -1;
    for (int j = 0; j < s.length(); ++j)
    {
        if (!check(s[j]))
        {
            if (bg != -1)
            {
                bool flag = true;
                string str = s.substr(bg, j - bg);
                for (int i = 1; i <= tot; ++i)
                    if (str == p[i].first && !vis[i])
                    {
                        vis[i] = true;
                        later += calc(p[i].second);
                        flag = false;
                        vis[i] = false;
                        break;
                    }
                if (flag)
                    later += str;
                bg = -1;
            }
            later += s[j];
        }
        else
        {
            if (bg == -1)
                bg = j;
        }
    }
    if (bg != -1)
    {
        bool flag = true;
        string str = s.substr(bg, s.length() - bg);
        for (int i = 1; i <= tot; ++i)
            if (str == p[i].first && !vis[i])
            {
                vis[i] = true;
                later += calc(p[i].second);
                flag = false;
                vis[i] = false;
                break;
            }
        if (flag)
            later += str;
    }
    return later;
}
signed main()
{
    read(n);
    for (int i = 1; i <= n; ++i)
        getline(cin, str[i]);
    for (int i = 1; i <= n; ++i)
    {
        if (str[i][0] == '#')
        {
            if (str[i][1] == 'd')
            {
                int where = 0;
                for (int j = 8; j < str[i].length() && str[i][j] != ' '; where = ++j)
                    ;
                string a, b;
                a = str[i].substr(8, where - 8);
                b = str[i].substr(where + 1, str[i].length() - where - 1);
                p[++tot] = make_pair(a, b);
            }
            else
            {
                string nmsl = str[i].substr(7, str[i].length() - 7);
                for (int j = 1; j <= tot; ++j)
                    if (nmsl == p[j].first)
                    {
                        for (int k = j; k < tot; ++k)
                            p[k] = p[k + 1];
                        --tot;
                        break;
                    }
            }
        }
        else
        {
            string later;
            int bg = -1;
            for (int j = 0; j < str[i].length(); ++j)
            {
                if (!check(str[i][j]))
                {
                    if (bg != -1)
                    {
                        later += calc(str[i].substr(bg, j - bg));
                        memset(vis, 0, sizeof(vis));
                        bg = -1;
                    }
                    later += str[i][j];
                }
                else
                {
                    if (bg == -1)
                        bg = j;
                }
            }
            if (bg != -1)
                later += calc(str[i].substr(bg, str[i].length() - bg));
            memset(vis, 0, sizeof(vis));
            str[i] = later;
        }
    }
    for (int i = 1; i <= n; ++i)
    {
        if (str[i][0] == '#')
            cout << endl;
        else
            cout << str[i] << endl;
    }
    return 0;
}