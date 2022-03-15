#include<cstdio>
#include<algorithm>
using namespace std;
inline int read()
{
	long long x=0;
	char s=getchar();
	while(s<'0'||s>'9')s=getchar();
	while(s>='0'&&s<='9')
	{
		x=(x<<1)+(x<<3)+s-'0';
		s=getchar();
	}
	return x;
}
int n,m,a[100001],l,r,ans;
inline bool check(const int &d)
{
	int cow=1,res=a[1]+d;
	for(register int i=2; i<=n; i++)
		if(a[i]>=res)
		{
			++cow;
			res=a[i]+d;
		}
	return cow>=m;
}
int main()
{
	n=read();
	m=read();
	for(register int i=1; i<=n; i++)
		a[i]=read();
	std::sort(a+1,a+1+n);
	l=1;
	r=a[n]-a[1];
	while(l<=r)
	{
		int mid=(l+r)>>1;
		if(check(mid))
		{
			ans=mid;
			l=mid+1;
		}
		else r=mid-1;
	}
	printf("%d\n",ans);
	return 0;
}
