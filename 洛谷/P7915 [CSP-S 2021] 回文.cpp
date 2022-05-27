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
const int N = 1e6 + 5;
int n, a[N];
int pos[N][2];
inline int reverse(int x)
{
    if (pos[a[x]][0] == x)
        return pos[a[x]][1];
    else
        return pos[a[x]][0];
}
char answer[N];
inline bool checkl()
{
    int rev = reverse(1);
    int l = 2, r = 2 * n - 1;
    deque<int> q1, q2;
    answer[1] = 'L';
    answer[2 * n] = 'L';
    for (int i = 2; i < rev; ++i)
        q1.push_back(a[i]);
    for (int i = 2 * n; i > rev; --i)
        q2.push_back(a[i]);
    while (!q1.empty() || !q2.empty())
    {
        if (q1.size() >= 2 && q1.front() == q1.back())
        {
            answer[l++] = 'L';
            answer[r--] = 'L';
            q1.pop_front();
            q1.pop_back();
        }
        else if (!q1.empty() && !q2.empty() && q1.front() == q2.back())
        {
            answer[l++] = 'L';
            answer[r--] = 'R';
            q1.pop_front();
            q2.pop_back();
        }
        else if (!q2.empty() && !q1.empty() && q2.front() == q1.back())
        {
            answer[l++] = 'R';
            answer[r--] = 'L';
            q2.pop_front();
            q1.pop_back();
        }
        else if (q2.size() >= 2 && q2.front() == q2.back())
        {
            answer[l++] = 'R';
            answer[r--] = 'R';
            q2.pop_front();
            q2.pop_back();
        }
        else
            return false;
    }
    answer[2 * n + 1] = '\0';
    printf("%s\n", answer + 1);
    return true;
}
inline bool checkr()
{
    int rev = reverse(2 * n);
    int l = 2, r = 2 * n - 1;
    deque<int> q1, q2;
    answer[1] = 'R';
    answer[2 * n] = 'L';
    for (int i = 1; i < rev; ++i)
        q1.push_back(a[i]);
    for (int i = 2 * n - 1; i > rev; --i)
        q2.push_back(a[i]);
    while (!q1.empty() || !q2.empty())
    {
        if (q1.size() >= 2 && q1.front() == q1.back())
        {
            answer[l++] = 'L';
            answer[r--] = 'L';
            q1.pop_front();
            q1.pop_back();
        }
        else if (!q1.empty() && !q2.empty() && q1.front() == q2.back())
        {
            answer[l++] = 'L';
            answer[r--] = 'R';
            q1.pop_front();
            q2.pop_back();
        }
        else if (!q2.empty() && !q1.empty() && q2.front() == q1.back())
        {
            answer[l++] = 'R';
            answer[r--] = 'L';
            q2.pop_front();
            q1.pop_back();
        }
        else if (q2.size() >= 2 && q2.front() == q2.back())
        {
            answer[l++] = 'R';
            answer[r--] = 'R';
            q2.pop_front();
            q2.pop_back();
        }
        else
            return false;
    }
    answer[2 * n + 1] = '\0';
    printf("%s\n", answer + 1);
    return true;
}
inline void work()
{
    read(n);
    for (int i = 1; i <= n; ++i)
        pos[i][0] = pos[i][1] = 0;
    for (int i = 1; i <= 2 * n; ++i)
    {
        read(a[i]);
        if (!pos[a[i]][0])
            pos[a[i]][0] = i;
        else
            pos[a[i]][1] = i;
    }
    if (checkl())
        return;
    if (checkr())
        return;
    printf("-1\n");
}
signed main()
{
    int T;
    read(T);
    while (T--)
        work();
    return 0;
}
