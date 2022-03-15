#include<cstdio>
#include<algorithm>
#define re register
#define ll long long
using namespace std;
const int N=1e5+6;
int wa[N],wb[N],ws[N];
inline bool cmp(int *r,int a,int b,int l)
{
	return r[a]==r[b]&&r[a+l]==r[b+l];
}
inline void da(int *r,int *sa,int n,int m)
{
	int *x=wa,*y=wb;
	re int i,j,p;
	for(i=0; i<m; ++i)
		ws[i]=0;
	for(i=0; i<n; ++i)
		++ws[x[i]=r[i]];
	for(i=1; i<m; ++i)
		ws[i]+=ws[i-1];
	for(i=n-1; i>=0; --i)
		sa[--ws[x[i]]]=i;
	for(j=1,p=1; p<n; j<<=1,m=p)
	{
		for(i=n-j,p=0; i<n; ++i)
			y[p++]=i;
		for(i=0; i<n; ++i)
			if(sa[i]>=j)
				y[p++]=sa[i]-j;
		for(i=0; i<m; ++i)
			ws[i]=0;
		for(i=0; i<n; ++i)
			++ws[x[i]];
		for(i=1; i<m; ++i)
			ws[i]+=ws[i-1];
		for(i=n-1; i>=0; --i)
			sa[--ws[x[y[i]]]]=y[i];
		for(i=1,p=1,swap(x,y),x[sa[0]]=0; i<n; ++i)
			x[sa[i]]=cmp(y,sa[i-1],sa[i],j)?p-1:p++;
	}
}
int sa[N],Rank[N],r[N],height[N];
inline void calheight(int *r,int *sa,int n)
{
	re int i,j,h=0;
	for(i=1; i<=n; ++i)
		Rank[sa[i]]=i;
	for(i=0; i<n; height[Rank[i++]]=h)
		for(h?--h:0,j=sa[Rank[i]-1]; r[i+h]==r[j+h]; ++h);

}
char str[N];
int n;
int main()
{
	scanf("%d%s",&n,str);
	ll ans=1ll*n*(n+1)/2;
	for(re int i=0; i<n; ++i)
		r[i]=str[i];
	r[n]=0;
//	printf("%lld\n",ans);
	da(r,sa,n+1,128);
	calheight(r,sa,n);
	for(re int i=1; i<=n; ++i)
		ans-=height[i];
	printf("%lld\n",ans);
	return 0;
}
