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
const int N=10005;
int n,m,k;
int a[N];
int sg[N];
bitset<N>exist;
inline void solve()
{
	read(n);
	int ans=0;
	for(int i=1; i<=n; ++i)
	{
		int x;
		read(x);
		ans^=sg[x];
	}
	putchar(ans?'W':'L');
}
inline void work()
{
	for(int i=1; i<=k; ++i)
		read(a[i]);
	read(m);
	for(int i=1; i<=10000; ++i)
	{
		exist.set();
		for(int j=1; j<=k; ++j)
			if(i>=a[j])
				exist[sg[i-a[j]]]=false;
		sg[i]=(int)exist._Find_first();
	}
	while(m--)
		solve();
	putchar('\n');
}
signed main()
{
	while(read(k),k)
		work();
	return 0;
}


