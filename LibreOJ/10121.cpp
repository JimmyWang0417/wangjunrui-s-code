#include<cstdio>
#define re register
using namespace std;
inline int read()
{
	char s=getchar();
	bool f=false;
	int x=0;
	while(!(s>='0'&&s<='9'))
	{
		if(s=='-')
			f=true;
		s=getchar();
	}
	while(s>='0'&&s<='9')
	{
		x=(x<<1)+(x<<3)+s-'0';
		s=getchar();
	}
	return f?-x:x;
}
inline int max(int a,int b)
{
	return a>b?a:b;
}
const int N=2e5+5,M=1e6,logN=21;
int head[M<<1+5],a[N],st[N],log[N],maxx[N][logN+3],n,m;
inline int find(int li,int ri)
{
	if(st[li]==li)
		return li;
	if(st[ri]<li)
		return ri+1;
	int mid,l=li,r=ri;
	while(l<=r)
	{
		mid=l+r>>1;
		if(st[mid]<li)
			l=mid+1;
		else
			r=mid-1;
	}
	return l;
}
#define query(l,r)(max(maxx[l][log[r-l+1]],maxx[r-(1<<log[r-l+1])+1][log[r-l+1]]))
int main()
{
	int l,r,mid,ans,temp;
	n=read();
	m=read();
	log[0]=-1;
	for(re int i=1,x; i<=n; i++)
	{
		x=read();
		st[i]=max(st[i-1],head[x+M]+1);
		a[i]=i-st[i]+1;
		log[i]=log[i>>1]+1;
		head[x+M]=i;
	}
	for(re int i=1; i<=n; i++)
		maxx[i][0]=a[i];
	for(re int j=1; j<=logN; j++)
		for(re int i=1; i+(1<<j)-1<=n; i++)
			maxx[i][j]=max(maxx[i][j-1],maxx[i+(1<<j-1)][j-1]);
	while(m--)
	{
		l=read()+1;
		r=read()+1;
		ans=0;
		mid=find(l,r);
		if(mid>l)
			ans=mid-l;
		if(mid<=r)
			ans=max(ans,query(mid,r));
		printf("%d\n",ans);
	}
	return 0;
}
