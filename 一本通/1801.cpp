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
	return;
}
int ans,n;
int main()
{
	read(n);
	for(re int i=1; i<=n; i++)
		for(re int j=i<<1; j<=n; j+=i)
			ans+=(i^j)==j-i;
	printf("%d\n",ans);
	return 0;
}
