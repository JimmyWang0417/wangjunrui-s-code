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
const int N=(1<<10)+5;
int n,m;
char str[N];
bitset<N>exist,vis;
int belong[N];
vector<int>g[N];
inline bool find(int u)
{
	for(auto v:g[u])
	{
		if(vis[v])
			continue;
		vis[v]=true;
		if(!belong[v]||find(belong[v]))
		{
			belong[v]=u;
			return true;
		}
	}
	return false;
}
signed main()
{
	while(read(n,m),n||m)
	{
		int cnt=0;
		for(int i=1; i<=m; ++i)
		{
			scanf("%s",str);
			int x=0,pos=-1;
			for(int j=0; j<n; ++j)
				if(str[j]=='1')
					x|=(1<<j);
				else if(str[j]=='*')
					pos=j;
			exist[x]=true;
			if(pos!=-1)
				exist[x^(1<<pos)]=true;
		}
		for(int i=0; i<(1<<n); ++i)
			if(exist[i])
			{
				++cnt;
				for(int j=0; j<n; ++j)
					if(exist[i^(1<<j)])
					{
						g[i].push_back(i^(1<<j));
					}

			}
		memset(belong,0,sizeof(belong));
		int ans=0;
		for(int i=0; i<(1<<n); ++i)
		{
			ans+=find(i);
			vis.reset();
		}
		printf("%d\n",cnt-ans/2);
		for(int i=0; i<(1<<n); ++i)
			g[i].clear();
		exist.reset();
	}
	return 0;
}


