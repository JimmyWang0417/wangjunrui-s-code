#include<cstdio>
#include<cmath>
#include<algorithm>
#include<bitset>
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
	return;
}
#define re register
#define ll long long
int a[110],T,n,sum,ans;
bool f[25010];
int main()
{
	read(T);
	while(T--)
	{
		read(n);
		ans=sum=0;
		for(re int i=1; i<=n; i++)
		{
			read(a[i]);
			sum+=a[i];
		}
		f[0]=true;
		sort(a+1,a+1+n);
		for(re int i=1; i<=n; i++)
		{
			if(f[a[i]])
			{
				++ans;
				continue;
			}
			for(re int j=a[i]; j<=a[n]; j++)
				f[j]=f[j]|f[j-a[i]];
		}
		/*for(re int i=1; i<=sum; i++)
			printf("%d ",(int)f[i]);*/
		printf("%d\n",n-ans);
		fill(f+1,f+1+a[n],0);
	}
}
