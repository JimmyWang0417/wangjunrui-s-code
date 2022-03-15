#include<cstdio>
#include<cmath>
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
inline int gcd(int a,int b)
{
	return b==0?a:gcd(b,a%b);
}
int main()
{
	re int i,x,a0,a1,b0,b1,t,k,ans;
	read(t);
	while(t--)
	{
		ans=0;
		read(a0);
		read(a1);
		read(b0);
		read(b1);
		if(b1%b0!=0)
		{
			printf("0\n");
			continue;
		}
		k=sqrt(b0);
		if(k*k==b0)
		{
			int x=b1/k;
			if(gcd(x,b0)==k&&gcd(x,a0)==a1)
				ans=-1;
		}
		for(i=1; i<=k; i++)
			if(b0%i==0)
			{
				x=b1/b0*i;
				if(gcd(x,b0)==i&&gcd(x,a0)==a1)
					ans++;
				x=b1/i;
				if(gcd(x,b0)==b0/i&&gcd(x,a0)==a1)
					ans++;
			}
		printf("%d\n",ans);
	}
	return 0;
}
