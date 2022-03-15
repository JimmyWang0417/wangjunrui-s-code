#include <cstdio>
#include <algorithm>
#define int ll
#define re register
#define ll long long
#define ull unsigned long long
#define rep(i,a,b) for(re int i=a;i<=b;++i)
#define per(i,a,b) for(re int i=a;i>=b;--i)
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
inline int gcd(int a,int b)
{
	if(b==0)
		return a;
	else
		return gcd(b,a%b);
}
inline void work()
{
	int p1,p2,k;
	read(p1),read(p2),read(k);
	if(k==1)
	{
		printf("No\n");
		return;
	}
	int g=gcd(p1,p2);
	p1/=g,p2/=g;
	if(p1>p2)
		swap(p1,p2);
	if((k-1)*p1+1<p2)
		printf("No\n");
	else
		printf("Yes\n");
}
signed main()
{
	
	int T;
	read(T);
	while(T--)
		work();
	return 0;
}
