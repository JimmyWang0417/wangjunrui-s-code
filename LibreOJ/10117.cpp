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
const int N=1e5+5;
int n,m;
long long c[N];
inline int lowbit(int x)
{
	return x&(-x);
}
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
	for(re int i=1,a,b,c;i<=m;i++)
	{
		a=read();
		if(a&1)
		{
			b=read();
			c=read();
			update(b,1);
			update(c+1,-1);
		}
		else
		{
			b=read();
			printf("%d\n",sum(b)&1);
		}
	}
}

