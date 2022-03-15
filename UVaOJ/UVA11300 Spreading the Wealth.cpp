#include<cstdio>
#include<algorithm>
#define re register
#define ll long long
using namespace std;
int n;
ll tot,c[(int)1e6+10],M,ans;
template<typename T>
inline void read(T&x)
{
	x=0;
	char s=getchar();
	bool f=false;
	while(!(s>='0'&&s<='9'))
	{
		if(s=='-')
			f=true;
		s=getchar();
	}
	while(s>='0'&&s<='9')
	{
		x=(x<<1)+(x<<3)+s-'0';
		s=getchar();
	}
	if(f)
		x=(~x)+1;
}
int main()
{
	while(scanf("%d",&n)!=EOF)
	{
		ans=tot=0ll;
		c[0]=0ll;
		re ll x;
		for(re int i=1; i<=n; ++i)
		{
			read(x);
			tot+=x;
			c[i]=c[i-1]+x;
		}
		M=tot/n;
		for(re int i=1; i<n; ++i)
			c[i]-=M*i;
		nth_element(c+1,c+(n>>1),c+n);
		ll x1=c[n>>1];
		for(re int i=0; i<n; ++i)
			ans+=abs(x1-c[i]);
		printf("%lld\n",ans);
	}
	return 0;
}
