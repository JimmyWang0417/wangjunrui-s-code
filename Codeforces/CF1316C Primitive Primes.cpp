#include<cstdio>
#include<map>
#include<algorithm>
#define int long long
#define re register
using namespace std;
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
signed main()
{
	int n , m , p;
	scanf("%lld%lld%lld",&n,&m,&p);
	int ans = -1;
	for(re int i=1; i<=n; ++i)
	{
		int x ;
		read(x);
		if(ans == -1 && x % p)
			ans = i - 1;
	}
	int res = -1;
	for(re int i=1;i<=m;++i)
	{
		int x;
		read(x);
		if(res == -1 && x % p)
			res = i - 1;
	}
	printf("%lld\n",ans+res);
	return 0;
}
