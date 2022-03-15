#include<cstdio>
#include<algorithm>
#define re register
#define ll long long
#define lowbit(x) (x&(-x))
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
const int N=5e5+5;
int c[N],tot,n;
inline void update(const int &x)
{
	for(re int i=x; i<=tot; i+=lowbit(i))
		++c[i];
}
inline int sum(const int &x)
{
	int res=0ll;
	for(re int i=x; i; i-=lowbit(i))
		res+=c[i];
	return res;
}
int a[N],p[N];
int main()
{
	read(n);
	for(re int i=1; i<=n; ++i)
	{
		read(a[i]);
		p[i]=a[i];
	}
	sort(p+1,p+1+n);
	tot=unique(p+1,p+1+n)-p-1;
	ll ans=0ll;
	for(re int i=n; i>=1; --i)
	{
		int x=lower_bound(p+1,p+1+tot,a[i])-p;
		ans+=sum(x-1);
		update(x);
	}
	printf("%lld\n",ans);
	return 0;
}
