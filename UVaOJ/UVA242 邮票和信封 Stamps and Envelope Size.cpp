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
const int N=1e4+5;
int n,m,s;
vector<int>g[N],G;
int dp[N];
int answer[N];
signed main()
{
	while(read(m),m)
	{
		read(n);
		for(int now=0; now<n; ++now)
		{
			int cnt;
			read(cnt);
			while(cnt--)
			{
				int val;
				read(val);
				g[now].push_back(val);
			}
			sort(g[now].begin(),g[now].end());
		}
		for(int now=0; now<n; ++now)
		{
			memset(dp,0x3f,sizeof(dp));
			dp[0]=0;
//			for(auto v:g[now])
//				printf(" %d",v);
//			putchar('\n');
			for(int i=0; ; ++i)
			{
				if(dp[i]>m)
				{
					answer[now]=i-1;
					break;
				}
				if(dp[i]<m)
					for(auto v:g[now])
						dp[i+v]=min(dp[i+v],dp[i]+1);
			}
//			for(int i=0; i<=answer[now]; ++i)
//				printf("dp[%d]=%d\n",i,dp[i]);
//			putchar('\n');
		}
		int where=0;
		for(int now=1; now<n; ++now)
		{
			if(answer[where]==answer[now]?(g[where].size()==g[now].size()?g[where]>g[now]:g[where].size()>g[now].size()):answer[where]<answer[now])
					where=now;
		}
		printf("max coverage = %3d :",answer[where]);
		for(auto v:g[where])
			printf("%3d",v);
		putchar('\n');
		for(int now=0; now<n; ++now)
			g[now].clear();
	}
	return 0;
}


