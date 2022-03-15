#include<cstdio>
#include<cstring>
#define re register
using namespace std;
const int base=10000,N=1e4+5;
int a[N],b[N],c[N],f[N],s0=0,T;
char s[N];
inline void mark(int a[])
{
	while((a[a[0]]==0)&&a[0]>0)
		a[0]--;
}
inline void init(int a[])
{
	scanf("%s",s);
	int len=strlen(s);
	for(re int i=0,j; i<len; i++)
	{
		j=(len-i+3)/4;
		a[j]=(a[j]<<1)+(a[j]<<3)+s[i]-'0';
	}
	a[0]=(len+3)/4;
}
inline void print(int a[])
{
	printf("%d",a[a[0]]);
	for(re int i=a[0]-1; i>0; i--)
	for(re int j=base/10;j>0;j/=10)
		printf("%d",a[i]/j%10);
	putchar('\n');
}
inline int compare(int a[],int b[])
{
	if(a[0]>b[0])
		return 1;
	if(a[0]<b[0])
		return -1;
	for(re int i=a[0]; i>=1; i--)
		if(a[i]>b[i])
			return 1;
		else if(a[i]<b[i])
			return -1;
	return 0;
}
inline void div(int a[],int k)
{
	int i,t=0;
	for(re int i=a[0]; i>=1; i--)
	{
		t=t*base+a[i];
		a[i]=t/k;
		t%=k;
	}
	mark(a);
}
inline void minus(int a[],int b[])
{
	for(re int i=1; i<=a[0]; i++)
	{
		a[i]-=b[i];
		if(a[i]<0)
		{
			a[i+1]--;
			a[i]+=base;
		}
	}
	mark(a);
}
inline void gcd(int a[],int b[],int t)
{
	bool ta=false,tb=false;
	if(compare(a,b)==0)
	{
		T=t;
		return;
	}
	if(compare(a,b)<0)
	{
		gcd(b,a,t);
		return;
	}
	if(a[1]%2==0)
	{
		div(a,2);
		ta=true;
	}
	if(b[1]%2==0)
	{
		div(b,2);
		tb=true;
	}
	if(ta&&tb)
		gcd(a,b,t+1);
	else if((!ta)&&(!tb))
	{
		minus(a,b);
		gcd(a,b,t);
	}
	else
		gcd(a,b,t);
}
inline void mulhigh(int a[],int b[])
{
	memset(c,0,sizeof(c));
	for(re int i=1; i<=a[0]; i++)
		for(re int j=1; j<=b[0]; j++)
		{
			c[i+j-1]+=a[i]*b[j];
			c[i+j]+=c[i+j-1]/base;
			c[i+j-1]%=base;
		}
	c[0]=a[0]+b[0];
	mark(c);
	for(re int i=0; i<=c[0]; i++)
		a[i]=c[i];
}
inline void mullow(int a[],int k)
{
	for(re int i=1; i<=a[0]; i++)
		a[i]*=k;
	for(re int i=1; i<=a[0]; i++)
	{
		a[i+1]+=a[i]/base;
		a[i]%=base;
	}
	while(a[a[0]+1])
	{
		a[0]++;
		a[a[0]+1]=a[a[0]]/base;
		a[a[0]]%=base;
	}
}
int main()
{
	init(a);
	init(b);
	gcd(a,b,0);
	if(T==0)
		print(a);
	else
	{
		f[0]=f[1]=1;
		for(re int i=1; i<=T; i++)
			mullow(f,2);
		mulhigh(f,a);
		print(f);
	}
	return 0;
}
