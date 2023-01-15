/**
 *    unicode: UTF-8
 *    name:    P7738 [NOI2021] 量子通信
 *    author:  whitepaperdog
 *    created: 2022.07.25 周一 10:53:57 (Asia/Shanghai)
 **/
#include <algorithm>
#include <bitset>
#include <cstdio>
#include <iostream>
#include <list>
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
constexpr int N = 4e5 + 5, M = 256;
int n, m;
ull a1, a2;
bitset<M> a[N], b;
char str[N];
int st[N], top;
bool vis[N];
inline ull myRand(ull &k1, ull &k2)
{
    ull k3 = k1, k4 = k2;
    k1 = k4;
    k3 ^= (k3 << 23);
    k2 = k3 ^ k4 ^ (k3 >> 17) ^ (k4 >> 26);
    return k2 + k4;
}
bool lastans;
struct Edge
{
    int next, to;
} edge[N * 16];
int head[16][(1 << 16)], num_edge;
inline void add_edge(int from1, int from2, int to)
{
    edge[++num_edge].next = head[from1][from2];
    edge[num_edge].to = to;
    head[from1][from2] = num_edge;
}
inline void gen()
{
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < 256; ++j)
            a[i][j] = (myRand(a1, a2) & (1ull << 32)) ? 1 : 0;
    for (int i = 0; i < n; ++i)
        for (int j = 0, now = 0; j < 256; ++j)
        {
            now |= a[i][j] << (j % 16);
            if (j % 16 == 15)
            {
                add_edge(j / 16, now, i);
                now = 0;
            }
        }
}
inline void work()
{
    while (top)
        vis[st[top--]] = false;
    int len;
    scanf("%s", str);
    read(len);
    for (int j = 0; j < 64; ++j)
    {
        int x = str[j] >= '0' && str[j] <= '9' ? str[j] - '0' : str[j] - 'A' + 10;
        b[j * 4 + 3] = (x & 1) ^ lastans;
        b[j * 4 + 2] = ((x >> 1) & 1) ^ lastans;
        b[j * 4 + 1] = ((x >> 2) & 1) ^ lastans;
        b[j * 4 + 0] = ((x >> 3) & 1) ^ lastans;
    }
    for (int j = 0, now = 0; j < 256; ++j)
    {
        now |= b[j] << (j % 16);
        if (j % 16 == 15)
        {
            for (int e = head[j / 16][now]; e; e = edge[e].next)
            {
                int &k = edge[e].to;
                if (vis[k])
                    continue;
                if ((int)(a[k] ^ b).count() <= len)
                {
                    lastans = 1;
                    printf("1\n");
                    return;
                }
                vis[st[++top] = k] = true;
            }
            now = 0;
        }
    }
    printf("0\n");
    lastans = false;
}
signed main()
{
    read(n, m, a1, a2);
    gen();
    for (int i = 0; i < m; ++i)
        work();
    return 0;
}