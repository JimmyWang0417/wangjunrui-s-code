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
const int N=2005,M=6005;
struct Edge
{
	int next,to;
} edge[M];
int head[N],num_edge;
inline void add_edge(int from,int to)
{
	edge[++num_edge].next=head[from];
	edge[num_edge].to=to;
	head[from]=num_edge;
}
int n,m,k;
int in[N];
bitset<N>exist[N];
int sg[N];
signed main()
{
	read(n,m,k);
	for(int i=1; i<=m; ++i)
	{
		int x,y;
		read(x,y);
		add_edge(y,x);
		++in[x];
	}
	queue<int>q;
	for(int i=1; i<=n; ++i)
		if(!in[i])
			q.push(i);
	while(!q.empty())
	{
		int u=q.front();
		q.pop();
		for(int i=0; i<=n; ++i)
			if(!exist[u][i])
			{
				sg[u]=i;
				break;
			}
		for(int i=head[u]; i; i=edge[i].next)
		{
			int &v=edge[i].to;
			exist[v][sg[u]]=true;
			if(!--in[v])
				q.push(v);
		}
	}
	int ans=0;
	for(int i=1; i<=k; ++i)
	{
		int pos;
		read(pos);
		ans^=sg[pos];
	}
	printf(ans?"win":"lose");
	return 0;
}


