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
const int N=1e6+5;
int n,a,b,c;
ll sum[N];
ll dp[N];
int q[N];
#define g(x) (dp[x]+a*sum[x]*sum[x]-b*sum[x])
inline double calc(int x,int y)
{
	return (double)(g(y)-g(x))/(double)(sum[y]-sum[x]);
}
signed main()
{
	read(n,a,b,c);
	for(int i=1; i<=n; ++i)
	{
		int x;
		read(x);
		sum[i]=sum[i-1]+x;
	}
	int head=1,tail=1;
	q[1]=0;
	for(int i=1; i<=n; ++i)
	{
		while(head<tail&&calc(q[head],q[head+1])>=2*a*sum[i])
			++head;
//		cout<<head<<' '<<tail<<' '<<q[head]<<endl;
		dp[i]=dp[q[head]]+a*(sum[i]-sum[q[head]])*(sum[i]-sum[q[head]])+b*(sum[i]-sum[q[head]])+c;
		while(head<tail&&calc(q[tail],q[tail-1])<=calc(i,q[tail]))
			--tail;
		q[++tail]=i;
	}
//	for(int i=1; i<=n; ++i)
//		cout<<dp[i]<<' ';
	cout<<dp[n];
	return 0;
}


