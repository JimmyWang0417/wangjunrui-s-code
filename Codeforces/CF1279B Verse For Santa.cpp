#include<cstdio>
#define re register
#define int long long
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
const int N=1e6+10;
int n,s,a[N],sum,wheremax,maxx,where;
signed main()
{
	int T;
	read(T);
	while(T--)
	{
		sum=maxx=0;
		read(n);
		read(s);
		for(re int i=1; i<=n; ++i)
		{
			read(a[i]);
			sum+=a[i];
		}
		if(sum<=s)
		{
			printf("%d\n",0);
			continue;
		}
		sum=0;
		for(re int i=1; i<=n; ++i)
		{
			sum+=a[i];
			if(sum>s)
			{
				maxx=i-1;
				break;
			}
		}
		int ans=0;
		for(re int k=1; k<=n; ++k)
		{
			int now=0,sumnow=0;
			for(re int i=1; i<=n; ++i)
				if(i!=k)
				{
					sumnow+=a[i];
					if(sumnow>s)
					{
						now=i-1;
						break;
					}
				}
			if(now>ans)
				ans=now,where=k;
		}
		if(ans<=maxx)
			printf("%d\n",0);
		else
			printf("%d\n",where);
	}
}
