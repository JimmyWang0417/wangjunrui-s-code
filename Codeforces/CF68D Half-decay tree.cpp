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
map<int,int>mp;
int h,q;
inline double dfs(int u,int ans)
{
		return ans>=mp[u]?ans:0.5*(dfs(u<<1,max(ans,mp[u]-mp[u<<1]))+dfs(u<<1|1,max(ans,mp[u]-mp[u<<1|1])));
}
signed main()
{
	read(h,q);
	while(q--)
	{
		static char opt[10];
		scanf("%s",opt);
		if(opt[0]=='a')
		{
			int x,v;
			read(x,v);
			while(x)
			{
				mp[x]+=v;
				x>>=1;
			}
		}
		else
			printf("%lf\n",dfs(1,0));
	}
	return 0;
}


