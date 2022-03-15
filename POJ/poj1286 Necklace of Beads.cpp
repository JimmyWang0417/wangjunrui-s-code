#include <cstdio>
#define int long long
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
template<typename T>
inline void clear(T*a,int l,int r,int val)
{
	memset(&a[l],val,sizeof(T)*(r-l+1));
}
inline int getphi(int n)
{
	int ans=n;
	for(int i=2; i*i<=n; ++i)
	{
		if(n%i==0)
		{
			while(n%i==0)
				n/=i;
			ans-=ans/i;
		}
	}
	if(n>1)
		ans-=ans/n;
	return ans;
}
inline int quickpow(int a,int b)
{
	int res=1;
	while(b)
	{
		if(b&1)
			res=res*a;
		a=a*a;
		b>>=1;
	}
	return res;
}
signed main()
{
	int n;
	while(read(n),~n)
	{
		if(n==0)
		{
			printf("0\n");
			continue;
		}
		int ans=0;
		int i=1;
		for(; i*i<n; ++i)
			if(n%i==0)
				ans+=quickpow(3,i)*getphi(n/i)+quickpow(3,n/i)*getphi(i);
		if(i*i==n)
			ans+=quickpow(3,i)*getphi(i);
//		printf("%lld\n",ans);
		if(n&1)
			ans+=n*quickpow(3,(n+1)/2);
		else
			ans+=(n/2)*(quickpow(3,n/2)+quickpow(3,n/2+1));
//		printf("nmsl\n");
		printf("%lld\n",ans/2/n);
	}
	return 0;
}


