#include<cstdio>
#include<algorithm>
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
#define int long long
int a[100003],sum;
signed main()
{
	int T,n,m;
	read(T);
	while(T--)
	{
		sum=0;
		read(n),read(m);
		for(re int i=1; i<=n; ++i)
		{
			read(a[i]);
			sum+=a[i];
		}
		printf("%lld\n",min(sum,m));
	}
	return 0;
}
