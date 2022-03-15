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
const int N=2005,M=6e5+5;
int n,cnt;
int a[M],b[M];
ll sum[M],dp[25][N],nmsl;
int q[N];
inline void work1()
{
	ll ans=0x7ffffffffffffffll;
	for(int now=0; now<n; ++now)
	{
		for(int i=1; i<=n; ++i)
			b[i]=a[now+i];
//		for(int i=1; i<=n; ++i)
//			printf("%d ",b[i]);
//		putchar('\n');
		for(int i=1; i<=n; ++i)
			sum[i]=sum[i-1]+b[i];
		memset(dp,0x3f,sizeof(dp));
		dp[0][0]=0;
		for(int k=1; k<=cnt; ++k)
		{
#define g(x) (dp[k-1][x]+sum[x]*sum[x])
			int head=1,tail=1;
			q[1]=0;
			for(int i=1; i<=n; ++i)
			{
				while(head<tail&&g(q[head+1])-g(q[head])<=2*sum[i]*(sum[q[head+1]]-sum[q[head]]))
					++head;
				dp[k][i]=dp[k-1][q[head]]+(sum[i]-sum[q[head]])*(sum[i]-sum[q[head]]);
				while(head<tail&&(g(q[tail])-g(q[tail-1]))*(sum[i]-sum[q[tail]])>=(g(i)-g(q[tail]))*(sum[q[tail]]-sum[q[tail-1]]))
					--tail;
				q[++tail]=i;
			}
		}
		ans=min(ans,dp[cnt][n]);
	}
//	printf("%lld\n",ans);
	printf("%lld\n",cnt*(cnt*ans-nmsl*nmsl));
}
inline void work2()
{
#define calc(i,j) ((sum[i]-sum[j])*(sum[i]-sum[j])+(sum[n]-sum[i]+sum[j])*(sum[n]-sum[i]+sum[j]))
	for(int i=1; i<=n*2; ++i)
		sum[i]=sum[i-1]+a[i];
	ll ans=0x7ffffffffffffffll;
	for(int i=1,j=0; i<=n; ++i)
	{
		while((sum[i]-sum[j])*2>=nmsl)
			++j;
		ans=min(ans,calc(i,j));
		if(j)
			ans=min(ans,calc(i,j-1));
	}
	printf("%lld\n",cnt*(cnt*ans-nmsl*nmsl));
#undef calc
}
inline void work3()
{
	for(int i=1; i<=n*2; ++i)
		sum[i]=sum[i-1]+a[i];

	ll ans=0x7ffffffffffffffll;
	for(int j=0,i=1,k=2; i<=n; ++i)
	{
		while((sum[i]-sum[j])*cnt>=nmsl)
			++j;
		while((sum[k]-sum[i])*cnt<=nmsl)
			++k;
#define calc(i,j,k) ((sum[j]-sum[i])*(sum[j]-sum[i])+(sum[k]-sum[j])*(sum[k]-sum[j])+(sum[n]-sum[k]+sum[i])*(sum[n]-sum[k]+sum[i]))
		for(int l=max(j-1,0); l<=min(j+1,i); ++l)
			for(int r=max(k-1,i); r<=min(k+1,n); ++r)
				ans=min(ans,calc(l,i,r));
	}
	printf("%lld\n",cnt*(cnt*ans-nmsl*nmsl));
#undef calc
}
signed main()
{
	freopen("spaceship.in","r",stdin),freopen("spaceship.out","w",stdout);
	read(n,cnt);
	for(int i=1; i<=n; ++i)
	{
		read(a[i]);
		nmsl+=a[i];
	}
	for(int i=1; i<=n; ++i)
		a[i+n]=a[i];
	if(cnt==2)
		work2();
	else if(cnt==3)
		work3();
	else
		work1();
	return 0;
}


