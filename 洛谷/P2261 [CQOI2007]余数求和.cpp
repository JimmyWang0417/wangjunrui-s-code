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
signed main()
{
	int n,k;
	read(n,k);
	ll ans=(ll)n*k;
	for(re int l=1,r; l<=n&&l<=k; l=r+1)
	{
		r=std::min(k/(k/l),n);
		ans-=(ll)(r-l+1)*(l+r)/2*(k/l);
//		printf("%d %d %d\n",l,r,(r-l+1)*(l+r)/2);
	}
	printf("%lld\n",ans);
	return 0;
}


