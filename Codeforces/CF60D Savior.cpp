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
const int N=1e7+5;
inline int gcd(int n,int m)
{
	return m==0?n:gcd(m,n%m);
}
int n;
int fa[N];
inline int find(int x)
{
	return fa[x]==x?x:fa[x]=find(fa[x]);
}
int ans=0;
inline void unionn(int x,int y)
{
	if(!fa[x]||!fa[y])
		return;
//	printf("%d %d\n",x,y);
	if(find(x)==find(y))
		return;
	fa[find(x)]=find(y);
	--ans;
}
signed main()
{
	read(n);
	ans=n;
	int maxx=0;
	for(int i=1; i<=n; ++i)
	{
		int x;
		read(x);
		fa[x]=x;
		maxx=max(maxx,x);
	}
	for(int x=1; 2*x*x<=maxx; ++x)
		for(int y=x+1; 2*x*y<=maxx&&y*y-x*x<=maxx; ++y)
		{
			int a=y*y-x*x,b=2*x*y,c=x*x+y*y;
			if(gcd(a,b)==1)
			{
				unionn(a,b);
				if(c<=maxx)
				{
					unionn(a,c);
					unionn(b,c);
				}
//printf("Yes %d %d %d\n",a,b,c);
			}
		}
	printf("%d\n",ans);
	return 0;
}


