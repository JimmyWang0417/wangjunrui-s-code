#include <set>
#include <map>
#include <cmath>
#include <queue>
#include <vector>
#include <cstdio>
#include <bitset>
#include <cstring>
#include <iostream>
#include <algorithm>
#define lowbit(x) (x&(-x))
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
inline void clear(T*a,int l,int r,T val)
{
	memset(&a[l],val,sizeof(T)*(r-l+1));
}
using std::swap;
const int N=2e5+5;
int wa[N],wb[N],ws[N];
inline bool cmp(int *r,int a,int b,int len)
{
	return r[a]==r[b]&&r[a+len]==r[b+len];
}
inline void da(int *r,int *sa,int n,int m)
{
	int p,*x=wa,*y=wb;
	for(re int i=0; i<m; ++i)
		ws[i]=0;
	for(re int i=0; i<n; ++i)
		++ws[x[i]=r[i]];
	for(re int i=1; i<m; ++i)
		ws[i]+=ws[i-1];
	for(re int i=n-1; i>=0; --i)
		sa[--ws[x[i]]]=i;
	for(re int j=1; j<=n; j<<=1)
	{
		p=0;
		for(re int i=n-j; i<n; ++i)
			y[p++]=i;
		for(re int i=0; i<n; ++i)
			if(sa[i]>=j)
				y[p++]=sa[i]-j;
		for(re int i=0; i<m; ++i)
			ws[i]=0;
		for(re int i=0; i<n; ++i)
			++ws[x[y[i]]];
		for(re int i=1; i<m; ++i)
			ws[i]+=ws[i-1];
		for(re int i=n-1; i>=0; --i)
			sa[--ws[x[y[i]]]]=y[i];
		swap(x,y),m=1,x[sa[0]]=0;
		for(re int i=1; i<n; ++i)
			x[sa[i]]=cmp(y,sa[i-1],sa[i],j)?m-1:m++;
		if(m>=n)
			break;
	}
}
int sa[N],r[N];
char str[N];
signed main()
{
	scanf("%s",str);
	int len=(int)strlen(str);
	for(re int i=0; i<len; ++i)
		r[i]=r[i+len]=str[i];
	da(r,sa,len*2,'z'+1);
	for(re int i=0; i<len*2; ++i)
		if(sa[i]<len)
			putchar(r[sa[i]+len-1]);
	putchar('\n');
	return 0;
}


