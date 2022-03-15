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
const int N=2e7+5;
char a[N],b[N];
int n,m;
int z[N],p[N];
inline void expre()
{
	z[1]=m;
	for(int i=2,l=0,r=0; i<=m; ++i)
	{
		if(i<=r)
			z[i]=min(z[i-l+1],r-i+1);
		while(i+z[i]<=m&&b[i+z[i]]==b[z[i]+1])
			++z[i];
		if(i+z[i]-1>r)
		{
			l=i;
			r=i+z[i]-1;
		}
	}
}
inline void exkmp()
{
	for(int i=1,l=0,r=0; i<=n; ++i)
	{
		if(i<=r)
			p[i]=min(z[i-l+1],r-i+1);
		while(i+p[i]<=n&&a[i+p[i]]==b[p[i]+1])
			++p[i];
		if(i+p[i]-1>r)
		{
			l=i;
			r=i+p[i]-1;
		}
	}
}
signed main()
{
	scanf("%s%s",a+1,b+1);
	n=(int)strlen(a+1),m=(int)strlen(b+1);
	expre(),exkmp();

	ll ans=0;
	for(int i=1; i<=m; ++i)
		ans^=(ll)i*(z[i]+1);
	printf("%lld\n",ans);

	ans=0;
	for(int i=1; i<=n; ++i)
		ans^=(ll)i*(p[i]+1);
	printf("%lld\n",ans);
	return 0;
}


