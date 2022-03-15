#include <cstdio>
#include <algorithm>
#define re register
using namespace std;
template<typename T>
inline void read(T&x)
{
	x=0;
	char s=(char)getchar();
	bool flag=false;
	while(!(s>='0'&&s<='9'))
	{
		if(s=='-')
			flag=true;
		s=(char)getchar();
	}
	while(s>='0'&&s<='9')
	{
		x=(x<<1)+(x<<3)+s-'0';
		s=(char)getchar();
	}
	if(flag)
		x=(~x)+1;
}
const int N=2e5+5;
int a[N],f[N],g[N],n;
inline int query()
{
	for(re int i=1; i<=n; ++i)
		f[i]=max(f[i-1],0)+a[i];
	for(re int i=n; i>=1; --i)
		g[i]=max(g[i+1],0)+a[i];
	for(re int i=2; i<=n; ++i)
		f[i]=max(f[i],f[i-1]);
	for(re int i=n-1; i>=1; --i)
		g[i]=max(g[i],g[i+1]);
	int ans=~0x7fffffff;
	for(re int i=1; i<n; ++i)
		ans=max(ans,f[i]+g[i+1]);
	return ans;
}
int main()
{
	int tot=0,sum=0;
	read(n);
	for(re int i=1; i<=n; ++i)
	{
		read(a[i]);
		sum+=a[i];
		tot+=(a[i]>=0);
	}
	int ans1=query();
	if(tot<=1)
		printf("%d\n",ans1);
	else
	{
		for(re int i=1; i<=n; ++i)
			a[i]=-a[i];
		printf("%d\n",max(ans1,sum+query()));
	}
	return 0;
}
