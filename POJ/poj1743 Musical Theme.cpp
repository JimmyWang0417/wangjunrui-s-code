#include<cstdio>
#include<algorithm>
#define re register
#define ll long long
using namespace std;
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
const int N=20000+5;
int wa[N],wb[N],ws[N];
int r[N],Rank[N],sa[N],height[N];
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
	for(re int i=n-1; i>=0; --i)
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
			++ws[x[y[i]]];
		for(i=1; i<m; ++i)
			ws[i]+=ws[i-1];
		for(i=n-1; i>=0; --i)
			sa[--ws[x[y[i]]]]=y[i];
		for(swap(x,y),x[sa[0]]=0,p=1,i=1; i<n; ++i)
			x[sa[i]]=cmp(y,sa[i-1],sa[i],j)?p-1:p++;
	}
}
#define rank Rank
inline void calheight(int *r,int *sa,int n)
{
	for(re int i=1; i<=n; ++i)
		rank[sa[i]]=i;
	for(re int i=0,j,k=0; i<n; height[rank[i++]]=k)
		for(k?--k:0,j=sa[rank[i]-1]; r[i+k]==r[j+k]; ++k);
}
inline bool check(int *sa,int n,int k)
{
	int maxx=sa[1],minn=sa[1];
	for(re int i=2; i<=n; ++i)
	{
		if(height[i]<k)
			maxx=minn=sa[i];
		else
		{
			maxx=max(maxx,sa[i]);
			minn=min(minn,sa[i]);
			if(maxx-minn>k)
				return true;
		}
	}
	return false;
}
int n;
int main()
{
	while(read(n),n)
	{
		--n;
		int now,pre;
		read(pre);
		for(re int i=0; i<n; ++i)
		{
			read(now);
			r[i]=now-pre+100;
			pre=now;
		}
		r[n]=0;
		da(r,sa,n+1,200);
		calheight(r,sa,n);
		int left=1,right=(n>>1);
		while(left<=right)
		{
			int mid=(left+right)>>1;
			if(check(sa,n,mid))
				left=mid+1;
			else
				right=mid-1;
		}
		printf("%d\n",left>=5?left:0);
	}
}
