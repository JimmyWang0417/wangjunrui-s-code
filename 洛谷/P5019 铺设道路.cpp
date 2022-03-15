#include<cstdio>
#include<algorithm>
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
int n;
ll sum;
int main()
{
	read(n);
	for(re int i=1,x,last=0; i<=n; i++)
	{
		read(x);
		sum+=max(x-last,0);
		last=x;
	}
	printf("%lld\n",sum);
	return 0;
}
