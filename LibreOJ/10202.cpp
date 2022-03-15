#include<cstdio>
#include<cstring>
#define re register
using namespace std;
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
typedef int mainint;
#define int long long
const int N=1e6+5,mo=1e9+7;
long long prime[N],v[N],s,n,m;
long long c[N],ans=1ll;
inline void primes(int n,int&s) {
    for (re int i=2;i<=n;i++) {
        if (!v[i]) v[i]=i,prime[++s]=i;
        for (re int j=1;j<=s;j++) {
            if (prime[j]>v[i]||prime[j]>n/i) break;
            v[i*prime[j]]=prime[j];
        }
    }
}
mainint main()
{
	read(n);
	primes(n,m);
	for(re int i=1; i<=m; i++)
	{
		int P=prime[i];
		for(re int j=P; j<=n; j*=P)
			c[i]+=(n/j);
		c[i]%=mo;
	}
	for(re int i=1; i<=m; i++)
		ans=(ans*((c[i]<<1)|1))%mo;
	printf("%lld\n",ans);
	return 0;
}

