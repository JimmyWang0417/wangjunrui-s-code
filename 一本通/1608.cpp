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
ll dp[N];
int q[N];
ll sumt[N],sumc[N];
int top=1;
inline int find(ll x)
{
	int l=1,r=top;
	while(l<r)
	{
		int mid=(l+r)>>1;
		if(dp[q[mid+1]]-dp[q[mid]]<=x*(sumc[q[mid+1]]-sumc[q[mid]]))
			l=mid+1;
		else
			r=mid;
	}
	return q[l];
}
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
	q[1]=0;
	for(int i=1; i<=n; ++i)
	{
		int pos=find(s+sumt[i]);
		dp[i]=dp[pos]+sumt[i]*(sumc[i]-sumc[pos])+s*(sumc[n]-sumc[pos]);
		while(top>1&&(dp[q[top]]-dp[q[top-1]])*(sumc[i]-sumc[q[top]])>=(dp[i]-dp[q[top]])*(sumc[q[top]]-sumc[q[top-1]]))
			--top;
		q[++top]=i;
	}
	printf("%lld\n",dp[n]);
	return 0;
}
