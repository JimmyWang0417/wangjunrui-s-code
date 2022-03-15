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
inline void clear(T*a,int l,int r,int val)
{
	memset(&a[l],val,sizeof(T)*(r-l+1));
}
const int mod=10086;
int d[35],cnt=1;
inline void add(int &x,int y)
{
	x+=y;
	if(x>=mod)
		x-=mod;
}
inline void insert(int x)
{
	for(re int i=31; i>=0; --i)
		if((x>>i)&1)
		{
			if(!d[i])
			{
				d[i]=x;
				return;
			}
			else
				x^=d[i];
		}
	add(cnt,cnt);
}
inline void work()
{
	for(re int i=1; i<=31; ++i)
		for(re int j=0; j<i; ++j)
			if((d[i]>>j)&1)
				d[i]^=1<<j;
}
int n;
signed main()
{
	read(n);
	for(re int i=1; i<=n; ++i)
	{
		int val;
		read(val);
		insert(val);
	}
	work();
	int x;
	read(x);
	int rk=0;
//	printf("%d\n",cnt);
	for(re int i=31; i>=0; --i)
		if(d[i])
		{
			add(rk,rk);
//		printf(" %d ",x>>i);
			if((x>>i)&1)
			{
				add(rk,1);
				x^=d[i];
			}
//		printf("%d %d %d\n",i,x,rk);
		}
	printf("%d\n",(rk*cnt+1)%mod);
	return 0;
}


