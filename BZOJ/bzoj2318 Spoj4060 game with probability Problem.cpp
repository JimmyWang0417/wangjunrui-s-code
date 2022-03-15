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
const int N=1e6;
double dp[2][2],*f0=dp[0],*f1=dp[1];
inline void work()
{
	int n;
	double p,q;
	scanf("%d%lf%lf",&n,&p,&q);
	f0[0]=0,f0[1]=1;
	for(int i=1; i<=1000&&i<=n; ++i)
	{
		if(f0[0]>f0[1])
		{
			f1[0]=(f0[1]*(1-p)+f0[0]*p*(1-q))/(1-p*q);
			f1[1]=(f0[0]*(1-q)+f0[1]*q*(1-p))/(1-p*q);
		}
		else
		{
			f1[0]=(f0[1]*p+f0[0]*(1-p)*q)/(1-(1-p)*(1-q));
			f1[1]=(f0[0]*q+f0[1]*(1-q)*p)/(1-(1-p)*(1-q));
		}
		swap(f0,f1);
	}
	printf("%lf\n",f0[0]);
}
signed main()
{
	int T;
	read(T);
	while(T--)
		work();
	return 0;
}

