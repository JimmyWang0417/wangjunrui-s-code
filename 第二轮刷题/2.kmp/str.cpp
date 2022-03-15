#include<cstdio>
#include<cstring>
#define re register
#define solve(x,len) (x<len?x:0)
using namespace std;
template<typename T>
inline void read(T&x)
{
	x=0;
	char s=getchar();
	bool f=false;
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
	if(f)
		x=(~x)+1;
}
const int N=1e6+5;
int T,n,m,head[N],c,a[N],b[N],p[N];
int stra[N],strb[N];
int ans[N];
inline void pre()
{
	p[1]=0;
	for(re int i=2,j=0; i<=m; ++i)
	{
		while(j&&solve(b[i],j+1)!=solve(b[j+1],j+1))
			j=p[j];
		if(solve(b[i],j+1)==solve(b[j+1],j+1))
			++j;
		p[i]=j;
	}
}
inline void kmp()
{
	ans[0]=0;
	for(re int i=0,j=0; i<n; ++i)
	{
		while(j&&solve(a[i+1],j+1)!=solve(b[j+1],j+1))
			j=p[j];
		if(solve(a[i+1],j+1)==solve(b[j+1],j+1))
			++j;
		if(j==m)
		{
			ans[++ans[0]]=i+1-m+1;
			j=p[j];
		}
	}
	printf("%d\n",ans[0]);
	for(re int i=1; i<=ans[0]; ++i)
		printf("%d ",ans[i]);
	printf("\n");
}
int main()
{
	read(T),read(c);
	while(T--)
	{
		read(n),read(m);
		memset(head,0,sizeof(head));
		for(re int i=1; i<=n; ++i)
		{
			read(stra[i]);
			a[i]=i-head[stra[i]];
			head[stra[i]]=i;
		}
		memset(head,0,sizeof(head));
		for(re int i=1; i<=m; ++i)
		{
			read(strb[i]);
			b[i]=i-head[strb[i]];
			head[strb[i]]=i;
		}
//		for(re int i=1; i<=n; i++)
//		printf("%d %d\n",a[i],b[i]);
		pre();
//		for(re int i=1; i<=m; ++i)
//			printf("%d ",p[i]);
//		printf("\n");
		kmp();
	}
}
