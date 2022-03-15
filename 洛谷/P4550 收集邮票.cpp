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
int n;
double f[1000010],dp[1000010];
int main()
{
	read(n);
	for(re int i=n-1; i>=0; i--)
	{
		f[i]=+(double)n/(n-i)+f[i+1];
		dp[i]=(double)i*(f[i]+1)/(n-i)+f[i+1]+dp[i+1];
	}
	printf("%.2lf\n",dp[0]);
	return 0;
}

