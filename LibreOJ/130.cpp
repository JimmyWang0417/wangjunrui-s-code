#include<cstdio>
#define re register
using namespace std;
const int N=1e6+5;
int n,q;
long long c[N];
inline int lowbit(int n)
{
	return n&(-n);
}
inline void update(int x,long long y)
{
	for(; x<=n; x+=lowbit(x))
		c[x]+=y;
}
inline long long sum(int x)
{
	long long ans=0;
	for(; x; x-=lowbit(x))
		ans+=c[x];
	return ans;
}
int main()
{
	scanf("%d%d",&n,&q);
	for(re int i=1,a; i<=n; i++)
	{
		scanf("%lld",&a);
		update(i,a);
	}
	for(re int i=1; i<=q; i++)
	{
		int x;
		long long y,z;
		scanf("%d%lld%lld",&x,&y,&z);
		if(x==1)
			update(y,z);
		else
			printf("%lld\n",sum(z)-sum(y-1));
	}
	return 0;
}
