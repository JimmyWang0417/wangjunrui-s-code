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
const int N=3e5+5;
int dp[N];
int q[N];
int sumt[N],sumc[N];
signed main()
{
	int n,s;
	read(n,s);
	for(int i=1; i<=n; ++i)
	{
		int t,c;
		read(t,c);
		sumt[i]=sumt[i-1]+t;
		sumc[i]=sumc[i-1]+c;
	}
	int head=1,tail=1;
	q[1]=0;
	for(int i=1; i<=n; ++i)
	{
		while(head<tail&&dp[q[head+1]]-dp[q[head]]<=(s+sumt[i])*(sumc[q[head+1]]-sumc[q[head]]))
			++head;
		dp[i]=dp[q[head]]+sumt[i]*(sumc[i]-sumc[q[head]])+s*(sumc[n]-sumc[q[head]]);
		while(head<tail&&(dp[q[tail]]-dp[q[tail-1]])*(sumc[i]-sumc[q[tail]])>=(dp[i]-dp[q[tail]])*(sumc[q[tail]]-sumc[q[tail-1]]))
			--tail;
		q[++tail]=i;
	}
	printf("%d\n",dp[n]);
	return 0;
}
