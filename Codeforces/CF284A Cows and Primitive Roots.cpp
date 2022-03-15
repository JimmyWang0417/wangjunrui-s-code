#include <cstdio>
#define int long long
#define re register
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
inline int euler(int x)
{
	int ans=x;
	for(re int i=2; i*i<=x; ++i)
		if(x%i==0)
		{
			do
				x/=i;
			while(x%i==0);
			ans=ans/i*(i-1);
		}
	if(x>1)
		ans=ans/x*(x-1);
	return ans;
}
signed main()
{
	int p;
	read(p);
	printf("%lld\n",euler(euler(p)));
	return 0;
}
