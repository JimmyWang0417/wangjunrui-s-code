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
using namespace std;
ll getblack(int x1,int y1,int x2,int y2)
{
	bool opt=(x1+y1)&1;
	int n=x2-x1+1,m=y2-y1+1;
	if(opt) return 1LL*n*(m/2)+((m&1)?(n/2)+(n&1):0);
	else return 1LL*n*(m/2)+((m&1)?(n/2):0);
}
ll getwhite(int x1,int y1,int x2,int y2)
{
	return 1LL*(x2-x1+1)*(y2-y1+1)-getblack(x1,y1,x2,y2);
}
int main()
{
	int T;
	for(read(T); T--;)
	{
		int n,m,x1,y1,x2,y2,x3,y3,x4,y4;
		read(n,m);
		swap(n,m);
		long long s1=getwhite(1,1,n,m);
		read(x1,y1,x2,y2,x3,y3,x4,y4);
		int u=max(x1,x3),d=min(x2,x4);
		int l=max(y1,y3),r=min(y2,y4);
		if(u<=d&&l<=r)
			s1+=getblack(x1,y1,x2,y2)-getblack(u,l,d,r)-getwhite(x3,y3,x4,y4);
		else
			s1+=getblack(x1,y1,x2,y2)-getwhite(x3,y3,x4,y4);
		printf("%lld %lld\n",s1,(ll)n*m-s1);
	}
	return 0;
}
