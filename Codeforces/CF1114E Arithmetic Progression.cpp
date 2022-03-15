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
const int N=1e6+5;
int cnt=0;
int n;
int tot,a[N];
bool vis[N];
signed main()
{
	read(n);
	int l=0,r=1e9;
	while(l<r)
	{
		int mid=(l+r)>>1;
		printf("> %d\n",mid);
		fflush(stdout);
		int x;
		read(x);
		if(x)
			l=mid+1;
		else
			r=mid;
		++cnt;
	}
	mt19937 rnd((unsigned int)time(0));
	for(int i=1; i<=min(n,60-cnt); ++i)
	{
		int x=rnd()%n+1;
		while(vis[x])
			x=rnd()%n+1;
		vis[x]=true;
		printf("? %d\n",x);
		fflush(stdout);
		read(x);
		a[++tot]=x;
	}
	int d=0;
	for(int i=1; i<=tot; ++i)
		if(a[i]!=-1)
		{
			d=__gcd(d,l-a[i]);
			for(int j=i+1; j<=tot; ++j)
				if(a[j]!=-1)
					d=__gcd(d,abs(a[j]-a[i]));
		}
	printf("! %d %d\n",l-d*(n-1),d);
	fflush(stdout);
	return 0;
}


