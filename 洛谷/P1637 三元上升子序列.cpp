#include <cstdio>
#include <cstring>
#include <algorithm>
#define ll long long
#define re register
#define lowbit(x) (x&(-x))
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
using namespace std;
const int N=3e4+5;
int n,c[N],tot;
ll a[N],p[N],ans;
int pre[N];
inline void add(int x,int y)
{
	for(; x<=tot; x+=lowbit(x))
		c[x]+=y;
}
inline int query(int x)
{
	int res=0;
	for(; x; x-=lowbit(x))
		res+=c[x];
	return res;
}
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
	for(re int i=1; i<=n; ++i)
	{
		int x=lower_bound(p+1,p+1+tot,a[i])-p;
		pre[i]=query(x-1);
		add(x,1);
	}
	memset(c,0,sizeof(c));
	for(re int i=n; i>=1; --i)
	{
		int x=lower_bound(p+1,p+1+tot,a[i])-p;
		ans+=pre[i]*(query(tot)-query(x));
		add(x,1);
	}
	printf("%lld\n",ans);
	return 0;
}
