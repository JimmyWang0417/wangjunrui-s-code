#include<cstdio>
#define re register
#define lowbit(x) (x&(-x))
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
long long c[1000010];
int n,m,pre,a,b,cc;
inline void update(int x,int y)
{
	for(; x<=n; x+=lowbit(x))
		c[x]+=y;
}
inline long long sum(int x)
{
	long long  ans=0;
	for(; x; x-=lowbit(x))
		ans+=c[x];
	return ans;
}
int main()
{
	n=read();
	m=read();
	for(re int i=1; i<=n; i++)
	{
		a=read();
		update(i,a-pre);
		pre=a;
	}
	for(re int i=1; i<=m; i++)
	{
		a=read();
		if(a&1)
		{
			a=read();
			b=read();
			cc=read();
			update(a,cc);
			update(b+1,-cc);
		}
		else
		{
			b=read();
			printf("%lld\n",sum(b));
		}
	}
	return 0;
}

