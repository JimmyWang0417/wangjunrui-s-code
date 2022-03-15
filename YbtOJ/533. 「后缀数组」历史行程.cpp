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
const int N=1e5+5,BLOCK=25005;
char str[N];
#define ws nmsl
#define rank Rank
int wa[N],wb[N],ws[N],sa[N],height[N],rank[N];
inline bool cmp(int *r,int a,int b,int l)
{
	return str[a]==str[b]&&str[a+l]==str[b+l];
}
inline void da(int *sa,int n,int m)
{
	int *x=wa,*y=wb;
	int i,j,p;
	for(i=1; i<=m; ++i)
		ws[i]=0;
	for(i=1; i<=n; ++i)
		++ws[x[i]=str[i]-'0'+1];
	for(i=2; i<=m; ++i)
		ws[i]+=ws[i-1];
	for(i=n; i>=1; --i)
		sa[ws[x[i]]--]=i;
	for(j=1,p=1; j<n&&p<=n; j<<=1,m=p)
	{
		for(p=0,i=n-j+1; i<=n; ++i)
			y[++p]=i;
		for(i=1; i<=n; ++i)
			if(sa[i]>j)
				y[++p]=sa[i]-j;
		for(i=1; i<=m; ++i)
			ws[i]=0;
		for(i=1; i<=n; ++i)
			++ws[x[i]];
		for(i=2; i<=m; ++i)
			ws[i]+=ws[i-1];
		for(i=n; i>=1; --i)
			sa[ws[x[y[i]]]--]=y[i];
		for(swap(x,y),i=1,p=0; i<=n; ++i)
			x[sa[i]]=cmp(y,sa[i-1],sa[i],j)?p:++p;
//		for(int i=1; i<=n; ++i)
//			printf("%d ",x[i]);
//		putchar('\n');
	}
	for(i=1; i<=n; ++i)
		rank[sa[i]]=i;
	int k=0;
	for(i=1,j; i<=n; height[rank[i++]]=k)
		for(k?--k:0,j=sa[rank[i]-1]; str[i+k]==str[j+k]; ++k);
}
int n,m;
signed main()
{
	return 0;
}


