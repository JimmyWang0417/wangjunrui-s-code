#include <bits/stdc++.h>
#define lowbit(x) ((x)&(-(x)))
#define re register
#define ll long long
#define ull unsigned long long
#define rep(i,a,b) for(re int i=a;i<=b;++i)
#define per(i,a,b) for(re int i=a;i>=b;--i)
template<typename T>
inline void read(T&x)
{
	x=0;
	char s=(char)getchar();
	bool f=false;
	while(!(s>='0'&&s<='9'))
	{
		if(s=='-')
			f=true;
		s=(char)getchar();
	}
	while(s>='0'&&s<='9')
	{
		x=(x<<1)+(x<<3)+s-'0';
		s=(char)getchar();
	}
	if(f)
		x=(~x)+1;
}
template<typename T,typename ...T1>
inline void read(T&x,T1&...x1)
{
	read(x);
	read(x1...);
}
template<typename T>
inline void clear(T*array,int l,int r,int val)
{
	memset(&array[l],val,sizeof(T)*(r-l+1));
}
using namespace std;
int m,n;
signed main()
{
	read(m,n);
	if(n==1)
		printf("-1\n");
	else if((n==2&&m==3)||(n==3&&m==5))
		printf("11\n");
	else
	{
		bool flag=false;
		int ans=0;
		for(;;)
		{
			if(n>=m*2)
			{
				printf("%d\n",ans+1);
				return 0;
			}
			if(n>m)
			{
				printf("%d\n",ans+3);
				return 0;
			}
			if(n==m)
			{
				printf("%d\n",ans+5);
				return 0;
			}
			if(!flag)
			{
				m-=n-2;
				ans=4;
				flag=true;
			}
			else
			{
				if(n==2||n==3)
				{
					printf("-1");
					return 0;
				}
				m-=n/2-1;
				ans+=2;
			}
		}
	}
	return 0;
}


