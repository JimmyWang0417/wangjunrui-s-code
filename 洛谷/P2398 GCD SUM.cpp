#include <cstdio>
#define re register
#define ll long long
using namespace std;
template <typename T>
inline void read(T &x)
{
	x=0;
	char s=(char)getchar();
	bool flag=false;
	while(s<'0'||s>'9')
	{
		if(s=='-')
			flag=true;
		s=(char)getchar();
	}
	while(s>='0'&&s<='9')
	{
		x=(x<<1)+(x<<3)+(s^'0');
		s=(char)getchar();
	}
	if(flag)
		x=~x+1;
	return;
}

int n;
ll ans,f[100000+5];
int main()
{
	read(n);
	for(re int i=n; i>=1; --i)
	{
		f[i]=1ll*n/i*(n/i);
		for(re int j=(i<<1); j<=n; j+=i)
			f[i]-=f[j];
		ans+=i*f[i];
//		printf("%d ",f[i]);
	}
	printf("%lld\n",ans);
	return 0;
}
