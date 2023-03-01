/**
 *    name:     A. 小 G 的 cmd
 *    author:   whitepaperdog (蒟蒻wjr)
 *    located:  Xuanwu District, Nanjing City, Jiangsu Province, China
 *    created:  2023.02.28 周二 08:05:52 (Asia/Shanghai)
 *    unicode:  UTF-8
 *    standard: c++23
 **/
#include <cstdio>
#include <iostream>
#include <queue>
#include <set>
#include <string>
typedef long long ll;
typedef unsigned long long ull;
// __extension__ typedef __int128 int128;
#define lowbit(x) ((x) & (-(x)))
using namespace std;
constexpr int N = 1e5 + 5;
constexpr bool T = true;
int n, m;
string str[N];
int a[N];
template <typename T>
struct Queue
{
    priority_queue<T, vector<T>, greater<T>> p, q;
    inline bool empty()
    {
        return p.size() == q.size();
    }
    inline int size()
    {
        return (int)(q.size() - p.size());
    }
    inline T top()
    {
        while (!p.empty() && q.top() == p.top())
        {
            q.pop();
            p.pop();
        }
        return q.top();
    }
    inline void pop()
    {
        q.pop();
    }
    inline void pop(T x)
    {
        p.push(x);
    }
    inline void push(T x)
    {
        q.push(x);
    }
    inline void swap(Queue &rhs)
    {
        p.swap(rhs.p);
        q.swap(rhs.q);
    }
    inline void clear()
    {
        while (!p.empty())
            p.pop();
        while (!q.empty())
            q.pop();
    }
};
int dp[20][N], Log[N];
inline int query(int l, int r)
{
    int k = Log[r - l + 1];
    return max(dp[k][l], dp[k][r - (1 << k) + 1]);
}
typedef Queue<pair<int, int>> node;
node que[N], all;
int q[N], head, tail;
inline void merge(node &x, node &y)
{
    if (x.size() < y.size())
        swap(x, y);
    while (!y.empty())
    {
        x.push(y.top());
        y.pop();
    }
    y.clear();
}
inline pair<int, int> operator+(const pair<int, int> &lhs, const int &rhs)
{
    return make_pair(lhs.first + rhs, lhs.second);
}
inline void insert(int x, pair<int, int> y)
{
    node qwq;
    qwq.push(y);
    while (head <= tail && q[tail] <= x)
    {
        all.pop(que[tail].top() + q[tail]);
        merge(qwq, que[tail--]);
    }
    que[++tail].swap(qwq);
    q[tail] = x;
    all.push(que[tail].top() + q[tail]);
}
int f[N], g[N];
inline bool check(int mid)
{
    head = 1, tail = 0;
    f[0] = -1;
    for (int i = 1; i <= n; ++i)
    {
        insert(a[i], make_pair(f[i - 1], i - 1));
        while (head <= tail && que[head].top().second < i - mid)
        {
            all.pop(que[head].top() + q[head]);
            que[head].pop();
            if (!que[head].empty())
                all.push(que[head].top() + q[head]);
            else
                ++head;
        }
        f[i] = all.top().first + 1;
        g[i] = all.top().second;
    }
    all.clear();
    for (int i = 1; i <= n; ++i)
        que[i].clear();
    return f[n] <= m;
}
int p[N], tot;
int qwq[N];
signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    cin >> n >> m;
    for (int i = 1; i <= n; ++i)
    {
        cin >> str[i];
        a[i] = (int)str[i].length();
    }
    Log[0] = -1;
    for (int i = 1; i <= n; ++i)
    {
        Log[i] = Log[i >> 1] + 1;
        dp[0][i] = a[i];
    }
    for (int j = 0; j < Log[n]; ++j)
        for (int i = 1; i + (2 << j) - 1 <= n; ++i)
            dp[j + 1][i] = max(dp[j][i], dp[j][i + (1 << j)]);
    int l = 1, r = n;
    while (l <= r)
    {
        int mid = (l + r) >> 1;
        if (check(mid))
            r = mid - 1;
        else
            l = mid + 1;
    }
    if (!T)
        cout << l << endl;
    else
    {
        check(l);
        for (int i = n; i; i = g[i])
        {
            p[++tot] = i;
            qwq[tot] = 1;
        }
        cout << l << ' ' << tot << endl;
        for (int i = tot; i >= 1; --i)
            cout << query(p[i + 1] + 1, p[i]) << ' ';
        cout << endl;
        for (int j = 1; j <= l; ++j)
        {
            for (int i = tot; i >= 1; --i)
            {
                if (p[i + 1] + qwq[i] <= p[i])
                {
                    cout << str[p[i + 1] + qwq[i]];
                    int len = query(p[i + 1] + 1, p[i]);
                    for (int k = a[p[i + 1] + qwq[i]]; k <= len; ++k)
                        cout << ' ';
                    ++qwq[i];
                }
                else
                {
                    int len = query(p[i + 1] + 1, p[i]);
                    for (int k = 0; k <= len; ++k)
                        cout << ' ';
                }
            }
            cout << endl;
        }
    }
    return 0;
}