#include <set>
#include <map>
#include <cmath>
#include <queue>
#include <vector>
#include <cstdio>
#include <bitset>
#include <cstring>
#include <iostream>
#include <algorithm>
#define lowbit(x) (x&(-x))
#define re register
#define ll long long
#define ull unsigned long long
#define rep(i,a,b) for(re int i=a;i<=b;++i)
#define per(i,a,b) for(re int i=a;i>=b;--i)
using namespace std;
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
vector<pair<int,int> >a,b;
map<int,int>fa;
inline int find(int x)
{
	return fa.count(x)?fa[x]=find(fa[x]):x;
}
inline void unionn(int x,int y)
{
	int fx=find(x),fy=find(y);
	if(fx==fy)
		return;
	fa[fx]=fy;
}
inline void work()
{
	a.clear(),b.clear(),fa.clear();
	int n;
	read(n);
	for(re int i=1; i<=n; ++i)
	{
		int l,r,opt;
		read(l,r,opt);
		(opt?a:b).push_back(make_pair(l,r));
	}
	a.shrink_to_fit(),b.shrink_to_fit();
	for(auto i:a)
		unionn(i.first,i.second);
	for(auto i:b)
		if(find(i.first)==find(i.second))
		{
			printf("NO\n");
			return;
		}
	printf("YES\n");
}
signed main()
{
	int T;
	read(T);
	while(T--)
		work();
	return 0;
}
