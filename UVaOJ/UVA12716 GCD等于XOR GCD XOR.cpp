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
const int N=30000000+5;
int ans[N];
signed main()
{
	for(re int i=1; i<=30000000; i++)
		for(re int j=2; j*i<=30000000; j++)
			if((i^(j*i))==(j*i)-i)ans[j*i]++;
	for(re int i=1; i<=30000000; i++)ans[i]+=ans[i-1];
	int kase=0;
	int T;
	read(T);
	while(T--)
	{
		int n;
		read(n);
		printf("Case %d: %d\n",++kase,ans[n]);
	}
	return 0;
}


