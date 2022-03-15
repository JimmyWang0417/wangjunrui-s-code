#include<cstdio>
#include<cmath>
#include<cstring>
#include<iostream>
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
const int N=50010;
long long n,k,m[N];
long long a[N],ans,l,r,mid,now,nn;
inline bool check(long long p)
{
	now=k;
	nn=n;
	for(re int i=0; i<=n; i++)
		a[i]=m[i];
	while(now)
	{
		if(nn==0)
			return true;
		now--;
		for(re int i=nn; i>=1; i--)
		{
			int x=p-(nn-i)*(nn-i);
			if(x<=0)
				break;
			a[i]-=x;
		}
		while(nn>=0&&a[nn]<0)
			nn--;
	}
	if(nn==0)
		return true;
	return false;
}
int main()
{
	read(n);
	read(k);
	for(re int i=1; i<=n; i++)
		read(m[i]);
	l=0;
	r=1e9;
	while(l<=r)
	{
		mid=l+r>>1;
		if(check(mid))
		{
			ans=mid;
			r=mid-1;
		}
		else
			l=mid+1;
	}
	printf("%lld\n",ans);
	return 0;
}
