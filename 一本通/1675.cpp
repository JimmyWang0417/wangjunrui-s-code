#include<cstdio>
#include<cstring>
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
const int N=3010,INF=0x3f3f3f3f;
int n,d[N],f[N],sum[N];
int main()
{
	read(n);
	for(re int i=1,x; i<=n; i++)
	{
		read(x);
		sum[i]=sum[i-1]+x;
	}
	memset(d,INF,sizeof(d));
	d[0]=0;
	for(re int i=1; i<=n; i++)
		for(re int j=i-1; j>=0; j--)
			if(sum[i]-sum[j]>=d[j])
			{
				d[i]=sum[i]-sum[j];
				f[i]=f[j]+i-j-1;
				break;
			}
	printf("%d\n",f[n]);
	return 0;
}

