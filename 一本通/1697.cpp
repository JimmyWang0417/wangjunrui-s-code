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
const int LEN=100000,mod=1000000007;
int t,p[LEN],f[LEN],n,m;
char a[LEN],b[LEN];
inline void pre()
{
	p[1]=0;
	for(re int i=1,j=0; i<m; i++)
	{
		while(j&&b[i+1]!=b[j+1])
			j=p[j];
		if(b[i+1]==b[j+1])
			j++;
		p[i+1]=j;
	}
}
inline int sum()
{
	f[0]=1;
	for(re int i=0,j=0; i<n; i++)
	{
		f[i+1]=f[i];
		while(j&&a[i+1]!=b[j+1])
			j=p[j];
		if(a[i+1]==b[j+1])
			j++;
		if(j==m)
		{
			f[i+1]=(f[i+1]+f[i-m+1])%mod;
			j=p[j];
		}
	}
	return f[n];
}
int main()
{
	read(t);
	while(t--)
	{
		scanf("%s%s",a+1,b+1);
		n=strlen(a+1);
		m=strlen(b+1);
		pre();
		printf("%d\n",sum());
	}
	return 0;
}
