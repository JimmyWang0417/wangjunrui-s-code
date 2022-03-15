#include<set>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define re register
using namespace std;
const int N=1e6+10;
int wa[N],wb[N],ws[N],sa[N];
inline bool cmp(int *r,int a,int b,int l)
{
	return r[a]==r[b]&&r[a+l]==r[b+l];
}
inline void da(int *r,int *sa,int n,int m)
{
	re int i,j,p;
	int *x=wa,*y=wb;
	for(i=0; i<m; ++i)
		ws[i]=0;
	for(i=0; i<n; ++i)
		++ws[x[i]=r[i]];
	for(i=1; i<m; ++i)
		ws[i]+=ws[i-1];
	for(i=n-1; i>=0; --i)
		sa[--ws[x[i]]]=i;
	for(p=1,j=1; p<n; j<<=1,m=p)
	{
		for(p=0,i=n-j; i<n; ++i)
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
		for(swap(x,y),i=1,p=1,x[sa[0]]=0; i<n; ++i)
			x[sa[i]]=cmp(y,sa[i-1],sa[i],j)?p-1:p++;
	}
}
int Rank[N],index[N],height[N];
#define rank Rank
inline void calheight(int *r,int *sa,int n)
{
	re int i,j,h=0;
	for(i=1; i<=n; ++i)
		rank[sa[i]]=i;
	for(i=0; i<n; height[rank[i++]]=h)
		for(h?--h:0,j=sa[rank[i]-1]; r[i+h]==r[j+h]; ++h);
}
#undef rank
int n,len,r[N];
char str[N];
int main()
{
	scanf("%s",str);
	int n=strlen(str);
	for(re int i=0; str[i]; ++i)
		r[len++]=str[i];
	r[len++]=1;
	scanf("%s",str);
	for(re int i=0; str[i]; ++i)
		r[len++]=str[i];
	r[len]=0;
//	for(re int i=0;i<=len;++i)
//	printf("%c",r[i]);
	da(r,sa,len+1,200);
	int ans=0;
	calheight(r,sa,len);
	for(re int i=2; i<=len; ++i)
		if(height[i]>ans)
			if(n<sa[i-1]&&n>sa[i]||n>sa[i-1]&&n<sa[i])
				ans=height[i];
	printf("%d\n",ans);
}
