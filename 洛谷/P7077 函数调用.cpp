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
const int N=1e5+5,mod=998244353;
inline int times(int x,int y)
{
	return (int)((ll)x*y%mod);
}
inline void add(int &x,int y)
{
	x+=y;
	if(x>=mod)
		x-=mod;
}
struct node
{
	int opt,pos,add,mul;
	int cnt;
} a[N];
vector<int>g1[N],g2[N];
int n,m,data[N];
bitset<N>vis;
int mul=1;
inline void dfs(int u)
{
	if(vis[u])
		return;
	vis.set(u);
	mul=times(mul,a[u].mul);
	for(auto v:g2[u])
		dfs(v);
}
int in[N];
signed main()
{
	read(n);
	for(int i=1; i<=n; ++i)
		read(data[i]);
	read(m);
	for(int i=1; i<=m; ++i)
	{
		read(a[i].opt);
		if(a[i].opt==1)
		{
			read(a[i].pos,a[i].add);
			a[i].mul=1;
		}
		else if(a[i].opt==2)
			read(a[i].mul);
		else
		{
			a[i].mul=1;
			int cnt;
			read(cnt);
			while(cnt--)
			{
				int x;
				read(x);
				g1[i].push_back(x);
				g2[x].push_back(i);
			}
		}
	}
	int cnt;
	read(cnt);
	while(cnt--)
	{
		int x;
		read(x);
		g1[0].push_back(x);
		g2[x].push_back(0);
	}
	queue<int>q;
	for(int i=0; i<=n; ++i)
	{
		in[i]=(int)g2[i].size();
		if(!in[i])
			q.push(i);
		g1[i].reverse();
	}
	while(!q.empty())
	{
		int u=q.front();
		q.pop();
		for(auto v:g1[u])
		{
			if(!--in[v])
				q.push(v);
			add(a[v].cnt,times(a[u].cnt,));
		}
	}
	dfs(0);
	return 0;
}


