#include<cstdio>
#include<set>
#include<algorithm>
#define re register
using namespace std;
const int N=100105;
int wa[N],wb[N],ws[N],sa[N],height[N],Rank[N],r[N],kase;
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
#define rank Rank
inline void calheight(int *r,int *sa,int n)
{
	re int i,j,h=0;
	for(i=1; i<=n; ++i)
		rank[sa[i]]=i;
	for(i=0; i<n; height[rank[i++]]=h)
		for(h?--h:0,j=sa[rank[i]-1]; r[i+h]==r[j+h]; h++);
}
#undef rank
int len,nn,n,index[N];
int ans[N],ss,yes[N],ii;
inline bool check(int mid)
{
	re int i,j,k,t,s,flag=0;
	for(i=2; i<=len; i=j+1)
	{
		for(; height[i]<mid && i<=len; i++);
		for(j=i; height[j]>=mid; j++);
		if(j-i+1<nn) continue;
		ii++;
		s=0;
		for(k=i-1; k<j; k++)
			if((t=index[sa[k]])!=0)
				if(yes[t]!=ii) yes[t]=ii,s++;
		if(s>=nn) if(flag) ans[++ss]=sa[i-1];
			else ans[ss=1]=sa[i-1],flag=1;
	}
	return flag;
}
char str[1005];
int main()
{
	while(scanf("%d",&n)!=EOF&&n)
	{
		len=0;
		scanf("%d",&n);
		nn=n/2+1;
		for(re int i=1; i<=n; ++i)
		{
			scanf("%s",str);
			for(re int j=0; str[j]; ++j)
			{
				index[len]=i;
				r[len++]=str[j]+100;
			}
			index[len]=0;
			r[len++]=i;
		}
		--len;
		r[len]=0;
//	printf("%d\n",len);
//	for(re int i=0; i<=len; ++i)
//		printf("%d ",r[i]);
		da(r,sa,len+1,227);
		calheight(r,sa,len);
//	for(re int i=0; i<=len; ++i)
//		printf("%d ",height[i]);
		height[len+1]=-1;
		int left=1,right=1000;
		while(left<=right)
		{
			int mid=left+right>>1;
			if(check(mid))
				left=mid+1;
			else
				right=mid-1;
		}
		if(kase++)
			putchar('\n');
		if(right==0) printf("?\n");
		else for(re int i=1,k; i<=ss; i++)
			{
				k=ans[i];
				for(re int j=0; j<right; j++) putchar(r[k+j]-100);
				putchar('\n');
			}
//	printf("%d\n",right);
	}
}
