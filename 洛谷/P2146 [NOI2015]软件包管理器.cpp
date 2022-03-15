#include <cstdio>
#include <algorithm>
using namespace std;
template <typename T>
inline void read(T &x)
{
	x = 0;
	char s = getchar();
	bool f = false;
	while (!(s >= '0' && s <= '9'))
	{
		if (s == '-')
			f = true;
		s = getchar();
	}
	while (s >= '0' && s <= '9')
	{
		x = (x << 1) + (x << 3) + s - '0';
		s = getchar();
	}
	if (f)
		x = (~x) + 1;
}
#define re register
#define ls (k << 1)
#define rs (k << 1 | 1)
const int N = 1e5 + 10, M = 2e5 + 10, T = 4e5 + 10;
struct Edge
{
	int next, to;
} edge[M];
int num_edge, head[N];
struct Tree
{
	int l, r, size, sum, flag;
} tree[T];
char s[110];
int n, q, cnt;
int idx[N], rk[N], dep[N], fa[N], top[N], size[N], son[N];		//rk[i]其实并没有什么用这只是我的习惯 
inline void add_edge(int from, int to)
{
	edge[++num_edge].next = head[from];
	edge[num_edge].to = to;
	head[from] = num_edge;
}
inline void dfs1(int u, int f)
{
	fa[u] = f;
	dep[u] = dep[f] + 1;
	size[u] = 1;
	for (re int i = head[u]; i; i = edge[i].next)
	{
		int &v = edge[i].to;
		if (v == f)
			continue;
		dfs1(v, u);
		size[u] += size[v];
		if (size[son[u]] < size[v])
			son[u] = v;
	}
}
inline void dfs2(int u, int tp)
{
	idx[u] = ++cnt;
	rk[cnt] = u;
	top[u] = tp;
	if (!son[u])
		return;
	dfs2(son[u], tp);
	for (re int i = head[u]; i; i = edge[i].next)
	{
		int &v = edge[i].to;
		if (idx[v])
			continue;
		dfs2(v, v);
	}
}
inline void pushdown(int k)
{
	if (~tree[k].flag)//相当于tree[k].flag!=-1 
	{
		tree[ls].sum = tree[ls].size * tree[k].flag;
		tree[rs].sum = tree[rs].size * tree[k].flag;
		tree[ls].flag = tree[rs].flag = tree[k].flag;
		tree[k].flag = -1;
	}
}
inline void build(int k, int l, int r)
{
	tree[k].l = l;
	tree[k].r = r;
	tree[k].size = r - l + 1;
	if (l == r)
	{
		tree[k].flag = -1;
		return;
	}
	int mid = l + r >> 1;
	build(ls, l, mid);
	build(rs, mid + 1, r);
}
inline void update1(int k, int l, int r, int val)
{
	if (l <= tree[k].l && tree[k].r <= r)
	{
		tree[k].sum = tree[k].size * val;
		tree[k].flag = val;
		return;
	}
	int mid = (tree[k].l + tree[k].r) >> 1;
	pushdown(k);
	if (l <= mid)
		update1(ls, l, r, val);
	if (mid < r)
		update1(rs, l, r, val);
	tree[k].sum = tree[ls].sum + tree[rs].sum;
}
inline void update2(int x, int y)
{
	while (top[x] != top[y])
	{
		if (dep[top[x]] < dep[top[y]])
			swap(x, y);
		update1(1, idx[top[x]], idx[x], 1);
		x = fa[top[x]];
	}
	if (dep[x] > dep[y])
		swap(x, y);
	update1(1, idx[x], idx[y], 1);
}
int main()
{
	read(n);
	for (re int i = 2, x; i <= n; ++i)
	{
		read(x);
		add_edge(x + 1, i);
	}
	dfs1(1, 0);
	dfs2(1, 1);
	build(1, 1, n);
	read(q);
	for (re int i = 1, before, x; i <= q; ++i)
	{
		scanf("%s", s);
		read(x);
		++x;
		before = tree[1].sum;
		if (s[0] == 'i')
		{
			update2(1, x);
			printf("%d\n", tree[1].sum - before);
		}
		else if (s[0] == 'u')
		{
			update1(1, idx[x], idx[x] + size[x] - 1, 0);
			printf("%d\n", before - tree[1].sum);
		}
	}
	return 0;
}
