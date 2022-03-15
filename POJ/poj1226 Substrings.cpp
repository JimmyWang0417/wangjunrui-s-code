#include<set>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define re register
#define ll long long
using namespace std;
const int N=100*100*5;
int wa[N],wb[N],wv[N],ws[N];
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
		for(i=0; i<n; ++i)
			wv[i]=x[y[i]];
		for(i=0; i<m; ++i)
			ws[i]=0;
		for(i=0; i<n; ++i)
			++ws[wv[i]];
		for(i=1; i<m; ++i)
			ws[i]+=ws[i-1];
		for(i=n-1; i>=0; --i)
			sa[--ws[wv[i]]]=y[i];
		for(swap(x,y),p=1,x[sa[0]]=0,i=1; i<n; ++i)
			x[sa[i]]=cmp(y,sa[i-1],sa[i],j)?p-1:p++;
	}
}
int Rank[N],height[N];
inline void calheight(int *r,int *sa,int n)
{
	re int i,j,k=0;
	for(re int i=1; i<=n; ++i)
		Rank[sa[i]]=i;
	for(i=0; i<n; height[Rank[i++]]=k)
		for(k?--k:0,j=sa[Rank[i]-1]; r[i+k]==r[j+k]; ++k);
	return;
}
int r[N],sa[N],len,n,t,index[N];
char str[100+5];
inline bool check(int x)
{
	set<int>se;
	for(re int i=1; i<len; ++i)
		if(height[i]>=x)
		{
			se.insert(index[sa[i]]);
			se.insert(index[sa[i-1]]);
		}
		else
		{
			if(se.size()==n)
				return true;
			se.clear();
		}
	if(se.size()==n)
		return true;
	return false;
}
inline void solve()
{
	if(n==1)
	{
		printf("%d\n",strlen(str));
		return;
	}
	int l=1,r=100,mid,ans=0;
	while(l<=r)
	{
		mid=l+r>>1;
		if(check(mid))
		{
			ans=mid;
			l=mid+1;
		}
		else
			r=mid-1;
	}
	printf("%d\n",ans);
}
int main()
{
	scanf("%d",&t);
	while(t--)
	{
		scanf("%d",&n);
		len=0;
		for(re int i=1,val=0; i<=n; ++i)
		{
			scanf("%s",str);
			int length=strlen(str);
			for(re int j=0; j<length; ++j)
			{
				index[len]=i;
				r[len++]=(str[j]-'A'+2*n+1);
			}
			index[len]=i;
			r[len++]=val++;
			for(re int j=length-1; j>=0; --j)
			{
				index[len]=i;
				r[len++]=(str[j]-'A'+2*n+1);
			}
			index[len]=i;
			r[len++]=val++;
		}
		da(r,sa,len,300);
		calheight(r,sa,len-1);
		solve();
	}
	return 0;
}
