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
const int N=20;
int n,a[N];
inline void work()
{
	read(n);
	for(int i=0; i<n; ++i)
		read(a[i]);
	for(int S=(1<<n)-1; S>=1; --S)
	{
		int res=0;
		for(int i=0; i<n; ++i)
			if((S>>i)&1)
				res^=a[i];
		if(!res)
		{
			printf("NO\n");
			return;
		}
	}
	printf("YES\n");
}
signed main()
{
	for(int i=1; i<=10; ++i)
		work();
	return 0;
}


