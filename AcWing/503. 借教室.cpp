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
int n,m,a[N];
int d[N],s[N],t[N];
int diff[N];
inline bool check(int x)
{
	memset(diff,0,sizeof(diff));
	for(int i=1; i<=x; ++i)
	{
		diff[s[i]]+=d[i];
		diff[t[i]+1]-=d[i];
	}
	for(int i=1; i<=n; ++i)
	{
		diff[i]+=diff[i-1];
		if(diff[i]>a[i])
			return false;
	}
	return true;
}
signed main()
{
	read(n,m);
	for(int i=1; i<=n; ++i)
		read(a[i]);
	for(int i=1; i<=m; ++i)
		read(d[i],s[i],t[i]);
	if(check(m))
	{
		printf("0\n");
		return 0;
	}
	int l=0,r=m;
	while(l<=r)
	{
		int mid=(l+r)>>1;
		if(check(mid))
			l=mid+1;
		else
			r=mid-1;
	}
	printf("-1\n%d\n",l);
	return 0;
}


