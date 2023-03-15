/**
 *    name:
 *    author:   whitepaperdog (蒟蒻wjr)
 *    located:  Xuanwu District, Nanjing City, Jiangsu Province, China
 *    created:  2023.03.12 周日 14:58:46 (Asia/Shanghai)
 *    unicode:  UTF-8
 *    standard: c++23
 **/
#include "guess.h"
#include <algorithm>
#include <cstdio>
typedef long long ll;
typedef unsigned long long ull;
#define lowbit(x) ((x) & (-(x)))
using namespace std;
ll p[64];
inline ll solve(ll pos, ll l, ll r)
{
    if (l == r)
        return l;
    if (l > r)
        swap(l, r);
    ll len = 3, mid;
    while (len < r - l + 1)
        len = len * 2 + 1;
    if (pos < r - len + 1)
        mid = r - len / 2;
    else if (pos > l + len - 1)
        mid = l + len / 2;
    else if (pos <= l)
        mid = pos + len / 2;
    else
        mid = pos - len / 2;
    ll q = 2 * mid - pos;
    int g = Guess(q);
    if (g == 0)
        return mid;
    if ((q > mid && g > 0) || (q < mid && g < 0))
        return solve(q, min(mid + 1, r), r);
    return solve(q, l, max(mid - 1, l));
}
inline ll solve(ll ed, ll n)
{
    auto calc = [ed](auto x)
    {
        return ed == 1 ? x : ed - x + 1;
    };
    if (n == 1)
        return calc(1);
    if (n == 2)
    {
        int g = Guess(calc(1));
        if (g > 0)
            return calc(1);
        return calc(2);
    }
    if (n == 3)
    {
        int g = Guess(calc(1));
        if (g > 0)
            return calc(1);
        if (g == 0)
            return calc(2);
        return calc(3);
    }
    if (n == 4)
    {
        int g = Guess(calc(3));
        if (g < 0)
            return calc(4);
        g = Guess(calc(1));
        if (g < 0)
            return calc(3);
        if (g == 0)
            return calc(2);
        return calc(1);
    }
    if (n == 5)
    {
        int g = Guess(calc(3));
        if (g < 0)
            return calc(5);
        if (g == 0)
            return calc(4);
        g = Guess(calc(1));
        if (g < 0)
            return calc(3);
        if (g == 0)
            return calc(2);
        return calc(1);
    }
    if (n == 6)
    {
        int g = Guess(calc(1));
        if (g > 0)
        {
            g = Guess(calc(3));
            if (g > 0)
                return calc(3);
            if (g == 0)
                return calc(2);
            return calc(1);
        }
        g = Guess(calc(9));
        if (g > 0)
            return calc(6);
        if (g == 0)
            return calc(5);
        return calc(4);
    }
    if (n == 7)
    {
        int g = Guess(calc(1));
        if (g == 0)
            return calc(4);
        if (g > 0)
        {
            g = Guess(calc(3));
            if (g > 0)
                return calc(3);
            if (g == 0)
                return calc(2);
            return calc(1);
        }
        g = Guess(calc(11));
        if (g > 0)
            return calc(7);
        if (g == 0)
            return calc(6);
        return calc(5);
    }
    int m = 0;
    while (p[m] < n)
        ++m;
    int g = Guess(calc(p[m - 2] - 2));
    if (g == 0)
        return calc((p[m - 2] - 2 + n) / 2);
    if (g < 0)
        return solve(calc(p[m - 2] - 2), calc((p[m - 2] - 2 + n) / 2 + 1), calc(n));
    g = Guess(calc(p[m - 2]));
    if (g < 0)
        return solve(ed, p[m - 2]);
    if (g == 0)
        return calc(p[m - 2] - 1);
    return solve(calc(p[m - 2]), calc(p[m - 2]), calc((p[m - 2] + n - 3) / 2));
}
ll HC(ll n, int)
{
    if (n == 1)
        return 1;
    if (n == 2)
    {
        Guess(1);
        if (Guess(2) < 0)
            return 1;
        return 2;
    }
    if (n == 3)
    {
        Guess(1);
        int g = Guess(3);
        if (g < 0)
            return 1;
        if (g == 0)
            return 2;
        return 3;
    }
    if (!p[0])
    {
        p[0] = 1, p[1] = 3, p[2] = 7;
        for (int i = 3; i <= 60; ++i)
            p[i] = p[i - 2] + (1ll << i);
    }
    ll mid = (n + 2) / 2;
    Guess(mid - 2);
    int g = Guess(mid);
    if (g < 0)
        return solve(1, mid);
    if (g == 0)
        return mid - 1;
    return solve(n, n - mid + 1);
}
