#include<cstdio>
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
struct Matrix
{
	int n,m;
	long long g[3][3];
} c,res,a,f;
const int mod=1000000007;
inline Matrix operator * (const Matrix&a,const Matrix&b)
{
	c.n=a.n;
	c.m=b.m;
	for(re int i=1; i<=c.n; i++)
		for(re int j=1; j<=c.m; j++)
			c.g[i][j]=0;
	for(re int i=1; i<=c.n; i++)
		for(re int j=1; j<=c.m; j++)
			for(re int k=1; k<=a.m; k++)
				c.g[i][j]=(c.g[i][j]+a.g[i][k]*b.g[k][j])%mod;
	return c;
}
inline Matrix operator ^ (Matrix a,long long b)
{
	res.n=res.m=2;
	for(re int i=1; i<=res.n; i++)
		for(re int j=1; j<=res.m; j++)
			res.g[i][j]=(i==j);
	while(b)
	{
		if(b&1)
			res=res*a;
		a=a*a;
		b>>=1;
	}
	return res;
}
inline void print(Matrix a)
{
	for(re int i=1; i<=a.n; i++)
	{
		for(re int j=1; j<=a.m; j++)
			printf("%d ",a.g[i][j]);
		putchar('\n');
	}
}
long long n;
int main()
{
	read(n);
	if(n<1)
	{
		printf("0\n");
		return 0;
	}
	if(n<3)
	{
		printf("1\n");
		return 0;
	}
	a.n=a.m=f.m=2;
	f.n=a.g[1][1]=a.g[2][1]=a.g[1][2]=f.g[1][1]=f.g[1][2]=1ll;
	printf("%d\n",(f*(a^(n-2))).g[1][1]);
	return 0;
}

