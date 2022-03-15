#include<cstdio>
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
inline void Exgcd(long long a,long long b,long long&d,long long&x,long long&y)
{
	if(b==0)
	{
		d=a;
		x=1;
		y=0;
	}
	else
	{
		Exgcd(b,a%b,d,x,y);
		int t=x;
		x=y;
		y=t-a/b*y;
	}
	return;
}
const int N=11;
int n,a[N],b[N];
long long m=1,ans;
int main()
{
	read(n);
	for(re int i=1; i<=n; i++)
	{
		read(a[i]);
		m*=a[i];
		read(b[i]);
	}
	long long mi,x,y,d;
	for(re int i=1; i<=n; i++)
	{
		mi=m/a[i];
		Exgcd(mi,a[i],d,x,y);
		ans=(ans+x*mi*b[i])%m;
	}
	printf("%lld\n",(ans+m)%m);
	return 0;
}

