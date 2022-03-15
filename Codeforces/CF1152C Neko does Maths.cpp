#include <cstdio>
#include <algorithm>
#define re register
#define ll long long
#define int ll
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
template<typename T,typename ...T1>
inline void read(T&x,T1&...x1)
{
	read(x);
	read(x1...);
}
int a,b;
int ans,pos;
inline void solve(int gcd)
{
	int now=b/gcd;
	if(gcd*now<b)
		++now;
	now*=gcd;
	int sum=(now*(now+(a-b)))/gcd;
	if(sum<ans||(sum==ans&&now-b<pos))
	{
		ans=sum;
		pos=now-b;
	}
}
inline void work(int val)
{
	for(re int i=1; i*i<=val; ++i)
		if(val%i==0)
		{
			solve(i);
			solve(val/i);
		}
}
signed main()
{
	read(a,b);
	if(a>b)
		swap(a,b);
	ans=a*b;
	pos=0;
	work(b-a);
	printf("%lld\n",pos);
	return 0;
}

