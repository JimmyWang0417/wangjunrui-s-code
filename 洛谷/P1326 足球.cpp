#include<cstdio>
#define min(x,y) ((x)<(y)?(x):(y))
int main()
{
	long long s,t,n;
	while(scanf("%lld%lld%lld",&s,&t,&n)!=EOF)
	{
		long long maxx,minn;
		if(s<n)
		{
			maxx=3*s;
			maxx+=n-s-1;
			if(t==0)
				++maxx;
		}
		else
		{
			maxx=3*(n-1);
			if(s-(n-1)>t)
				maxx+=3;
			else if(s-(n-1)==t)
				++maxx;
		}
		if(s>t)
		{
			minn=3;
			if(t<n-1)
				minn+=n-1-t;
		}
		else
		{
			long long a=3,b=0;
			if(t<n-1)
				a+=n-1-t;
			if(n>t-s)
				b=n-(t-s);
			minn=min(a,b);
		}
		printf("%lld %lld\n",maxx,minn);
	}
	return 0;
}
