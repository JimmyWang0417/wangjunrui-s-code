#include<cstdio>
#include<iostream>
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
	return;
}
int q[1000010];
ll sum[1000010],ans;
int main()
{
	re int n,tmp,tail;
	read(n);
	read(tmp);
	q[tail=1]=1;
	sum[1]=tmp;
	ans=tmp;
	for(re int i=2; i<=n; ++i)
	{
		read(tmp);
		sum[i]=sum[i-1]+tmp;
		ans=max(ans,sum[i]-sum[q[0]]);
		//printf("%d\n",sum[i]-sum[q[head]]);
		while(~tail&&sum[q[tail]]>=sum[i])
			--tail;
		q[++tail]=i;
		//putchar('\n');
	}
	printf("%lld\n",ans);
	return 0;
}
