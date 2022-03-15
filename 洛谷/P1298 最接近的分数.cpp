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
const double eps=1e-15;
int m,n;
double x;
inline int check(double x)
{
	return (x>eps)-(x<-eps);
}
int main()
{
	scanf("%d%d",&m,&n);
	scanf("%lf",&x);
	re int leftm=0,leftn=1,rightn=1,rightm=0;
	for(re int mm=1,nn=1; mm<=m&&nn<=n; mm=leftm+rightn,nn=leftn+rightm)
	{
		switch(check(x*nn-mm))
		{
			case 0:
			{
				printf("%d/%d\n",mm,nn);
				return 0;
			}
			case 1:
				leftm=mm,leftn=nn;
				break;
			case -1:
				rightn=mm,rightm=nn;
				break;
		}
	}
	if(rightm==0)
	{
		printf("%d/%d\n",leftm,leftn);
		return 0;
	}
	switch(check((x-1.*leftm/leftn)-(1.*rightn/rightm-x)))
	{
		case 1:
			printf("%d/%d\n",rightn,rightm);
			break;
		case 0:
			puts("TOO MANY");
			break;
		case -1:
			printf("%d/%d\n",leftm,leftn);
	}
	return 0;
}

