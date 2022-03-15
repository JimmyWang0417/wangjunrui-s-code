
// Problem : P5858 ¡¸SWTR-03¡¹Golden Sword
// Contest : Luogu
// URL : https://www.luogu.com.cn/problem/P5858
// Memory Limit : 256 MB
// Time Limit : 500000 ms
// Powered by CP Editor (https://github.com/cpeditor/cpeditor)

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
inline void clear(T*a,int l,int r,int val)
{
	memset(&a[l],val,sizeof(T)*(r-l+1));
}
const int N=5505;
int n,w,s,a[N];
ll dp[N][N];
int q[N];
using std::max;
signed main()
{
	memset(dp,~1,sizeof(dp));
	read(n,w,s);
	for(re int i=1; i<=n; ++i)
		read(a[i]);
	dp[0][0]=0;
	for(re int i=1; i<=n; ++i)
	{
		int head=1,tail=1;
		q[1]=w;
		for(re int j=w; j>=1; --j)
		{
			while(head<=tail&&q[head]>j+s-1)
				++head;
			while(head<=tail&&dp[i-1][q[tail]]<=dp[i-1][j-1])
				--tail;
			q[++tail]=j-1;
			dp[i][j]=dp[i-1][q[head]]+(ll)a[i]*j;
		}
	}
	ll ans=dp[0][1];
	for(re int i=1; i<=w; ++i)
		ans=max(ans,dp[n][i]);
	printf("%lld\n",ans);
	return 0;
}


