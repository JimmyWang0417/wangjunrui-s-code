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
const int N=50005;
int n;
pair<int,int>a[N];
signed main()
{
	read(n);
	for(int i=1; i<=n; ++i)
	{
		int w,s;
		read(w,s);
		a[i]=make_pair(w+s,w);
	}
	sort(a+1,a+1+n);
	int res=-1e9,sum=0;
	for(int i=1; i<=n; ++i)
	{
		int w=a[i].second,s=a[i].first-w;
		res=max(res,sum-s);
		sum+=w;
	}
	printf("%d\n",res);
	return 0;
}


