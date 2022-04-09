#include <bits/stdc++.h>

using namespace std;

const int N = 125005;

int ans[N];
int fail[N];
int lenS, lenT;
char s[N], t[N];

int fa[N];
int blk[N], cb;

inline int tr(char ch) { return ch - 'a'; }

void solve(int res)
{
    int cur(0);
    fail[1] = 0;
    for (int i = 2; i <= lenT; ++i)
    {
        while (cur && fa[tr(t[i])] != fa[tr(t[cur + 1])])
            cur = fail[cur];
        if (fa[tr(t[i])] == fa[tr(t[cur + 1])])
            ++cur;
        fail[i] = cur;
    }
    cur = 0;
    for (int i = 1; i <= lenS; ++i)
    {
        while (cur && fa[tr(s[i])] != fa[tr(t[cur + 1])])
            cur = fail[cur];
        if (fa[tr(s[i])] == fa[tr(t[cur + 1])])
            ++cur;
        if (cur == lenT)
        {
            ans[i] = min(ans[i], res);
            cur = fail[cur];
        }
    }
}

void divSet(int dep)
{
    if (dep > tr('f'))
    {
        solve(6 - cb);
        return void();
    }

    fa[dep] = dep;
    blk[++cb] = dep;
    divSet(dep + 1);

    blk[cb--] = 0;
    for (int i = 1; i <= cb; ++i)
    {
        fa[dep] = blk[i];
        divSet(dep + 1);
    }
}

int main()
{

    freopen("Antetokounmpo.in", "r", stdin);
    freopen("Antetokounmpo.out", "w", stdout);
    scanf("%s %s", s + 1, t + 1);
    lenS = strlen(s + 1);
    lenT = strlen(t + 1);

    for (int i = lenT; i <= lenS; ++i)
        ans[i] = 233;
    divSet(0);
    for (int i = lenT; i <= lenS; ++i)
        printf("%d%c", ans[i], " \n"[i == lenS]);
    return 0;
}
