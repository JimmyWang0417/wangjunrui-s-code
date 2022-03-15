#include <cstdio>
#include <algorithm>
#define ll long long
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
#define int ll
const int N=1e5+5;
int n,a[N],p[N];
bool vis[N];
inline void work()
{
	int ans=0;
	read(n);
	for(re int i=1; i<=n; ++i)
	{
		read(a[i]);
		p[i]=a[i];
	}
	sort(p+1,p+1+n);
	for(re int i=1; i<=n; ++i)
	{
		int x=lower_bound(p+1,p+1+n,a[i])-p;
		if(!vis[x])
		{
			++ans;
			vis[x]=true;
		}
	}
	for(re int i=1; i<=n; ++i)
	{
		int x=lower_bound(p+1,p+1+n,a[i])-p;
		vis[x]=false;
	}
	printf("%lld\n",ans);
}
signed main()
{
	int T;
	read(T);
	while(T--)
		work();
	return 0;
}
