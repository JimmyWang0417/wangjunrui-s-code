#include<cstdio>
#include<algorithm>
#include<cstring>
#define re register
using namespace std;
const int N=1e6+5,M=130;
int wa[N],wb[N],wv[N],ws[N],sa[N];
inline bool cmp(int *r,int a,int b,int l)
{
	return r[a]==r[b]&&r[a+l]==r[b+l];
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
char str[N];
int r[N];
int main()
{
	scanf("%s",str);
	int length=strlen(str);
	for(re int i=0; i<length; ++i)
		r[i]=str[i];
	da(r,sa,length,M);
	for(re int i=0; i<length; ++i)
		printf("%d ",sa[i]+1);
	printf("\n");
	return 0;
}
