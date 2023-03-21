/**
 *    name:     C. Claire 的魔术
 *    author:   whitepaperdog (蒟蒻wjr)
 *    located:  Xuanwu District, Nanjing City, Jiangsu Province, China
 *    created:  2023.03.16 周四 16:37:51 (Asia/Shanghai)
 *    unicode:  UTF-8
 *    standard: c++23
 **/
#include "lancllords.h"
#include <algorithm>
#include <cmath>
#include <cstdio>
#include <tuple>
#include <vector>
typedef long long ll;
typedef unsigned long long ull;
#define lowbit(x) ((x) & (-(x)))
using namespace std;
constexpr int N = 1e5 + 5;
inline int query(int x, int y)
{
    static int p = 0, q = 0;
    while (p < x)
    {
        inc_p();
        ++p;
    }
    while (p > x)
    {
        dec_p();
        --p;
    }
    while (q < y)
    {
        inc_q();
        ++q;
    }
    while (q > y)
    {
        dec_q();
        --q;
    }
    return cmp();
}
int belong[N];
int small[N];
int block;
struct Query
{
    int l, r, id;
    Query(int _l = 0, int _r = 0, int _id = 0) : l(_l), r(_r), id(_id) {}
    inline bool operator<(const Query &rhs) const
    {
        int lblock = l / block, rblock = rhs.l / block;
        return lblock == rblock ? (lblock & 1 ? r < rhs.r : r > rhs.r) : l < rhs.l;
    }
};
inline vector<int> merge(vector<int> A, vector<int> B, int l, int r)
{
    if (A.size() < B.size())
        swap(A, B);
    if (B.empty())
        return A;
    if (A.size() == 1)
    {
        vector<int> C = {A[0], B[0]};
        if (query(C[1], C[0]))
            swap(C[0], C[1]);
        return C;
    }
    vector<int> A1, A2;
    for (int i = 0; i < (int)A.size(); i += 2)
        A1.push_back(A[i]);
    auto C2 = merge(A1, B, l, r);
    for (int i = 0, j = 0; i < (int)A.size(); i += 2)
    {
        while (j < (int)C2.size() && C2[j] != A[i])
            j++;
        belong[i] = j;
    }
    if (A.size() % 2 == 0)
        belong[A.size()] = (int)C2.size();
    vector<Query> qwq;
    for (int i = 1; i < (int)A.size(); i += 2)
    {
        small[i] = 0;
        for (int j = belong[i - 1] + 1; j < belong[i + 1]; ++j)
        {
            if (A[i] < C2[j])
                qwq.emplace_back(A[i], C2[j], -i);
            else
                qwq.emplace_back(C2[j], A[i], i);
        }
    }
    if (!qwq.empty())
    {
        block = (r - l + 1) / sqrt(qwq.size());
        sort(qwq.begin(), qwq.end());
        for (auto [x, y, id] : qwq)
        {
            if (id > 0)
                small[id] += query(x, y);
            else
                small[-id] += 1 - query(x, y);
        }
    }
    int now = 0;
    vector<int> C;
    for (int i = 1; i < (int)A.size(); i += 2)
    {
        int cnt = 0;
        belong[i] = belong[i - 1] + small[i];
        while (now <= belong[i])
            C.push_back(C2[now++]);
        C.push_back(A[i]);
    }
    while (now < (int)C2.size())
        C.push_back(C2[now++]);
    return C;
}
vector<int> ccf;
inline void solve(int l, int r)
{
    if (l == r)
        return;
    int mid = (l + r) >> 1;
    solve(l, mid);
    solve(mid + 1, r);
    vector<int> A, B;
    for (int i = l; i <= mid; i++)
        A.push_back(ccf[i]);
    for (int i = mid + 1; i <= r; i++)
        B.push_back(ccf[i]);
    auto C = merge(A, B, l, r);
    for (int i = l; i <= r; i++)
        ccf[i] = C[i - l];
}
vector<int> answer(int n)
{
    ccf.resize(n);
    for (int i = 0; i < n; ++i)
        ccf[i] = i;
    solve(0, n - 1);
    vector<int> qwq(n);
    for (int i = 0; i < (int)ccf.size(); ++i)
        qwq[ccf[i]] = i;
    return qwq;
}