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
const int N=1e5+5;
#define ws wdnmd
int wa[N],wb[N],ws[N],sa[N],rk[N],height[N];
inline bool cmp(int *r,int a,int b,int l)
{
	return r[a]==r[b]&&r[a+l]==r[b+l];
}
inline void da(char *str,int n,int m)
{
	int *x=wa,*y=wb;

	fill(ws+1,ws+1+m,0);
	for(int i=1; i<=n; ++i)
		++ws[x[i]=str[i]-'a'+1];
	for(int i=2; i<=m; ++i)
		ws[i]+=ws[i-1];
	for(int i=n; i>=1; --i)
		sa[ws[x[i]]--]=i;

	for(int p,j=1; j<n&&p<=n; j<<=1,m=p)
	{
		p=0;
		for(int i=n-j+1; i<=n; ++i)
			y[++p]=i;
		for(int i=1; i<=n; ++i)
			if(sa[i]>j)
				y[++p]=sa[i]-j;

		fill(ws+1,ws+1+m,0);
		for(int i=1; i<=n; ++i)
			++ws[x[i]];
		for(int i=2; i<=m; ++i)
			ws[i]+=ws[i-1];
		for(int i=n; i>=1; --i)
			sa[ws[x[y[i]]]--]=y[i];

		swap(x,y);
		p=0;
		for(int i=1; i<=n; ++i)
			x[sa[i]]=cmp(y,sa[i],sa[i-1],j)?p:++p;
	}
	for(int i=1; i<=n; ++i)
		rk[sa[i]]=i;
	for(int i=1,j=0; i<=n; ++i)
	{
		if(j)
			--j;
		while(str[i+j]==str[sa[rk[i]-1]+j])
			++j;
		height[i]=j;
	}
}
char str[N];
signed main()
{
	scanf("%s",str+1);
	int n=(int)strlen(str+1);
	da(str,n,26);
	for(int i=1; i<=n; ++i)
		printf("%d ",sa[i]);
	putchar('\n');
	for(int i=2; i<=n; ++i)
		printf("%d ",height[sa[i]]);
	putchar('\n');
	return 0;
}


