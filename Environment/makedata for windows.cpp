#include <algorithm>
#include <bitset>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <fstream>
#include <sstream>
#include <windows.h>
#define lowbit(x) (x & (-x))
#define re register
#define ll long long
#define ull unsigned long long
#define rep(i, a, b) for (re int i = a; i <= b; ++i)
#define per(i, a, b) for (re int i = a; i >= b; --i)
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
const int N = 1e5 + 5;
char str[N];
inline void work(int val)
{
    Sleep(1000);
    system("make.exe");
    system("std.exe");
    sprintf(str, "copy ans.in data\\ans%d.in", val), system(str);
    sprintf(str, "copy ans.out data\\ans%d.out", val), system(str);
}
signed main()
{
    int l, r;
    read(l, r);
    cerr << "begin" << ends;
    for (re int i = l; i <= r; ++i)
        work(i);
    return 0;
}
