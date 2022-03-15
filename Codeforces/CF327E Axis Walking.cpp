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
const int mod=1e9+7;
inline void add(int &x,int y)
{
	x+=y;
	if(x>=mod)
		x-=mod;
}
int n,a[(1<<24)+5],m,b[5];
int dp[(1<<24)+5];
inline bool check(int S)
{
	int res=0;
	while(S)
	{
		res+=a[lowbit(S)];
		S-=lowbit(S);
	}
	for(int i=0; i<m; ++i)
		if(b[i]==res)
			return true;
	return false;
}
signed main()
{
	read(n);
	for(int i=1; i<(1<<n); i<<=1)
		read(a[i]);
	read(m);
	for(int i=0; i<m; ++i)
		read(b[i]);
	dp[0]=1;
	for(int S=1; S<(1<<n); ++S)
	{
		if(check(S))
			continue;
		for(int i=S; i; i-=lowbit(i))
			add(dp[S],dp[S^lowbit(i)]);
	}
	printf("%d\n",dp[(1<<n)-1]);
	return 0;
}


