#include <cstdio>
#include <algorithm>
#define ll long long
#define re register
#define int ll
using std::sort;
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
const int N=105,M=2005;
int T,n,a[N],b[N];
inline void work()
{
	read(n);
	for(re int i=1; i<=n; ++i)
		read(a[i]);
	for(re int i=1; i<=n; ++i)
		read(b[i]);
	sort(a+1,a+1+n);
	sort(b+1,b+1+n);
	for(re int i=1; i<=n; ++i)
		printf("%lld ",a[i]);
	putchar('\n');
	for(re int i=1; i<=n; ++i)
		printf("%lld ",b[i]);
	putchar('\n');
}
signed main()
{
	read(T);
	while(T--)
		work();
	return 0;
}
