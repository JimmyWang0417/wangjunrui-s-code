#include <bits/stdc++.h>
#define lowbit(x) ((x)&(-(x)))
#define re register
#define ll long long
#define ull unsigned long long
#define rep(i,a,b) for(re int i=a;i<=b;++i)
#define per(i,a,b) for(re int i=a;i>=b;--i)
template<typename T>
inline void read(T&x)
{
	x=0;
	char s=(char)getchar();
	bool f=false;
	while(!(s>='0'&&s<='9'))
	{
		if(s=='-')
			f=true;
		s=(char)getchar();
	}
	while(s>='0'&&s<='9')
	{
		x=(x<<1)+(x<<3)+s-'0';
		s=(char)getchar();
	}
	if(f)
		x=(~x)+1;
}
template<typename T,typename ...T1>
inline void read(T&x,T1&...x1)
{
	read(x);
	read(x1...);
}
template<typename T>
inline void clear(T*array,int l,int r,int val)
{
	memset(&array[l],val,sizeof(T)*(r-l+1));
}
using namespace std;
const int N=2e5+5;
struct Edge
{
	int next,to;
} edge[N];
int head[N],num_edge;
inline void add_edge(int from,int to)
{
	edge[++num_edge].next=head[from];
	edge[num_edge].to=to;
	head[from]=num_edge;
}
int n,a[N];
multiset<int>se[N];
inline void merge(multiset<int> &x,multiset<int> &y)
{
	if(x.size()<y.size())
		swap(x,y);
	for(multiset<int>::iterator it=y.begin(); it!=y.end(); ++it)
		x.insert(*it);
}
inline void dfs(int u)
{
	for(int i=head[u]; i; i=edge[i].next)
	{
		int &v=edge[i].to;
		dfs(v);
		merge(se[u],se[v]);
	}
	multiset<int>::iterator it=se[u].lower_bound(a[u]);
	if(it!=se[u].end())
		se[u].erase(it);
	se[u].insert(a[u]);
}
signed main()
{
	read(n);
	for(int i=1; i<=n; ++i)
	{
		int fa;
		read(a[i],fa);
		add_edge(fa,i);
	}
	dfs(1);
	printf("%llu\n",se[1].size());
	return 0;
}


