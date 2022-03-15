#include<cstdio>
#define re register
#define ll long long
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
ll a,b,c,l,x,y,d,t;
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
		t=x;
		x=y;
		y=t-a/b*x;
	}
	return;
}
int k;
int main()
{
	while(read(a),read(b),read(c),read(k),
	        a!=0||b!=0||c!=0||k!=0)
	{
		l=1ll<<(long long)k;
		//printf(" %d ",l);
		Exgcd(c,l,d,x,y);
		if((b-a)%d!=0)
		{
			printf("FOREVER\n");
			continue;
		}
		printf("%lld\n",(x*(b-a)/d%(l/d)+(l/d))%(l/d));
	}
	return 0;
}
