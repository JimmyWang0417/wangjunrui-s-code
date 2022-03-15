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
const int maxn=2e6+5;
int n,k,p,color,price,head[maxn],sum[maxn],cnt[maxn],now;long long answer;
int main()
{
	n=read();
	k=read();
	p=read();
	for(re int i=1; i<=n; i++)
	{
		color=read();
		price=read();
		if(price<=p)
			now=i;
		if(now>=head[color])
			sum[color]=cnt[color];
		answer+=sum[color];
		head[color]=i;
		cnt[color]++;
	}
	printf("%lld\n",answer);
	return 0;
}

