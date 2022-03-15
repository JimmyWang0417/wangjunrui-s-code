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
const int N=1.5e4+5;
char str[N];
int p[N];
int k;
ll ans;
inline void solve(char *a)
{
	p[1]=0;
	int n=strlen(a+1);
//	printf("%s\n",s+1);
	for(re int i=1,j=0; i<n; ++i)
	{
		while(j&&a[j+1]!=a[i+1])
			j=p[j];
		if(a[j+1]==a[i+1])
			++j;
		p[i+1]=j;
	}
//	for(re int i=1; i<=n; ++i)
//		printf("%d ",p[i]);
//	putchar('\n');
	for(re int i=1,j=0; i<n; ++i)
	{
		while(j&&a[j+1]!=a[i+1])
			j=p[j];
		if(a[j+1]==a[i+1])
			++j;
		while((j<<1)>=(i+1))
			j=p[j];
		if(j>=k)
			++ans;
	}
}
signed main()
{
	scanf("%s",str+1);
	read(k);
	int len=strlen(str+1)-(k<<1);
	for(re int i=0; i<len; ++i)
		solve(str+i);
	printf("%lld\n",ans);
	return 0;
}


