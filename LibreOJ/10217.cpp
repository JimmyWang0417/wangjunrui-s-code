#include<cstdio>
#define re register
#define ll int
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
inline void Exgcd(ll a,ll b,ll&d,ll&x,ll&y)
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
const int n=3,a[4]= {0,23,28,33},M=21252;
int sum,b[4],Mi,gcd,x,y;
long long ans,d;
int main()
{
	for(re int i=1; i<=n; i++)
		read(b[i]);
	read(d);
	while((~b[1]||~b[2]||~b[3]||~d))
	{
		
		for(re int i=1; i<=n; i++)
		{
			Mi=M/a[i];
			Exgcd(Mi,a[i],gcd,x,y);
			//printf(" %d ",gcd);
			ans=((ans+Mi*x*b[i])%M+M)%M;
		}
		int k=(ans-d+M)%M;
		if(k==0)
			k=M;
		printf("Case %d: the next triple peak occurs in %d days.\n",++sum,k);
		for(re int i=1; i<=n; i++)
			read(b[i]);
		read(d);
		ans=0;
	}
	return 0;
}
