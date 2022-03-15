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
int n,a[N],b[N];
int nmsl=1;
int higher[N];
int cnt[N];
int st[N],top;
signed main()
{
	read(n);
	for(int i=1; i<=n; ++i)
	{
		read(a[i]);
		if(a[i]>a[nmsl])
			nmsl=i;
	}
	int tot=0;
	for(int i=nmsl+1; i<=n; ++i)
		b[++tot]=a[i];
	for(int i=1; i<nmsl; ++i)
		b[++tot]=a[i];
	n=tot;
	top=0;
	ll ans=0;
	for(int i=1; i<=n; ++i)
		printf("%d ",b[i]);
	putchar('\n');
	for(int i=1; i<=n; ++i)
	{
		while(top&&b[st[top]]<b[i])
			--top;
		if(top)
			ans+=cnt[st[top]]+(i-st[top]-1);
		else
			ans+=i-1;
		cnt[i]=top;
		st[++top]=i;
		printf("%lld\n",ans);
//		printf("%d\n",top);
//		for(int j=1; j<=top; ++j)
//			printf("%d ",st[j]);
//		putchar('\n');
	}
	putchar('\n');
	printf("%lld\n",ans+n);
	return 0;
}


