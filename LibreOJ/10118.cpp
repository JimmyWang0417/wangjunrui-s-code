#include<cstdio>
#define re register
using namespace std;
#define lowbit(x) (x&(-x))
int n,m,a,b,c,d,k;
long long s[1<<13][1<<13];
inline void update(int x,int y,int z)
{
	int i=x;
	while(i<=n)
	{
		int j=y;
		while(j<=m)
		{
			s[i][j]+=z;
			j+=lowbit(j);
		}
		i+=lowbit(i);
	}
}
inline long long sum(int x,int y)
{
	int i=x,j;
	long long res=0;
	while(i)
	{
		j=y;
		while(j)
		{
			res+=s[i][j];
			j-=lowbit(j);
		}
		i-=lowbit(i);
	}
	return res;
}
int main()
{
	scanf("%d%d",&n,&m);
	while(scanf("%d",&k)==1)
	{
		if(k&1)
		{
			scanf("%d%d%d",&a,&b,&c);
			update(a,b,c);
		}
		else
		{
			scanf("%d%d%d%d",&a,&b,&c,&d);
			printf("%lld\n",sum(c,d)+sum(a-1,b-1)-sum(c,b-1)-sum(a-1,d));
		}
	}
	return 0;
}

