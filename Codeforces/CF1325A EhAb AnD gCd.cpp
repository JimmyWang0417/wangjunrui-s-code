#include <cstdio>
#define ll long long
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
#define int ll
inline void work()
{
	int x;
	read(x);
	printf("%d %lld\n",1,x-1);
}
signed main()
{
	int T;
	read(T);
	while(T--)
		work();
	return 0;
}
