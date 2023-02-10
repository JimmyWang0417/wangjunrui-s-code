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
string str[] = {
    "",
    "0\n",
    "1\nlea ebx, [2*eax]\n",
    "1\nlea ebx, [eax + 2*eax]\n",
    "1\nlea ebx, [4*eax]\n",
    "1\nlea ebx, [eax + 4*eax]\n",
    "2\nlea ebx, [2*eax]\nlea ecx, [ebx + 4*eax]\n",
    "2\nlea ebx, [eax + 2*eax]\nlea ecx, [ebx + 4*eax]\n",
    "1\nlea ebx, [8*eax]\n",
    "1\nlea ebx, [eax + 8*eax]\n",
    "2\nlea ebx, [2*eax]\nlea ecx, [ebx + 8*eax]\n",
    "2\nlea ebx, [eax + 2*eax]\nlea ecx, [ebx + 8*eax]\n",
    "2\nlea ebx, [4*eax]\nlea ecx, [ebx + 8*eax]\n",
    "2\nlea ebx, [eax + 2*eax]\nlea ecx, [eax + 4*ebx]\n",
    "3\nlea ebx, [2*eax]\nlea ecx, [eax + 2*eax]\nlea edx, [ebx + 4*ecx]\n",
    "2\nlea ebx, [eax + 2*eax]\nlea ecx, [ebx + 4*ebx]\n",
    "2\nlea ebx, [2*eax]\nlea ecx, [8*ebx]\n",
    "2\nlea ebx, [2*eax]\nlea ecx, [eax + 8*ebx]\n",
    "2\nlea ebx, [2*eax]\nlea ecx, [ebx + 8*ebx]\n",
    "2\nlea ebx, [eax + 8*eax]\nlea ecx, [eax + 2*ebx]\n",
    "2\nlea ebx, [4*eax]\nlea ecx, [ebx + 4*ebx]\n",
    "2\nlea ebx, [eax + 4*eax]\nlea ecx, [eax + 4*ebx]\n",
    "3\nlea ebx, [2*eax]\nlea ecx, [eax + 4*eax]\nlea edx, [ebx + 4*ecx]\n",
    "3\nlea ebx, [eax + 2*eax]\nlea ecx, [eax + 4*eax]\nlea edx, [ebx + 4*ecx]\n",
    "2\nlea ebx, [8*eax]\nlea ecx, [ebx + 2*ebx]\n",
    "2\nlea ebx, [eax + 2*eax]\nlea ecx, [eax + 8*ebx]\n",
    "3\nlea ebx, [2*eax]\nlea ecx, [eax + 2*eax]\nlea edx, [ebx + 8*ecx]\n",
    "2\nlea ebx, [eax + 2*eax]\nlea ecx, [ebx + 8*ebx]\n",
    "3\nlea ebx, [4*eax]\nlea ecx, [eax + 2*eax]\nlea edx, [ebx + 8*ecx]\n",
    "3\nlea ebx, [eax + 2*eax]\nlea ecx, [eax + 4*eax]\nlea edx, [ecx + 8*ebx]\n",
    "3\nlea ebx, [2*eax]\nlea ecx, [ebx + 4*eax]\nlea edx, [ecx + 4*ecx]\n",
    "3\nlea ebx, [eax + 2*eax]\nlea ecx, [ebx + 4*eax]\nlea edx, [ecx + 8*ebx]\n",
    "2\nlea ebx, [4*eax]\nlea ecx, [8*ebx]\n",
    "2\nlea ebx, [4*eax]\nlea ecx, [eax + 8*ebx]\n",
    "3\nlea ebx, [2*eax]\nlea ecx, [4*eax]\nlea edx, [ebx + 8*ecx]\n",
    "3\nlea ebx, [2*eax]\nlea ecx, [eax + 8*ebx]\nlea edx, [eax + 2*ecx]\n",
    "2\nlea ebx, [4*eax]\nlea ecx, [ebx + 8*ebx]\n",
    "2\nlea ebx, [eax + 8*eax]\nlea ecx, [eax + 4*ebx]\n",
    "3\nlea ebx, [2*eax]\nlea ecx, [eax + 8*eax]\nlea edx, [ebx + 4*ecx]\n",
    "3\nlea ebx, [eax + 2*eax]\nlea ecx, [eax + 8*eax]\nlea edx, [ebx + 4*ecx]\n",
    "2\nlea ebx, [8*eax]\nlea ecx, [ebx + 4*ebx]\n",
    "2\nlea ebx, [eax + 4*eax]\nlea ecx, [eax + 8*ebx]\n",
    "3\nlea ebx, [2*eax]\nlea ecx, [eax + 4*eax]\nlea edx, [ebx + 8*ecx]\n",
    "3\nlea ebx, [eax + 2*eax]\nlea ecx, [eax + 4*eax]\nlea edx, [ebx + 8*ecx]\n",
    "3\nlea ebx, [4*eax]\nlea ecx, [eax + 4*eax]\nlea edx, [ebx + 8*ecx]\n",
    "2\nlea ebx, [eax + 4*eax]\nlea ecx, [ebx + 8*ebx]\n",
    "3\nlea ebx, [eax + 4*eax]\nlea ecx, [ebx + 1*eax]\nlea edx, [ecx + 8*ebx]\n",
    "3\nlea ebx, [eax + 2*eax]\nlea ecx, [ebx + 8*eax]\nlea edx, [ebx + 4*ecx]\n",
    "3\nlea ebx, [2*eax]\nlea ecx, [8*ebx]\nlea edx, [ecx + 2*ecx]\n",
    "3\nlea ebx, [2*eax]\nlea ecx, [ebx + 4*eax]\nlea edx, [eax + 8*ecx]\n",
    "3\nlea ebx, [2*eax]\nlea ecx, [ebx + 4*eax]\nlea edx, [ebx + 8*ecx]\n",
    "3\nlea ebx, [2*eax]\nlea ecx, [eax + 8*ebx]\nlea edx, [ecx + 2*ecx]\n",
    "3\nlea ebx, [4*eax]\nlea ecx, [ebx + 2*eax]\nlea edx, [ebx + 8*ecx]\n",
    "3\nlea ebx, [eax + 2*eax]\nlea ecx, [eax + 4*ebx]\nlea edx, [eax + 4*ecx]\n",
    "3\nlea ebx, [2*eax]\nlea ecx, [ebx + 4*eax]\nlea edx, [ecx + 8*ecx]\n",
    "3\nlea ebx, [eax + 2*eax]\nlea ecx, [ebx + 8*eax]\nlea edx, [ecx + 4*ecx]\n",
    "3\nlea ebx, [8*eax]\nlea ecx, [ebx + 4*eax]\nlea edx, [ebx + 4*ecx]\n",
    "3\nlea ebx, [eax + 2*eax]\nlea ecx, [ebx + 4*eax]\nlea edx, [eax + 8*ecx]\n",
    "4\nlea ebx, [2*eax]\nlea ecx, [eax + 2*eax]\nlea edx, [ecx + 4*eax]\nlea eex, [ebx + 8*edx]\n",
    "3\nlea ebx, [eax + 2*eax]\nlea ecx, [ebx + 4*eax]\nlea edx, [ebx + 8*ecx]\n",
    "3\nlea ebx, [4*eax]\nlea ecx, [ebx + 8*eax]\nlea edx, [ecx + 4*ecx]\n",
    "3\nlea ebx, [eax + 2*eax]\nlea ecx, [ebx + 4*ebx]\nlea edx, [eax + 4*ecx]\n",
    "4\nlea ebx, [2*eax]\nlea ecx, [eax + 2*eax]\nlea edx, [ecx + 4*ecx]\nlea eex, [ebx + 4*edx]\n",
    "3\nlea ebx, [eax + 2*eax]\nlea ecx, [ebx + 4*eax]\nlea edx, [ecx + 8*ecx]\n",
    "2\nlea ebx, [8*eax]\nlea ecx, [8*ebx]\n",
    "2\nlea ebx, [8*eax]\nlea ecx, [eax + 8*ebx]\n",
    "3\nlea ebx, [2*eax]\nlea ecx, [8*eax]\nlea edx, [ebx + 8*ecx]\n",
    "3\nlea ebx, [4*eax]\nlea ecx, [eax + 8*ebx]\nlea edx, [eax + 2*ecx]\n",
    "3\nlea ebx, [2*eax]\nlea ecx, [eax + 8*ebx]\nlea edx, [4*ecx]\n",
    "3\nlea ebx, [2*eax]\nlea ecx, [eax + 8*ebx]\nlea edx, [eax + 4*ecx]\n",
    "3\nlea ebx, [2*eax]\nlea ecx, [eax + 8*ebx]\nlea edx, [ebx + 4*ecx]\n",
    "4\nlea ebx, [2*eax]\nlea ecx, [eax + 2*eax]\nlea edx, [eax + 8*ebx]\nlea eex, [ecx + 4*edx]\n",
    "2\nlea ebx, [8*eax]\nlea ecx, [ebx + 8*ebx]\n",
    "2\nlea ebx, [eax + 8*eax]\nlea ecx, [eax + 8*ebx]\n",
    "3\nlea ebx, [2*eax]\nlea ecx, [eax + 8*eax]\nlea edx, [ebx + 8*ecx]\n",
    "3\nlea ebx, [eax + 2*eax]\nlea ecx, [eax + 8*eax]\nlea edx, [ebx + 8*ecx]\n",
    "3\nlea ebx, [4*eax]\nlea ecx, [eax + 8*eax]\nlea edx, [ebx + 8*ecx]\n",
    "3\nlea ebx, [eax + 4*eax]\nlea ecx, [eax + 8*eax]\nlea edx, [ebx + 8*ecx]\n",
    "4\nlea ebx, [2*eax]\nlea ecx, [eax + 2*eax]\nlea edx, [ecx + 8*ebx]\nlea eex, [ebx + 4*edx]\n",
    "4\nlea ebx, [2*eax]\nlea ecx, [eax + 2*eax]\nlea edx, [ecx + 8*ebx]\nlea eex, [ecx + 4*edx]\n",
    "3\nlea ebx, [2*eax]\nlea ecx, [8*ebx]\nlea edx, [ecx + 4*ecx]\n",
    "2\nlea ebx, [eax + 8*eax]\nlea ecx, [ebx + 8*ebx]\n",
    "3\nlea ebx, [2*eax]\nlea ecx, [ebx + 8*eax]\nlea edx, [ebx + 8*ecx]\n",
    "3\nlea ebx, [eax + 4*eax]\nlea ecx, [eax + 8*ebx]\nlea edx, [eax + 2*ecx]\n",
    "3\nlea ebx, [4*eax]\nlea ecx, [ebx + 4*ebx]\nlea edx, [ebx + 4*ecx]\n",
    "3\nlea ebx, [2*eax]\nlea ecx, [eax + 8*ebx]\nlea edx, [ecx + 4*ecx]\n",
    "4\nlea ebx, [2*eax]\nlea ecx, [eax + 4*eax]\nlea edx, [ecx + 8*ebx]\nlea eex, [ebx + 4*edx]\n",
    "3\nlea ebx, [eax + 4*eax]\nlea ecx, [eax + 8*ebx]\nlea edx, [ebx + 2*ecx]\n",
    "3\nlea ebx, [8*eax]\nlea ecx, [ebx + 2*eax]\nlea edx, [ebx + 8*ecx]\n",
    "3\nlea ebx, [eax + 2*eax]\nlea ecx, [ebx + 8*eax]\nlea edx, [eax + 8*ecx]\n",
    "3\nlea ebx, [2*eax]\nlea ecx, [ebx + 8*eax]\nlea edx, [ecx + 8*ecx]\n",
    "3\nlea ebx, [eax + 2*eax]\nlea ecx, [ebx + 8*eax]\nlea edx, [ebx + 8*ecx]\n",
    "4\nlea ebx, [2*eax]\nlea ecx, [eax + 4*eax]\nlea edx, [ecx + 8*ecx]\nlea eex, [ebx + 2*edx]\n",
    "3\nlea ebx, [eax + 4*eax]\nlea ecx, [eax + 2*ebx]\nlea edx, [ebx + 8*ecx]\n",
    "4\nlea ebx, [2*eax]\nlea ecx, [ebx + 4*eax]\nlea edx, [ecx + 8*ebx]\nlea eex, [ecx + 4*edx]\n",
    "3\nlea ebx, [eax + 4*eax]\nlea ecx, [ebx + 8*ebx]\nlea edx, [ebx + 2*ecx]\n",
    "3\nlea ebx, [4*eax]\nlea ecx, [8*ebx]\nlea edx, [ecx + 2*ecx]\n",
    "3\nlea ebx, [4*eax]\nlea ecx, [ebx + 8*eax]\nlea edx, [eax + 8*ecx]\n",
    "4\nlea ebx, [2*eax]\nlea ecx, [4*eax]\nlea edx, [ecx + 8*eax]\nlea eex, [ebx + 8*edx]\n",
    "3\nlea ebx, [4*eax]\nlea ecx, [eax + 8*ebx]\nlea edx, [ecx + 2*ecx]\n",
    "3\nlea ebx, [4*eax]\nlea ecx, [ebx + 8*eax]\nlea edx, [ebx + 8*ecx]\n",
    "3\nlea ebx, [eax + 2*eax]\nlea ecx, [eax + 8*ebx]\nlea edx, [eax + 4*ecx]\n",
    "4\nlea ebx, [2*eax]\nlea ecx, [4*eax]\nlea edx, [ebx + 8*ecx]\nlea eex, [edx + 2*edx]\n",
    "3\nlea ebx, [eax + 2*eax]\nlea ecx, [eax + 8*ebx]\nlea edx, [ebx + 4*ecx]\n",
    "3\nlea ebx, [8*eax]\nlea ecx, [ebx + 4*eax]\nlea edx, [ebx + 8*ecx]\n",
    "3\nlea ebx, [eax + 2*eax]\nlea ecx, [eax + 4*ebx]\nlea edx, [eax + 8*ecx]\n",
    "4\nlea ebx, [2*eax]\nlea ecx, [eax + 2*eax]\nlea edx, [eax + 4*ecx]\nlea eex, [ebx + 8*edx]\n",
    "3\nlea ebx, [eax + 2*eax]\nlea ecx, [eax + 4*ebx]\nlea edx, [ebx + 8*ecx]\n",
    "3\nlea ebx, [4*eax]\nlea ecx, [ebx + 8*eax]\nlea edx, [ecx + 8*ecx]\n",
    "3\nlea ebx, [eax + 2*eax]\nlea ecx, [ebx + 8*ebx]\nlea edx, [eax + 4*ecx]\n",
    "4\nlea ebx, [2*eax]\nlea ecx, [eax + 2*eax]\nlea edx, [ecx + 8*ecx]\nlea eex, [ebx + 4*edx]\n",
    "3\nlea ebx, [eax + 2*eax]\nlea ecx, [ebx + 8*ebx]\nlea edx, [ebx + 4*ecx]\n",
    "4\nlea ebx, [2*eax]\nlea ecx, [8*ebx]\nlea edx, [ecx + 8*eax]\nlea eex, [ecx + 4*edx]\n",
    "3\nlea ebx, [eax + 8*eax]\nlea ecx, [ebx + 4*eax]\nlea edx, [ebx + 8*ecx]\n",
    "4\nlea ebx, [2*eax]\nlea ecx, [eax + 2*eax]\nlea edx, [ebx + 4*ecx]\nlea eex, [ebx + 8*edx]\n",
    "4\nlea ebx, [2*eax]\nlea ecx, [eax + 2*eax]\nlea edx, [ebx + 4*ecx]\nlea eex, [ecx + 8*edx]\n",
    "4\nlea ebx, [4*eax]\nlea ecx, [eax + 2*eax]\nlea edx, [ebx + 8*ecx]\nlea eex, [ebx + 4*edx]\n",
    "3\nlea ebx, [eax + 2*eax]\nlea ecx, [eax + 4*ebx]\nlea edx, [ecx + 8*ecx]\n",
    "4\nlea ebx, [2*eax]\nlea ecx, [ebx + 4*eax]\nlea edx, [ecx + 8*eax]\nlea eex, [ecx + 8*edx]\n",
    "4\nlea ebx, [2*eax]\nlea ecx, [eax + 8*ebx]\nlea edx, [ecx + 2*ecx]\nlea eex, [edx + 4*ecx]\n",
    "3\nlea ebx, [8*eax]\nlea ecx, [ebx + 2*ebx]\nlea edx, [ecx + 4*ecx]\n",
    "3\nlea ebx, [eax + 2*eax]\nlea ecx, [ebx + 4*ebx]\nlea edx, [eax + 8*ecx]\n",
    "4\nlea ebx, [2*eax]\nlea ecx, [eax + 2*eax]\nlea edx, [ecx + 4*ecx]\nlea eex, [ebx + 8*edx]\n",
    "3\nlea ebx, [eax + 2*eax]\nlea ecx, [ebx + 4*ebx]\nlea edx, [ebx + 8*ecx]\n",
    "4\nlea ebx, [4*eax]\nlea ecx, [eax + 2*eax]\nlea edx, [ecx + 4*ecx]\nlea eex, [ebx + 8*edx]\n",
    "3\nlea ebx, [eax + 2*eax]\nlea ecx, [eax + 8*ebx]\nlea edx, [ecx + 4*ecx]\n",
    "4\nlea ebx, [2*eax]\nlea ecx, [eax + 2*eax]\nlea edx, [ebx + 4*ecx]\nlea eex, [edx + 8*edx]\n",
    "4\nlea ebx, [eax + 2*eax]\nlea ecx, [ebx + 4*eax]\nlea edx, [ecx + 8*eax]\nlea eex, [ecx + 8*edx]\n",
    "3\nlea ebx, [2*eax]\nlea ecx, [8*ebx]\nlea edx, [8*ecx]\n",
    "3\nlea ebx, [2*eax]\nlea ecx, [8*ebx]\nlea edx, [eax + 8*ecx]\n",
    "3\nlea ebx, [2*eax]\nlea ecx, [8*ebx]\nlea edx, [ebx + 8*ecx]\n",
    "3\nlea ebx, [8*eax]\nlea ecx, [eax + 8*ebx]\nlea edx, [eax + 2*ecx]\n",
    "3\nlea ebx, [4*eax]\nlea ecx, [4*ebx]\nlea edx, [ebx + 8*ecx]\n",
    "3\nlea ebx, [4*eax]\nlea ecx, [eax + 8*ebx]\nlea edx, [eax + 4*ecx]\n",
    "4\nlea ebx, [2*eax]\nlea ecx, [4*eax]\nlea edx, [eax + 8*ecx]\nlea eex, [ebx + 4*edx]\n",
    "3\nlea ebx, [eax + 2*eax]\nlea ecx, [ebx + 4*ebx]\nlea edx, [ecx + 8*ecx]\n",
    "3\nlea ebx, [2*eax]\nlea ecx, [eax + 8*ebx]\nlea edx, [8*ecx]\n",
    "3\nlea ebx, [2*eax]\nlea ecx, [eax + 8*ebx]\nlea edx, [eax + 8*ecx]\n",
    "3\nlea ebx, [2*eax]\nlea ecx, [eax + 8*ebx]\nlea edx, [ebx + 8*ecx]\n",
    "4\nlea ebx, [2*eax]\nlea ecx, [eax + 2*eax]\nlea edx, [eax + 8*ebx]\nlea eex, [ecx + 8*edx]\n",
    "3\nlea ebx, [4*eax]\nlea ecx, [eax + 4*ebx]\nlea edx, [ebx + 8*ecx]\n",
    "4\nlea ebx, [2*eax]\nlea ecx, [eax + 4*eax]\nlea edx, [eax + 8*ebx]\nlea eex, [ecx + 8*edx]\n",
    "4\nlea ebx, [2*eax]\nlea ecx, [ebx + 4*eax]\nlea edx, [eax + 8*ebx]\nlea eex, [ecx + 8*edx]\n",
    "4\nlea ebx, [4*eax]\nlea ecx, [eax + 2*eax]\nlea edx, [ecx + 8*ebx]\nlea eex, [ecx + 4*edx]\n",
    "3\nlea ebx, [2*eax]\nlea ecx, [8*ebx]\nlea edx, [ecx + 8*ecx]\n",
    "3\nlea ebx, [2*eax]\nlea ecx, [ebx + 8*ebx]\nlea edx, [eax + 8*ecx]\n",
    "3\nlea ebx, [2*eax]\nlea ecx, [ebx + 8*ebx]\nlea edx, [ebx + 8*ecx]\n",
    "3\nlea ebx, [eax + 8*eax]\nlea ecx, [eax + 8*ebx]\nlea edx, [eax + 2*ecx]\n",
    "3\nlea ebx, [4*eax]\nlea ecx, [ebx + 8*ebx]\nlea edx, [ebx + 4*ecx]\n",
    "3\nlea ebx, [eax + 8*eax]\nlea ecx, [eax + 4*ebx]\nlea edx, [eax + 4*ecx]\n",
    "4\nlea ebx, [2*eax]\nlea ecx, [eax + 8*eax]\nlea edx, [eax + 4*ecx]\nlea eex, [ebx + 4*edx]\n",
    "4\nlea ebx, [eax + 2*eax]\nlea ecx, [eax + 8*eax]\nlea edx, [eax + 4*ecx]\nlea eex, [ebx + 4*edx]\n",
    "3\nlea ebx, [8*eax]\nlea ecx, [ebx + 8*ebx]\nlea edx, [ebx + 2*ecx]\n",
    "3\nlea ebx, [2*eax]\nlea ecx, [eax + 8*ebx]\nlea edx, [ecx + 8*ecx]\n",
    "4\nlea ebx, [2*eax]\nlea ecx, [eax + 2*eax]\nlea edx, [ecx + 8*ebx]\nlea eex, [ebx + 8*edx]\n",
    "3\nlea ebx, [eax + 8*eax]\nlea ecx, [eax + 8*ebx]\nlea edx, [ebx + 2*ecx]\n",
    "4\nlea ebx, [4*eax]\nlea ecx, [eax + 2*eax]\nlea edx, [ecx + 4*ebx]\nlea eex, [ebx + 8*edx]\n",
    "3\nlea ebx, [eax + 8*eax]\nlea ecx, [eax + 4*ebx]\nlea edx, [ebx + 4*ecx]\n",
    "4\nlea ebx, [4*eax]\nlea ecx, [ebx + 2*eax]\nlea edx, [ecx + 8*ebx]\nlea eex, [ecx + 4*edx]\n",
    "4\nlea ebx, [eax + 2*eax]\nlea ecx, [eax + 8*eax]\nlea edx, [ebx + 4*ecx]\nlea eex, [ebx + 4*edx]\n",
    "3\nlea ebx, [4*eax]\nlea ecx, [8*ebx]\nlea edx, [ecx + 4*ecx]\n",
    "3\nlea ebx, [4*eax]\nlea ecx, [ebx + 4*ebx]\nlea edx, [eax + 8*ecx]\n",
    "3\nlea ebx, [2*eax]\nlea ecx, [ebx + 8*ebx]\nlea edx, [ecx + 8*ecx]\n",
    "3\nlea ebx, [eax + 8*eax]\nlea ecx, [ebx + 8*ebx]\nlea edx, [eax + 2*ecx]\n",
    "3\nlea ebx, [4*eax]\nlea ecx, [ebx + 4*ebx]\nlea edx, [ebx + 8*ecx]\n",
    "3\nlea ebx, [4*eax]\nlea ecx, [eax + 8*ebx]\nlea edx, [ecx + 4*ecx]\n",
    "4\nlea ebx, [2*eax]\nlea ecx, [eax + 4*eax]\nlea edx, [eax + 8*ecx]\nlea eex, [ebx + 4*edx]\n",
    "4\nlea ebx, [4*eax]\nlea ecx, [eax + 8*ebx]\nlea edx, [ecx + 2*eax]\nlea eex, [edx + 4*ecx]\n",
    "3\nlea ebx, [8*eax]\nlea ecx, [ebx + 4*ebx]\nlea edx, [ebx + 4*ecx]\n",
    "3\nlea ebx, [eax + 4*eax]\nlea ecx, [eax + 4*ebx]\nlea edx, [eax + 8*ecx]\n",
    "4\nlea ebx, [2*eax]\nlea ecx, [4*eax]\nlea edx, [ebx + 8*ecx]\nlea eex, [edx + 4*edx]\n",
    "3\nlea ebx, [eax + 8*eax]\nlea ecx, [eax + 2*ebx]\nlea edx, [ecx + 8*ecx]\n",
    "4\nlea ebx, [2*eax]\nlea ecx, [ebx + 8*eax]\nlea edx, [eax + 8*ecx]\nlea eex, [ecx + 2*edx]\n",
    "3\nlea ebx, [eax + 4*eax]\nlea ecx, [eax + 4*ebx]\nlea edx, [ebx + 8*ecx]\n",
    "4\nlea ebx, [2*eax]\nlea ecx, [ebx + 8*eax]\nlea edx, [eax + 4*ecx]\nlea eex, [ecx + 4*edx]\n",
    "4\nlea ebx, [2*eax]\nlea ecx, [eax + 8*ebx]\nlea edx, [eax + 2*ecx]\nlea eex, [edx + 4*edx]\n",
    "4\nlea ebx, [2*eax]\nlea ecx, [8*ebx]\nlea edx, [ecx + 4*eax]\nlea eex, [ecx + 8*edx]\n",
    "4\nlea ebx, [2*eax]\nlea ecx, [eax + 4*eax]\nlea edx, [ebx + 4*ecx]\nlea eex, [eax + 8*edx]\n",
    "4\nlea ebx, [2*eax]\nlea ecx, [eax + 4*eax]\nlea edx, [ebx + 4*ecx]\nlea eex, [ebx + 8*edx]\n",
    "4\nlea ebx, [8*eax]\nlea ecx, [eax + 2*ebx]\nlea edx, [ecx + 8*ebx]\nlea eex, [ecx + 2*edx]\n",
    "3\nlea ebx, [4*eax]\nlea ecx, [ebx + 4*ebx]\nlea edx, [ecx + 8*ecx]\n",
    "3\nlea ebx, [eax + 4*eax]\nlea ecx, [ebx + 8*ebx]\nlea edx, [eax + 4*ecx]\n",
    "4\nlea ebx, [2*eax]\nlea ecx, [eax + 4*eax]\nlea edx, [ecx + 8*ecx]\nlea eex, [ebx + 4*edx]\n",
    "4\nlea ebx, [eax + 2*eax]\nlea ecx, [eax + 4*eax]\nlea edx, [ecx + 8*ecx]\nlea eex, [ebx + 4*edx]\n",
    "4\nlea ebx, [4*eax]\nlea ecx, [eax + 4*eax]\nlea edx, [ecx + 8*ecx]\nlea eex, [ebx + 4*edx]\n",
    "3\nlea ebx, [eax + 4*eax]\nlea ecx, [ebx + 8*ebx]\nlea edx, [ebx + 4*ecx]\n",
    "4\nlea ebx, [2*eax]\nlea ecx, [ebx + 8*eax]\nlea edx, [ebx + 2*ecx]\nlea eex, [ecx + 8*edx]\n",
    "4\nlea ebx, [2*eax]\nlea ecx, [eax + 8*ebx]\nlea edx, [ecx + 2*ecx]\nlea eex, [edx + 8*ecx]\n",
    "4\nlea ebx, [4*eax]\nlea ecx, [ebx + 8*eax]\nlea edx, [ecx + 8*ebx]\nlea eex, [ecx + 4*edx]\n",
    "3\nlea ebx, [eax + 4*eax]\nlea ecx, [eax + 4*ebx]\nlea edx, [ecx + 8*ecx]\n",
    "4\nlea ebx, [2*eax]\nlea ecx, [eax + 8*eax]\nlea edx, [ebx + 4*ecx]\nlea eex, [edx + 4*edx]\n",
    "4\nlea ebx, [eax + 2*eax]\nlea ecx, [ebx + 8*eax]\nlea edx, [eax + 4*ecx]\nlea eex, [ecx + 4*edx]\n",
    "3\nlea ebx, [8*eax]\nlea ecx, [8*ebx]\nlea edx, [ecx + 2*ecx]\n",
    "3\nlea ebx, [8*eax]\nlea ecx, [ebx + 2*ebx]\nlea edx, [eax + 8*ecx]\n",
    "4\nlea ebx, [2*eax]\nlea ecx, [8*eax]\nlea edx, [ecx + 8*ebx]\nlea eex, [ebx + 8*edx]\n",
    "3\nlea ebx, [8*eax]\nlea ecx, [eax + 8*ebx]\nlea edx, [ecx + 2*ecx]\n",
    "4\nlea ebx, [2*eax]\nlea ecx, [ebx + 4*eax]\nlea edx, [eax + 8*ecx]\nlea eex, [4*edx]\n",
    "4\nlea ebx, [2*eax]\nlea ecx, [ebx + 4*eax]\nlea edx, [eax + 8*ecx]\nlea eex, [eax + 4*edx]\n",
    "4\nlea ebx, [2*eax]\nlea ecx, [8*eax]\nlea edx, [ebx + 8*ecx]\nlea eex, [edx + 2*edx]\n",
    "4\nlea ebx, [4*eax]\nlea ecx, [eax + 8*ebx]\nlea edx, [eax + 2*ecx]\nlea eex, [edx + 4*ecx]\n",
    "3\nlea ebx, [8*eax]\nlea ecx, [ebx + 2*ebx]\nlea edx, [ebx + 8*ecx]\n",
    "3\nlea ebx, [eax + 2*eax]\nlea ecx, [eax + 8*ebx]\nlea edx, [eax + 8*ecx]\n",
    "4\nlea ebx, [2*eax]\nlea ecx, [eax + 2*eax]\nlea edx, [eax + 8*ecx]\nlea eex, [ebx + 8*edx]\n",
    "3\nlea ebx, [eax + 2*eax]\nlea ecx, [eax + 8*ebx]\nlea edx, [ebx + 8*ecx]\n",
    "4\nlea ebx, [2*eax]\nlea ecx, [eax + 8*ebx]\nlea edx, [4*ecx]\nlea eex, [edx + 8*ecx]\n",
    "3\nlea ebx, [eax + 4*eax]\nlea ecx, [eax + 8*ebx]\nlea edx, [ecx + 4*ecx]\n",
    "4\nlea ebx, [2*eax]\nlea ecx, [ebx + 4*eax]\nlea edx, [eax + 4*ecx]\nlea eex, [ecx + 8*edx]\n",
    "4\nlea ebx, [2*eax]\nlea ecx, [eax + 8*ebx]\nlea edx, [eax + 4*ecx]\nlea eex, [edx + 2*edx]\n",
    "4\nlea ebx, [2*eax]\nlea ecx, [8*ebx]\nlea edx, [ecx + 8*eax]\nlea eex, [ecx + 8*edx]\n",
    "4\nlea ebx, [2*eax]\nlea ecx, [eax + 2*eax]\nlea edx, [ebx + 8*ecx]\nlea eex, [eax + 8*edx]\n",
    "4\nlea ebx, [2*eax]\nlea ecx, [eax + 2*eax]\nlea edx, [ebx + 8*ecx]\nlea eex, [ebx + 8*edx]\n",
    "4\nlea ebx, [2*eax]\nlea ecx, [eax + 2*eax]\nlea edx, [ebx + 8*ecx]\nlea eex, [ecx + 8*edx]\n",
    "4\nlea ebx, [4*eax]\nlea ecx, [ebx + 2*eax]\nlea edx, [ebx + 8*ecx]\nlea eex, [ebx + 4*edx]\n",
    "4\nlea ebx, [4*eax]\nlea ecx, [eax + 4*ebx]\nlea edx, [ecx + 8*ebx]\nlea eex, [ecx + 4*edx]\n",
    "4\nlea ebx, [2*eax]\nlea ecx, [ebx + 4*eax]\nlea edx, [ebx + 4*ecx]\nlea eex, [ecx + 8*edx]\n",
    "4\nlea ebx, [eax + 2*eax]\nlea ecx, [eax + 4*eax]\nlea edx, [ebx + 8*ecx]\nlea eex, [edx + 4*edx]\n",
    "3\nlea ebx, [8*eax]\nlea ecx, [ebx + 2*ebx]\nlea edx, [ecx + 8*ecx]\n",
    "3\nlea ebx, [eax + 2*eax]\nlea ecx, [ebx + 8*ebx]\nlea edx, [eax + 8*ecx]\n",
    "4\nlea ebx, [2*eax]\nlea ecx, [eax + 2*eax]\nlea edx, [ecx + 8*ecx]\nlea eex, [ebx + 8*edx]\n",
    "3\nlea ebx, [eax + 2*eax]\nlea ecx, [ebx + 8*ebx]\nlea edx, [ebx + 8*ecx]\n",
    "4\nlea ebx, [4*eax]\nlea ecx, [eax + 2*eax]\nlea edx, [ecx + 8*ecx]\nlea eex, [ebx + 8*edx]\n",
    "4\nlea ebx, [2*eax]\nlea ecx, [eax + 8*ebx]\nlea edx, [ecx + 2*ecx]\nlea eex, [ecx + 4*edx]\n",
    "4\nlea ebx, [2*eax]\nlea ecx, [eax + 8*eax]\nlea edx, [ebx + 8*ecx]\nlea eex, [edx + 2*edx]\n",
    "4\nlea ebx, [eax + 2*eax]\nlea ecx, [ebx + 4*eax]\nlea edx, [ebx + 8*ebx]\nlea eex, [ecx + 8*edx]\n",
    "4\nlea ebx, [4*eax]\nlea ecx, [8*ebx]\nlea edx, [ecx + 4*ebx]\nlea eex, [ecx + 4*edx]\n",
    "3\nlea ebx, [eax + 2*eax]\nlea ecx, [eax + 8*ebx]\nlea edx, [ecx + 8*ecx]\n",
    "4\nlea ebx, [2*eax]\nlea ecx, [ebx + 8*ebx]\nlea edx, [ecx + 8*eax]\nlea eex, [ecx + 8*edx]\n",
    "4\nlea ebx, [4*eax]\nlea ecx, [eax + 2*eax]\nlea edx, [ebx + 8*ecx]\nlea eex, [ecx + 8*edx]\n",
    "4\nlea ebx, [4*eax]\nlea ecx, [eax + 2*eax]\nlea edx, [ebx + 8*ecx]\nlea eex, [ebx + 8*edx]\n",
    "4\nlea ebx, [4*eax]\nlea ecx, [eax + 8*ebx]\nlea edx, [ecx + 4*ebx]\nlea eex, [ecx + 4*edx]\n",
    "4\nlea ebx, [4*eax]\nlea ecx, [ebx + 2*eax]\nlea edx, [ebx + 4*ecx]\nlea eex, [ecx + 8*edx]\n",
    "4\nlea ebx, [4*eax]\nlea ecx, [eax + 8*ebx]\nlea edx, [ecx + 2*ecx]\nlea eex, [edx + 4*ecx]\n",
    "4\nlea ebx, [8*eax]\nlea ecx, [eax + 4*eax]\nlea edx, [ebx + 4*ecx]\nlea eex, [ebx + 8*edx]\n",
    "4\nlea ebx, [eax + 2*eax]\nlea ecx, [eax + 4*eax]\nlea edx, [ecx + 8*ebx]\nlea eex, [eax + 8*edx]\n",
    "4\nlea ebx, [2*eax]\nlea ecx, [eax + 2*eax]\nlea edx, [ebx + 8*ecx]\nlea eex, [edx + 8*edx]\n",
    "4\nlea ebx, [eax + 2*eax]\nlea ecx, [eax + 4*eax]\nlea edx, [ecx + 8*ebx]\nlea eex, [ebx + 8*edx]\n",
    "4\nlea ebx, [4*eax]\nlea ecx, [ebx + 8*eax]\nlea edx, [ecx + 4*ebx]\nlea eex, [ecx + 8*edx]\n",
    "4\nlea ebx, [eax + 2*eax]\nlea ecx, [eax + 4*eax]\nlea edx, [ecx + 8*ebx]\nlea eex, [ecx + 8*edx]\n",
    "4\nlea ebx, [eax + 4*eax]\nlea ecx, [ebx + 1*eax]\nlea edx, [ebx + 4*ecx]\nlea eex, [ecx + 8*edx]\n",
    "4\nlea ebx, [eax + 2*eax]\nlea ecx, [ebx + 4*eax]\nlea edx, [eax + 4*ecx]\nlea eex, [ecx + 8*edx]\n",
    "4\nlea ebx, [2*eax]\nlea ecx, [8*ebx]\nlea edx, [ecx + 2*ecx]\nlea eex, [edx + 4*edx]\n",
    "4\nlea ebx, [2*eax]\nlea ecx, [ebx + 4*eax]\nlea edx, [ecx + 4*ecx]\nlea eex, [eax + 8*edx]\n",
    "4\nlea ebx, [2*eax]\nlea ecx, [ebx + 4*eax]\nlea edx, [ecx + 4*ecx]\nlea eex, [ebx + 8*edx]\n",
    "3\nlea ebx, [eax + 2*eax]\nlea ecx, [ebx + 8*ebx]\nlea edx, [ecx + 8*ecx]\n",
    "4\nlea ebx, [4*eax]\nlea ecx, [ebx + 2*eax]\nlea edx, [ecx + 4*ecx]\nlea eex, [ebx + 8*edx]\n",
    "4\nlea ebx, [2*eax]\nlea ecx, [ebx + 4*eax]\nlea edx, [eax + 8*ecx]\nlea eex, [edx + 4*edx]\n",
    "4\nlea ebx, [2*eax]\nlea ecx, [ebx + 4*eax]\nlea edx, [ecx + 4*ecx]\nlea eex, [ecx + 8*edx]\n",
    "4\nlea ebx, [eax + 2*eax]\nlea ecx, [eax + 4*ebx]\nlea edx, [ecx + 8*ecx]\nlea eex, [ecx + 2*edx]\n",
    "4\nlea ebx, [8*eax]\nlea ecx, [ebx + 2*eax]\nlea edx, [ecx + 2*ecx]\nlea eex, [ebx + 8*edx]\n",
    "4\nlea ebx, [eax + 2*eax]\nlea ecx, [ebx + 4*eax]\nlea edx, [ecx + 8*ebx]\nlea eex, [eax + 8*edx]\n",
    "4\nlea ebx, [2*eax]\nlea ecx, [ebx + 4*eax]\nlea edx, [ebx + 8*ecx]\nlea eex, [edx + 4*edx]\n",
    "4\nlea ebx, [eax + 2*eax]\nlea ecx, [ebx + 4*eax]\nlea edx, [ecx + 8*ebx]\nlea eex, [ebx + 8*edx]\n",
    "4\nlea ebx, [4*eax]\nlea ecx, [eax + 2*eax]\nlea edx, [ebx + 8*ecx]\nlea eex, [edx + 8*edx]\n",
    "4\nlea ebx, [eax + 2*eax]\nlea ecx, [ebx + 4*eax]\nlea edx, [ecx + 8*ecx]\nlea eex, [eax + 4*edx]\n",
    "5\nlea ebx, [2*eax]\nlea ecx, [eax + 2*eax]\nlea edx, [ecx + 4*eax]\nlea eex, [edx + 8*edx]\nlea efx, [ebx + 4*eex]\n",
    "4\nlea ebx, [2*eax]\nlea ecx, [eax + 8*ebx]\nlea edx, [ecx + 2*ecx]\nlea eex, [edx + 4*edx]\n",
};
signed main()
{
    int n;
    read(n);
    cout << str[n] << endl;
    return 0;
}