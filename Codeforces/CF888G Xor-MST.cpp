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
int ch[N*31][2],tot;
inline void insert(int val)
{
	int u=0;
	for(int i=29; i>=0; --i)
	{
		int c=(val>>i)&1;
		if(!ch[u][c])
			ch[u][c]=++tot;
		u=ch[u][c];
	}
}
inline int query(int val)
{
	int u=0,res=0;
	for(int i=29; i>=0; --i)
	{
		int c=(val>>i)&1;
		if(ch[u][c])
			u=ch[u][c];
		else
		{
			res+=1<<i;
			u=ch[u][!c];
		}
	}
	return res;
}
int n,a[N];
inline ll solve(int dep,const vector<int>&tree)
{
	if(dep==-1)
		return 0;
	vector<int>son[2];
	for(auto v:tree)
		son[(v>>dep)&1].push_back(v);
	if(son[0].size()&&son[1].size())
	{
		for(auto v:son[0])
			insert(v);
		int res=0x7fffffff;
		for(auto v:son[1])
			res=min(res,query(v));
		clear(ch,0,tot,0);
		tot=0;
		return solve(dep-1,son[0])+res+solve(dep-1,son[1]);
	}
	else if(son[0].size())
		return solve(dep-1,son[0]);
	else return solve(dep-1,son[1]);
}
signed main()
{
	read(n);
	vector<int>tree;
	for(int i=1; i<=n; ++i)
	{
		int x;
		read(x);
		tree.push_back(x);
	}
	printf("%lld\n",solve(29,tree));
	return 0;
}


