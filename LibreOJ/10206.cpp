#include<cstdio>
#include<cmath>
#include<algorithm>
#define re register
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
const int N=(1<<10)+5;
int num[N],f[N],n,m,q[N];
inline void work(int n)
{
	q[m=1]=n;
	int maxx=1;
	int k=sqrt(n),ans=0;
	for(re int i=2; i<=k; i++)
	{
		if(n%i==0)
		{
			q[++m]=i;
			q[++m]=n/i;
		}
	}
	if(k*k==n)
		m--;
	stable_sort(q+1,q+1+m);
	num[1]=1;
	f[1]=1;
	for(re int i=2; i<=m; i++)
	{
		num[i]=1,f[i]=1;
		for(re int j=i-1; j; j--)
			if(q[i]%q[j]==0)
			{
				if(num[i]<num[j]+1)
				{
					num[i]=num[j]+1;
					f[i]=f[j];
				}
				else if(num[i]==num[j]+1)
					f[i]+=f[j];
			}
		if(num[i]>maxx)
			maxx=num[i];
	}
	for(re int i=1; i<=m; i++)
		if(num[i]==maxx)
			ans+=f[i];
	printf("%d %d\n",maxx,ans);
}
int main()
{
	while(scanf("%d",&n)==1)
		work(n);
}

