#include<cstdio>
#define re register
using namespace std;
inline int read()
{
	char s=getchar();
	bool f=false;
	int x=0;
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
	return f?-x:x;
}
inline int abs(int x)
{
	return x>0?x:~x+1;
}
long long power[13],f[12][10];
inline void pre_work()
{
	power[0]=1;
	for(re int i=1; i<=12; i++)
		power[i]=power[i-1]*10;
	for(re int i=0; i<=9; i++)
		f[1][i]=1;
	for(re int i=2; i<=11; i++)
		for(re int j=0; j<=9; j++)
			for(re int k=0; k<=9; k++)
				if(abs(j-k)>=2)
					f[i][j]+=f[i-1][k];
}
inline long long count(int x)
{
	int w=0,y,pre;
	long long ans=0;
	while(power[w]<=x)w++;
	for(re int i=1; i<w; i++)
		for(re int j=1; j<=9; j++)
			ans+=f[i][j];
	y=x/power[w-1];
	for(re int j=1; j<y; j++)
		ans+=f[w][j];
	pre=y;
	x%=power[w-1];
	for(re int i=w-1; i>=1; i--)
	{
		y=x/power[i-1];
		for(re int j=0; j<y; j++)
			if(abs(j-pre)>=2)
				ans+=f[i][j];
		if(abs(pre-y)<2)break;
		pre=y;
		x%=power[i-1];
	}
	return ans;
}
int main()
{
	int a=read(),b=read();
	pre_work();
	printf("%d\n",count(b+1)-count(a)); 
}

